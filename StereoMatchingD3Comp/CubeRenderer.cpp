#include "pch.h"
#include "Config.h"
#include "CubeRenderer.h"
#include "DDSTextureLoader.h"
#include "ShadersLoader.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel;
using namespace Windows::UI::Core;

#define GPU true

ConstantParameters * ConstantParametersBuffer = new ConstantParameters(12, 0.0001f, 0.11f, 9, 0.1f, 0.0275f, 0.0078f);

CubeRenderer::CubeRenderer() :
	m_indexCount(0),
	m_loadingComplete(false),
	m_sameImage(true)
{
}

void CubeRenderer::CreateDeviceResources()
{
	Direct3DBase::CreateDeviceResources();

	TextureCache * textureCache = TextureCache::Instance(Size(384, 288), m_d3dDevice.Get());
	m_costVolumeRenderer = new CostVolumeRenderer(m_d3dDevice.Get(), Size(384, 288));
	m_meanImagesRenderer = new MeanImagesRenderer(m_d3dDevice.Get(), Size(384, 288));

	auto initTexturesCache = TexturesBuffer->InitializeAsync().then([this] () 
	{
		//	auto initCVRenderer = m_costVolumeRenderer->Initialize().then([this] () 
		//	{
		//		auto initMIRenderer = m_meanImagesRenderer->Initialize().then([this] () 
		//		{
		auto loadVSTask = DX::ReadDataAsync("SimpleVertexShader.cso");
		auto loadPSTask = DX::ReadDataAsync("ToScreenPixelShader.cso");
		auto loadTX1Task = DX::ReadDataAsync("Media\\textures\\left.dds");
		auto loadTX2Task = DX::ReadDataAsync("Media\\textures\\right.dds");
		auto createPSTask_Mean_H = ShadersLoader::LoadPS("Mean_PixelShaderH.cso", m_d3dDevice.Get(), &m_pixelShader_Mean_H);
		auto createPSTask_Mean_W = ShadersLoader::LoadPS("Mean_PixelShaderW.cso", m_d3dDevice.Get(), &m_pixelShader_Mean_W);

		auto createVSTask = loadVSTask.then([this](Platform::Array<byte>^ fileData) {

			DX::ThrowIfFailed(
				m_d3dDevice->CreateVertexShader(
				fileData->Data,
				fileData->Length,
				nullptr,
				&m_vertexShader
				)
				);

			const D3D11_INPUT_ELEMENT_DESC vertexDesc[] = 
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
				{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
			};

			DX::ThrowIfFailed(
				m_d3dDevice->CreateInputLayout(
				vertexDesc,
				ARRAYSIZE(vertexDesc),
				fileData->Data,
				fileData->Length,
				&m_inputLayout
				)
				);
		});

		auto createPSTask = loadPSTask.then([this](Platform::Array<byte>^ fileData) {

			DX::ThrowIfFailed(
				m_d3dDevice->CreatePixelShader(
				fileData->Data,
				fileData->Length,
				nullptr,
				&m_pixelShader
				)
				);

			CD3D11_BUFFER_DESC constantParametersBufferDesc(sizeof(ConstantParameters), D3D11_BIND_CONSTANT_BUFFER);
			DX::ThrowIfFailed(
				m_d3dDevice->CreateBuffer(
				&constantParametersBufferDesc,
				nullptr,
				&m_constantParameterBuffer
				)
				);
		});

		auto createTX1Task = loadTX1Task.then([this](Platform::Array<byte>^ fileData) {

			ComPtr<ID3D11Resource> texture;
			ComPtr<ID3D11ShaderResourceView> textureView = nullptr;

			DX::ThrowIfFailed(
				CreateDDSTextureFromMemory(
				m_d3dDevice.Get(), 
				fileData->Data,
				fileData->Length,
				&texture, 
				&textureView)
				);

			DX::ThrowIfFailed(
				texture.As(&m_texture1)
				);

			DX::ThrowIfFailed(
				textureView.As(&m_texture1View)
				);
		});

		auto createTX2Task = loadTX2Task.then([this](Platform::Array<byte>^ fileData) {

			ComPtr<ID3D11Resource> texture;
			ComPtr<ID3D11ShaderResourceView> textureView = nullptr;

			DX::ThrowIfFailed(
				CreateDDSTextureFromMemory(
				m_d3dDevice.Get(), 
				fileData->Data,
				fileData->Length,
				&texture, 
				&textureView)
				);

			DX::ThrowIfFailed(
				texture.As(&m_texture2)
				);

			DX::ThrowIfFailed(
				textureView.As(&m_texture2View)
				);
		});

		auto setInputImages = (createTX1Task && createTX2Task).then([this] () {

			ConstantParametersBuffer->dx = 1.0f / m_renderTargetSize.Width;
			ConstantParametersBuffer->dy = 1.0f / m_renderTargetSize.Height;

			m_costVolumeRenderer->SetStereoTexture(m_texture1View.Get(), m_texture2View.Get());
			m_meanImagesRenderer->SetStereoTexture(m_texture1View.Get(), m_texture2View.Get());

			// create the sampler
			D3D11_SAMPLER_DESC samplerDesc;
			samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
			samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
			samplerDesc.MipLODBias = 0;
			samplerDesc.MaxAnisotropy = 0;
			samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
			samplerDesc.BorderColor[0] = 0;
			samplerDesc.BorderColor[1] = 0;
			samplerDesc.BorderColor[2] = 0;
			samplerDesc.BorderColor[3] = 0;
			samplerDesc.MinLOD = 0;
			samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

			DX::ThrowIfFailed(
				m_d3dDevice->CreateSamplerState(
				&samplerDesc,
				&m_sampler
				)
				);
		});

		auto createScene = (createVSTask && createPSTask && createPSTask_Mean_H && createPSTask_Mean_W && setInputImages).then([this] () {

			VertexPositionTexel surfaceVertices[] =
			{
				{ XMFLOAT3(-1.0,  1.0, 0.5f), XMFLOAT2(0.0f, 0.0f) },
				{ XMFLOAT3( 1.0,  1.0, 0.5f), XMFLOAT2(1.0f, 0.0f) },
				{ XMFLOAT3( 1.0, -1.0, 0.5f), XMFLOAT2(1.0f, 1.0f) },
				{ XMFLOAT3(-1.0, -1.0, 0.5f), XMFLOAT2(0.0f, 1.0f) },
			};

			D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
			vertexBufferData.pSysMem = surfaceVertices;
			vertexBufferData.SysMemPitch = 0;
			vertexBufferData.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(surfaceVertices), D3D11_BIND_VERTEX_BUFFER);
			DX::ThrowIfFailed(
				m_d3dDevice->CreateBuffer(
				&vertexBufferDesc,
				&vertexBufferData,
				&m_vertexBuffer
				)
				);

			unsigned short surfaceIndices[] = 
			{
				0, 1, 2,
				0, 2, 3
			};

			m_indexCount = ARRAYSIZE(surfaceIndices);

			D3D11_SUBRESOURCE_DATA indexBufferData = {0};
			indexBufferData.pSysMem = surfaceIndices;
			indexBufferData.SysMemPitch = 0;
			indexBufferData.SysMemSlicePitch = 0;
			CD3D11_BUFFER_DESC indexBufferDesc(sizeof(surfaceIndices), D3D11_BIND_INDEX_BUFFER);
			DX::ThrowIfFailed(
				m_d3dDevice->CreateBuffer(
				&indexBufferDesc,
				&indexBufferData,
				&m_indexBuffer
				)
				);
		});

		auto createGPUBuffer = createScene.then([this] ()
		{
			D3D11_TEXTURE2D_DESC desc;
			ZeroMemory(&desc, sizeof(desc));
			m_texture1->GetDesc(&desc);
			desc.MipLevels = 1;
			desc.ArraySize = 1;
			desc.SampleDesc.Count = 1;
			desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
			desc.Usage = D3D11_USAGE_DEFAULT;
			desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
			desc.CPUAccessFlags = 0;
			desc.MiscFlags = 0;

			DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&desc, nullptr, &m_GPU1_Texture_H));
			DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&desc, nullptr, &m_GPU2_Texture_H));
			DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&desc, nullptr, &m_GPU1_Texture_W));
			DX::ThrowIfFailed(m_d3dDevice->CreateTexture2D(&desc, nullptr, &m_GPU2_Texture_W));

			D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
			renderTargetViewDesc.Format = desc.Format;
			renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			renderTargetViewDesc.Texture2D.MipSlice = 0;

			DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(m_GPU1_Texture_H.Get(), &renderTargetViewDesc, m_GPU1_Texture_H_target.GetAddressOf()));	
			DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(m_GPU2_Texture_H.Get(), &renderTargetViewDesc, m_GPU2_Texture_H_target.GetAddressOf()));	
			DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(m_GPU1_Texture_W.Get(), &renderTargetViewDesc, m_GPU1_Texture_W_target.GetAddressOf()));	
			DX::ThrowIfFailed(m_d3dDevice->CreateRenderTargetView(m_GPU2_Texture_W.Get(), &renderTargetViewDesc, m_GPU2_Texture_W_target.GetAddressOf()));	

			D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
			shaderResourceViewDesc.Format = desc.Format;
			shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
			shaderResourceViewDesc.Texture2D.MipLevels = 1;

			DX::ThrowIfFailed(m_d3dDevice->CreateShaderResourceView(m_GPU1_Texture_H.Get(), &shaderResourceViewDesc, m_GPU1_Texture_H_shaderView.GetAddressOf()));
			DX::ThrowIfFailed(m_d3dDevice->CreateShaderResourceView(m_GPU2_Texture_H.Get(), &shaderResourceViewDesc, m_GPU2_Texture_H_shaderView.GetAddressOf()));
			DX::ThrowIfFailed(m_d3dDevice->CreateShaderResourceView(m_GPU1_Texture_W.Get(), &shaderResourceViewDesc, m_GPU1_Texture_W_shaderView.GetAddressOf()));
			DX::ThrowIfFailed(m_d3dDevice->CreateShaderResourceView(m_GPU2_Texture_W.Get(), &shaderResourceViewDesc, m_GPU2_Texture_W_shaderView.GetAddressOf()));
		});

		auto createCPUBuffer = createGPUBuffer.then([this] ()
		{
			// Create CPU textures
		});

		(createCPUBuffer).then([this] () {

			m_loadingComplete = true;
			m_sameImage = false;

		});

		//		});
		//	});
	});
}

void CubeRenderer::CreateWindowSizeDependentResources()
{
	Direct3DBase::CreateWindowSizeDependentResources();

	float aspectRatio = m_windowBounds.Width / m_windowBounds.Height;
	float fovAngleY = 70.0f * XM_PI / 180.0f;
	if (aspectRatio < 1.0f)
	{
		fovAngleY /= aspectRatio;
	}
}

void CubeRenderer::Update(float timeTotal, float timeDelta)
{
}

void CubeRenderer::Render()
{

	// Only draw the cube once it is loaded (loading is asynchronous).
	if (!m_loadingComplete)
		return;

	// Input images for stereo matching
	ID3D11ShaderResourceView * inputImages[] = 
	{
		m_texture1View.Get(),
		m_texture2View.Get(),
	};

	// Update constant parameters
	m_d3dContext->UpdateSubresource(m_constantParameterBuffer.Get(), 0, NULL, ConstantParametersBuffer, 0, 0);
	m_d3dContext->PSSetConstantBuffers(0, 1, m_constantParameterBuffer.GetAddressOf());

	// Render blur

	if (GPU)
	{
		ID3D11ShaderResourceView * images[] = 
		{
			m_GPU1_Texture_W_shaderView.Get(),
			m_GPU2_Texture_W_shaderView.Get()
		};
		this->GPUBlur();
		this->Render(images);
	}
	else
	{
		this->CPUBlur();
		this->Render();
	}

	// Render mean textures for input images (eq. no. 1)
	const Texture * meanInputImages[ARRAYSIZE(inputImages)];
	m_meanImagesRenderer->RenderSimple(m_d3dContext.Get(), 
		inputImages, 
		(const Texture*(*)[]) &meanInputImages, 
		ARRAYSIZE(inputImages));
	ID3D11ShaderResourceView * meanInputImages_resourceViews[ARRAYSIZE(meanInputImages)];
	for (int i = 0; i < ARRAYSIZE(meanInputImages); ++i)
		meanInputImages_resourceViews[i] = meanInputImages[i]->ResourceView;

	// Render variance images (eq. no. 5)
	const Texture * varianceInputImages[ARRAYSIZE(inputImages) * 2];
	m_meanImagesRenderer->RenderVariance(m_d3dContext.Get(), 
		inputImages, 
		meanInputImages_resourceViews, 
		(const Texture*(*)[]) &varianceInputImages, 
		ARRAYSIZE(inputImages));
	ID3D11ShaderResourceView * varianceInputImages_resourceViews[ARRAYSIZE(varianceInputImages)];
	for (int i = 0; i < ARRAYSIZE(varianceInputImages); ++i)
		varianceInputImages_resourceViews[i] = varianceInputImages[i]->ResourceView;
	{
		ID3D11ShaderResourceView * screenOutput[] = 
		{
			varianceInputImages[0]->ResourceView,
			varianceInputImages[1]->ResourceView
		};
		//Render(screenOutput);
		//goto free_varianceInputImages;
	}





	// Render cost volumes for input images
	const Texture * costVolumes[MAX_DISPARITY / 4];
	m_costVolumeRenderer->RenderCostVolumes(m_d3dContext.Get(), 
		inputImages, 
		MAX_DISPARITY / 4, 
		(const Texture*(*)[]) &costVolumes);
	ID3D11ShaderResourceView * costVolumes_resourceViews[ARRAYSIZE(costVolumes)];
	for (int i = 0; i < ARRAYSIZE(costVolumes_resourceViews); ++i)
		costVolumes_resourceViews[i] = costVolumes[i]->ResourceView;







	// Render mean textures for cost volumes (eq. no. 2)
	const Texture * meanCostVolumes[ARRAYSIZE(costVolumes)];
	m_meanImagesRenderer->RenderSimple(m_d3dContext.Get(), 
		costVolumes_resourceViews, 
		(const Texture*(*)[]) &meanCostVolumes, 
		ARRAYSIZE(costVolumes));
	ID3D11ShaderResourceView * meanCostVolumes_resourceViews[ARRAYSIZE(meanCostVolumes)];
	for (int i = 0; i < ARRAYSIZE(meanCostVolumes); ++i)
		meanCostVolumes_resourceViews[i] = meanCostVolumes[i]->ResourceView;

	// Render mean textures for images multiplied by cost volumes (eq. no. 3)
	const Texture * meanImageCostVolumes[ARRAYSIZE(costVolumes_resourceViews) * 4];
	m_meanImagesRenderer->RenderMultiplied(m_d3dContext.Get(), 
		inputImages[0], 
		costVolumes_resourceViews, 
		(const Texture*(*)[]) &meanImageCostVolumes, 
		ARRAYSIZE(costVolumes_resourceViews));
	ID3D11ShaderResourceView * meanImageCostVolumes_resourceViews[ARRAYSIZE(meanImageCostVolumes)];
	for (int i = 0; i < ARRAYSIZE(meanImageCostVolumes); ++i)
		meanImageCostVolumes_resourceViews[i] = meanImageCostVolumes[i]->ResourceView;
	for (int i = 0; i < ARRAYSIZE(costVolumes); ++i) // We don't need cost volumes anymore
		TexturesBuffer->Free(costVolumes[i]);

	// Render covariance textures (eq. no. 4)
	const Texture * convolution[ARRAYSIZE(meanImageCostVolumes)];
	m_meanImagesRenderer->RenderCovariance(m_d3dContext.Get(), 
		meanInputImages_resourceViews[0],
		meanCostVolumes_resourceViews,
		meanImageCostVolumes_resourceViews, 
		(const Texture*(*)[]) &convolution,
		ARRAYSIZE(meanImageCostVolumes_resourceViews));
	ID3D11ShaderResourceView * convolution_resourceViews[ARRAYSIZE(convolution)];
	for (int i = 0; i < ARRAYSIZE(convolution); ++i)
		convolution_resourceViews[i] = convolution[i]->ResourceView;
	for (int i = 0; i < ARRAYSIZE(meanImageCostVolumes); ++i) // We don't need images multiplied by cost volumes anymore
		TexturesBuffer->Free(meanImageCostVolumes[i]);
	{
		ID3D11ShaderResourceView * screenOutput[] = 
		{
			convolution[0]->ResourceView,
			convolution[1]->ResourceView
		};
		//Render(screenOutput);
		//goto free_varianceInputImages;
	}

	// Render parameter "a"
	const Texture * a[ARRAYSIZE(convolution)];
	m_meanImagesRenderer->RenderA(m_d3dContext.Get(), 
		convolution_resourceViews, 
		varianceInputImages_resourceViews,
		(const Texture*(*)[]) &a, 
		ARRAYSIZE(convolution));
	for (int i = 0; i < ARRAYSIZE(convolution); ++i) // We don't need convolutions anymore
		TexturesBuffer->Free(convolution[i]);
	ID3D11ShaderResourceView * a_resourceViews[ARRAYSIZE(a)];
	for (int i = 0; i < ARRAYSIZE(a); ++i)
		a_resourceViews[i] = a[i]->ResourceView;
	{
		ID3D11ShaderResourceView * screenOutput[] = 
		{
			a[0]->ResourceView,
			a[1]->ResourceView
		};
		//Render(screenOutput);
		//goto free_varianceInputImages;
	}

	// Render parameter "b"
	const Texture * b[ARRAYSIZE(a) / 4];
	m_meanImagesRenderer->RenderB(m_d3dContext.Get(), 
		meanCostVolumes_resourceViews, 
		a_resourceViews,
		meanInputImages_resourceViews[0],
		(const Texture*(*)[]) &b, 
		ARRAYSIZE(a));
	for (int i = 0; i < ARRAYSIZE(meanCostVolumes); ++i) // We don't need mean cost volumes anymore
		TexturesBuffer->Free(meanCostVolumes[i]);
	ID3D11ShaderResourceView * b_resourceViews[ARRAYSIZE(b)];
	for (int i = 0; i < ARRAYSIZE(b); ++i)
		b_resourceViews[i] = b[i]->ResourceView;
	{
		ID3D11ShaderResourceView * screenOutput[] = 
		{
			b[0]->ResourceView,
			b[1]->ResourceView
		};
		//Render(screenOutput);
		//goto free_varianceInputImages;
	}

	// Render boxFIlter(a)
	const Texture * meanA[ARRAYSIZE(a)];
	m_meanImagesRenderer->RenderSimple(m_d3dContext.Get(), 
		a_resourceViews, 
		(const Texture*(*)[]) &meanA, 
		ARRAYSIZE(a));
	for (int i = 0; i < ARRAYSIZE(a); ++i) // We don't need convolutions anymore
		TexturesBuffer->Free(a[i]);
	ID3D11ShaderResourceView * meanA_resourceViews[ARRAYSIZE(meanA)];
	for (int i = 0; i < ARRAYSIZE(meanA); ++i)
		meanA_resourceViews[i] = meanA[i]->ResourceView;
	{
		ID3D11ShaderResourceView * screenOutput[] = 
		{
			meanA[0]->ResourceView,
			meanA[1]->ResourceView
		};
		//Render(screenOutput);
	}

	// Render boxFIlter(b)
	const Texture * meanB[ARRAYSIZE(b)];
	m_meanImagesRenderer->RenderSimple(m_d3dContext.Get(), 
		b_resourceViews, 
		(const Texture*(*)[]) &meanB, 
		ARRAYSIZE(b));
	for (int i = 0; i < ARRAYSIZE(b); ++i) // We don't need convolutions anymore
		TexturesBuffer->Free(b[i]);
	ID3D11ShaderResourceView * meanB_resourceViews[ARRAYSIZE(meanB)];
	for (int i = 0; i < ARRAYSIZE(meanB); ++i)
		meanB_resourceViews[i] = meanB[i]->ResourceView;
	{
		ID3D11ShaderResourceView * screenOutput[] = 
		{
			meanB[0]->ResourceView,
			meanB[1]->ResourceView
		};
		//Render(screenOutput);
	}

	// Render q
	const Texture * q[ARRAYSIZE(meanB)];
	m_meanImagesRenderer->RenderQ(m_d3dContext.Get(), 
		meanA_resourceViews, 
		inputImages[0],
		meanB_resourceViews, 
		(const Texture*(*)[]) &q, 
		ARRAYSIZE(b));	
	ID3D11ShaderResourceView * q_resourceViews[ARRAYSIZE(meanB)];
	for (int i = 0; i < ARRAYSIZE(q); ++i)
		q_resourceViews[i] = q[i]->ResourceView;
	{
		ID3D11ShaderResourceView * screenOutput[] = 
		{
			q[0]->ResourceView,
			q[1]->ResourceView
		};
		//Render(screenOutput);
		//goto free_meanInputImages;
	}

	for (int i = 0; i < ARRAYSIZE(meanA); ++i) // We don't need convolutions anymore
		TexturesBuffer->Free(meanA[i]);
	for (int i = 0; i < ARRAYSIZE(meanB); ++i) // We don't need convolutions anymore
		TexturesBuffer->Free(meanB[i]);

	const Texture * disparity[ARRAYSIZE(q) / 4];
	m_meanImagesRenderer->RenderDisparity(m_d3dContext.Get(), 
		q_resourceViews, 
		(const Texture*(*)[]) &disparity, 
		ARRAYSIZE(q));	
	{
		ID3D11ShaderResourceView * screenOutput[] = 
		{
			disparity[0]->ResourceView
		};
		Render(screenOutput);
	}	

	for (int i = 0; i < ARRAYSIZE(q); ++i) // We don't need convolutions anymore
		TexturesBuffer->Free(q[i]);	
	for (int i = 0; i < ARRAYSIZE(disparity); ++i) // We don't need convolutions anymore
		TexturesBuffer->Free(disparity[i]);

free_varianceInputImages:
	TexturesBuffer->Free(varianceInputImages[0]);
	TexturesBuffer->Free(varianceInputImages[1]);
	TexturesBuffer->Free(varianceInputImages[2]);
	TexturesBuffer->Free(varianceInputImages[3]);

free_meanInputImages:
	TexturesBuffer->Free(meanInputImages[0]);
	TexturesBuffer->Free(meanInputImages[1]);
}

void CubeRenderer::Render(ID3D11ShaderResourceView * * resource)
{
	static bool clearStencil = true;
	const float midnightBlue[] = { 0.098f, 0.098f, 0.439f, 1.000f };

	m_d3dContext->OMSetRenderTargets(
		1,
		m_renderTargetView.GetAddressOf(),
		0//m_depthStencilView.Get()			// This increases performance!
		);
	m_d3dContext->PSSetShaderResources(
		0, 
		1,
		resource
		);

	if (clearStencil)
	{
		m_d3dContext->ClearRenderTargetView(
			m_renderTargetView.Get(),
			midnightBlue
			);

		//m_d3dContext->ClearDepthStencilView(
		//	m_depthStencilView.Get(),
		//	D3D11_CLEAR_DEPTH,
		//	1.0f,
		//	0
		//	);

		/*m_d3dContext->UpdateSubresource(
		m_constantBuffer.Get(),
		0,
		NULL,
		&m_constantBufferData,
		0,
		0
		);*/

		UINT stride = sizeof(VertexPositionTexel);
		UINT offset = 0;
		m_d3dContext->IASetVertexBuffers(
			0,
			1,
			m_vertexBuffer.GetAddressOf(),
			&stride,
			&offset
			);

		m_d3dContext->IASetIndexBuffer(
			m_indexBuffer.Get(),
			DXGI_FORMAT_R16_UINT,
			0
			);

		m_d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_d3dContext->IASetInputLayout(m_inputLayout.Get());

		m_d3dContext->VSSetShader(
			m_vertexShader.Get(),
			nullptr,
			0
			);

		m_d3dContext->VSSetConstantBuffers(
			0,
			1,
			m_constantBuffer.GetAddressOf()
			);

		m_d3dContext->PSSetSamplers(
			0, 
			1, 
			m_sampler.GetAddressOf()
			);

		clearStencil = false;
	}

	m_d3dContext->PSSetShader(
		m_pixelShader.Get(),
		nullptr,
		0
		);

	m_d3dContext->DrawIndexed(
		m_indexCount,
		0,
		0
		);
}

void CubeRenderer::GPUBlur()
{

	UINT stride = sizeof(VertexPositionTexel);
	UINT offset = 0;
	m_d3dContext->IASetVertexBuffers(
		0,
		1,
		m_vertexBuffer.GetAddressOf(),
		&stride,
		&offset
		);

	m_d3dContext->IASetIndexBuffer(
		m_indexBuffer.Get(),
		DXGI_FORMAT_R16_UINT,
		0
		);

	m_d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_d3dContext->IASetInputLayout(m_inputLayout.Get());

	m_d3dContext->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	m_d3dContext->PSSetSamplers(0, 1, m_sampler.GetAddressOf());

	ID3D11ShaderResourceView * incInput[] =
	{
		m_texture1View.Get(),
		m_texture2View.Get()
	};
	ID3D11RenderTargetView * tmpRenderTargets[] = 
	{
		m_GPU1_Texture_H_target.Get(),
		m_GPU2_Texture_H_target.Get()
	};
	m_d3dContext->PSSetShader(m_pixelShader_Mean_H.Get(), nullptr, 0);
	m_d3dContext->OMSetRenderTargets( 2, tmpRenderTargets, 0);
	m_d3dContext->PSSetShaderResources(0, 2, incInput);
	m_d3dContext->DrawIndexed(m_indexCount, 0, 0);

	ID3D11ShaderResourceView * tmpResourceView[] =
	{
		m_GPU1_Texture_H_shaderView.Get(),
		m_GPU2_Texture_H_shaderView.Get()
	};
	ID3D11RenderTargetView * resultRenderTargets[] = 
	{
		m_GPU1_Texture_W_target.Get(),
		m_GPU2_Texture_W_target.Get()
	};
	m_d3dContext->PSSetShader(m_pixelShader_Mean_W.Get(), nullptr, 0);
	m_d3dContext->OMSetRenderTargets(2, resultRenderTargets, 0);
	m_d3dContext->PSSetShaderResources(0, 2, tmpResourceView);
	m_d3dContext->DrawIndexed(m_indexCount, 0, 0);
}

void CubeRenderer::CPUBlur()
{
	throw ref new Platform::Exception(E_NOTIMPL);
}

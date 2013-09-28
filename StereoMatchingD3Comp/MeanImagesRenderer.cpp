#include "pch.h"
#include "Config.h"
#include "MeanImagesRenderer.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel;
using namespace Windows::UI::Core;

MeanImagesRenderer::MeanImagesRenderer(ID3D11Device1 * device, Windows::Foundation::Size viewportSize) :
	AbstractProcessingStage(device, viewportSize)
{
}

Concurrency::task<void> MeanImagesRenderer::_Initialize()
{
	auto loadVSTask = DX::ReadDataAsync("MeanImageVertexShader.cso");
	auto loadPSTask_CV_H = DX::ReadDataAsync("MeanCostVolumePixelShaderH.cso");
	auto loadPSTask_CV_W = DX::ReadDataAsync("MeanCostVolumePixelShaderW.cso");
	auto loadPSTask_MUL = DX::ReadDataAsync("MultiplyColorAndGrayPixelShader.cso");

	auto createVSTask = loadVSTask.then([this](Platform::Array<byte>^ fileData) {
		DX::ThrowIfFailed(
			m_device->CreateVertexShader(
			fileData->Data,
			fileData->Length,
			nullptr,
			&m_vertexShader
			)
			);

		const D3D11_INPUT_ELEMENT_DESC vertexDesc[] = 
		{
			{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		DX::ThrowIfFailed(
			m_device->CreateInputLayout(
			vertexDesc,
			ARRAYSIZE(vertexDesc),
			fileData->Data,
			fileData->Length,
			&m_inputLayout
			)
			);

	});

	auto createPSTask_CV_H = loadPSTask_CV_H.then([this](Platform::Array<byte>^ fileData) {
		DX::ThrowIfFailed(
			m_device->CreatePixelShader(
			fileData->Data,
			fileData->Length,
			nullptr,
			&m_pixelShader_CV_H
			)
			);
	});

	auto createPSTask_CV_W = loadPSTask_CV_W.then([this](Platform::Array<byte>^ fileData) {
		DX::ThrowIfFailed(
			m_device->CreatePixelShader(
			fileData->Data,
			fileData->Length,
			nullptr,
			&m_pixelShader_CV_W
			)
			);
	});

	auto createPSTask_MUL = loadPSTask_MUL.then([this](Platform::Array<byte>^ fileData) {
		DX::ThrowIfFailed(
			m_device->CreatePixelShader(
			fileData->Data,
			fileData->Length,
			nullptr,
			&m_pixelShader_MUL
			)
			);
	});

	auto createTargetTexture = (createPSTask_MUL && createPSTask_CV_H && createPSTask_CV_W && createVSTask).then([this] () {

		const int count = 2 + MAX_DISPARITY + MAX_DISPARITY + MAX_DISPARITY / 4;
		ID3D11Texture2D * subTargets[count];
		ID3D11Texture2D * targets[count];

		ID3D11Texture2D * renderTarget = 0;
		D3D11_TEXTURE2D_DESC desc;

		ZeroMemory(&desc, sizeof(desc));
		desc.Width = (uint32) this->GetWidth();
		desc.Height = (uint32) this->GetHeight();
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.SampleDesc.Count = 1;
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		for (int i = 0; i < count; ++i)
		{
			DX::ThrowIfFailed(
				m_device->CreateTexture2D(
				&desc, 
				nullptr, 
				&renderTarget)
				);

			targets[i] = renderTarget;

			DX::ThrowIfFailed(
				m_device->CreateTexture2D(
				&desc, 
				nullptr, 
				&renderTarget)
				);

			subTargets[i] = renderTarget;
		}

		this->SetTargetResource(count, targets, DXGI_FORMAT_R32G32B32A32_FLOAT);
		this->SetIntermediateTargetResource(1, count, subTargets, DXGI_FORMAT_R32G32B32A32_FLOAT);
	});

	auto createScene = (createTargetTexture).then([this] () {

		// Create surface
		VertexPosition vertices[] =
		{
			{ XMFLOAT3(-1.0f,  1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
			{ XMFLOAT3( 1.0f,  1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
			{ XMFLOAT3( 1.0f, -1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
			{ XMFLOAT3(-1.0f, -1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
		};

		D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
		vertexBufferData.pSysMem = vertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(vertices), D3D11_BIND_VERTEX_BUFFER);
		DX::ThrowIfFailed(
			m_device->CreateBuffer(
			&vertexBufferDesc,
			&vertexBufferData,
			&m_vertexBuffer
			)
			);

		unsigned short cubeIndices[] = 
		{
			0, 1, 2,
			0, 2, 3
		};

		m_indexCount = ARRAYSIZE(cubeIndices);

		D3D11_SUBRESOURCE_DATA indexBufferData = {0};
		indexBufferData.pSysMem = cubeIndices;
		indexBufferData.SysMemPitch = 0;
		indexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC indexBufferDesc(sizeof(cubeIndices), D3D11_BIND_INDEX_BUFFER);

		DX::ThrowIfFailed(
			m_device->CreateBuffer(
			&indexBufferDesc,
			&indexBufferData,
			&m_indexBuffer
			)
			);
	});

	auto createSampler = createScene.then([this] () {

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
			m_device->CreateSamplerState(
			&samplerDesc,
			&m_sampler
			)
			);
	});

	return createSampler;
}

void MeanImagesRenderer::SetStereoTexture(ID3D11ShaderResourceView * left, ID3D11ShaderResourceView * right)
{
	m_textureLeftView = left;
	m_textureRightView = right;
}

void MeanImagesRenderer::SetCostVolume(ID3D11ShaderResourceView * * costVolume, uint8 count)
{
	if (MAX_DISPARITY / 4 != count)
		return;

	for(int i = 0; i < count; ++i)
	{
		m_costVolume[i] = costVolume[i];
	}
}

void MeanImagesRenderer::_RenderImages(ID3D11DeviceContext1 * context)
{
	ID3D11ShaderResourceView * textures[] = 
	{
		m_textureLeftView.Get(),
		m_textureRightView.Get()
	};

	context->PSSetShader(
		m_pixelShader_CV_H.Get(),
		nullptr,
		0
		);

	context->OMSetRenderTargets(
		2,
		this->GetIntermediateRenderTargets(1),
		0//m_depthStencilView.Get()			// This increases performance!
		);

	context->PSSetShaderResources(
		0, 
		2,
		textures
		);

	context->DrawIndexed(
		m_indexCount,
		0,
		0
		);

	context->PSSetShader(
		m_pixelShader_CV_W.Get(),
		nullptr,
		0
		);

	textures[0] = this->GetShaderResourceTargets(1)[0];
	textures[1] = this->GetShaderResourceTargets(1)[1];

	context->OMSetRenderTargets(
		2,
		this->GetRenderTargets(),
		0//m_depthStencilView.Get()			// This increases performance!
		);

	context->PSSetShaderResources(
		0, 
		2,
		textures
		);

	context->DrawIndexed(
		m_indexCount,
		0,
		0
		);
}

void MeanImagesRenderer::_RenderCostVolumes(ID3D11DeviceContext1 * context)
{
	for (int i = 2; i < 2 + MAX_DISPARITY / 4; i+=2)
	{
		ID3D11ShaderResourceView * textures[] = 
		{
			m_costVolume[i-2].Get(),
			m_costVolume[i-1].Get()
		};

		context->PSSetShader(
			m_pixelShader_CV_H.Get(),
			nullptr,
			0
			);

		context->OMSetRenderTargets(
			2,
			this->GetIntermediateRenderTargets(1) + i,
			0//m_depthStencilView.Get()			// This increases performance!
			);

		context->PSSetShaderResources(
			0, 
			2,
			textures
			);

		context->DrawIndexed(
			m_indexCount,
			0,
			0
			);

		context->PSSetShader(
			m_pixelShader_CV_W.Get(),
			nullptr,
			0
			);

		textures[0] = this->GetShaderResourceTargets(1)[0+i];
		textures[1] = this->GetShaderResourceTargets(1)[1+i];

		context->OMSetRenderTargets(
			2,
			this->GetRenderTargets() + i,
			0//m_depthStencilView.Get()			// This increases performance!
			);

		context->PSSetShaderResources(
			0, 
			2,
			textures
			);

		context->DrawIndexed(
			m_indexCount,
			0,
			0
			);
	}
}

void MeanImagesRenderer::_RenderImageCostVolumes(ID3D11DeviceContext1 * context)
{
	context->PSSetShader(
		m_pixelShader_MUL.Get(),
		nullptr,
		0
		);
	
	ComPtr<ID3D11ShaderResourceView> * tmp = m_costVolume;
	for (int i = 0; i < MAX_DISPARITY / 4; ++i)
	{
		ID3D11ShaderResourceView * textures[] = 
		{
			m_textureLeftView.Get(),
			m_costVolume[i].Get()
		};

		context->OMSetRenderTargets(
			2,
			this->GetRenderTargets() + i + 2 + MAX_DISPARITY / 4,
			0//m_depthStencilView.Get()			// This increases performance!
			);

		context->PSSetShaderResources(
			0, 
			2,
			textures
			);

		context->DrawIndexed(
			m_indexCount,
			0,
			0
			);
	}
	
	ComPtr<ID3D11ShaderResourceView> * tmp2 = m_costVolume;
	for (int i = 0; i < MAX_DISPARITY / 4; ++i)
	{
		ID3D11ShaderResourceView * textures[] = 
		{
			m_textureRightView.Get(),
			m_costVolume[i].Get()
		};

		context->OMSetRenderTargets(
			2,
			this->GetRenderTargets() + i + 2 + MAX_DISPARITY / 2,
			0//m_depthStencilView.Get()			// This increases performance!
			);

		context->PSSetShaderResources(
			0, 
			2,
			textures
			);

		context->DrawIndexed(
			m_indexCount,
			0,
			0
			);
	}
}

void MeanImagesRenderer::_Render(ID3D11DeviceContext1 * context)
{
	static bool clearStencil = true;
	const float midnightBlue[] = { 0.098f, 0.098f, 0.439f, 1.000f };

	if (clearStencil) 
	{
		for (int i = 0; i < m_resultsCount[0]; ++i)
		{
			context->ClearRenderTargetView(
				m_resultTargetView[0][i],
				midnightBlue
				);
		}

		UINT stride = sizeof(VertexPosition);
		UINT offset = 0;
		context->IASetVertexBuffers(
			0,
			1,
			m_vertexBuffer.GetAddressOf(),
			&stride,
			&offset
			);

		context->IASetIndexBuffer(
			m_indexBuffer.Get(),
			DXGI_FORMAT_R16_UINT,
			0
			);

		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		context->IASetInputLayout(m_inputLayout.Get());

		context->VSSetShader(
			m_vertexShader.Get(),
			nullptr,
			0
			);

		context->PSSetSamplers(
			0, 
			1, 
			m_sampler.GetAddressOf()
			);

		clearStencil = false;
	}

	this->_RenderImages(context);
	this->_RenderCostVolumes(context);
	//this->_RenderImageCostVolumes(context);
}

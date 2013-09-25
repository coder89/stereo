#include "pch.h"
#include "Config.h"
#include "CubeRenderer.h"
#include "DDSTextureLoader.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel;
using namespace Windows::UI::Core;

ConstantParameters * ConstantParametersBuffer = new ConstantParameters(9, 0.0001f, 0.9f, 9, 0.1f, 0.028f, 0.008f);

CubeRenderer::CubeRenderer() :
	m_indexCount(0),
	m_loadingComplete(false)
{
}

void CubeRenderer::CreateDeviceResources()
{
	Direct3DBase::CreateDeviceResources();

	m_costVolumeRenderer = new CostVolumeRenderer(m_d3dDevice.Get(), Size(900, 750));

	auto initCVRenderer = m_costVolumeRenderer->Initialize();

	auto loadVSTask = DX::ReadDataAsync("SimpleVertexShader.cso");
	auto loadPSTask = DX::ReadDataAsync("ToScreenPixelShader.cso");
	auto loadTX1Task = DX::ReadDataAsync("Media\\textures\\im2_medium.dds");
	auto loadTX2Task = DX::ReadDataAsync("Media\\textures\\im6_medium.dds");

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

		//CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
		//DX::ThrowIfFailed(
		//	m_d3dDevice->CreateBuffer(
		//	&constantBufferDesc,
		//	nullptr,
		//	&m_constantBuffer
		//	)
		//	);

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

	auto setInputImages = (createTX1Task && createTX2Task && initCVRenderer).then([this] () {

		ConstantParametersBuffer->dx = 1.0f / m_renderTargetSize.Width;
		ConstantParametersBuffer->dy = 1.0f / m_renderTargetSize.Height;

		m_costVolumeRenderer->SetStereoTexture(m_texture1View.Get(), m_texture2View.Get());

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

	auto createScene = (createVSTask && createPSTask && setInputImages).then([this] () {

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

	createScene.then([this] () {

		m_loadingComplete = true;

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

	/*XMStoreFloat4x4(
	&m_constantBufferData.projection,
	XMMatrixTranspose(
	XMMatrixPerspectiveFovRH(
	fovAngleY,
	aspectRatio,
	0.01f,
	100.0f
	)
	)
	);

	XMVECTOR eye = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	XMVECTOR at = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));
	XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixIdentity());*/// XMMatrixTranspose(XMMatrixRotationY(timeTotal * XM_PIDIV4)));
}

void CubeRenderer::Update(float timeTotal, float timeDelta)
{
	(void) timeDelta; // Unused parameter.

	//XMVECTOR eye = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	//XMVECTOR at = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	//XMVECTOR up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//XMStoreFloat4x4(&m_constantBufferData.view, XMMatrixTranspose(XMMatrixLookAtRH(eye, at, up)));
	//XMStoreFloat4x4(&m_constantBufferData.model, XMMatrixIdentity()); XMMatrixTranspose(XMMatrixRotationY(timeTotal * XM_PIDIV4)));
}

void CubeRenderer::Render()
{
	// Only draw the cube once it is loaded (loading is asynchronous).
	if (!m_loadingComplete)
	{
		return;
	}

	m_d3dContext->UpdateSubresource(
		m_constantParameterBuffer.Get(),
		0,
		NULL,
		ConstantParametersBuffer,
		0,
		0
		);

	m_d3dContext->PSSetConstantBuffers(
		0,
		1,
		m_constantParameterBuffer.GetAddressOf()
		);

	m_costVolumeRenderer->Render(m_d3dContext.Get());

	Render(m_costVolumeRenderer->GetResultViews());
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

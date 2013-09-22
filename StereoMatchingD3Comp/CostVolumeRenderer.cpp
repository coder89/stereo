#include "pch.h"
#include "CostVolumeRenderer.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel;
using namespace Windows::UI::Core;

#include "DDSTextureLoader.h"

CostVolumeRenderer::CostVolumeRenderer(ID3D11Device1 * device)
{
	m_loadingComplete = false;
	m_d3dDevice = device;
}

void CostVolumeRenderer::Initialize(uint32 width, uint32 height)
{
	m_width = width;
	m_height = height;

	m_viewport = CD3D11_VIEWPORT(
		0.0f,
		0.0f,
		m_width,
		m_height
		);

	auto loadVSTask = DX::ReadDataAsync("CostVolumeVertexShader.cso");
	auto loadPSTask = DX::ReadDataAsync("BoxFilterPixelShaderW.cso");

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

		CD3D11_BUFFER_DESC constantParametersBufferDesc(sizeof(ConstantParametersBuffer), D3D11_BIND_CONSTANT_BUFFER);
		DX::ThrowIfFailed(
			m_d3dDevice->CreateBuffer(
			&constantParametersBufferDesc,
			nullptr,
			&m_constantParameterBuffer
			)
			);

		CD3D11_BUFFER_DESC textureProjectionBufferDesc(sizeof(TextureProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
		DX::ThrowIfFailed(
			m_d3dDevice->CreateBuffer(
			&textureProjectionBufferDesc,
			nullptr,
			&m_textureProjectionBuffer
			)
			);
	});

	auto createTargetTexture = (createPSTask && createVSTask).then([this] () {

		D3D11_TEXTURE2D_DESC desc;
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

		ZeroMemory(&desc, sizeof(desc));
		desc.Width = m_width;
		desc.Height = m_height;
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ArraySize = 1;
		desc.MipLevels = 1;
		desc.SampleDesc.Count = 1;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		DX::ThrowIfFailed(
			m_d3dDevice->CreateTexture2D(
			&desc, 
			nullptr, 
			&m_renderTarget)
			);

		renderTargetViewDesc.Format = desc.Format;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetViewDesc.Texture2D.MipSlice = 0;

		DX::ThrowIfFailed(
			m_d3dDevice->CreateRenderTargetView(
			m_renderTarget.Get(),
			&renderTargetViewDesc,
			&m_renderTargetView)
			);	

		shaderResourceViewDesc.Format = desc.Format;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture2D.MipLevels = 1;

		DX::ThrowIfFailed(
			m_d3dDevice->CreateShaderResourceView(
			m_renderTarget.Get(),
			&shaderResourceViewDesc,
			&m_renderShaderResourceView)
			);

		// Create a depth stencil view.
		CD3D11_TEXTURE2D_DESC depthStencilDesc(
			DXGI_FORMAT_D24_UNORM_S8_UINT,
			static_cast<UINT>(desc.Width),
			static_cast<UINT>(desc.Height),
			1,
			1,
			D3D11_BIND_DEPTH_STENCIL
			);

		ComPtr<ID3D11Texture2D> depthStencil;
		DX::ThrowIfFailed(
			m_d3dDevice->CreateTexture2D(
			&depthStencilDesc,
			nullptr,
			&depthStencil
			)
			);

		CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
		DX::ThrowIfFailed(
			m_d3dDevice->CreateDepthStencilView(
			depthStencil.Get(),
			&depthStencilViewDesc,
			&m_depthStencilView
			)
			);

		//// Set the rendering viewport to target the entire window.
		//CD3D11_VIEWPORT viewport(
		//	0.0f,
		//	0.0f,
		//	desc.Width,
		//	desc.Height
		//	);
		//m_d3dContext->RSSetViewports(1, &viewport);
		//D3D11_TEXTURE3D_DESC texDesc;
		//texDesc.Width 	= desc.Width;
		//texDesc.Height	= desc.Height;
		//texDesc.Depth  	= 20;
		//texDesc.MipLevels = 0;
		//texDesc.Format	= DXGI_FORMAT_D32_FLOAT;
		//texDesc.Usage      	= D3D11_USAGE_DEFAULT;
		//texDesc.BindFlags  	= D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		//texDesc.CPUAccessFlags = 0; 
		//texDesc.MiscFlags  	= D3D11_RESOURCE_MISC_GENERATE_MIPS;
		//DX::ThrowIfFailed(
		//m_d3dDevice->CreateTexture3D(
		//&texDesc, 
		//0, 
		//&m_costmap
		//)
		//);
		//DX::ThrowIfFailed(
		//m_d3dDevice->CreateRenderTargetView(
		//m_costmap.Get()->, 
		//0, 
		//&m_costmapRenderView
		//)
		//);
		//DX::ThrowIfFailed(
		//m_d3dDevice->CreateShaderResourceView(
		//m_costmap.Get(), 
		//0, 
		//&m_costmapShaderView
		//)
		//);
	});

	auto createScene = createTargetTexture.then([this] () {

		// Create surface
		VertexPositionColor cubeVertices[] =
		{
			{ XMFLOAT3(-1.0f,  1.0f, 0.5f), XMFLOAT2(0.0f, 0.0f) },
			{ XMFLOAT3( 1.0f,  1.0f, 0.5f), XMFLOAT2(1.0f, 0.0f) },
			{ XMFLOAT3( 1.0f, -1.0f, 0.5f), XMFLOAT2(1.0f, 1.0f) },
			{ XMFLOAT3(-1.0f, -1.0f, 0.5f), XMFLOAT2(0.0f, 1.0f) },
		};

		D3D11_SUBRESOURCE_DATA vertexBufferData = {0};
		vertexBufferData.pSysMem = cubeVertices;
		vertexBufferData.SysMemPitch = 0;
		vertexBufferData.SysMemSlicePitch = 0;
		CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(cubeVertices), D3D11_BIND_VERTEX_BUFFER);
		DX::ThrowIfFailed(
			m_d3dDevice->CreateBuffer(
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
			m_d3dDevice->CreateBuffer(
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
			m_d3dDevice->CreateSamplerState(
			&samplerDesc,
			&m_sampler
			)
			);
	});

	createSampler.then([this] () {

		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		m_renderTarget.Get()->GetDesc(&desc);

		m_constantParametersBufferData.alpha = 0.9f;
		m_constantParametersBufferData.Tc = 0.028f;
		m_constantParametersBufferData.Tg = 0.008f;
		m_constantParametersBufferData.dx = 1.0f / desc.Width;
		m_textureProjectionBufferData.disparity = 0.0f;

		m_loadingComplete = true;
	});

}

void CostVolumeRenderer::SetLeftTexture(ID3D11Texture2D * texture, ID3D11ShaderResourceView * textureView)
{
	m_textureLeft = texture;
	m_textureLeftView = textureView;
}

void CostVolumeRenderer::SetRightTexture(ID3D11Texture2D * texture, ID3D11ShaderResourceView * textureView)
{
	m_textureRight = texture;
	m_textureRightView = textureView;
}

ID3D11ShaderResourceView * * CostVolumeRenderer::GetShaderResourceView()
{
	return m_renderShaderResourceView.GetAddressOf();
}

void CostVolumeRenderer::Render(ID3D11DeviceContext * context)
{
	const float midnightBlue[] = { 0.098f, 0.098f, 0.439f, 1.000f };

	if (!m_loadingComplete)
	{
		return;
	}

	ID3D11ShaderResourceView* nullSrv = NULL;
	context->PSSetShaderResources(0, 1, &nullSrv);

	context->RSSetViewports(1, &m_viewport);

	context->OMSetRenderTargets(
		1,
		m_renderTargetView.GetAddressOf(),
		m_depthStencilView.Get()
		);

	context->ClearRenderTargetView(
		m_renderTargetView.Get(),
		midnightBlue
		);

	context->ClearDepthStencilView(
		m_depthStencilView.Get(),
		D3D11_CLEAR_DEPTH,
		1.0f,
		0
		);

	context->UpdateSubresource(
		m_constantParameterBuffer.Get(),
		0,
		NULL,
		&m_constantParametersBufferData,
		0,
		0
		);

	UINT stride = sizeof(VertexPositionColor);
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

	context->PSSetShader(
		m_pixelShader.Get(),
		nullptr,
		0
		);

	context->PSSetSamplers(
		0, 
		1, 
		m_sampler.GetAddressOf()
		);

	context->PSSetConstantBuffers(
		0,
		1,
		m_constantParameterBuffer.GetAddressOf()
		);

	context->PSSetShaderResources(
		0, 
		1,
		m_textureLeftView.GetAddressOf()
		);

	context->PSSetShaderResources(
		1, 
		1,
		m_textureRightView.GetAddressOf()
		);

	for (int i = 0; i < 30; ++i)
	context->DrawIndexed(
		m_indexCount,
		0,
		0
		);
}

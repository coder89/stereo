#include "pch.h"
#include "Config.h"
#include "TextureCache.h"

TextureCache * TexturesBuffer = nullptr;

Texture::Texture(Windows::Foundation::Size size, ID3D11Device * device) :
	Size(size)
{
	D3D11_TEXTURE2D_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	desc.Width = (uint32) size.Width;
	desc.Height = (uint32) size.Height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.SampleDesc.Count = 1;
	desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	DX::ThrowIfFailed(
		device->CreateTexture2D(
		&desc, 
		nullptr, 
		&Resource
		)
		);

	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
	renderTargetViewDesc.Format = desc.Format;
	renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
	renderTargetViewDesc.Texture2D.MipSlice = 0;

	DX::ThrowIfFailed(
		device->CreateRenderTargetView(
		Resource,
		&renderTargetViewDesc,
		&RenderTarget
		)
		);	

	D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
	shaderResourceViewDesc.Format = desc.Format;
	shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
	shaderResourceViewDesc.Texture2D.MipLevels = 1;

	DX::ThrowIfFailed(
		device->CreateShaderResourceView(
		Resource,
		&shaderResourceViewDesc,
		&ResourceView
		)
		);
}

TextureCache * TextureCache::Instance(Windows::Foundation::Size size, ID3D11Device * device)
{
	if (!TexturesBuffer)
		TexturesBuffer = new TextureCache(size, device);
	return TexturesBuffer;
}

TextureCache::TextureCache(Windows::Foundation::Size size, ID3D11Device * device) :
	m_device(device),
	m_size(size)
{
	TexturesBuffer = this;
}

Concurrency::task<void> TextureCache::InitializeAsync()
{
	return Concurrency::create_task([this] ()
	{
		for (int i = 0; i < MAX_BUFFERS_COUNT; ++i)
		{
			m_available_stack.push(new Texture(m_size, m_device));
		}
	});
}
#include "pch.h"
#include "DirectXBase.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::Graphics::Display;

// Constructor.
DirectXBase::DirectXBase()
{
}

// Initialize the Direct3D resources required to run.
void DirectXBase::Initialize()
{
}

// These are the resources that depend on the device.
void DirectXBase::CreateDeviceResources()
{
}

void DirectXBase::UpdateDevice(ID3D11Device1* device, ID3D11DeviceContext1* context, ID3D11RenderTargetView* renderTargetView)
{
    m_d3dContext = context;
    m_d3dRenderTargetView = renderTargetView;

    if (m_d3dDevice.Get() != device)
    {
        m_d3dDevice = device;
        CreateDeviceResources();

        // Force call to CreateWindowSizeDependentResources
        m_renderTargetSize.Width  = -1;
        m_renderTargetSize.Height = -1;
    }

    ComPtr<ID3D11Resource> renderTargetViewResource;
    m_d3dRenderTargetView->GetResource(&renderTargetViewResource);

    ComPtr<ID3D11Texture2D> backBuffer;
    DX::ThrowIfFailed(
        renderTargetViewResource.As(&backBuffer)
        );

    // Cache the rendertarget dimensions in our helper class for convenient use.
    D3D11_TEXTURE2D_DESC backBufferDesc;
    backBuffer->GetDesc(&backBufferDesc);

    if (m_renderTargetSize.Width  != static_cast<float>(backBufferDesc.Width) ||
        m_renderTargetSize.Height != static_cast<float>(backBufferDesc.Height))
    {
        m_renderTargetSize.Width  = static_cast<float>(backBufferDesc.Width);
        m_renderTargetSize.Height = static_cast<float>(backBufferDesc.Height);
        CreateWindowSizeDependentResources();
    }

    // Set the rendering viewport to target the entire window.
    CD3D11_VIEWPORT viewport(
        0.0f,
        0.0f,
        m_renderTargetSize.Width,
        m_renderTargetSize.Height
        );

    m_d3dContext->RSSetViewports(1, &viewport);
}


void DirectXBase::UpdateForWindowSizeChange(float width, float height)
{
    if (width != m_windowBounds.Width || height != m_windowBounds.Height)
    {
        m_windowBounds.Width  = width;
        m_windowBounds.Height = height;
    }
}

// Allocate all memory resources that depend on the window size.
void DirectXBase::CreateWindowSizeDependentResources()
{
    // Create a depth stencil view.
    CD3D11_TEXTURE2D_DESC depthStencilDesc(
        DXGI_FORMAT_D24_UNORM_S8_UINT,
        static_cast<UINT>(m_renderTargetSize.Width),
        static_cast<UINT>(m_renderTargetSize.Height),
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
            &m_d3dDepthStencilView
            )
        );
}
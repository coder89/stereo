#pragma once

#include "DirectXSample.h"

// Helper class that initializes DirectX APIs for 3D rendering.
ref class DirectXBase abstract
{
internal:
    DirectXBase();

    virtual void Initialize();
    virtual void CreateDeviceResources();
    virtual void UpdateDevice(ID3D11Device1* device, ID3D11DeviceContext1* context, ID3D11RenderTargetView* renderTargetView);
    virtual void UpdateForWindowSizeChange(float width, float height);
    virtual void CreateWindowSizeDependentResources();
    virtual void Render() = 0;

protected private:
    // Direct3D Objects.
    Microsoft::WRL::ComPtr<ID3D11Device1> m_d3dDevice;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext1> m_d3dContext;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_d3dRenderTargetView;
    Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_d3dDepthStencilView;

    // Cached renderer properties.
    Windows::Foundation::Size m_renderTargetSize;
    Windows::Foundation::Rect m_windowBounds;
};
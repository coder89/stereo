#include "pch.h"
#include "Config.h"
#include "CostVolumeRenderer.h"

using namespace DirectX;
using namespace Microsoft::WRL;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel;
using namespace Windows::UI::Core;

CostVolumeRenderer::CostVolumeRenderer(ID3D11Device1 * device, Windows::Foundation::Size viewportSize) :
    AbstractProcessingStage(device, viewportSize)
{
}

Concurrency::task<void> CostVolumeRenderer::_Initialize()
{
    auto loadVSTask = DX::ReadDataAsync("CostVolumeVertexShader.cso");
    auto loadPSTask = DX::ReadDataAsync("CostVolumePixelShader.cso");

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

    auto createPSTask = loadPSTask.then([this](Platform::Array<byte>^ fileData) {
        DX::ThrowIfFailed(
            m_device->CreatePixelShader(
            fileData->Data,
            fileData->Length,
            nullptr,
            &m_pixelShader
            )
            );

        CD3D11_BUFFER_DESC textureProjectionBufferDesc(sizeof(TextureProjectionConstantBuffer), D3D11_BIND_CONSTANT_BUFFER);
        DX::ThrowIfFailed(
            m_device->CreateBuffer(
            &textureProjectionBufferDesc,
            nullptr,
            &m_textureProjectionBuffer
            )
            );
    });

    auto createScene = (createPSTask && createVSTask).then([this] () {

        // Create surface
        VertexPositionColor vertices[] =
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
        samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_MIRROR;
        samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_MIRROR;
        samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_MIRROR;
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

void CostVolumeRenderer::SetStereoTexture(ID3D11ShaderResourceView * left, ID3D11ShaderResourceView * right)
{
    m_textureLeftView = left;
    m_textureRightView = right;
}

void CostVolumeRenderer::RenderCostVolumes(ID3D11DeviceContext1 * context,
                                           ID3D11ShaderResourceView * * images, 
                                           uint8 maxDisparity,
                                           const Texture * (*output)[])
{
    ID3D11RenderTargetView * resultRenderTargets[4];

    UINT stride = sizeof(VertexPositionColor);
    UINT offset = 0;
    context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
    context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    context->IASetInputLayout(m_inputLayout.Get());

    context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
    context->PSSetSamplers(0, 1, m_sampler.GetAddressOf());

    for (int i = 0; i < maxDisparity; i += 4)
    {
        resultRenderTargets[0] = ((*output)[i] = TexturesBuffer->Alloc())->RenderTarget;
        resultRenderTargets[1] = ((*output)[i+1] = TexturesBuffer->Alloc())->RenderTarget;
        resultRenderTargets[2] = ((*output)[i+2] = TexturesBuffer->Alloc())->RenderTarget;
        resultRenderTargets[3] = ((*output)[i+3] = TexturesBuffer->Alloc())->RenderTarget;

        context->PSSetShader(m_pixelShader.Get(), nullptr, 0);
        context->OMSetRenderTargets(4, resultRenderTargets, 0);
        context->PSSetShaderResources(0, 2, images);
        context->DrawIndexed(m_indexCount, 0, 0);
    }
}

void CostVolumeRenderer::_Render(ID3D11DeviceContext1 * context)
{
    /*static bool clearStencil = true;
    const float midnightBlue[] = { 0.098f, 0.098f, 0.439f, 1.000f };

    ID3D11ShaderResourceView * textures[] = 
    {
        m_textureLeftView.Get(),
        m_textureRightView.Get()
    };
    

    context->PSSetShaderResources(0, 2, textures);

    if (clearStencil) 
    {
        for (int i = 0; i < m_resultsCount[0]; ++i)
        {
            context->ClearRenderTargetView(m_resultTargetView[0][i], midnightBlue);
        }

        UINT stride = sizeof(VertexPositionColor);
        UINT offset = 0;
        context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
        context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

        context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        context->IASetInputLayout(m_inputLayout.Get());

        context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
        context->PSSetSamplers(0, 1, m_sampler.GetAddressOf());

        clearStencil = false;
    }

    context->PSSetShader(m_pixelShader.Get(), nullptr, 0);

    for (int i = 0; i < m_resultsCount[0]; i+=4)
    {
        context->OMSetRenderTargets(4, this->GetRenderTargets() + i, 0);
        context->DrawIndexed(m_indexCount, 0, 0);
    }*/
}

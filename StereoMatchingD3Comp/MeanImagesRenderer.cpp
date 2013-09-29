#include "pch.h"
#include "Config.h"
#include "MeanImagesRenderer.h"
#include "ShadersLoader.h"

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
	const D3D11_INPUT_ELEMENT_DESC tmp[] = 
	{
		{ "POSITION",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",  0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};    

	vertexDesc[0].SemanticName = tmp[0].SemanticName;
	vertexDesc[0].SemanticIndex = tmp[0].SemanticIndex;
	vertexDesc[0].Format = tmp[0].Format;
	vertexDesc[0].InputSlot = tmp[0].InputSlot;
	vertexDesc[0].AlignedByteOffset = tmp[0].AlignedByteOffset;
	vertexDesc[0].InputSlotClass = tmp[0].InputSlotClass;
	vertexDesc[0].InstanceDataStepRate = tmp[0].InstanceDataStepRate;

	vertexDesc[1].SemanticName = tmp[1].SemanticName;
	vertexDesc[1].SemanticIndex = tmp[1].SemanticIndex;
	vertexDesc[1].Format = tmp[1].Format;
	vertexDesc[1].InputSlot = tmp[1].InputSlot;
	vertexDesc[1].AlignedByteOffset = tmp[1].AlignedByteOffset;
	vertexDesc[1].InputSlotClass = tmp[1].InputSlotClass;
	vertexDesc[1].InstanceDataStepRate = tmp[1].InstanceDataStepRate;

	auto createVSTask = ShadersLoader::LoadVS("MeanImageVertexShader.cso", vertexDesc, ARRAYSIZE(vertexDesc), m_device.Get(), &m_vertexShader, &m_inputLayout);
	auto createPSTask_Mean_H = ShadersLoader::LoadPS("Mean_PixelShaderH.cso", m_device.Get(), &m_pixelShader_Mean_H);
	auto createPSTask_Mean_W = ShadersLoader::LoadPS("Mean_PixelShaderW.cso", m_device.Get(), &m_pixelShader_Mean_W);
	auto createPSTask_MixChannels = ShadersLoader::LoadPS("MixChannels_PixelShader.cso", m_device.Get(), &m_pixelShader_MixChannels);
	auto createPSTask_Covariance = ShadersLoader::LoadPS("Covariance_PixelShader.cso", m_device.Get(), &m_pixelShader_Covariance);
	auto createPSTask_Variance = ShadersLoader::LoadPS("Variance_PixelShader.cso", m_device.Get(), &m_pixelShader_Variance);
	auto createPSTask_MultiplyChannels = ShadersLoader::LoadPS("MultiplyWages_PixelShader.cso", m_device.Get(), &m_pixelShader_MultiplyChannels);
	auto createPSTask_A = ShadersLoader::LoadPS("A_PixelShader.cso", m_device.Get(), &m_pixelShader_A);
	auto createPSTask_B = ShadersLoader::LoadPS("B_PixelShader.cso", m_device.Get(), &m_pixelShader_B);
	auto createPSTask_Q = ShadersLoader::LoadPS("Q_PixelShader.cso", m_device.Get(), &m_pixelShader_Q);

	auto createScene = (createVSTask && 
						createPSTask_Mean_H && 
						createPSTask_Mean_W && 
						createPSTask_MixChannels && 
						createPSTask_Covariance && 
						createPSTask_Variance && 
						createPSTask_MultiplyChannels && 
						createPSTask_A && 
						createPSTask_B && 
						createPSTask_Q)
		.then([this] () {

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

/* OUTPUT:
*		boxFilter(I[0])
 *		boxFilter(I[1])
 *		boxFilter(I[2])
 *		boxFilter(I[3])
 *		....
 *		boxFilter(I[count-1])
 */
void MeanImagesRenderer::RenderSimple(ID3D11DeviceContext1 * context, 
									  ID3D11ShaderResourceView * * input, 
									  const Texture * (*output)[], 
									  uint8 count)
{
	const Texture * Buffer[] = 
	{
		TexturesBuffer->Alloc(),
		TexturesBuffer->Alloc()
	};

	ID3D11RenderTargetView * tmpRenderTargets[] = 
	{
		Buffer[0]->RenderTarget,
		Buffer[1]->RenderTarget
	};
	ID3D11RenderTargetView * resultRenderTargets[2];

	ID3D11ShaderResourceView * tmpResourceView[] = 
	{
		Buffer[0]->ResourceView,
		Buffer[1]->ResourceView
	};

	ID3D11ShaderResourceView * * incInput = input;

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

	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->PSSetSamplers(0, 1, m_sampler.GetAddressOf());

	for (int i = 0; i < count; i += 2, incInput += 2)
	{
		context->PSSetShader(m_pixelShader_Mean_H.Get(), nullptr, 0);
		context->OMSetRenderTargets( 2, tmpRenderTargets, 0);
		context->PSSetShaderResources(0, 2, incInput);
		context->DrawIndexed(m_indexCount, 0, 0);

		resultRenderTargets[0] = ((*output)[i] = TexturesBuffer->Alloc())->RenderTarget;
		resultRenderTargets[1] = ((*output)[i+1] = TexturesBuffer->Alloc())->RenderTarget;

		context->PSSetShader(m_pixelShader_Mean_W.Get(), nullptr, 0);
		context->OMSetRenderTargets(2, resultRenderTargets, 0);
		context->PSSetShaderResources(0, 2, tmpResourceView);
		context->DrawIndexed(m_indexCount, 0, 0);
	}

	TexturesBuffer->Free(Buffer[0]);
	TexturesBuffer->Free(Buffer[1]);
}

/* OUTPUT:
 *		boxFilter(I * d[0])
 *		boxFilter(I * d[1])
 *		boxFilter(I * d[2])
 *		boxFilter(I * d[3])
 *		....
 *		boxFilter(I * d[count-1])
 */
void MeanImagesRenderer::RenderMultiplied(ID3D11DeviceContext1 * context, 
										  ID3D11ShaderResourceView * image, 
										  ID3D11ShaderResourceView * * wages, 
										  const Texture * (*output)[], 
										  uint8 count)
{
	const Texture * Buffer[] = 
	{
		TexturesBuffer->Alloc(),
		TexturesBuffer->Alloc(),
		TexturesBuffer->Alloc(),
		TexturesBuffer->Alloc(),
		TexturesBuffer->Alloc(),
		TexturesBuffer->Alloc()
	};
	ID3D11RenderTargetView * tmpRenderTargets1[] = 
	{
		Buffer[0]->RenderTarget,
		Buffer[1]->RenderTarget,
		Buffer[2]->RenderTarget,
		Buffer[3]->RenderTarget
	};
	ID3D11ShaderResourceView * tmpResourceView1[] = 
	{
		Buffer[0]->ResourceView,
		Buffer[1]->ResourceView,
		Buffer[2]->ResourceView,
		Buffer[3]->ResourceView
	};

	ID3D11RenderTargetView * tmpRenderTargets2[] = 
	{
		Buffer[4]->RenderTarget,
		Buffer[5]->RenderTarget
	};
	ID3D11ShaderResourceView * tmpResourceView2[] = 
	{
		Buffer[4]->ResourceView,
		Buffer[5]->ResourceView
	};
	ID3D11RenderTargetView * resultRenderTargets[2];

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
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->PSSetSamplers(0, 1, m_sampler.GetAddressOf());

	for (int i = 0; i < count; ++i)
	{
		context->PSSetShader(m_pixelShader_MultiplyChannels.Get(), nullptr, 0);
		context->OMSetRenderTargets(4, tmpRenderTargets1, 0);
		context->PSSetShaderResources(0, 1, &image);
		context->PSSetShaderResources(1, 1, wages+i);
		context->DrawIndexed(m_indexCount, 0, 0);
		context->PSSetShaderResources(1, 0, nullptr);

		for (int j = 0; j < 4; j+=2)
		{
			context->PSSetShader(m_pixelShader_Mean_H.Get(), nullptr, 0);
			context->OMSetRenderTargets(2, tmpRenderTargets2, 0);
			context->PSSetShaderResources(0, 2, tmpResourceView1 + j);
			context->DrawIndexed(m_indexCount, 0, 0);

			resultRenderTargets[0] = ((*output)[i*4 + j] = TexturesBuffer->Alloc())->RenderTarget;
			resultRenderTargets[1] = ((*output)[i*4 + j + 1] = TexturesBuffer->Alloc())->RenderTarget;

			context->PSSetShader(m_pixelShader_Mean_W.Get(), nullptr, 0);
			context->OMSetRenderTargets(2, resultRenderTargets, 0);
			context->PSSetShaderResources(0, 2, tmpResourceView2);
			context->DrawIndexed(m_indexCount, 0, 0);
		}
	}

	TexturesBuffer->Free(Buffer[0]);
	TexturesBuffer->Free(Buffer[1]);
	TexturesBuffer->Free(Buffer[2]);
	TexturesBuffer->Free(Buffer[3]);
	TexturesBuffer->Free(Buffer[4]);
	TexturesBuffer->Free(Buffer[5]);
}

/* OUTPUT:
 *		boxFilter(I(RR,RG,RB)[0])
 *		boxFilter(I(GG,GB,BB)[0])
 *		boxFilter(I(RR,RG,RB)[1])
 *		boxFilter(I(GG,GB,BB)[1])
 *		....
 *		boxFilter(I(RR,RG,RB)[count-1])
 *		boxFilter(I(GG,GB,BB)[count-1])
 *
 * WHERE:
 *		I(RR,RG,RB) & I(GG,GB,BB) :
 *			an images where channels are defined as multiplication of input images channels,
 *			i.e. RR -> channel R multiplied by channel R of the same image.
 */
void MeanImagesRenderer::RenderVariance(ID3D11DeviceContext1* context, 
										ID3D11ShaderResourceView * * images, 
										const Texture * * meanImages, 
										const Texture * (*output)[], 
										uint8 count)
{
	const Texture * Buffer[] = 
	{
		TexturesBuffer->Alloc(),
		TexturesBuffer->Alloc(),
		TexturesBuffer->Alloc(),
		TexturesBuffer->Alloc(),
		TexturesBuffer->Alloc(),
		TexturesBuffer->Alloc()
	};

	ID3D11RenderTargetView * mixChannelsRenderTarget[] = 
	{
		Buffer[0]->RenderTarget,
		Buffer[1]->RenderTarget,
		Buffer[2]->RenderTarget,
		Buffer[3]->RenderTarget
	};
	ID3D11ShaderResourceView * mixChannelsResourceView[] = 
	{
		Buffer[0]->ResourceView,
		Buffer[1]->ResourceView,
		Buffer[2]->ResourceView,
		Buffer[3]->ResourceView
	};
	ID3D11RenderTargetView * tmpBoxHRenderTarget[] = 
	{
		Buffer[4]->RenderTarget,
		Buffer[5]->RenderTarget,
	};
	ID3D11ShaderResourceView * tmpBoxHResourceView[] = 
	{
		Buffer[4]->ResourceView,
		Buffer[5]->ResourceView,
	};
	ID3D11RenderTargetView * resultRenderTargets[2];


	UINT stride = sizeof(VertexPosition);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetInputLayout(m_inputLayout.Get());
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->PSSetSamplers(0, 1, m_sampler.GetAddressOf());

	ID3D11ShaderResourceView * * incInput = images;
	for (int i = 0; i < count; i += 2, incInput += 2)
	{
		context->PSSetShader(m_pixelShader_MixChannels.Get(), nullptr, 0);
		context->OMSetRenderTargets(4, mixChannelsRenderTarget, 0);
		context->PSSetShaderResources(0, 2, incInput);
		context->DrawIndexed(m_indexCount, 0, 0);

		for (int j = 0; j < 4; j += 2)
		{
			context->PSSetShader(m_pixelShader_Mean_H.Get(), nullptr, 0);
			context->OMSetRenderTargets(2, tmpBoxHRenderTarget, 0);
			context->PSSetShaderResources(0, 2, mixChannelsResourceView + j);
			context->DrawIndexed(m_indexCount, 0, 0);

			resultRenderTargets[0] = ((*output)[i*4 + j] = TexturesBuffer->Alloc())->RenderTarget;
			resultRenderTargets[1] = ((*output)[i*4 + j+1] = TexturesBuffer->Alloc())->RenderTarget;

			context->PSSetShader(m_pixelShader_Mean_W.Get(), nullptr, 0);
			context->OMSetRenderTargets(2, resultRenderTargets, 0);
			context->PSSetShaderResources(0, 2, tmpBoxHResourceView);
			context->DrawIndexed(m_indexCount, 0, 0);
		}
	}

	TexturesBuffer->Free(Buffer[0]);
	TexturesBuffer->Free(Buffer[1]);
	TexturesBuffer->Free(Buffer[2]);
	TexturesBuffer->Free(Buffer[3]);
	TexturesBuffer->Free(Buffer[4]);
	TexturesBuffer->Free(Buffer[5]);
}
 
/* OUTPUT:
*		boxFilter(I*d[0]) - boxFilter(I) * d[0]
*		boxFilter(I*d[1]) - boxFilter(I) * d[1]
*		boxFilter(I*d[2]) - boxFilter(I) * d[2]
*		boxFilter(I*d[3]) - boxFilter(I) * d[3]
*		....
*		boxFilter(I*d[3]) - boxFilter(I) * d[3]
 *
 * WHERE:
 *		I(RR,RG,RB) & I(GG,GB,BB) :
 *			an images where channels are defined as multiplication of input images channels,
 *			i.e. RR -> channel R multiplied by channel R of the same image.
 */
void MeanImagesRenderer::RenderCovariance(ID3D11DeviceContext1 * context,
										  ID3D11ShaderResourceView * meanImage, 
										  ID3D11ShaderResourceView * * meanCostVolumes, 
										  ID3D11ShaderResourceView * * meanImageCostVolumes, 
										  const Texture * (*output)[], 
										  uint8 count)
{
	ID3D11RenderTargetView * resultRenderTargets[4];

	UINT stride = sizeof(VertexPosition);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetInputLayout(m_inputLayout.Get());
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->PSSetSamplers(0, 1, m_sampler.GetAddressOf());
	
	ID3D11ShaderResourceView * incInput[6];
	incInput[0] = meanImage;
	for (int i = 0; i < count; i += 4)
	{
		incInput[1] = meanCostVolumes[i / 4];
		incInput[2] = meanImageCostVolumes[i];
		incInput[3] = meanImageCostVolumes[i + 1];
		incInput[4] = meanImageCostVolumes[i + 2];
		incInput[5] = meanImageCostVolumes[i + 3];

		resultRenderTargets[0] = ((*output)[i] = TexturesBuffer->Alloc())->RenderTarget;
		resultRenderTargets[1] = ((*output)[i + 1] = TexturesBuffer->Alloc())->RenderTarget;
		resultRenderTargets[2] = ((*output)[i + 2] = TexturesBuffer->Alloc())->RenderTarget;
		resultRenderTargets[3] = ((*output)[i + 3] = TexturesBuffer->Alloc())->RenderTarget;

		context->PSSetShader(m_pixelShader_Covariance.Get(), nullptr, 0);
		context->OMSetRenderTargets(4, resultRenderTargets, 0);
		context->PSSetShaderResources(0, 6, incInput);
		context->DrawIndexed(m_indexCount, 0, 0);
	}
}

void MeanImagesRenderer::RenderQ(ID3D11DeviceContext * context, 
									  ID3D11ShaderResourceView * * meanA, 
									  ID3D11ShaderResourceView * image, 
									  ID3D11ShaderResourceView * * meanB, 
									  const Texture * (*output)[], 
									  uint8 count)
{
	ID3D11RenderTargetView * resultRenderTargets[4];

	ID3D11ShaderResourceView * shaderResourceViews1[1];
	shaderResourceViews1[0] = image;
	ID3D11ShaderResourceView * shaderResourceViews2[4];
	ID3D11ShaderResourceView * shaderResourceViews3[4];

	UINT stride = sizeof(VertexPosition);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetInputLayout(m_inputLayout.Get());
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->PSSetSamplers(0, 1, m_sampler.GetAddressOf());
	context->PSSetShader(m_pixelShader_Q.Get(), nullptr, 0);

	for (int i = 0; i < count; i += 4)
	{
		shaderResourceViews2[0] = meanA[i];
		shaderResourceViews2[1] = meanA[i + 1];
		shaderResourceViews2[2] = meanA[i + 2];
		shaderResourceViews2[3] = meanA[i + 3];

		shaderResourceViews3[0] = meanB[i];
		shaderResourceViews3[1] = meanB[i + 1];
		shaderResourceViews3[2] = meanB[i + 2];
		shaderResourceViews3[3] = meanB[i + 3];

		resultRenderTargets[0] = ((*output)[i] = TexturesBuffer->Alloc())->RenderTarget;
		resultRenderTargets[1] = ((*output)[i + 1] = TexturesBuffer->Alloc())->RenderTarget;
		resultRenderTargets[2] = ((*output)[i + 2] = TexturesBuffer->Alloc())->RenderTarget;
		resultRenderTargets[3] = ((*output)[i + 3] = TexturesBuffer->Alloc())->RenderTarget;

		context->OMSetRenderTargets(4, resultRenderTargets, 0);
		context->PSSetShaderResources(0, 1, shaderResourceViews1);
		context->PSSetShaderResources(1, 4, shaderResourceViews2);
		context->PSSetShaderResources(2, 4, shaderResourceViews3);
		context->DrawIndexed(m_indexCount, 0, 0);
	}

	context->PSSetShaderResources(1, 0, nullptr);
	context->PSSetShaderResources(2, 0, nullptr);
}

/* Input:
 *   N x convolution texture
 *   2 x variance textures
 * Output:
 *   N x 'a' texture
 */
void MeanImagesRenderer::RenderA(ID3D11DeviceContext * context, 
								 ID3D11ShaderResourceView * * convolution, 
								 ID3D11ShaderResourceView * * variance, 
								 const Texture * (*output)[], 
								 uint8 count)
{
	ID3D11RenderTargetView * resultRenderTargets[4];

	ID3D11ShaderResourceView * shaderResourceViews1[2];
	shaderResourceViews1[0] = variance[0];
	shaderResourceViews1[1] = variance[1];
	ID3D11ShaderResourceView * shaderResourceViews2[4];

	UINT stride = sizeof(VertexPosition);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetInputLayout(m_inputLayout.Get());
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->PSSetSamplers(0, 1, m_sampler.GetAddressOf());
	context->PSSetShader(m_pixelShader_A.Get(), nullptr, 0);
	context->PSSetShaderResources(0, 2, shaderResourceViews1);

	for (int i = 0; i < count; i += 4)
	{
		shaderResourceViews2[0] = convolution[i];
		shaderResourceViews2[1] = convolution[i + 1];
		shaderResourceViews2[2] = convolution[i + 2];
		shaderResourceViews2[3] = convolution[i + 3];

		resultRenderTargets[0] = ((*output)[i] = TexturesBuffer->Alloc())->RenderTarget;
		resultRenderTargets[1] = ((*output)[i + 1] = TexturesBuffer->Alloc())->RenderTarget;
		resultRenderTargets[2] = ((*output)[i + 2] = TexturesBuffer->Alloc())->RenderTarget;
		resultRenderTargets[3] = ((*output)[i + 3] = TexturesBuffer->Alloc())->RenderTarget;

		context->OMSetRenderTargets(4, resultRenderTargets, 0);
		context->PSSetShaderResources(1, 4, shaderResourceViews2);
		context->DrawIndexed(m_indexCount, 0, 0);
	}

	context->PSSetShaderResources(1, 0, nullptr);
}

/* Input:
 *   N x boxFilter(d)
 *   N x 'a' texture
 *   1 x mean image
 * Output:
 *   N x 'b' texture
 */
void MeanImagesRenderer::RenderB(ID3D11DeviceContext * context, 
								 ID3D11ShaderResourceView * * meanD, 
								 ID3D11ShaderResourceView * * a, 
								 ID3D11ShaderResourceView * meanImage, 
								 const Texture * (*output)[], 
								 uint8 count)
{
	ID3D11RenderTargetView * resultRenderTargets[4];

	ID3D11ShaderResourceView * shaderResourceViews1[1];
	shaderResourceViews1[0] = meanImage;
	ID3D11ShaderResourceView * shaderResourceViews2[1];
	ID3D11ShaderResourceView * shaderResourceViews3[6];

	UINT stride = sizeof(VertexPosition);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, m_vertexBuffer.GetAddressOf(), &stride, &offset);
	context->IASetIndexBuffer(m_indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);
	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	context->IASetInputLayout(m_inputLayout.Get());
	context->VSSetShader(m_vertexShader.Get(), nullptr, 0);
	context->PSSetSamplers(0, 1, m_sampler.GetAddressOf());
	context->PSSetShader(m_pixelShader_B.Get(), nullptr, 0);
	context->PSSetShaderResources(0, 1, shaderResourceViews1);

	for (int i = 0; i < count; i += 4)
	{
		shaderResourceViews2[0] = meanD[i / 4];

		shaderResourceViews3[0] = a[i];
		shaderResourceViews3[1] = a[i + 1];
		shaderResourceViews3[2] = a[i + 2];
		shaderResourceViews3[3] = a[i + 3];

		resultRenderTargets[0] = ((*output)[i] = TexturesBuffer->Alloc())->RenderTarget;
		resultRenderTargets[1] = ((*output)[i + 1] = TexturesBuffer->Alloc())->RenderTarget;
		resultRenderTargets[2] = ((*output)[i + 2] = TexturesBuffer->Alloc())->RenderTarget;
		resultRenderTargets[3] = ((*output)[i + 3] = TexturesBuffer->Alloc())->RenderTarget;

		context->OMSetRenderTargets(4, resultRenderTargets, 0);
		context->PSSetShaderResources(1, 1, shaderResourceViews2);
		context->PSSetShaderResources(2, 4, shaderResourceViews3);
		context->DrawIndexed(m_indexCount, 0, 0);
	}

	context->PSSetShaderResources(1, 0, nullptr);
	context->PSSetShaderResources(2, 0, nullptr);
}

void MeanImagesRenderer::_Render(ID3D11DeviceContext1 * context)
{
	static bool clearStencil = true;
	const float midnightBlue[] = { 0.098f, 0.098f, 0.439f, 1.000f };

	//if (clearStencil) 
	//{
	//	for (int i = 0; i < m_resultsCount[0]; ++i)
	//	{
	//		context->ClearRenderTargetView(
	//			m_resultTargetView[0][i],
	//			midnightBlue
	//			);
	//	}

	//	UINT stride = sizeof(VertexPosition);
	//	UINT offset = 0;
	//	context->IASetVertexBuffers(
	//		0,
	//		1,
	//		m_vertexBuffer.GetAddressOf(),
	//		&stride,
	//		&offset
	//		);

	//	context->IASetIndexBuffer(
	//		m_indexBuffer.Get(),
	//		DXGI_FORMAT_R16_UINT,
	//		0
	//		);

	//	context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//	context->IASetInputLayout(m_inputLayout.Get());

	//	context->VSSetShader(
	//		m_vertexShader.Get(),
	//		nullptr,
	//		0
	//		);

	//	context->PSSetSamplers(
	//		0, 
	//		1, 
	//		m_sampler.GetAddressOf()
	//		);

	//	clearStencil = false;
	//}

	//this->_RenderCostVolumes(context);
	////this->_RenderImageCostVolumes(context);
}

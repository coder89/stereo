#pragma once

#include "Direct3DBase.h"

// This class renders a simple spinning cube.
class MeanImagesRenderer : public AbstractProcessingStage
{
	struct VertexPosition
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 tex;
	};

public:

	MeanImagesRenderer(ID3D11Device1 * device, Windows::Foundation::Size viewportSize);

	// Sets textures
	void SetStereoTexture(ID3D11ShaderResourceView * left, ID3D11ShaderResourceView * right);

	// Sets cost volume textures
	void SetCostVolume(ID3D11ShaderResourceView * * costVolume, uint8 count);
	
	/* Render mean image for all input images.
	 * Caller is responsible for releasing shader resource handlers.
	 */
	void RenderSimple(ID3D11DeviceContext1 * context, 
					  ID3D11ShaderResourceView * * input, 
					  const Texture * (*output)[], 
					  uint8 count);
	
	/* Render mean image for input image multiplied by wages. 
	 * 1 input image & 1 wages image results in 4 output images.
	 * Each wage is stored in separate channel of wages texture - so 4 wages per image.
	 * Caller is responsible for releasing shader resource handlers.
	 */
	void RenderMultiplied(ID3D11DeviceContext1 * context, 
					 	  ID3D11ShaderResourceView * image, 
						  ID3D11ShaderResourceView * * wages, 
						  const Texture * (*output)[], 
						  uint8 count);
	
	/* Render variance image for each input image. 
	 * 1 input image results in 1 output images.
	 * Caller is responsible for releasing shader resource handlers.
	 */
	void RenderVariance(ID3D11DeviceContext1* context, 
						ID3D11ShaderResourceView * * images, 
						const Texture * * meanImages, 
						const Texture * (*output)[], 
						uint8 count);
	
	/* Render covariance of input images.
	 * Caller is responsible for releasing shader resource handlers.
	 */
	void RenderCovariance(ID3D11DeviceContext1 * context,
							ID3D11ShaderResourceView * meanImage, 
							ID3D11ShaderResourceView * * meanCostVolumes, 
							ID3D11ShaderResourceView * * meanImageCostVolumes, 
							const Texture * (*output)[], 
							uint8 count);

private:
	
	D3D11_INPUT_ELEMENT_DESC vertexDesc[2];

	// Initialize rendering stage
	Concurrency::task<void> _Initialize();

	// [overriden] Renders complete stage
	void _Render(ID3D11DeviceContext1 * context);
	// Input resource views
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureLeftView;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureRightView;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_costVolume[MAX_DISPARITY / 4];
	
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;
	
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;

	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader_Mean_H;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader_Mean_W;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader_MultiplyChannels;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader_MixChannels;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader_Covariance;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader_Variance;
	
	uint32 m_indexCount;
	uint32 m_vertexCount;
};

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

private:

	// Initialize rendering stage
	Concurrency::task<void> _Initialize();

	// [overriden] Renders complete stage
	void _Render(ID3D11DeviceContext1 * context);
	void _RenderImages(ID3D11DeviceContext1 * context);
	void _RenderCostVolumes(ID3D11DeviceContext1 * context);
	void _RenderImageCostVolumes(ID3D11DeviceContext1 * context);

	// Input resource views
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureLeftView;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureRightView;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_costVolume[MAX_DISPARITY / 4];
	
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;
	
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;

	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader_CV_H;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader_CV_W;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader_MUL;
	
	uint32 m_indexCount;
	uint32 m_vertexCount;
};

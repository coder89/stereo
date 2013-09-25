#pragma once

#include "Direct3DBase.h"
#include "AbstractProcessingStage.h"

// This class renders a simple spinning cube.
class CostVolumeRenderer : public AbstractProcessingStage
{
	__declspec(align(16)) struct TextureProjectionConstantBuffer
	{
		float disparity;	// Used to calculate cost volume for different disparities
	};

	struct InstanceBuffer
	{
		DirectX::XMFLOAT3 pos;
		//float disparity;	// Used to calculate cost volume for different disparities
	};

	struct VertexPositionColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 tex;
	};

public:

	CostVolumeRenderer(ID3D11Device1 * device, Windows::Foundation::Size viewportSize);

	// Sets textures
	void SetStereoTexture(ID3D11ShaderResourceView * left, ID3D11ShaderResourceView * right);


private:

	// Initialize rendering stage
	Concurrency::task<void> _Initialize();

	// [overriden] Renders complete stage
	void _Render(ID3D11DeviceContext1 * context);

	// Input resource views
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureLeftView;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureRightView;
	
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;
	
	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;

	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantParameterBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_textureProjectionBuffer;
	
	uint32 m_indexCount;
	uint32 m_vertexCount;
	TextureProjectionConstantBuffer m_textureProjectionBufferData;
};

#pragma once

#include "Direct3DBase.h"
// This class renders a simple spinning cube.
class CostVolumeRenderer 
{
	struct ConstantParametersBuffer
	{
		float alpha;
		float Tc;
		float Tg;
		float dx;			// Used in gradient calculation
	};

	struct TextureProjectionConstantBuffer
	{
		float disparity;	// Used to calculate cost volume for different disparities
		float _empty1;
		float _empty2;
		float _empty3;
	};

	struct VertexPositionColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT2 tex;
	};

public:

	CostVolumeRenderer(ID3D11Device1 * device);

	void Initialize(uint32 width, uint32 height);
	void SetLeftTexture(ID3D11Texture2D * texture, ID3D11ShaderResourceView * textureView);
	void SetRightTexture(ID3D11Texture2D * texture, ID3D11ShaderResourceView * textureView);
	void Render(ID3D11DeviceContext * context);

	uint32 GetWidth()
	{
		return m_width;
	}
	uint32 GetHeight()
	{
		return m_height;
	}
	ID3D11ShaderResourceView * * GetShaderResourceView();
	bool IsInitialized()
	{
		return m_loadingComplete;
	}

private:
	
	Microsoft::WRL::ComPtr<ID3D11Device1> m_d3dDevice;

	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_sampler;

	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_textureLeft;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureLeftView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_textureRight;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_textureRightView;

	Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_indexBuffer;

	Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixelShader;

	Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantParameterBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_textureProjectionBuffer;
	
	Microsoft::WRL::ComPtr<ID3D11Texture2D> m_renderTarget;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_renderTargetView;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> m_depthStencilView;

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_renderShaderResourceView;
	
	CD3D11_VIEWPORT m_viewport;
	uint32 m_indexCount;
	bool m_loadingComplete;
	uint32 m_width;
	uint32 m_height;
	ConstantParametersBuffer m_constantParametersBufferData;
	TextureProjectionConstantBuffer m_textureProjectionBufferData;
};

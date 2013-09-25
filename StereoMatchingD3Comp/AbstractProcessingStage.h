#include "Direct3DBase.h"
#include "Config.h"

class AbstractProcessingStage abstract
{
public:

	// Ctor
	AbstractProcessingStage(ID3D11Device1 * device, Windows::Foundation::Size viewportSize)
	{
		m_device = device;
		m_viewportSize = viewportSize;
		m_initialized = false;
	}

	// Initializer task
	Concurrency::task<void> Initialize()
	{
		return _Initialize().then([this] ()
		{
			m_initialized = true;
		});
	}

	// Check if stage is initialized
	bool IsInitialized()
	{
		return m_initialized;
	}

	// Viewport height
	float GetHeight()
	{
		return m_viewportSize.Height;
	}
	
	// Viewport width
	float GetWidth()
	{
		return m_viewportSize.Width;
	}

	// Viewport size
	Windows::Foundation::Size GetSize()
	{
		return m_viewportSize;
	}

	// Rendering result view
	ID3D11ShaderResourceView * * GetResultViews()
	{
		return m_resultResourceView;
	};

	// Rendering result views count
	uint8 GetResultCount()
	{
		return m_resultsCount;
	};

	// Performs stage rendering
	void Render(ID3D11DeviceContext1 * context)
	{
		if (!m_initialized)
		{
			return;
		}

		this->_Render(context);
	}

protected:

	// Rendering result view
	ID3D11RenderTargetView * * GetRenderTargets()
	{
		return m_resultTargetView;
	};

	// Implement this method with stage initialization code
	virtual Concurrency::task<void> _Initialize() = 0;

	// Implement this method with stage rendering code
	virtual void _Render(ID3D11DeviceContext1 * context) = 0;

	// Invoke this method in stage initialization code to 
	// initialize rendering target structures
	void SetTargetResource(uint8 count, ID3D11Texture2D * * target, DXGI_FORMAT targetFormat)
	{
		m_resultsCount = count;	

		for (int i = 0; i < count; ++i)
		{
			m_resultResource[i] = target[i];

			D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
			D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;

			renderTargetViewDesc.Format = targetFormat;
			renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
			renderTargetViewDesc.Texture2D.MipSlice = 0;

			DX::ThrowIfFailed(
				m_device->CreateRenderTargetView(
				m_resultResource[i],
				&renderTargetViewDesc,
				&(m_resultTargetView[i]))
				);	

			shaderResourceViewDesc.Format = targetFormat;
			shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
			shaderResourceViewDesc.Texture2D.MostDetailedMip = 0;
			shaderResourceViewDesc.Texture2D.MipLevels = 1;

			DX::ThrowIfFailed(
				m_device->CreateShaderResourceView(
				m_resultResource[i],
				&shaderResourceViewDesc,
				&(m_resultResourceView[i]))
				);
		}

		// TODO: Sharing depth scencil??
	}
	
	// Invoke this method in stage initialization code to 
	// initialize rendering target structures
	// NOTE: Not supported on WP8 level_9_3
	/*void SetTargetResource(ID3D11Texture3D * target, DXGI_FORMAT targetFormat)
	{
		m_resultResource = target;
		
		D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc;
		D3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc;
		
		renderTargetViewDesc.Format = targetFormat;
		renderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE3D;
		renderTargetViewDesc.Texture3D.FirstWSlice = 0;
		renderTargetViewDesc.Texture3D.MipSlice = 0;
		renderTargetViewDesc.Texture3D.WSize = -1; // use all slices

		DX::ThrowIfFailed(
			m_device->CreateRenderTargetView(
			m_resultResource.Get(),
			&renderTargetViewDesc,
			&m_resultTargetView)
			);	

		shaderResourceViewDesc.Format = targetFormat;
		shaderResourceViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE3D;
		shaderResourceViewDesc.Texture3D.MostDetailedMip = 0;
		shaderResourceViewDesc.Texture3D.MipLevels = 1;

		DX::ThrowIfFailed(
			m_device->CreateShaderResourceView(
			m_resultResource.Get(),
			&shaderResourceViewDesc,
			&m_resultResourceView)
			);

		// TODO: Sharing depth scencil??
	}
	*/

	// Direct3D device
	Microsoft::WRL::ComPtr<ID3D11Device> m_device;

	// Result targets
	uint8 m_resultsCount;
	ID3D11Resource * m_resultResource[MAX_DISPARITY / 4];
	ID3D11ShaderResourceView * m_resultResourceView[MAX_DISPARITY / 4];
	ID3D11RenderTargetView * m_resultTargetView[MAX_DISPARITY / 4];

private:

	// Other stuff
	bool m_initialized;
	Windows::Foundation::Size m_viewportSize;

};
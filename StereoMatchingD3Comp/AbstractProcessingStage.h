#pragma once

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

	// Implement this method with stage initialization code
	virtual Concurrency::task<void> _Initialize() = 0;

	// Implement this method with stage rendering code
	virtual void _Render(ID3D11DeviceContext1 * context) = 0;

	// Direct3D device
	Microsoft::WRL::ComPtr<ID3D11Device> m_device;

private:

	// Other stuff
	bool m_initialized;
	Windows::Foundation::Size m_viewportSize;

};
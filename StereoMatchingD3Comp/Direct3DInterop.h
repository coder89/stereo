#pragma once

#include "pch.h"
#include "BasicTimer.h"
#include "CubeRenderer.h"
#include <DrawingSurfaceNative.h>

namespace StereoMatchingD3Comp
{

	public delegate void RequestAdditionalFrameHandler();
	public delegate void RecreateSynchronizedTextureHandler();

	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Direct3DInterop sealed : public Windows::Phone::Input::Interop::IDrawingSurfaceManipulationHandler
	{
	public:
		Direct3DInterop();

		Windows::Phone::Graphics::Interop::IDrawingSurfaceContentProvider^ CreateContentProvider();

		// IDrawingSurfaceManipulationHandler
		virtual void SetManipulationHost(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ manipulationHost);

		event RequestAdditionalFrameHandler^ RequestAdditionalFrame;
		event RecreateSynchronizedTextureHandler^ RecreateSynchronizedTexture;

		property Windows::Foundation::Size WindowBounds;
		property Windows::Foundation::Size NativeResolution;
		property Windows::Foundation::Size RenderResolution
		{
			Windows::Foundation::Size get(){ return m_renderResolution; }
			void set(Windows::Foundation::Size renderResolution);
		}

	protected:
		// Event Handlers
		void OnPointerPressed(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);
		void OnPointerMoved(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);
		void OnPointerReleased(Windows::Phone::Input::Interop::DrawingSurfaceManipulationHost^ sender, Windows::UI::Core::PointerEventArgs^ args);

	internal:
		HRESULT STDMETHODCALLTYPE Connect(_In_ IDrawingSurfaceRuntimeHostNative* host);
		void STDMETHODCALLTYPE Disconnect();
		HRESULT STDMETHODCALLTYPE PrepareResources(_In_ const LARGE_INTEGER* presentTargetTime, _Out_ BOOL* contentDirty);
		HRESULT STDMETHODCALLTYPE GetTexture(_In_ const DrawingSurfaceSizeF* size, _Inout_ IDrawingSurfaceSynchronizedTextureNative** synchronizedTexture, _Inout_ DrawingSurfaceRectF* textureSubRectangle);
		ID3D11Texture2D* GetTexture();

	private:
		CubeRenderer^ m_renderer;
		BasicTimer^ m_timer;
		Windows::Foundation::Size m_renderResolution;
	};

}

#pragma once
#include "pch.h" 
#include "AppResourceManager.h" 
#include <dwrite.h>
#pragma comment(lib, "dwrite.lib")

namespace Resource
{
	class D2DResourceManager
	{
	public:
		static shared_ptr<D2DResourceManager> Get()
		{
			static shared_ptr<D2DResourceManager> instance(new D2DResourceManager());

			return instance;
		}
		virtual ~D2DResourceManager() = default;

		void initialize();

		const ComPtr<ID3D11Device>& getDevice() { return device; }
		const ComPtr<ID2D1DeviceContext>& getContext() { return context; }
		const ComPtr<IWICImagingFactory>& getFactory() { return factory; }
		const ComPtr<IDXGISwapChain1>& getSwapChain() { return m_SwapChain; }

		// RectAngle 
		const ComPtr<ID2D1HwndRenderTarget> getRenderTarget() { return m_renderTarget; }
		void setRenderTarget(const ComPtr<ID2D1HwndRenderTarget>& target) { m_renderTarget = target; }

		const ComPtr<ID2D1SolidColorBrush> getBrush() { return m_brush; }
		void setBrush(const ComPtr<ID2D1SolidColorBrush>& brush) { m_brush = brush; }

		void setBrushColor(const D2D1::ColorF color) { m_brush->SetColor(color);}

		// Text  
		const ComPtr<IDWriteTextFormat> getTextFormat() { return m_writeTextFormat; }

	public:
		D2DResourceManager();
		shared_ptr<AppResourceManager> m_windowResource;

		ComPtr<ID3D11Device> device;
		ComPtr<ID2D1DeviceContext> context;
		ComPtr<IWICImagingFactory> factory;

		// 그리려는 타겟 
		ComPtr<ID2D1HwndRenderTarget> m_renderTarget;
		ComPtr<ID2D1SolidColorBrush>	 m_brush;

		// 비트맵 리소스를 관리하는 자원
		ComPtr<ID2D1Bitmap1>			m_d2dBitmap;
		ComPtr<IDXGISwapChain1>			m_SwapChain;

		// Text 를 출력하기 위한 Factory 와 format 
		ComPtr<IDWriteFactory> m_writeFactory;
		ComPtr<IDWriteTextFormat> m_writeTextFormat;

	};
}



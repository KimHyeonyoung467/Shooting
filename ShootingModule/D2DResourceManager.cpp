#include "pch.h"
#include "D2DResourceManager.h"

namespace Resource
{
	D2DResourceManager::D2DResourceManager() : m_windowResource(AppResourceManager::Get())
	{

	}

	void D2DResourceManager::initialize()
	{
		HRESULT hr;

		// D3D11 디바이스 생성
		D3D_FEATURE_LEVEL featureLevel;
		D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0 };
		D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
			D3D11_CREATE_DEVICE_BGRA_SUPPORT, levels, 1,
			D3D11_SDK_VERSION, device.GetAddressOf(), &featureLevel, nullptr);

		// D2D 팩토리 및 디바이스
		ComPtr<ID2D1Factory8> d2dFactory;
		D2D1_FACTORY_OPTIONS options = {};
		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, options, d2dFactory.GetAddressOf());

		// Rect 그리기 위한 factory RenderTarget 설정 
		RECT rc;
		GetClientRect(m_windowResource->getHwnd(), &rc);
		d2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(m_windowResource->getHwnd(), D2D1::SizeU(rc.right, rc.bottom)),
			m_renderTarget.ReleaseAndGetAddressOf());

		ComPtr<IDXGIDevice> dxgiDevice;
		device.As(&dxgiDevice);

		ComPtr<ID2D1Device7> d2dDevice;
		d2dFactory->CreateDevice((dxgiDevice.Get()), d2dDevice.GetAddressOf());
		d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, context.GetAddressOf());

		ComPtr<IDXGIFactory7> dxgiFactory;
		CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));

		// Create WIC factory
		hr = CoCreateInstance(CLSID_WICImagingFactory,
			NULL, CLSCTX_INPROC_SERVER,
			__uuidof(factory),
			(void**)factory.GetAddressOf());

		// 그리기 위한 brush 설정 
		hr = context->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black),
			m_brush.GetAddressOf());

		// Text 를 위한 Factory 생성 및 Format 생성 
		DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(m_writeFactory),
			reinterpret_cast<IUnknown**> (m_writeFactory.GetAddressOf())
		);

		//DwiteFactory 의 형태 
		m_writeFactory->CreateTextFormat(
			L"Cooper", // Font name 
			nullptr,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			15.0f,   // Font Size
			L"", //locale
			&m_writeTextFormat
		);

		// 텍스트를 수평 및 수직으로 중앙에 맞춥니다.
		m_writeTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		m_writeTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	
		// SwapChain 생성
		DXGI_SWAP_CHAIN_DESC1 scDesc = {};
		scDesc.Width = m_windowResource->getWidth();
		scDesc.Height = m_windowResource->getHeight();
		scDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		scDesc.SampleDesc.Count = 1;
		scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		scDesc.BufferCount = 2;
		scDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		dxgiFactory->CreateSwapChainForHwnd(device.Get(), m_windowResource->getHwnd(), &scDesc, nullptr, nullptr, m_SwapChain.GetAddressOf());

		// 백버퍼를 타겟으로 설정
		ComPtr<IDXGISurface> backBuffer;
		m_SwapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
		D2D1_BITMAP_PROPERTIES1 bmpProps = D2D1::BitmapProperties1(
			D2D1_BITMAP_OPTIONS_TARGET | D2D1_BITMAP_OPTIONS_CANNOT_DRAW,
			D2D1::PixelFormat(scDesc.Format, D2D1_ALPHA_MODE_PREMULTIPLIED)
		);
		// D2D1 비트맵 생성
		context->CreateBitmapFromDxgiSurface(backBuffer.Get(), &bmpProps, m_d2dBitmap.GetAddressOf());
		context->SetTarget(m_d2dBitmap.Get());
	}


}

#include "pch.h"
#include "Application.h"

void ConsolePrint()
{
	AllocConsole();

	// C 런타임 stdout/stderr 리다이렉트
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	freopen_s(&fp, "CONOUT$", "w", stderr);

	// C++ 스트림도 동기화
	std::ios::sync_with_stdio(true);

	// 테스트
	std::cout << "콘솔과 Direct2D 윈도우를 동시에 사용합니다.\0\n";
}

Application::Application() : m_appResource(Resource::AppResourceManager::Get()),
m_d2DResource(Resource::D2DResourceManager::Get())
{
}

Application::~Application()
{
	std::cout.unsetf(std::ios::boolalpha);
}

void Application::Initialize()
{
	// bool 타입 변수를 true / false 로 콘솔창에 띄우기 
	std::cout.setf(std::ios::boolalpha);

	m_appResource->WindowInitialize();
	m_d2DResource->initialize();
	ConsolePrint();

	Time::InitTime();


}

void Application::Run()
{
	MSG msg = {};
	bool isquit = true;

	while (isquit == true)
	{
		while (msg.message != WM_QUIT && PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				return;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		// 렌더 호출  
		update();
		Render();
	}
}

void Application::update()
{
	Time::updateTime();

}

void Application::Render()
{
	beginDraw(D2D1::ColorF::Black);

}
void Application::beginDraw(const D2D1::ColorF& color)
{
	m_d2DResource->getContext()->BeginDraw();
	m_d2DResource->getContext()->Clear(color);
}

void Application::endDraw()
{
	m_d2DResource->getContext()->EndDraw();
	m_d2DResource->getSwapChain()->Present(1, 0);
}

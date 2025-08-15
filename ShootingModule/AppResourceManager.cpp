#include "pch.h"
#include "AppResourceManager.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


namespace Resource
{

	void AppResourceManager::WindowInitialize()
	{
		CoInitialize(nullptr);
		wchar_t szPath[MAX_PATH]{};

		GetModuleFileNameW(nullptr, szPath, MAX_PATH);
		m_modulePath = szPath;

		GetCurrentDirectoryW(MAX_PATH, szPath);
		m_workingPath = szPath;

		m_hInstance = GetModuleHandleW(nullptr);
		m_hCursor = m_hCursor != nullptr ? m_hCursor : LoadCursorW(NULL, IDC_ARROW);

		WNDCLASSEX wc{};
		wc.cbSize = sizeof(WNDCLASSEXW);
		wc.style = m_classStyle;
		wc.lpfnWndProc = WndProc;
		wc.hInstance = m_hInstance;
		wc.lpszClassName = m_className.c_str();
		wc.hCursor = m_hCursor;
		wc.hIcon = m_hIcon;
		wc.hCursor = m_hCursor;
		wc.hIconSm = m_hIconSmall;

		RegisterClassExW(&wc);

		RECT clientRect{ 0, 0, (LONG)m_width, (LONG)m_height };

		AdjustWindowRect(&clientRect, m_windowStyle, FALSE);

		m_hwnd = CreateWindowExW(
			0,
			m_className.c_str(),
			m_windowName.c_str(),
			m_windowStyle,
			m_x, m_y,
			clientRect.right - clientRect.left, // 너비
			clientRect.bottom - clientRect.top, // 높이
			nullptr,
			nullptr,
			m_hInstance,
			this // 인스턴스 주소를 NCREATESTRUCT의 lpCreateParams에 저장
		);
		ShowWindow(m_hwnd, SW_SHOW);
		UpdateWindow(m_hwnd);
	}

	AppResourceManager::AppResourceManager() : m_hwnd(nullptr), m_hInstance(nullptr),
		m_width(1200), m_height(700), m_className(L"Cat of Dog"), m_windowName(L"Your Cat? or Dog?"),
		m_classStyle(CS_HREDRAW | CS_VREDRAW), m_windowStyle(WS_OVERLAPPEDWINDOW),
		m_x (CW_USEDEFAULT), m_y(CW_USEDEFAULT)
	{

	}


}
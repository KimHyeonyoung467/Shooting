// Winmain.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "pch.h"
#include "framework.h"
#include "Winmain.h"
#include "DemoGameApp.h" 



int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow)
{
	DemoGameApp* m_app = new DemoGameApp(); 

	m_app->Initialize(); 
	m_app->Run(); 

	delete m_app; 
}
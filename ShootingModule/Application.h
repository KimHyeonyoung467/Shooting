#pragma once
#include "AppResourceManager.h" 
#include "D2DResourceManager.h" 
#include "SceneManager.h"
#include "GameObject.h" 


#include "Timer.h" 

// test Header 
#include "DrawText.h" 

class Application
{
public:
	Application();
	~Application();

	virtual void Initialize();
	virtual void Run();
	virtual void update();
	virtual void Render();

	// SceneManager Plus
	void beginDraw(const D2D1::ColorF& color);
	void endDraw();

private:
	shared_ptr<Resource::AppResourceManager> m_appResource;
	shared_ptr<Resource::D2DResourceManager> m_d2DResource;
};


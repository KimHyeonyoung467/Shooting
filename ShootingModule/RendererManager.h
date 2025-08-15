#pragma once
#include "pch.h" 
#include "D2DResourceManager.h"
#include "RectAngle.h" 

class IRectAngle;

class RendererManager
{
public: 
	RendererManager(Transform* tr);
	~RendererManager() = default; 

	void Initialize(); 
	void update(); 
	void Render(); 

	// Direct2D 초기화 
	// GameObject 에서 RenderManager 의 그리기 
	IRectAngle* getRectAngle() {  return m_rect; } // IRectAngle 자식인 RectAngle 타입 
	const D2D1_RECT_F& getRect() const { return rect; }

	void setColor(const D2D1::ColorF& color) { m_color = color;  }
	const D2D1::ColorF getColor() { return m_color; }
private: 
	// 사각형 그리기 함수 제공용 클래스 
	IRectAngle* m_rect;	
	D2D1_RECT_F rect; 
	D2D1::ColorF m_color; 

	Transform* m_transform;	
	shared_ptr<Resource::D2DResourceManager> m_d2DResource; 
};


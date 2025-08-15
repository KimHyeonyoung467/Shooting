#pragma once
#include "pch.h" 
#include "Transform.h" 
#include "D2DResourceManager.h"
#include "RendererManager.h"
#include "IRectAngle.h" 

class ColliderLiner
{
public:
	// 인터페이스 실수를 막기 위한 팩토리 함수 
	static ColliderLiner* drawLiner(Transform* tr)
	{
		return new ColliderLiner(tr); 
	}

	// GameObject 의 Rect 를 받아서 Rect 의 크기 만큼의 ColliderLiner 범위를 잠고, 
	// RendererManager 의 m_rect 를 사용해 그린다. 

	void Initialize();
	void update();
	void Render();

	void setTransform(Transform* tr) { m_transform = tr; }
	const Transform* getTransform() const {	return m_transform; } 

	const RendererManager* getRender() const { return m_render; }

	const IRectAngle* getRectAngle() const { return m_rect; }

	void setColor(const D2D1::ColorF& color) { m_color = color; }
	const D2D1::ColorF& getColor() const { return m_color; }
private:
	ColliderLiner(Transform* obj);
	Transform* m_transform; 

	Vector2 m_position;
	Vector2 m_scale;

	RendererManager* m_render; // Collider 충돌 범위 그릴 상자를 가진 RendererManager 
									// RendererManager 에서 색깔도 변경 가능 
	D2D1::ColorF m_color; 

	IRectAngle* m_rect; 
	D2D1_RECT_F rect; 

	shared_ptr<Resource::D2DResourceManager> m_d2DResource;
};


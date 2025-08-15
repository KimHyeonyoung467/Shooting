#include "pch.h"
#include "ColliderLiner.h"
#include "RectAngle.h" 

ColliderLiner::ColliderLiner(Transform* tr)
	: m_transform(tr), m_position(), m_scale(),m_render(new RendererManager(m_transform)), m_color(D2D1::ColorF::Black),
	rect{}, m_rect(new RectAngle()), m_d2DResource(Resource::D2DResourceManager::Get())
{

}

void ColliderLiner::Initialize()
{
	//  Collider Liner 크기와 위치 
	m_scale = m_transform->getlocalScale();
	m_position = m_transform->getlocalPosition();

	setColor(D2D1::ColorF::HotPink);
	// 그릴 상자에 위치와 크기를 적용 
	rect = m_rect->createRectAngle(m_position, m_scale);


}

void ColliderLiner::update()
{
	m_scale = m_transform->getlocalScale();
	m_position = m_transform->getlocalPosition();
	
	m_scale->get_xpos() + 0.2f; 
	m_scale->get_ypos() + 0.2f;

	rect = m_rect->createRectAngle(m_position, m_scale);

}

void ColliderLiner::Render()
{
	auto Color = getColor(); 
	m_d2DResource->setBrushColor(Color);

	auto* brush = m_d2DResource->getBrush().Get();
	m_rect->drawsRectAngle(rect, brush);
}

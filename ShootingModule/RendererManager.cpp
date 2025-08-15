#include "pch.h"
#include "RendererManager.h"

RendererManager::RendererManager(Transform* tr) 
	: m_rect(new RectAngle()), 
	rect{ }, m_transform(tr), 
	m_d2DResource(Resource::D2DResourceManager::Get()), m_color(D2D1::ColorF::White)
{

}

void RendererManager::Initialize()
{

}

void RendererManager::update()
{	
	rect = m_rect->createRectAngle(m_transform->getlocalPosition(), m_transform->getlocalScale());
}

void RendererManager::Render()
{
	m_d2DResource->setBrushColor(m_color); 
	m_rect->drawFillRectAngle(rect, m_transform->getlocalMatrix());
}



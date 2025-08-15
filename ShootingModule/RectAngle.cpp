#include "pch.h"
#include "RectAngle.h"

RectAngle::RectAngle() : m_d2DResource(Resource::D2DResourceManager::Get()),
m_rect{ 0.0f, 0.0f, 1.0f, 1.0f }
{

}

D2D1_RECT_F RectAngle::createRectAngle(const Vector2& pos, const Vector2& scale)
{
	m_rect = { pos.get_xpos(), pos.get_ypos(), 
				pos.get_xpos() + scale.get_xpos(), 
				pos.get_ypos() + scale.get_ypos() };

	return m_rect; 
}


void RectAngle::drawRectAngle(const D2D1_RECT_F& rect)
{
	auto brush = m_d2DResource->getBrush();
	m_d2DResource->getContext()->DrawRectangle(rect, brush.Get());
}

void RectAngle::drawRectAngle(const D2D1_RECT_F& rect, ID2D1SolidColorBrush* brush, 
								float strokWidth /*= 1.0f*/, ID2D1StrokeStyle* strokeStyle /*= nullptr*/)
{
	// rect 와 brush 만을 파라메터로 받도록 한다. 
	m_d2DResource->getContext()->DrawRectangle(rect, brush, strokWidth, strokeStyle);
}

void RectAngle::drawsRectAngle(const D2D1_RECT_F& rect, ID2D1SolidColorBrush* brush,
	float strokWidth /*= 2.0f*/, ID2D1StrokeStyle* strokeStyle /*= nullptr*/)
{
	// rect 와 brush 만을 파라메터로 받도록 한다. 
	m_d2DResource->getContext()->DrawRectangle(rect, brush, strokWidth, strokeStyle);
}

void RectAngle::drawFillRectAngle(const D2D1_RECT_F& rect)
{
	auto brush = m_d2DResource->getBrush();
	m_d2DResource->getContext()->FillRectangle(rect, brush.Get());
}

void RectAngle::drawFillRectAngle(const D2D1_RECT_F& rect, const D2D1::Matrix3x2F& matrix)
{
	m_d2DResource->getContext()->SetTransform(matrix); 

	auto brush = m_d2DResource->getBrush();
	m_d2DResource->getContext()->FillRectangle(rect, brush.Get());
}

void RectAngle::removeRectAngle(const D2D1_RECT_F& rect, ID2D1SolidColorBrush* brush)
{
	m_d2DResource->getContext()->FillRectangle(rect, brush);
}

void RectAngle::rectAngleTransform(const Vector2& pos, const Vector2& scale)
{
	// right, bottom
	auto right = pos.get_xpos() + scale.get_xpos(); 
	auto bottom = pos.get_ypos() + scale.get_ypos(); 

	m_rect = { pos.get_xpos(), pos.get_ypos(), right, bottom }; 

}


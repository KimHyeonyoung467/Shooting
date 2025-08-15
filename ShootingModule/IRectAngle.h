#pragma once
#include "pch.h" 
#include "Transform.h" 

class IRectAngle
{
public: 
	virtual D2D1_RECT_F createRectAngle(const Vector2& pos, const Vector2& scale) = 0;

	// 상자를 그리는 함수 
	virtual void drawRectAngle(const D2D1_RECT_F& rect) = 0;

	// 색이 꽉 찬 상자를 그리는 함수 
	virtual void drawFillRectAngle(const D2D1_RECT_F& rect) = 0; 
	virtual void drawFillRectAngle(const D2D1_RECT_F& rect, const D2D1::Matrix3x2F& matrix) = 0;
	virtual void drawsRectAngle(const D2D1_RECT_F& rect, ID2D1SolidColorBrush* brush, float strokWidth = 2.0f, ID2D1StrokeStyle* strokeStyle = nullptr) = 0; 

	// 상자를 삭제 하는 함수 
	virtual void removeRectAngle(const D2D1_RECT_F& rect, ID2D1SolidColorBrush* brush) = 0;

	// 상자의 위치를 조정 하는 함수 
	virtual void rectAngleTransform(const Vector2& pos, const Vector2& scale) = 0; 
	

};



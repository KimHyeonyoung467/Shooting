#pragma once
#include "pch.h" 
#include "Vector2.h"

class Transform
{
public: 
	Transform(); 
	~Transform(); 

	// transform 
	void setlocalPosition(const Vector2& pos);
	void setlocalPosition(float x, float y); 
	Vector2 getlocalPosition() const; 

	void setRotation(float angle); 
	const float& getRotation() const; 

	void setlocalscale(const Vector2& scale); 
	void setlocalscale(const float& sx, const float& xy);
	Vector2 getlocalScale() const; 

	const D2D1::Matrix3x2F getMatrix(); 
	const D2D1::Matrix3x2F getlocalMatrix(); 
	const void setMatrix(const D2D1::Matrix3x2F& matrix); 

	Vector2  Rotation(const Vector2& pos, float angleRad);

	const bool inverseMatrix();

private: 	
	Vector2 m_localposition; 
	Vector2 m_localscale; 
	float m_localrotation; 

	// mutable 을 사용해서 const 제약을 해제. 
	mutable D2D1::Matrix3x2F m_localMatrix;
	mutable bool m_isDirty = false; 

};


#include "pch.h"
#include "Transform.h"

Transform::Transform() : m_localposition{ 0.0f,0.0f }, m_localscale{ 1.0f,1.0f }, m_localrotation(0.0f), m_localMatrix(D2D1::Matrix3x2F::Identity())
{

}

Transform::~Transform()
{
}

void Transform::setlocalPosition(const Vector2& pos)
{
	m_localposition = pos;	

	getMatrix(); 
}

void Transform::setlocalPosition(float x, float y)
{
	m_localposition.set_transform(x, y);
}

Vector2 Transform::getlocalPosition() const
{
	return m_localposition;
}

void Transform::setRotation(float angle)
{
	if (angle >= 0.0f || angle <= 360.0f) // 0 ~ 360도 까지 
		m_localrotation = angle;
	else
		throw invalid_argument("angle 값은 0 ~ 360.0도");

	getMatrix();
}

const float& Transform::getRotation() const
{
	return m_localrotation;
}

void Transform::setlocalscale(const Vector2& scale)
{
	m_localscale = scale;
		getMatrix(); 
}

void Transform::setlocalscale(const float& sx, const float& sy)
{
	m_localscale.set_transform(sx, sy); 

}

Vector2 Transform::getlocalScale() const
{
	return m_localscale;
}

const D2D1::Matrix3x2F Transform::getMatrix()
{
	m_localMatrix = D2D1::Matrix3x2F::Translation(m_localposition.get_xpos(), m_localposition.get_ypos()) *
		D2D1::Matrix3x2F::Rotation(m_localrotation) *
		D2D1::Matrix3x2F::Scale(m_localscale.get_xpos(), m_localscale.get_ypos());

	m_isDirty = false;

	return m_localMatrix;
}

const D2D1::Matrix3x2F Transform::getlocalMatrix()
{
	return m_localMatrix;
}

const void Transform::setMatrix(const D2D1::Matrix3x2F& matrix)
{
	m_localMatrix = matrix;
}
Vector2 Transform::Rotation(const Vector2& pos, float angleRad)
{
	float cos_angle = cosf(angleRad);
	float sin_angle = sinf(angleRad);

	return Vector2(
		(pos.get_xpos() * cos_angle - pos.get_ypos() * sin_angle, sin_angle),
		pos.get_xpos() * sin_angle + pos.get_ypos() * cos_angle);

}

const bool Transform::inverseMatrix()
{
	return m_localMatrix.Invert(); 
}

#include "pch.h"
#include "Camera.h"

void Camera::createViewCamera(UINT width, UINT height)
{
	// 카메라의 크기 
	m_transform->setlocalPosition({ 0.0f, 0.0f });
	m_transform->setlocalscale(width, height);
	m_transform->setRotation(0.0f); 
	
	// 행렬 초기 계산 (갱신용으로도 사용) 
	m_viewMatrix = m_transform->getMatrix();	
}

D2D1::Matrix3x2F& Camera::getviewMatrix()
{
	// 갱신되지 않은 transform 의 행렬을 가져온다. Initialize 에서 이미 계산한 행렬을 가져오기 떄문에, 이곳에서는 역행렬 변환만이 필요하다. 
	m_viewMatrix.Invert(); 

	return m_viewMatrix; 
}

Camera::Camera(UINT width, UINT height)
	: m_viewMatrix(D2D1::Matrix3x2F::Identity()), 
	m_viewWidth(width), m_viewHeight(height)
{

}

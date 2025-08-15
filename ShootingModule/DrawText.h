#pragma once
#include "pch.h" 
#include <dwrite.h>
#pragma comment(lib, "dwrite.lib")

#include "D2DResourceManager.h" 
#include "AppResourceManager.h" 
#include "Transform.h" 
#include "RectAngle.h" 
#include "RendererManager.h"

class IRectAngle; 

class TextDraw
{
public: 
	TextDraw();

	// 원하는 텍스트를 받아서 셋팅 
	void setText(const wstring& txt) { m_text = txt; }
	wstring getText() { return m_text; }

	// 텍스트 transform 
	Transform* getTextTransform() { return m_transform; }

	void Initialize(); 
	void update(); 

	// Text 출력 오버로드 
	void drawText(); 
	void drawText(const int& vaule);

	const void setTextColor(D2D1::ColorF color); 
	const ComPtr<ID2D1SolidColorBrush> getTextBrush() { return m_textBrush; }

private: 
	wstring m_text; 

	Transform* m_transform; 
	shared_ptr<IRectAngle> m_rectAngle; 
	shared_ptr<RendererManager> m_render; 

	ComPtr<ID2D1SolidColorBrush> m_textBrush; 

	shared_ptr<Resource::AppResourceManager> m_appResource; 
	shared_ptr<Resource::D2DResourceManager> m_d2DResource;
	
	// DEBUG 
	const void DebugOutput() const; 
	wstring ToWString(const int& value);
};




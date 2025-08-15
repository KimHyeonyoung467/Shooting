#include "pch.h"
#include "DrawText.h"


void TextDraw::Initialize()
{
	// Text 전용 brush 생성 
	m_d2DResource->getContext()->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White),
		m_textBrush.GetAddressOf());

	// text 는 모두 30.0f 위치에서 시작 
	m_transform->setlocalPosition(30.0f, 30.0f);
	m_transform->setlocalscale(300.0f, 100.0f);

}

void TextDraw::update()
{
	m_render->update();
}


void TextDraw::drawText()
{
	auto context(m_d2DResource->getContext());
	auto brush(m_d2DResource->getBrush());

	//m_textRct 에 따라서 크기와 위치를 조정. 
	context->DrawText(
		m_text.c_str(),
		UINT32_MAX,
		m_d2DResource->getTextFormat().Get(),
		m_render->getRect(),
		m_textBrush.Get()
	);

}

void TextDraw::drawText(const int& vaule)
{
	auto context(m_d2DResource->getContext()); 
	auto brush(m_textBrush.Get()); 

	wstring str = m_text + ToWString(vaule);

	context->DrawText(
		str.c_str(),
		static_cast<UINT32> (str.length()),
		m_d2DResource->getTextFormat().Get(),
		m_render->getRect(),
		brush
	);

}

const void TextDraw::setTextColor(D2D1::ColorF color)
{
	m_textBrush->SetColor(color);
}

wstring TextDraw::ToWString(const int& value)
{
	wstring str = std::to_wstring(value);
	return str;
}

const void TextDraw::DebugOutput() const
{
	cout << "[DEBUG] Text Box Scale : " << " width : " << m_transform->getlocalScale().get_xpos()
		<< " height : " << m_transform->getlocalScale().get_ypos() << endl;

	cout << endl;

	cout << "[DEBUG] Text Box Position : " << " X : " << m_transform->getlocalPosition().get_xpos()
		<< " Y : " << m_transform->getlocalPosition().get_ypos() << endl;
}

TextDraw::TextDraw() :m_transform(new Transform()), m_appResource(Resource::AppResourceManager::Get()),
m_d2DResource(Resource::D2DResourceManager::Get()), m_rectAngle(make_shared<RectAngle>()), m_textBrush()
, m_render(make_shared< RendererManager>(m_transform))
{


}

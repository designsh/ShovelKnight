#include "EnchantressBackDrop.h"
#include <SGameEngineWindow.h>

#include "GlobalValue.h"

// Static Var

// Static Func

// member Var
EnchantressBackDrop::EnchantressBackDrop()
	: m_WindowSize(FLOAT4::ZERO),
	m_BackGround(nullptr)
{

}

EnchantressBackDrop::~EnchantressBackDrop()
{

}

// member Func
void EnchantressBackDrop::Start()
{
	// 키생성
	SGameEngineInput::CreateKey(L"EnchantressBackDropOff", 'C');
	SGameEngineInput::CreateKey(L"EnchantressBackDropOn", 'V');

	// 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 랜더러 생성
	m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::SkyBackGround);
	m_BackGround->TransCenterSetting(L"Enchantress_BackGround.bmp", { 1280.f, 720.f });
	m_BackGround->SetPivotPos({ 1280.f * 0.5f , 720.f * 0.5f });
	m_BackGround->CamEffectOff();
}

void EnchantressBackDrop::Update()
{
	if (true == SGameEngineInput::IsPress(L"EnchantressBackDropOff"))
	{
		m_BackGround->Off();
	}

	if (true == SGameEngineInput::IsPress(L"EnchantressBackDropOn"))
	{
		m_BackGround->On();
	}
}

void EnchantressBackDrop::DebugRender()
{

}

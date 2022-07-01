#include "EndingBackDrop.h"
#include <SGameEngineWindow.h>

#include "GlobalValue.h"

// Static Var

// Static Func

// member Var
EndingBackDrop::EndingBackDrop()
	: m_WindowSize(FLOAT4::ZERO),
	m_BackGround(nullptr)
{

}

EndingBackDrop::~EndingBackDrop()
{

}

// member Func
void EndingBackDrop::Start()
{
	// ������ ũ�⸦ �����´�
	m_WindowSize = SGameEngineWindow::GetSize();

	// �������� �����Ѵ�.
	m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::SkyBackGround);
	m_BackGround->TransCenterSetting(L"Ending_BackGround.bmp", { 1280.f, 720.f });
	m_BackGround->SetPivotPos({ 1280.f * 0.5f , 720.f * 0.5f });
	m_BackGround->CamEffectOff();
}

void EndingBackDrop::Update()
{

}

void EndingBackDrop::DebugRender()
{

}

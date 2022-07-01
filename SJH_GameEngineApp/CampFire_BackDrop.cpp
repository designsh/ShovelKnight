#include "CampFire_BackDrop.h"
#include <SGameEngineWindow.h>

#include "GlobalValue.h"

// Static Var

// Static Func

// member Var
CampFire_BackDrop::CampFire_BackDrop()
	: m_WindowSize(FLOAT4::ZERO),
	m_CampFire1(nullptr), m_CampFire2(nullptr),
	m_CampChangeEventer()
{

}

CampFire_BackDrop::~CampFire_BackDrop()
{

}

// member Func
void CampFire_BackDrop::Start()
{
	// ������ ũ�⸦ �����´�
	m_WindowSize = SGameEngineWindow::GetSize();

	// �������� �����Ѵ�.
	m_CampFire1 = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::CastleBackGround);
	m_CampFire1->TransCenterSetting(L"Ending_Tree1.bmp", { 672.f, 720.f });
	m_CampFire1->SetPivotPos({ 672.f , 720.f * 0.5f });
	m_CampFire1->CamEffectOff();

	m_CampFire2 = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::CastleBackGround);
	m_CampFire2->TransCenterSetting(L"Ending_Tree2.bmp", { 672.f, 720.f });
	m_CampFire2->SetPivotPos({ 672.f, 720.f * 0.5f });
	m_CampFire2->CamEffectOff();

	// Ÿ���̺��͸� �����Ѵ�.
	if (0 == m_CampChangeEventer.IsEventSize())
	{
		m_CampChangeEventer.CreateTimeEventEnd(0.2f, this, &CampFire_BackDrop::ImageChangeEnd);
		m_CampChangeEventer.LoopOn();
	}
}

void CampFire_BackDrop::Update()
{
	m_CampChangeEventer.Update();
}

void CampFire_BackDrop::DebugRender()
{

}

void CampFire_BackDrop::ImageChangeEnd()
{
	if (true == m_CampFire1->IsOn())
	{
		m_CampFire1->Off();
		m_CampFire2->On();
	}
	else if (true == m_CampFire2->IsOn())
	{
		m_CampFire1->On();
		m_CampFire2->Off();
	}
}

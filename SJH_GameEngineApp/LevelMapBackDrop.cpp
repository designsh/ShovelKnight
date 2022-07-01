#include "LevelMapBackDrop.h"
#include <SGameEngineResMgr.h>
#include <SGameEngineWindow.h>
#include <SGameEngineDebug.h>
#include <Windows.h>

#include "GlobalValue.h"

// Static Var

// Static Func

// member Var
LevelMapBackDrop::LevelMapBackDrop()
	: m_WindowSize(FLOAT4::ZERO),
	m_BackDrop(nullptr)
{

}

LevelMapBackDrop::~LevelMapBackDrop()
{

}

// member Func
void LevelMapBackDrop::Start()
{
	// Ű����
	SGameEngineInput::CreateKey(L"LevelMap_BackDropOff", 'C');
	SGameEngineInput::CreateKey(L"LevelMap_BackDropOn", 'V');

	// ������ ũ�Ⱑ������
	m_WindowSize = SGameEngineWindow::GetSize();

	m_BackDrop = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::SkyBackGround);
	m_BackDrop->TransCenterSetting(L"WolrdMapBackDrop.bmp", { 1280.f, 720.f });
	m_BackDrop->SetPivotPos({ m_WindowSize.x * 0.5f , m_WindowSize.y * 0.5f });
	m_BackDrop->CamEffectOff();
}

void LevelMapBackDrop::Update()
{
	if (true == SGameEngineInput::IsPress(L"LevelMap_BackDropOff"))
	{
		m_BackDrop->Off();
	}

	if (true == SGameEngineInput::IsPress(L"LevelMap_BackDropOn"))
	{
		m_BackDrop->On();
	}
}

void LevelMapBackDrop::DebugRender()
{

}

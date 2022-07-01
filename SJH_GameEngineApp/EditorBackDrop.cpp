#include "EditorBackDrop.h"
#include <SGameEngineResMgr.h>
#include <SGameEngineWindow.h>
#include <SGameEngineDebug.h>
#include <Windows.h>

// Static Var

// Static Func

// member Var
EditorBackDrop::EditorBackDrop() 
	: m_WindowSize(FLOAT4::ZERO), m_CollBackGround(nullptr), m_RefBackGround(nullptr), m_TileUI(nullptr), m_LevelMapBackGound(nullptr),
	m_EnchantressBackGound(nullptr), m_EnchantressCollBackGround(nullptr)
{

}

EditorBackDrop::~EditorBackDrop()
{

}

// member Func
void EditorBackDrop::Start()
{
	// 현재 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 씬 충돌맵 바탕 23040 x 4320
	m_CollBackGround = CreateRenderer<SGameEngineRendererBasic>(0);
	m_CollBackGround->TransCenterSetting(L"Editor_BackGround.bmp", { 23040.f, 4320.f });
	m_CollBackGround->SetPivotPos({ 23040 * 0.5f, 4320 * 0.5f });

	// 참고용 백그라운드
	m_RefBackGround = CreateRenderer<SGameEngineRendererBasic>(1);
	m_RefBackGround->TransCenterSetting(L"Stage_ref.bmp", { 1280.f, 720.f });
	m_RefBackGround->SetPivotPos({ 1280.f * 0.5f, 720.f * 0.5f });
	m_RefBackGround->CamEffectOff();

	//// Enchantress BackGround
	//m_EnchantressBackGound = CreateRenderer<SGameEngineRendererBasic>(0);
	//m_EnchantressBackGound->TransCenterSetting(L"Enchantress_BackDrop.bmp", { 1280.f, 720.f });
	//m_EnchantressBackGound->SetPivotPos({ 1280.f * 0.5f, 720.f * 0.5f });
	//m_EnchantressBackGound->CamEffectOff();

	//m_EnchantressCollBackGround = CreateRenderer<SGameEngineRendererBasic>(3);
	//m_EnchantressCollBackGround->TransCenterSetting(L"Enchantress_ColMap.bmp", { 1280.f, 2880.f });
	//m_EnchantressCollBackGround->SetPivotPos({ 1280.f * 0.5f, 2880.f * 0.5f });
	

	SGameEngineInput::CreateKey(L"Off", 'Z');
	SGameEngineInput::CreateKey(L"On", 'X');
}

void EditorBackDrop::Update()
{
	if (true == SGameEngineInput::IsPress(L"Off"))
	{
		m_RefBackGround->Off();
	}
	if (true == SGameEngineInput::IsPress(L"On"))
	{
		m_RefBackGround->On();
	}
}
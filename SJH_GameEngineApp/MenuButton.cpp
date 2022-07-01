#include "MenuButton.h"
#include <SGameEngineDirectory.h>
#include <SGameEngineWindow.h>
#include <Windows.h>

#include "MenuSelector.h"

// Static Var

// Static Func

// member Var
MenuButton::MenuButton() 
	: m_SelStart(nullptr), m_SelEditor(nullptr), m_SelExit(nullptr), m_MenuCover(nullptr),
	m_MenuBlinkEventer()
{

}

MenuButton::~MenuButton()
{

}

// member Func
void MenuButton::Start()
{
	// MenuButton을 화면에 띄운다.
	// 게임시작 메뉴
	m_SelStart = CreateRenderer<SGameEngineRendererBasic>(2);
	m_SelStart->TransSetting(L"StartGameMenu.bmp", { 260, 40 });
	m_SelStart->SetPivotPos({ 515.f, 420.f });

	// 맵에디터 메뉴
	m_SelEditor = CreateRenderer<SGameEngineRendererBasic>(2);
	m_SelEditor->TransSetting(L"MapEditorMenu.bmp", { 260, 40 });
	m_SelEditor->SetPivotPos({ 515.f, 480.f });

	// 나가기 메뉴
	m_SelExit = CreateRenderer<SGameEngineRendererBasic>(2);
	m_SelExit->TransSetting(L"ExitMenu.bmp", { 260, 40 });
	m_SelExit->SetPivotPos({ 515.f, 540.f });

	// 각 메뉴 가림막(기본 Off 상태)
	m_MenuCover = CreateRenderer<SGameEngineRendererBasic>(3);
	m_MenuCover->TransSetting(L"TitleMenu_Cover.bmp", { 260, 40 });
	m_MenuCover->SetPivotPos({ 515.f, 540.f });
	m_MenuCover->Off();

	// 각 메뉴 Blink 효과를 주기 위해 TimeEventer 생성
	if (0 == m_MenuBlinkEventer.IsEventSize())
	{
		m_MenuBlinkEventer.CreateTimeEvent(0.007f, this, &MenuButton::SelectMenuBlinkEnd, &MenuButton::SelectMenuBlinkStart, &MenuButton::SelectMenuBlinkStay);
		m_MenuBlinkEventer.LoopOn();
	}
	m_MenuBlinkEventer.Reset();
}

// 해당 객체 갱신
void MenuButton::Update()
{
	// 메뉴선택이 됬는지 계속해서 체크
	if (true == MenuSelector::m_bMenuSelect)
	{
		m_MenuBlinkEventer.Update();
	}
}

// 타임이벤터
void MenuButton::SelectMenuBlinkStart()
{
	// 몇번째 메뉴 선택인지 판단 
	// 단, Exit는 실행하지 않는다.
	if ((int)SelectMenu::MN_START == MenuSelector::m_iSelectMenu)
	{
		// 위치 조정
		m_MenuCover->SetPivotPos({ 515.f, 420.f });
	}
	else if ((int)SelectMenu::MN_EDITOR == MenuSelector::m_iSelectMenu)
	{
		// 위치 조정
		m_MenuCover->SetPivotPos({ 515.f, 480.f });
	}

	m_MenuCover->On();
}

void MenuButton::SelectMenuBlinkStay()
{

}

void MenuButton::SelectMenuBlinkEnd()
{
	// 커버이미지 Off
	m_MenuCover->Off();
}

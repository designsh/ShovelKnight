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
	// MenuButton�� ȭ�鿡 ����.
	// ���ӽ��� �޴�
	m_SelStart = CreateRenderer<SGameEngineRendererBasic>(2);
	m_SelStart->TransSetting(L"StartGameMenu.bmp", { 260, 40 });
	m_SelStart->SetPivotPos({ 515.f, 420.f });

	// �ʿ����� �޴�
	m_SelEditor = CreateRenderer<SGameEngineRendererBasic>(2);
	m_SelEditor->TransSetting(L"MapEditorMenu.bmp", { 260, 40 });
	m_SelEditor->SetPivotPos({ 515.f, 480.f });

	// ������ �޴�
	m_SelExit = CreateRenderer<SGameEngineRendererBasic>(2);
	m_SelExit->TransSetting(L"ExitMenu.bmp", { 260, 40 });
	m_SelExit->SetPivotPos({ 515.f, 540.f });

	// �� �޴� ������(�⺻ Off ����)
	m_MenuCover = CreateRenderer<SGameEngineRendererBasic>(3);
	m_MenuCover->TransSetting(L"TitleMenu_Cover.bmp", { 260, 40 });
	m_MenuCover->SetPivotPos({ 515.f, 540.f });
	m_MenuCover->Off();

	// �� �޴� Blink ȿ���� �ֱ� ���� TimeEventer ����
	if (0 == m_MenuBlinkEventer.IsEventSize())
	{
		m_MenuBlinkEventer.CreateTimeEvent(0.007f, this, &MenuButton::SelectMenuBlinkEnd, &MenuButton::SelectMenuBlinkStart, &MenuButton::SelectMenuBlinkStay);
		m_MenuBlinkEventer.LoopOn();
	}
	m_MenuBlinkEventer.Reset();
}

// �ش� ��ü ����
void MenuButton::Update()
{
	// �޴������� ����� ����ؼ� üũ
	if (true == MenuSelector::m_bMenuSelect)
	{
		m_MenuBlinkEventer.Update();
	}
}

// Ÿ���̺���
void MenuButton::SelectMenuBlinkStart()
{
	// ���° �޴� �������� �Ǵ� 
	// ��, Exit�� �������� �ʴ´�.
	if ((int)SelectMenu::MN_START == MenuSelector::m_iSelectMenu)
	{
		// ��ġ ����
		m_MenuCover->SetPivotPos({ 515.f, 420.f });
	}
	else if ((int)SelectMenu::MN_EDITOR == MenuSelector::m_iSelectMenu)
	{
		// ��ġ ����
		m_MenuCover->SetPivotPos({ 515.f, 480.f });
	}

	m_MenuCover->On();
}

void MenuButton::SelectMenuBlinkStay()
{

}

void MenuButton::SelectMenuBlinkEnd()
{
	// Ŀ���̹��� Off
	m_MenuCover->Off();
}

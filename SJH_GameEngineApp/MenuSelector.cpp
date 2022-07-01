#include "MenuSelector.h"
#include <SGameEngineInput.h>
#include <SGameEngineTimer.h>

#include "SGameCore.h"

// Static Var
bool MenuSelector::m_bMenuSelect = false;
int MenuSelector::m_iSelectMenu = (int)SelectMenu::MN_START;
SoundPlayer MenuSelector::m_ActionSound;

// Static Func
int MenuSelector::GetSelectMenu()
{
	return m_iSelectMenu;
}

// member Var
MenuSelector::MenuSelector() 
	: m_Selector(), m_Speed(1.f), m_MoveTime(0.5f), m_Move(true), m_bLerpFlag(false), m_bLerpMoveStart(false), m_bLerpMoveEnd(false),
	m_WindowSize(), m_LerpTime(0.0f)
{

}

MenuSelector::~MenuSelector()
{

}

// member Func
void MenuSelector::SelectorLerpStart()
{
	if (true == m_bLerpMoveStart)
	{
		m_LerpTime += SGameEngineTimer::MainTimer.FDeltaTime();
		m_LerpPos = FLOAT4::Lerp2D(m_LerpStartPos, m_LerpEndPos, m_LerpTime);

		SetPosition(m_LerpPos);

		if (1.0f < m_LerpTime)
		{
			m_LerpPos = FLOAT4::ZERO;
			m_LerpTime = 0.0f;
			m_bLerpMoveStart = false;
			m_bLerpFlag = false;
			m_bLerpMoveEnd = true;
		}

		return;
	}

	if (true == m_bLerpFlag)
	{
		m_LerpStartPos = GetPosition();
		m_LerpEndPos = GetPosition();

		m_LerpEndPos += FLOAT4::RIGHT * m_WindowSize.x;
		m_LerpTime = 0.0f;
		m_bLerpMoveStart = true;
	}
}

void MenuSelector::Start()
{
	// 윈도우의 크기를 가져온다.
	m_WindowSize = SGameEngineWindow::GetSize();

	// 키를 만들어낸다.
	SGameEngineInput::CreateKey(L"SelectorDown", VK_DOWN);
	SGameEngineInput::CreateKey(L"SelectorUp", VK_UP);
	SGameEngineInput::CreateKey(L"MenuSelect", VK_SPACE);

	// MenuSelector를 화면에 띄운다.
	m_Selector = CreateRenderer<SGameEngineRendererBasic>(3);
	m_Selector->TransSetting(L"Menu Selector.bmp", { 100, 30 }, { 0, 0 });
	m_Selector->SetPivotPos({ 380.f, 425.f }); // 초기값
}

void MenuSelector::Update()
{
	// 러프 종료시
	if (true == m_bLerpMoveEnd)
	{
		// 씬을 전환한다.
		if (m_iSelectMenu == (int)SelectMenu::MN_START)
		{
			SGameCore::SceneManager.ChangeScene(L"GameIntro");
		}
		else if (m_iSelectMenu == (int)SelectMenu::MN_EDITOR)
		{
			SGameCore::SceneManager.ChangeScene(L"TileMapEditor");
		}
		else if (m_iSelectMenu == (int)SelectMenu::MN_EXIT)
		{
			// 프로그램 종료
			SGameEngineWindow::WindowEnd(false);
		}

		// 전환완료 후 Flag해제한다.
		m_bLerpMoveEnd = false;
	}

	// 러프 시작시
	SelectorLerpStart();

	// 메뉴 Select Key Down시 현재 액터는 러프를이용하여 
	// 오른쪽으로 이동한다.
	// 러프 완료후 Flag True
	if (true == SGameEngineInput::IsDown(L"MenuSelect"))
	{
		// 액션 사운드 실행
		m_ActionSound = SGameEngineSound::Play(L"TitleScene_CursorSelect.mp3", false, 0);

		// Menu Blink를 위해 Flag On
		m_bMenuSelect = true;

		// 러프 시키기 위해 Flag On
		m_bLerpFlag = true;
	}

	// 키보드의 따라 MenuSelector가 위치좌표를 갱신한다.
	// 이때 MenuSelector는 자신이 가리키고있는 메뉴를 가지고있다.

	// MenuSelector가 아래메뉴로 이동한다.
	if (true == SGameEngineInput::IsDown(L"SelectorDown"))
	{
		m_ActionSound = SGameEngineSound::Play(L"TitleScene_CursorMove.mp3", false, 0);

		if (m_iSelectMenu == (int)SelectMenu::MN_START)
		{
			m_iSelectMenu = (int)SelectMenu::MN_EDITOR;
			MovePosition({ 0.f, 60.f });
		}
		else if(m_iSelectMenu == (int)SelectMenu::MN_EDITOR)
		{
			m_iSelectMenu = (int)SelectMenu::MN_EXIT;
			MovePosition({ 0.f, 60.f });
		}
		else if (m_iSelectMenu == (int)SelectMenu::MN_EXIT)
		{
			m_iSelectMenu = (int)SelectMenu::MN_START;
			MovePosition({ 0.f, -120.f });
		}
	}

	// MenuSelector가 위메뉴로 이동한다.
	if (true == SGameEngineInput::IsDown(L"SelectorUp"))
	{
		m_ActionSound = SGameEngineSound::Play(L"TitleScene_CursorMove.mp3", false, 0);

		if (m_iSelectMenu == (int)SelectMenu::MN_START)
		{
			m_iSelectMenu = (int)SelectMenu::MN_EXIT;
			MovePosition({ 0.f, 120.f });
		}
		else if (m_iSelectMenu == (int)SelectMenu::MN_EDITOR)
		{
			m_iSelectMenu = (int)SelectMenu::MN_START;
			MovePosition({ 0.f, -60.f });
		}
		else if (m_iSelectMenu == (int)SelectMenu::MN_EXIT)
		{
			m_iSelectMenu = (int)SelectMenu::MN_EDITOR;
			MovePosition({ 0.f, -60.f });
		}
	}

	// MenuSelector는 좌우로 움직인다.
	// Delta Time을 체크하여 일정시간에 좌우로 움직임
	m_MoveTime -= SGameEngineTimer::MainTimer.FDeltaTime();
	if (false == m_bLerpFlag)
	{
		if (0.0f >= m_MoveTime)
		{
			if (true == m_Move)
			{
				MovePosition({ 30.f, 0.f });
				m_Move = false;
			}
			else
			{
				MovePosition({ -30.f, 0.f });
				m_Move = true;
			}
			m_MoveTime = 0.5f;
		}
	}
}

SGameEngineRendererBasic* MenuSelector::GetSelector()
{
	return m_Selector;
}

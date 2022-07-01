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
	// �������� ũ�⸦ �����´�.
	m_WindowSize = SGameEngineWindow::GetSize();

	// Ű�� ������.
	SGameEngineInput::CreateKey(L"SelectorDown", VK_DOWN);
	SGameEngineInput::CreateKey(L"SelectorUp", VK_UP);
	SGameEngineInput::CreateKey(L"MenuSelect", VK_SPACE);

	// MenuSelector�� ȭ�鿡 ����.
	m_Selector = CreateRenderer<SGameEngineRendererBasic>(3);
	m_Selector->TransSetting(L"Menu Selector.bmp", { 100, 30 }, { 0, 0 });
	m_Selector->SetPivotPos({ 380.f, 425.f }); // �ʱⰪ
}

void MenuSelector::Update()
{
	// ���� �����
	if (true == m_bLerpMoveEnd)
	{
		// ���� ��ȯ�Ѵ�.
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
			// ���α׷� ����
			SGameEngineWindow::WindowEnd(false);
		}

		// ��ȯ�Ϸ� �� Flag�����Ѵ�.
		m_bLerpMoveEnd = false;
	}

	// ���� ���۽�
	SelectorLerpStart();

	// �޴� Select Key Down�� ���� ���ʹ� �������̿��Ͽ� 
	// ���������� �̵��Ѵ�.
	// ���� �Ϸ��� Flag True
	if (true == SGameEngineInput::IsDown(L"MenuSelect"))
	{
		// �׼� ���� ����
		m_ActionSound = SGameEngineSound::Play(L"TitleScene_CursorSelect.mp3", false, 0);

		// Menu Blink�� ���� Flag On
		m_bMenuSelect = true;

		// ���� ��Ű�� ���� Flag On
		m_bLerpFlag = true;
	}

	// Ű������ ���� MenuSelector�� ��ġ��ǥ�� �����Ѵ�.
	// �̶� MenuSelector�� �ڽ��� ����Ű���ִ� �޴��� �������ִ�.

	// MenuSelector�� �Ʒ��޴��� �̵��Ѵ�.
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

	// MenuSelector�� ���޴��� �̵��Ѵ�.
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

	// MenuSelector�� �¿�� �����δ�.
	// Delta Time�� üũ�Ͽ� �����ð��� �¿�� ������
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

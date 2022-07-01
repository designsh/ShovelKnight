#include "EndingCredit.h"
#include <SGameEngineWindow.h>

#include "GlobalValue.h"

// Static Var
SoundPlayer EndingCredit::m_EndingStageBgm;

// Static Func

// member Var
EndingCredit::EndingCredit()
	: m_WindowSize(FLOAT4::ZERO),
	m_ResPath(),
	m_BackDrop(nullptr), m_CampFireBackDrop(nullptr), m_EndingText(nullptr), m_CampFire(nullptr), m_PlayerObject(nullptr)
{

}

EndingCredit::~EndingCredit()
{

}

// member Func
void EndingCredit::Start()
{
	// ������ ũ�Ⱑ������
	m_WindowSize = SGameEngineWindow::GetSize();

	// Debug Renderer On/Off Key
	SGameEngineInput::CreateKey(L"EndingScene_DebugOff", 'P');
	SGameEngineInput::CreateKey(L"EndingScene_DebugOn", 'O');

	// ���� ���� �̹��� Cut ����
	EndingCreditImageCut();

	// BackGround ���� ���� ����
	EndingCreditCreateBackDrop();

	// Object ���� ���� ����
	EndingCreditCreateObject();
}

void EndingCredit::SceneUpdate()
{
	// ����� ���� On/Off Key Down
	if (true == SGameEngineInput::IsDown(L"EndingScene_DebugOff"))
	{
		IsDebugRenderOff();
	}
	else if (true == SGameEngineInput::IsDown(L"EndingScene_DebugOn"))
	{
		IsDebugRenderOn();
	}
}

void EndingCredit::SceneChangeStart()
{
	m_EndingStageBgm = SGameEngineSound::Play(L"Ending_music.mp3", true, 100);
}

void EndingCredit::SceneChangeEnd()
{
	m_EndingStageBgm.Stop();
}

void EndingCredit::SceneDebugRender()
{
	SGameEngineString FPS = L"FPS";
	FPS += SGameEngineString::ToString(1.0f / SGameEngineTimer::MainTimer.GetFDeltaTime());
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 60, FPS.c_str(), lstrlen(FPS.c_str()));

	FLOAT4 MousePos = SGameEngineWindow::MousePos();
	SGameEngineString MousePosText = L"MousePos";
	MousePosText += L"X : ";
	MousePosText += SGameEngineString::ToString(MousePos.ix());
	MousePosText += L"Y : ";
	MousePosText += SGameEngineString::ToString(MousePos.iy());
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 80, MousePosText.c_str(), lstrlen(MousePosText.c_str()));
}

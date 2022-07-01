#include "Enchantress.h"
#include <SGameEngineWindow.h>

#include "GlobalValue.h"
#include "Enchantress_ShovelKnight.h"
#include "Enchantress_FinalBoss.h"

// Static Var
SoundPlayer Enchantress::m_EnchantressStageBgm;

// Static Func

// member Var
Enchantress::Enchantress()
	: m_WindowSize(FLOAT4::ZERO),
	m_ResPath(), m_TileFilePath(),
	m_BackDrop(nullptr), m_ColMap(nullptr), m_TileMap(nullptr),
	m_StateBar(nullptr),
	m_FinalBoss(nullptr),
	m_Player(nullptr),
	m_FadeInOut(nullptr)
{

}

Enchantress::~Enchantress()
{

}

// member Func
void Enchantress::Start()
{
	// Debug Renderer On/Off Key
	SGameEngineInput::CreateKey(L"Enchantress_DebugOff", 'P');
	SGameEngineInput::CreateKey(L"Enchantress_DebugOn", 'O');

	// ������ ũ�Ⱑ������
	m_WindowSize = SGameEngineWindow::GetSize();

	// ���� ���� �̹��� Cut ����
	EnchantressImageCut();

	// �浹 �׷� ����
	EnchantressCreateCollisionGroup();

	// ī�޶� ��ġ ����
	// �ʱ���ġ(0, 720) - �� ���۽� ī�޶��� ��ġ
	// ���� ������ġ (0, 0) - �ش� �� ���� �� �÷��̾ ���� ��ġ�� �����ϸ� ī�޶� �ʱ���ġ���� ���� �̵�(ī�޶� �̵�)
	// ���� ����Ϸ� ����������ġ(0, 1080) - ���� ����Ϸ� �ִϸ��̼� ������ ���Ͱ� ������ �������鼭 ���� ������ġ
	// ���� ������ġ(0, 2160) - ���� �� ���Ͱ� ���б��� ����... ���� �������鼭 �����Ÿ� �������� ī�޶�� ������ġ�� �����ȴ�.
	SetCamMove(FLOAT4(0.f, 720.f));

	// �÷��̾� ����
	m_Player = CreateActor<Enchantress_ShovelKnight>();
	m_Player->SetPosition({ 100.f, 1336.f });
	GlobalValue::FinalStage_MainPlayer = m_Player;

	// ���� ���� ���� ����
	EnchantressCreateMonster();

	// BackGround ���� ���� ����
	EnchantressCreateBackDrop();

	// Object ���� ���� ����
	EnchantressCreateObject();
}

void Enchantress::SceneUpdate()
{
	// ����� ���� On/Off Key Down
	if (true == SGameEngineInput::IsDown(L"Enchantress_DebugOff"))
	{
		IsDebugRenderOff();
	}
	else if (true == SGameEngineInput::IsDown(L"Enchantress_DebugOn"))
	{
		IsDebugRenderOn();
	}
}

void Enchantress::SceneChangeStart()
{
	// ������� ����
	m_EnchantressStageBgm = SGameEngineSound::Play(L"Enchantress.mp3", true, 100);

	// �����÷��̾�� ���������� ��������
	GlobalValue::FinalStage_MainPlayer = m_Player;
	GlobalValue::FinalStage_FinalBoss = m_FinalBoss;
}

void Enchantress::SceneChangeEnd()
{
	// ������� ����
	m_EnchantressStageBgm.Stop();
}

void Enchantress::SceneDebugRender()
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




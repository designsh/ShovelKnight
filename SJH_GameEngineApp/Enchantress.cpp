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

	// 윈도우 크기가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 현재 씬의 이미지 Cut 관련
	EnchantressImageCut();

	// 충돌 그룹 생성
	EnchantressCreateCollisionGroup();

	// 카메라 위치 설정
	// 초기위치(0, 720) - 씬 시작시 카메라의 위치
	// 몬스터 등장위치 (0, 0) - 해당 씬 시작 후 플레이어가 일정 위치에 도달하면 카메라 초기위치에서 위로 이동(카메라만 이동)
	// 몬스터 등장완료 격투시작위치(0, 1080) - 몬스터 등장완료 애니메이션 종료후 몬스터가 밑으로 내려오면서 격투 시작위치
	// 몬스터 격파위치(0, 2160) - 격파 후 몬스터가 방패기사로 변신... 이후 떨어지면서 일정거리 떨어지면 카메라는 격파위치로 설정된다.
	SetCamMove(FLOAT4(0.f, 720.f));

	// 플레이어 생성
	m_Player = CreateActor<Enchantress_ShovelKnight>();
	m_Player->SetPosition({ 100.f, 1336.f });
	GlobalValue::FinalStage_MainPlayer = m_Player;

	// 몬스터 관련 액터 생성
	EnchantressCreateMonster();

	// BackGround 관련 액터 생성
	EnchantressCreateBackDrop();

	// Object 관련 액터 생성
	EnchantressCreateObject();
}

void Enchantress::SceneUpdate()
{
	// 디버그 랜더 On/Off Key Down
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
	// 배경음악 지정
	m_EnchantressStageBgm = SGameEngineSound::Play(L"Enchantress.mp3", true, 100);

	// 메인플레이어와 최종보스를 전역설정
	GlobalValue::FinalStage_MainPlayer = m_Player;
	GlobalValue::FinalStage_FinalBoss = m_FinalBoss;
}

void Enchantress::SceneChangeEnd()
{
	// 배경음악 종료
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




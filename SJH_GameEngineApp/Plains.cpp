#include "Plains.h"
#include "ShovelKnight.h"            // 삽질기사(플레이어)
#include "SGameCore.h"              // 씬 전환을 위해 참조

#include "GlobalValue.h"

#include <SGameEngineRendererTile.h>
#include <SGameEngineWindow.h>
#include <SGameEngineInput.h>
#include <SGameEngineResMgr.h>

// Static Var

// Static Func

// member Var
Plains::Plains()
	: m_ResPath(), m_Player(nullptr), m_BackDrop(nullptr), m_CollisionMap(nullptr), m_TileMap(nullptr),
	m_TopBar(nullptr),
	m_DeathScreen(nullptr),
	m_MovingPlatform1(nullptr), m_MovingPlatform2(nullptr), m_MovingPlatform3(nullptr), m_MovingPlatform4(nullptr), m_MovingPlatform5(nullptr),
	m_Beeto1(nullptr), m_Beeto2(nullptr), m_Beeto3(nullptr), m_Beeto4(nullptr), m_Beeto5(nullptr), m_Beeto6(nullptr), m_Beeto7(nullptr), m_Beeto8(nullptr), m_Beeto9(nullptr), m_Beeto10(nullptr), m_Beeto11(nullptr),
	m_SkullSoldier1(nullptr), m_SkullSoldier2(nullptr), m_SkullSoldier3(nullptr), m_SkullSoldier4(nullptr),
	m_Slime1(nullptr), m_Slime2(nullptr), m_Slime3(nullptr), m_Slime4(nullptr), m_Slime5(nullptr), m_Slime6(nullptr),
	m_Dragon1(nullptr), m_Dragon2(nullptr), m_Dragon3(nullptr), m_Dragon4(nullptr), m_Dragon5(nullptr),
	m_Dozedrake1(nullptr), m_Dozedrake2(nullptr),
	m_FinalBoss(nullptr),
	m_Stone1(nullptr), m_Stone2(nullptr), m_Stone3(nullptr), m_Stone4(nullptr), m_Stone5(nullptr), m_Stone6(nullptr), m_Stone7(nullptr), m_Stone8(nullptr), m_Stone9(nullptr),
	m_DirtBlock1(nullptr), m_DirtBlock2(nullptr), m_DirtBlock3(nullptr), m_DirtBlock4(nullptr), m_DirtBlock5(nullptr), m_DirtBlock6(nullptr), m_DirtBlock7(nullptr), m_DirtBlock8(nullptr), m_DirtBlock9(nullptr), m_DirtBlock10(nullptr), m_DirtBlock11(nullptr), m_DirtBlock12(nullptr), m_DirtBlock13(nullptr), m_DirtBlock14(nullptr), m_DirtBlock15(nullptr), m_DirtBlock16(nullptr), m_DirtBlock17(nullptr), m_DirtBlock18(nullptr), m_DirtBlock19(nullptr), m_DirtBlock20(nullptr), m_DirtBlock21(nullptr), m_DirtBlock22(nullptr), m_DirtBlock23(nullptr), m_DirtBlock24(nullptr), m_DirtBlock25(nullptr), m_DirtBlock26(nullptr), m_DirtBlock27(nullptr), m_DirtBlock28(nullptr), m_DirtBlock29(nullptr), m_DirtBlock30(nullptr), m_DirtBlock31(nullptr), m_DirtBlock32(nullptr), m_DirtBlock33(nullptr), m_DirtBlock34(nullptr), m_DirtBlock35(nullptr), m_DirtBlock36(nullptr), m_DirtBlock37(nullptr), m_DirtBlock38(nullptr), m_DirtBlock39(nullptr), m_DirtBlock40(nullptr), m_DirtBlock41(nullptr), m_DirtBlock42(nullptr), m_DirtBlock43(nullptr), m_DirtBlock44(nullptr), m_DirtBlock45(nullptr), m_DirtBlock46(nullptr), m_DirtBlock47(nullptr), m_DirtBlock48(nullptr), m_DirtBlock49(nullptr), m_DirtBlock50(nullptr), m_DirtBlock51(nullptr), m_DirtBlock52(nullptr), m_DirtBlock53(nullptr), m_DirtBlock54(nullptr), m_DirtBlock55(nullptr), m_DirtBlock56(nullptr), m_DirtBlock57(nullptr), m_DirtBlock58(nullptr), m_DirtBlock59(nullptr), m_DirtBlock60(nullptr), m_DirtBlock61(nullptr), m_DirtBlock62(nullptr), m_DirtBlock63(nullptr), m_DirtBlock64(nullptr), m_DirtBlock65(nullptr), m_DirtBlock66(nullptr), m_DirtBlock67(nullptr), m_DirtBlock68(nullptr),
	m_DirtSmall1(nullptr), m_DirtSmall2(nullptr), m_DirtSmall3(nullptr), m_DirtSmall4(nullptr), m_DirtSmall5(nullptr), m_DirtSmall6(nullptr), m_DirtSmall7(nullptr), m_DirtSmall8(nullptr), m_DirtSmall9(nullptr), m_DirtSmall10(nullptr),
	m_PileBubbles1(nullptr), m_PileBubbles2(nullptr), m_PileBubbles3(nullptr), m_PileBubbles4(nullptr), m_PileBubbles5(nullptr), m_PileBubbles6(nullptr), m_PileBubbles7(nullptr),
	m_SavePoint1(nullptr), m_SavePoint2(nullptr), m_SavePoint3(nullptr), m_SavePoint4(nullptr),
	m_GoldObject1(nullptr), m_GoldObject2(nullptr), m_GoldObject3(nullptr), m_GoldObject4(nullptr), m_GoldObject5(nullptr), m_GoldObject6(nullptr), m_GoldObject7(nullptr), m_GoldObject8(nullptr), m_GoldObject9(nullptr), m_GoldObject10(nullptr), m_GoldObject11(nullptr), m_GoldObject12(nullptr), m_GoldObject13(nullptr), m_GoldObject14(nullptr), m_GoldObject15(nullptr), m_GoldObject16(nullptr), m_GoldObject17(nullptr), m_GoldObject18(nullptr), m_GoldObject19(nullptr),
	m_Platter1(nullptr)
{

}

Plains::~Plains()
{
	GlobalValue::MainPlayer = nullptr;
	GlobalValue::MainTileMap = nullptr;
	GlobalValue::FinalBoss = nullptr;
	GlobalValue::PlayerDeathScreen = nullptr;
}

// member Func
void Plains::Start()
{
	// 디버그랜더러 On/Off 키 설정
	SGameEngineInput::CreateKey(L"COLOFF", 'P');
	SGameEngineInput::CreateKey(L"COLON", 'O');

	// 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 현재 씬의 이미지 Cut 관련
	PlainsImageCut();

	// 충돌 그룹 생성
	PlainsCreateCollisionGroup();

	// 카메라 위치설정(처음맵으로 캠이동)
	SetCamMove(FLOAT4(0.f, 2160.f));

	// ShovelKight Actor를 생성하고 위치를 맞춘다.
	m_Player = CreateActor<ShovelKnight>();
	m_Player->SetPosition({ 100.f, (m_WindowSize.y - 132.f) + 2160.f });

	GlobalValue::MainPlayer = m_Player;

	// Object 관련 액터를 생성한다.
	PlainsCreateObject();

	// Monster관련 액터를 생성한다.
	PlainsCreateMonster();

	// 백그라운드 관련 액터를 생성한다.
	PlainsCreateBackDrop();

	// 각오브젝트 재생성 이벤터 생성
	if (0 == m_TimeEventer.IsEventSize())
	{
		m_TimeEventer.CreateTimeEventStart(8.0f, this, &Plains::ResurrectObject);
		m_TimeEventer.LoopOn();
	}
}

void Plains::SceneUpdate()
{
	// 각 오브젝트 타임이벤터 업데이트
	m_TimeEventer.Update();

	// 디버그 랜더 On/Off Key Down
	if (true == SGameEngineInput::IsDown(L"COLOFF"))
	{
		IsDebugRenderOff();
	}
	else if(true == SGameEngineInput::IsDown(L"COLON"))
	{
		IsDebugRenderOn();
	}
}

void Plains::SceneChangeStart()
{
	// 플레이어 등장효과음
	ShovelKnight::m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_AppearStart.mp3", false, 0);

	GlobalValue::MainPlayer = m_Player;
	GlobalValue::MainTileMap = m_TileMap;
	GlobalValue::FinalBoss = m_FinalBoss;
	GlobalValue::PlayerDeathScreen = m_DeathScreen;
}

void Plains::SceneChangeEnd()
{
	ShovelKnight::m_StageBgm.Stop();
}

void Plains::SceneDebugRender()
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

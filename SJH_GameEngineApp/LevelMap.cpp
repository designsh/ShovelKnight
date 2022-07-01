#include "LevelMap.h"
#include "SGameCore.h"              // 씬 전환을 위해 참조

#include <SGameEngineRendererTile.h>
#include <SGameEngineWindow.h>
#include <SGameEngineInput.h>
#include <SGameEngineResMgr.h>


#include "GlobalValue.h"
#include "PlayerMaker.h"

// Static Var
SoundPlayer LevelMap::m_LevelMapStageBgm;
SoundPlayer LevelMap::m_CloudMoveStartSound;
SoundPlayer LevelMap::m_PlainsEffectSound;

// Static Func

// member Var
LevelMap::LevelMap()
	: m_WindowSize(FLOAT4::ZERO), m_ResPath(), m_TileFilePath(),
	m_BackDrop(nullptr), m_TileMap(nullptr), m_CollisionMap(nullptr),
	m_PlainsIcon(nullptr), m_EnchantressIcon(nullptr), m_NoneIcon(nullptr), m_MapCloud(nullptr),
	m_Player(nullptr)
{

}

LevelMap::~LevelMap()
{

}

// member Func
void LevelMap::Start()
{
	// 키 생성
	// Debug Renderer On/Off Key
	SGameEngineInput::CreateKey(L"LevelMap_DebugOff", 'P');
	SGameEngineInput::CreateKey(L"LevelMap_DebugOn", 'O');

	// 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 현재 씬의 이미지 Cut 관련
	LevelMapImageCut();

	// 충돌 그룹 생성
	LevelMapCreateCollisionGroup();

	// 카메라 위치 설정
	SetCamMove(FLOAT4(0.f, 0.f));

	// 플레이어 마커 생성 및 설정(초기위치로 설정된다)
	m_Player = CreateActor<PlayerMaker>();
	m_Player->SetPosition({ 272.f, 592.f });
	GlobalValue::LevelMapPlayer = m_Player;

	// Object 관련 액터를 생성한다.
	LevelMapCreateObject();
	
	// 백그라운드 관련 액터를 생성한다.
	LevelMapCreateBackDrop();

}

void LevelMap::SceneUpdate()
{
	// 디버그 랜더 On/Off Key Down
	if (true == SGameEngineInput::IsDown(L"LevelMap_DebugOff"))
	{
		IsDebugRenderOff();
	}
	else if (true == SGameEngineInput::IsDown(L"LevelMap_DebugOn"))
	{
		IsDebugRenderOn();
	}
}

void LevelMap::SceneChangeStart()
{
	// 배경음악지정
	m_LevelMapStageBgm = SGameEngineSound::Play(L"LevelMap.mp3", true, 100);

	// 각 액터 액션시작 사운드 지정
	m_CloudMoveStartSound = SGameEngineSound::Play(L"LevelMap_Cloud_MoveStart.mp3", false, 0);
	m_PlainsEffectSound = SGameEngineSound::Play(L"LevelMap_StageClear.mp3", false, 0);

	GlobalValue::LevelMapPlayer = m_Player;
}

void LevelMap::SceneChangeEnd()
{
	m_LevelMapStageBgm.Stop();
}

void LevelMap::SceneDebugRender()
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



#include "PlayerMaker.h"
#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>

// Static Var
SoundPlayer PlayerMaker::m_MoveStartSound;
SoundPlayer PlayerMaker::m_CantMoveSound;
SoundPlayer PlayerMaker::m_StageSelectSound;

// Static Func

// member Var
PlayerMaker::PlayerMaker()
	: m_WindowSize(FLOAT4::ZERO),
	m_AniPlayer(nullptr), m_PlayerFSM(), m_MoveTile(nullptr),
	m_MoveTileFilePath(), m_PlayerPosIndex(FLOAT4::ZERO), m_LerpPoint(),
	m_PlayerCheckPos(FLOAT4::ZERO), m_PlayerCheckDir(FLOAT4::ZERO), m_iPlayerCheckColor(-1), m_bPlayerMove(false),
	m_LerpStartPos(FLOAT4::ZERO), m_LerpEndPos(FLOAT4::ZERO), m_LerpPos(FLOAT4::ZERO), m_LerpStartMove(false), m_LerpTime(0.0f),
	m_iPlayerMakerPoint(0)
{

}

PlayerMaker::~PlayerMaker()
{

}

// member Func
void PlayerMaker::Start()
{
	// 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 이동가능한 무브타일 설정
	CreateMoveTileMap();

	// 키 생성
	PlayerMaker_CreateKey();

	// 애니메이션 생성
	PlayerMaker_CreateAnimaion();

	// FSM 생성
	PlayerMaker_CreateFSM();
}

void PlayerMaker::Update()
{
	SetPlayerPosIndex();

	m_PlayerFSM.Update();
}

void PlayerMaker::SetCloudLerpEnd()
{
	m_bPlayerMove = true;
}

void PlayerMaker::SetPlayerLerpPoint(const FLOAT4& _CurPoint, const FLOAT4& _SecondPoint, const FLOAT4& _FinalPoint)
{
	m_LerpPoint[0] = _CurPoint;
	m_LerpPoint[1] = _SecondPoint;
	m_LerpPoint[2] = _FinalPoint;
}

void PlayerMaker::PlayerPixelCheck()
{
	//m_PlayerCheckPos = GetPosition() + m_MovePos;
	//m_PlayerCheckDir = FLOAT4(m_PlayerCheckPos.ix(), m_PlayerCheckPos.iy());
	//SGameEngineWinImage* FindImage = SGameEngineResMgr::Inst().FindImage(L"LevelMap_ColMap.bmp");
	//if (nullptr != FindImage)
	//{
	//	m_iPlayerCheckColor = FindImage->GetPixelColor(m_PlayerCheckDir.ix(), m_PlayerCheckDir.iy());
	//}
}

void PlayerMaker::DebugRender()
{
	FLOAT4 PixelBottom = m_PlayerCheckDir - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), PixelBottom.ix() - 2, PixelBottom.iy() - 2, PixelBottom.ix() + 2, PixelBottom.iy() + 2);

	// 플레이어 현재 타일기준 인덱스
	FLOAT4 TilePlayerIndex = m_PlayerPosIndex;
	SGameEngineString TilePlayerIndexText = L"TilePlayerIndex";
	TilePlayerIndexText += L"X : ";
	TilePlayerIndexText += SGameEngineString::ToString(TilePlayerIndex.ix());
	TilePlayerIndexText += L"Y : ";
	TilePlayerIndexText += SGameEngineString::ToString(TilePlayerIndex.iy());
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 440, TilePlayerIndexText.c_str(), lstrlen(TilePlayerIndexText.c_str()));
}

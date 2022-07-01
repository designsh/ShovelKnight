#include "DirtBlock_Small.h"
#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>
#include <SGameEngineCollision.h>

// Static Var
SoundPlayer DirtBlock_Small::m_DritBlockSmallSound;

// Static Func

// member Var
DirtBlock_Small::DirtBlock_Small()
	: m_WindowSize(FLOAT4::ZERO),
	m_DirtBlock(nullptr), m_DirtBlockCol(nullptr), m_AniDirtBlock(nullptr), m_DirtBlockFSM(),
	m_bDropCoin(false)
{

}

DirtBlock_Small::~DirtBlock_Small()
{

}

// member Func
void DirtBlock_Small::Start()
{
	// 현재 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 충돌체 생성
	m_DirtBlockCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::UI);
	m_DirtBlockCol->SetScale({ 36, 20 });
	m_DirtBlockCol->AddStartEvent(this, &DirtBlock_Small::CollisionStart);
	m_DirtBlockCol->AddStayEvent(this, &DirtBlock_Small::CollisionStay);
	m_DirtBlockCol->AddEndEvent(this, &DirtBlock_Small::CollisionEnd);
	m_DirtBlockCol->SetCheckData(1);

	// 애니메이션 설정
	m_AniDirtBlock = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniDirtBlock->SetRenderScale({ 550, 550 });
	m_AniDirtBlock->CreateAnimation(L"DIRTSMALLIDLE", L"dirtBlock_small.bmp", 0, 0); // 기본생성 이미지
	m_AniDirtBlock->CreateAnimation(L"DIRTSMALLATT", L"dirtBlock_small.bmp", 1, 3); // 플레이어의 공격

	// FSM 설정
	m_DirtBlockFSM.CreateState(L"DirtSmall_None", this, &DirtBlock_Small::IDLEStay, &DirtBlock_Small::IDLEStart, &DirtBlock_Small::IDLEEnd);
	m_DirtBlockFSM.CreateState(L"DirtSmall_BeShot", this, &DirtBlock_Small::BeShotStay, &DirtBlock_Small::BeShotStart, &DirtBlock_Small::BeShotEnd);
	m_DirtBlockFSM.ChangeState(L"DirtSmall_None");
}

void DirtBlock_Small::Update()
{
	m_DirtBlockFSM.Update();
}

bool DirtBlock_Small::IsDropCoin()
{
	return m_bDropCoin;
}

void DirtBlock_Small::DropCoinOn()
{
	m_bDropCoin = true;
}

void DirtBlock_Small::DropCoinOff()
{
	m_bDropCoin = false;
}

void DirtBlock_Small::DebugRender()
{
	Col2DData DirtBlockSmallColData;
	DirtBlockSmallColData.m_Pos = GetCamPosition() - m_DirtBlockCol->GetPivotPos();
	DirtBlockSmallColData.m_Size = m_DirtBlockCol->GetScale();
	RECT DirtBlockSmallColRect = { DirtBlockSmallColData.iLeft(), DirtBlockSmallColData.iTop(), DirtBlockSmallColData.iRight(), DirtBlockSmallColData.iBottom() };
	FrameRect(SGameEngineWindow::GetBackBufferDC(), &DirtBlockSmallColRect, SGameEngineWindow::GetGreenBrush());
}

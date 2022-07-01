#include "DirtBlock.h"
#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>
#include <SGameEngineCollision.h>

// Static Var
SoundPlayer DirtBlock::m_DritBlockSound;

// Static Func

// member Var
DirtBlock::DirtBlock()
	: m_WindowSize(FLOAT4::ZERO),
	m_DirtBlock(nullptr), m_DirtBlockCol(nullptr), m_AniDirtBlock(nullptr), m_DirtBlockFSM(),
	m_bDropCoin(false)

{

}

DirtBlock::~DirtBlock()
{

}

// member Func
void DirtBlock::Start()
{
	// 현재 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 충돌체 생성
	m_DirtBlockCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::UI);
	m_DirtBlockCol->SetScale({ 70, 50 });
	m_DirtBlockCol->AddStartEvent(this, &DirtBlock::CollisionStart);
	m_DirtBlockCol->AddStayEvent(this, &DirtBlock::CollisionStay);
	m_DirtBlockCol->AddEndEvent(this, &DirtBlock::CollisionEnd);
	m_DirtBlockCol->SetCheckData(1);

	// 애니메이션 설정
	m_AniDirtBlock = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniDirtBlock->SetRenderScale({ 550, 550 });
	m_AniDirtBlock->CreateAnimation(L"DIRTBLOCKIDLE", L"dirtBlock.bmp", 0, 0); // 기본생성 이미지
	m_AniDirtBlock->CreateAnimation(L"DIRTBLOCKATT", L"dirtBlock.bmp", 1, 3); // 플레이어의 첫번째공격

	// FSM 설정
	m_DirtBlockFSM.CreateState(L"DirtBlock_None", this, &DirtBlock::IDLEStay, &DirtBlock::IDLEStart, &DirtBlock::IDLEEnd);
	m_DirtBlockFSM.CreateState(L"DirtBlock_BeShot", this, &DirtBlock::BeShotStay, &DirtBlock::BeShotStart, &DirtBlock::BeShotEnd);
	m_DirtBlockFSM.ChangeState(L"DirtBlock_None");
}

void DirtBlock::Update()
{
	m_DirtBlockFSM.Update();
}

bool DirtBlock::IsDropCoin()
{
	return m_bDropCoin;
}

void DirtBlock::DropCoinOn()
{
	m_bDropCoin = true;
}

void DirtBlock::DropCoinOff()
{
	m_bDropCoin = false;
}

void DirtBlock::DebugRender()
{
	Col2DData DirtBlockColData;
	DirtBlockColData.m_Pos = GetCamPosition() - m_DirtBlockCol->GetPivotPos();
	DirtBlockColData.m_Size = m_DirtBlockCol->GetScale();
	RECT DirtBlockColRect = { DirtBlockColData.iLeft(), DirtBlockColData.iTop(), DirtBlockColData.iRight(), DirtBlockColData.iBottom() };
	FrameRect(SGameEngineWindow::GetBackBufferDC(), &DirtBlockColRect, SGameEngineWindow::GetGreenBrush());
}

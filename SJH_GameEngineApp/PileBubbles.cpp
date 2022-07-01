#include "PileBubbles.h"
#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>
#include <SGameEngineCollision.h>

// Static Var

// Static Func

// member Var
PileBubbles::PileBubbles()
	: m_WindowSize(FLOAT4::ZERO), m_PileBubbles(nullptr), m_PileBubblesCol(nullptr), m_AniPileBubbles(nullptr), m_PileBubblesFSM(),
	m_MovePos(FLOAT4::ZERO), m_MoveStartPos(FLOAT4::ZERO), m_MoveTargetPos(FLOAT4::ZERO),
	m_LerpMoveTime(0.0f), m_LerpSpeed(0.0f)
{

}

PileBubbles::~PileBubbles()
{

}

// member Func
void PileBubbles::Start()
{
	// 현재 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 충돌체 생성
	m_PileBubblesCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::UI);
	m_PileBubblesCol->SetScale({ 50, 50 });
	m_PileBubblesCol->AddStartEvent(this, &PileBubbles::CollisionStart);
	m_PileBubblesCol->AddStayEvent(this, &PileBubbles::CollisionStay);
	m_PileBubblesCol->AddEndEvent(this, &PileBubbles::CollisionEnd);

	// 애니메이션 설정(처음 Off상태, 플레이어와 일정거리가 되면 On)
	m_AniPileBubbles = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniPileBubbles->SetRenderScale({ 300, 300 });
	m_AniPileBubbles->CreateAnimation(L"PILEBUBBLESIDLE", L"digPileBubbles.bmp", 0, 0); // 기본생성 이미지
	m_AniPileBubbles->CreateAnimation(L"PILEBUBBLESAPPEAR", L"digPileBubbles.bmp", 0, 3); // 등장
	m_AniPileBubbles->CreateAnimation(L"PILEBUBBLESATT", L"digPileBubbles.bmp", 4, 5); // 플레이어의 내려찍기 공격 or 일반공격시
	m_AniPileBubbles->Off();

	// FSM 설정
	m_PileBubblesFSM.CreateState(L"PilBubbles_Find", this, &PileBubbles::FindStay, &PileBubbles::FindStart, &PileBubbles::FindEnd);
	m_PileBubblesFSM.CreateState(L"PilBubbles_Appear", this, &PileBubbles::AppearStay, &PileBubbles::AppearStart, &PileBubbles::AppearEnd);
	m_PileBubblesFSM.CreateState(L"PileBubbles_None", this, &PileBubbles::IDLEStay, &PileBubbles::IDLEStart, &PileBubbles::IDLEEnd);
	m_PileBubblesFSM.CreateState(L"PileBubbles_BeShot", this, &PileBubbles::BeShotStay, &PileBubbles::BeShotStart, &PileBubbles::BeShotEnd);
	m_PileBubblesFSM.ChangeState(L"PilBubbles_Find");
}

void PileBubbles::Update()
{
	// 상태를 갱신한다.
	m_PileBubblesFSM.Update();
}

FLOAT4 PileBubbles::GetMoveStartPos()
{
	return m_MoveStartPos;
}

FLOAT4 PileBubbles::GetMoveTargetPos()
{
	return m_MoveTargetPos;
}

void PileBubbles::SetMoveStartPos(FLOAT4 _StartPos)
{
	m_MoveStartPos = _StartPos;
}

void PileBubbles::SetMoveTargetPos(FLOAT4 _TargetPos)
{
	m_MoveTargetPos = _TargetPos;
}

float PileBubbles::GetLerpSpeed()
{
	return m_LerpSpeed;
}

void PileBubbles::SetLerpSpeed(float _Speed)
{
	m_LerpSpeed = _Speed;
}

void PileBubbles::DebugRender()
{
	Col2DData PilBubblesColData;
	PilBubblesColData.m_Pos = GetCamPosition() - m_PileBubblesCol->GetPivotPos();
	PilBubblesColData.m_Size = m_PileBubblesCol->GetScale();
	RECT PilBubblesColRect = { PilBubblesColData.iLeft(), PilBubblesColData.iTop(), PilBubblesColData.iRight(), PilBubblesColData.iBottom() };
	FrameRect(SGameEngineWindow::GetBackBufferDC(), &PilBubblesColRect, SGameEngineWindow::GetGreenBrush());
}

#include "Dozedrake_AttackBubble.h"

#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>

// Static Var

// Static Func

// member Var
Dozedrake_AttackBubble::Dozedrake_AttackBubble()
	: m_WindowSize(FLOAT4::ZERO),
	m_AniAttackBubble(nullptr), m_AttackBubbleCol(nullptr), m_AttackBubbleFSM(),
	m_MoveStartPos(FLOAT4::ZERO), m_MoveEndPos(FLOAT4::ZERO), m_UpMoveEndPos(FLOAT4::ZERO), m_MovePos(FLOAT4::ZERO),
	m_fLerpTime(0.0f), m_fUpLerpSpeed(0.0f), m_fMoveLerpSpeed(0.0f), m_bFirstMoveGet(false), m_bFirstUpGet(false),
	m_fMoveDistMax(0.0f), m_fUpDistMax(0.0f)
{

}

Dozedrake_AttackBubble::~Dozedrake_AttackBubble()
{

}

// member Func
void Dozedrake_AttackBubble::Start()
{
	// 현재 윈도우 크기를 가져온다.
	m_WindowSize = SGameEngineWindow::GetSize();

	// 충돌체 생성
	m_AttackBubbleCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::UI);
	m_AttackBubbleCol->SetScale({ 50, 50 });
	m_AttackBubbleCol->AddStartEvent(this, &Dozedrake_AttackBubble::CollisionStart);
	m_AttackBubbleCol->AddStayEvent(this, &Dozedrake_AttackBubble::CollisionStay);
	m_AttackBubbleCol->AddEndEvent(this, &Dozedrake_AttackBubble::CollisionEnd);

	// 애니메이션
	m_AniAttackBubble = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniAttackBubble->SetRenderScale({ 300, 300 });
	m_AniAttackBubble->CreateAnimation(L"BubbleMove", L"Dozedrake_Attack.bmp", 0, 3);
	m_AniAttackBubble->CreateAnimation(L"BubbleDeath", L"Dozedrake_Attack.bmp", 4, 5);

	// FSM 생성
	m_AttackBubbleFSM.CreateState(L"Bubble_Move", this, &Dozedrake_AttackBubble::MoveStay, &Dozedrake_AttackBubble::MoveStart, &Dozedrake_AttackBubble::MoveEnd);
	m_AttackBubbleFSM.CreateState(L"Bubble_UpMove", this, &Dozedrake_AttackBubble::UpMoveStay, &Dozedrake_AttackBubble::UpMoveStart, &Dozedrake_AttackBubble::UpMoveEnd);
	m_AttackBubbleFSM.CreateState(L"Bubble_Death", this, &Dozedrake_AttackBubble::DeathStay, &Dozedrake_AttackBubble::DeathStart, &Dozedrake_AttackBubble::DeathEnd);
	m_AttackBubbleFSM.ChangeState(L"Bubble_Move");
}

void Dozedrake_AttackBubble::Update()
{
	m_AttackBubbleFSM.Update();
}

void Dozedrake_AttackBubble::SetMoveDistMax(float _MaxDist)
{
	m_fMoveDistMax = _MaxDist;
}

void Dozedrake_AttackBubble::SetUpDistMax(float _MaxDist)
{
	m_fUpDistMax = _MaxDist;
}

void Dozedrake_AttackBubble::SetMoveLerpSpeed(float _Speed)
{
	m_fMoveLerpSpeed = _Speed;
}

void Dozedrake_AttackBubble::SetUpLerpSpeed(float _Speed)
{
	m_fUpLerpSpeed = _Speed;
}

FLOAT4 Dozedrake_AttackBubble::GetMoveEndPos()
{
	return m_MoveEndPos;
}

float Dozedrake_AttackBubble::GetMoveMax()
{
	return m_fMoveDistMax;
}

void Dozedrake_AttackBubble::DebugRender()
{
	// 머리 앞부분 충돌체
	Col2DData BubbleColData;
	BubbleColData.m_Pos = GetCamPosition() - m_AttackBubbleCol->GetPivotPos();
	BubbleColData.m_Size = m_AttackBubbleCol->GetScale();
	RECT BubbleColRect = { BubbleColData.iLeft(), BubbleColData.iTop(), BubbleColData.iRight(), BubbleColData.iBottom() };
	if (true == m_AttackBubbleCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &BubbleColRect, SGameEngineWindow::GetGreenBrush());
	}
}

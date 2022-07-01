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
	// ���� ������ ũ�� ��������
	m_WindowSize = SGameEngineWindow::GetSize();

	// �浹ü ����
	m_PileBubblesCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::UI);
	m_PileBubblesCol->SetScale({ 50, 50 });
	m_PileBubblesCol->AddStartEvent(this, &PileBubbles::CollisionStart);
	m_PileBubblesCol->AddStayEvent(this, &PileBubbles::CollisionStay);
	m_PileBubblesCol->AddEndEvent(this, &PileBubbles::CollisionEnd);

	// �ִϸ��̼� ����(ó�� Off����, �÷��̾�� �����Ÿ��� �Ǹ� On)
	m_AniPileBubbles = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniPileBubbles->SetRenderScale({ 300, 300 });
	m_AniPileBubbles->CreateAnimation(L"PILEBUBBLESIDLE", L"digPileBubbles.bmp", 0, 0); // �⺻���� �̹���
	m_AniPileBubbles->CreateAnimation(L"PILEBUBBLESAPPEAR", L"digPileBubbles.bmp", 0, 3); // ����
	m_AniPileBubbles->CreateAnimation(L"PILEBUBBLESATT", L"digPileBubbles.bmp", 4, 5); // �÷��̾��� ������� ���� or �Ϲݰ��ݽ�
	m_AniPileBubbles->Off();

	// FSM ����
	m_PileBubblesFSM.CreateState(L"PilBubbles_Find", this, &PileBubbles::FindStay, &PileBubbles::FindStart, &PileBubbles::FindEnd);
	m_PileBubblesFSM.CreateState(L"PilBubbles_Appear", this, &PileBubbles::AppearStay, &PileBubbles::AppearStart, &PileBubbles::AppearEnd);
	m_PileBubblesFSM.CreateState(L"PileBubbles_None", this, &PileBubbles::IDLEStay, &PileBubbles::IDLEStart, &PileBubbles::IDLEEnd);
	m_PileBubblesFSM.CreateState(L"PileBubbles_BeShot", this, &PileBubbles::BeShotStay, &PileBubbles::BeShotStart, &PileBubbles::BeShotEnd);
	m_PileBubblesFSM.ChangeState(L"PilBubbles_Find");
}

void PileBubbles::Update()
{
	// ���¸� �����Ѵ�.
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

#include "GoldObject.h"
#include <SGameEngineWindow.h>

// Static Var

// Static Func

// member Var
GoldObject::GoldObject()
	: m_WindowSize(FLOAT4::ZERO),
	m_GoldObjectRenderer(nullptr), m_GoldObjectCol(nullptr), m_AniGoldObject(nullptr), m_GoldObjectFSM(),
	m_iGold(0), m_CurAniMationName(), m_AniMationName()
{

}

GoldObject::~GoldObject()
{

}

// member Func
void GoldObject::Start()
{
	// 현재 윈도우 크기를 가져온다.
	m_WindowSize = SGameEngineWindow::GetSize();

	// 충돌체 생성
	m_GoldObjectCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::UI);
	m_GoldObjectCol->SetScale({ 50, 50 });
	m_GoldObjectCol->AddStartEvent(this, &GoldObject::CollisionStart);
	m_GoldObjectCol->AddStayEvent(this, &GoldObject::CollisionStay);
	m_GoldObjectCol->AddEndEvent(this, &GoldObject::CollisionEnd);

	// 기본 몬스터 애니메이션
	m_AniGoldObject = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::GoldObject);
	m_AniGoldObject->SetRenderScale({ 150, 150 });
	m_AniGoldObject->CreateAnimation(L"1_Gold", L"GoldObject.bmp", 0, 0);    // 1골드
	m_AniGoldObject->CreateAnimation(L"5_Gold", L"GoldObject.bmp", 1, 1);    // 5골드
	m_AniGoldObject->CreateAnimation(L"10_Gold", L"GoldObject.bmp", 2, 2);    // 10골드
	m_AniGoldObject->CreateAnimation(L"20_Gold", L"GoldObject.bmp", 3, 3);    // 10골드
	m_AniGoldObject->CreateAnimation(L"50_Gold", L"GoldObject.bmp", 4, 4);    // 50골드
	m_AniGoldObject->CreateAnimation(L"100_Gold", L"GoldObject.bmp", 5, 5);  // 100골드
	m_AniGoldObject->Off();

	m_GoldObjectFSM.CreateState(L"GoldObject_Find", this, &GoldObject::FindStay, &GoldObject::FindStart, &GoldObject::FindEnd);
	m_GoldObjectFSM.CreateState(L"GoldObject_Idle", this, &GoldObject::IdleStay, &GoldObject::IdleStart, &GoldObject::IdleEnd);

	// 초기상태 지정
	m_GoldObjectFSM.ChangeState(L"GoldObject_Find");
}

void GoldObject::Update()
{
	m_GoldObjectFSM.Update();
}

void GoldObject::SetAmountOfGold(int _Gold)
{
	m_iGold = _Gold;
}

void GoldObject::ChangeAniMation(const SGameEngineString& _ChangeAniName)
{
	m_CurAniMationName = L"";
	if (1 == m_iGold)
	{
		m_CurAniMationName = L"1_";
	}
	if (5 == m_iGold)
	{
		m_CurAniMationName = L"5_";
	}
	if (10 == m_iGold)
	{
		m_CurAniMationName = L"10_";
	}
	if (20 == m_iGold)
	{
		m_CurAniMationName = L"20_";
	}
	if (50 == m_iGold)
	{
		m_CurAniMationName = L"50_";
	}
	if (100 == m_iGold)
	{
		m_CurAniMationName = L"100_";
	}

	m_AniMationName = _ChangeAniName;
	m_CurAniMationName += _ChangeAniName;

	m_AniGoldObject->ChangeAnimationContinue(m_CurAniMationName);
}

void GoldObject::DebugRender()
{
	Col2DData ColData;
	ColData.m_Pos = GetCamPosition() - m_GoldObjectCol->GetPivotPos();
	ColData.m_Size = m_GoldObjectCol->GetScale();
	RECT ColRect = { ColData.iLeft(), ColData.iTop(), ColData.iRight(), ColData.iBottom() };
	if (true == m_GoldObjectCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &ColRect, SGameEngineWindow::GetGreenBrush());
	}
}
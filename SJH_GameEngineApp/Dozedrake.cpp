#include "Dozedrake.h"

#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>

#include "ShovelKnight.h"

// Static Var
SoundPlayer Dozedrake::m_DozedrakeSound;

// Static Func

// member Var
Dozedrake::Dozedrake()
	: m_WindowSize(FLOAT4::ZERO), m_DozedrakeInfo(), 
	m_AniDozedrake(nullptr), m_BeShotDozedrake(nullptr), m_DozedrakeFSM(), m_DozedrakeHeadCol(nullptr), m_DozedrakeBodyCol(nullptr),
	m_MoveDir(GlobalValue::BasicMoveType::Left), m_PrevMoveDir(GlobalValue::BasicMoveType::None), m_Speed(100.f),
	m_MovePos(FLOAT4::ZERO), m_MaxBackPos(FLOAT4::ZERO), 
	m_BubbleEvent(), m_AttackEndEvent(), m_DeathEvent(),
	m_fBlinkImageOnTime(0.2f), m_fBlinkImageOffTime(0.3f), m_bBlinkImage(false), m_fBlinkEndTime(0.5f),
	m_MaxDist(0.0f), 
	m_RandomPos(FLOAT4::ZERO),
	m_LimitBackMove(false)
{

}

Dozedrake::~Dozedrake()
{

}

// member Func
void Dozedrake::Start()
{
	// 현재 윈도우 크기를 가져온다.
	m_WindowSize = SGameEngineWindow::GetSize();

	// 몬스터 기본 정보 셋팅
	m_DozedrakeInfo.SetHP(7);
	m_DozedrakeInfo.SetMaxHP(7);
	m_DozedrakeInfo.SetDropCoin(150);

	// 몬스터 충돌체 생성
	// 머리 앞부분의 충돌체
	m_DozedrakeHeadCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Monster);
	m_DozedrakeHeadCol->SetScale({ 130, 100 });
	m_DozedrakeHeadCol->SetPivotPos({ 130.f, 50.f });
	m_DozedrakeHeadCol->AddStartEvent(this, &Dozedrake::HeadCollisionStart);
	m_DozedrakeHeadCol->AddStayEvent(this, &Dozedrake::HeadCollisionStay);
	m_DozedrakeHeadCol->AddEndEvent(this, &Dozedrake::HeadCollisionEnd);

	// 몸체 충돌체
	m_DozedrakeBodyCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Monster);
	m_DozedrakeBodyCol->SetScale({ 300, 650 });
	m_DozedrakeBodyCol->SetPivotPos({ -105.f, -100.f });
	m_DozedrakeBodyCol->AddStartEvent(this, &Dozedrake::BodyCollisionStart);
	m_DozedrakeBodyCol->AddStayEvent(this, &Dozedrake::BodyCollisionStay);
	m_DozedrakeBodyCol->AddEndEvent(this, &Dozedrake::BodyCollisionEnd);

	// 몬스터 애니메이션
	m_AniDozedrake = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Monster);
	m_AniDozedrake->SetRenderScale({ 900, 900 });
	m_AniDozedrake->CreateAnimation(L"DozedrakeIdle", L"Dozedrake_State.bmp", 0, 11);                              // 대기상태
	m_AniDozedrake->CreateAnimation(L"DozedrakeFrontMove", L"Dozedrake_State.bmp", 12, 17);                // 앞으로 이동
	m_AniDozedrake->CreateAnimation(L"DozedrakeAttack", L"Dozedrake_State.bmp", 18, 20, 0.1f, false);     // 공격모션 -> 공격(물방울 액터생성)
	m_AniDozedrake->CreateAnimation(L"DozedrakeAttackEnd", L"Dozedrake_State.bmp", 21, 23);          // 물방울 일정거리멀어짐 -> 공격끝모션
	m_AniDozedrake->CreateAnimation(L"DozedrakeBackMove", L"Dozedrake_State.bmp", 24, 29);          // 플레이어의해 머리 피격

	// 타격 이미지
	m_BeShotDozedrake = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::Monster + 1);
	m_BeShotDozedrake->TransCenterSetting(L"Dozedrake_BeShot.bmp", { 1536.f, 1280.f });
	m_BeShotDozedrake->SetCutData(0);
	m_BeShotDozedrake->SetRenderScale({ 900, 900 });
	m_BeShotDozedrake->Off();
	
	// 몬스터 상태
	m_DozedrakeFSM.CreateState(L"Dozedrake_Find", this, &Dozedrake::FindStay, &Dozedrake::FindStart, &Dozedrake::FindEnd);                                                                                         // 플레이어 찾는중
	m_DozedrakeFSM.CreateState(L"Dozedrake_Idle", this, &Dozedrake::IdleStay, &Dozedrake::IdleStart, &Dozedrake::IdleEnd);																							  // 대기상태
	m_DozedrakeFSM.CreateState(L"Dozedrake_FrontMove", this, &Dozedrake::FrontMoveStay, &Dozedrake::FrontMoveStart, &Dozedrake::FrontMoveEnd);									     	  // 앞으로 이동
	m_DozedrakeFSM.CreateState(L"Dozedrake_AttackStart", this, &Dozedrake::AttackStartStay, &Dozedrake::AttackStartStart, &Dozedrake::AttackStartEnd);											  // 공격모션시작(물방울생성)
	m_DozedrakeFSM.CreateState(L"Dozedrake_AttackComplate", this, &Dozedrake::AttackComplateStay, &Dozedrake::AttackComplateStart, &Dozedrake::AttackComplateEnd);          // 공격모션종료(물방울과의 일정거리가되면)
	m_DozedrakeFSM.CreateState(L"Dozedrake_BackMove", this, &Dozedrake::BackMoveStay, &Dozedrake::BackMoveStart, &Dozedrake::BackMoveEnd);												  // 뒤로 이동
	m_DozedrakeFSM.CreateState(L"Dozedrake_Death", this, &Dozedrake::DeathStay, &Dozedrake::DeathStart, &Dozedrake::DeathEnd);												                              // 사망상태(체력이 0이 되면 사망)
	m_DozedrakeFSM.ChangeState(L"Dozedrake_Find");
}																													

void Dozedrake::Update()
{
	m_DozedrakeFSM.Update();

	BeShotBlink();
}

void Dozedrake::BeShotBlink()
{
	if (true == m_bBlinkImage)
	{
		m_fBlinkImageOnTime -= SGameEngineTimer::FDeltaTime(5.f);
		if (0.0f >= m_fBlinkImageOnTime)
		{
			m_BeShotDozedrake->SetCutData(m_AniDozedrake->GetCurFrame());
			m_BeShotDozedrake->On();

			m_fBlinkImageOnTime = 0.2f;
		}

		m_fBlinkImageOffTime -= SGameEngineTimer::FDeltaTime(5.f);
		if (0.0f >= m_fBlinkImageOffTime)
		{
			m_BeShotDozedrake->Off();

			m_fBlinkImageOffTime = 0.3f;
		}

		m_fBlinkEndTime -= SGameEngineTimer::FDeltaTime();
		if (0.0f >= m_fBlinkEndTime)
		{
			m_bBlinkImage = false;
			m_fBlinkEndTime = 0.5f;

			// Off 시킨다.
			m_BeShotDozedrake->Off();
		}
	}
}

void Dozedrake::MoveCheck()
{
	m_MovePos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_MovePos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_Speed);
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_MovePos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_Speed);
	}
	m_PrevMoveDir = m_MoveDir;

	MovePosition(m_MovePos);
}

void Dozedrake::AttackBubbleCreate1()
{
	Dozedrake_AttackBubble* m_Bubble = GetScene()->CreateActor<Dozedrake_AttackBubble>();
	m_Bubble->SetPosition({ GetPosition().x - m_DozedrakeHeadCol->GetPivotPos().x, GetPosition().y - m_DozedrakeHeadCol->GetPivotPos().y });
	m_Bubble->SetMoveDistMax(-280.f);
	m_Bubble->SetUpDistMax(-500.f);
	m_Bubble->SetMoveLerpSpeed(1.0f);
	m_Bubble->SetUpLerpSpeed(0.17f);
}

void Dozedrake::AttackBubbleCreate2()
{
	Dozedrake_AttackBubble* m_Bubble = GetScene()->CreateActor<Dozedrake_AttackBubble>();
	m_Bubble->SetPosition({ GetPosition().x - m_DozedrakeHeadCol->GetPivotPos().x, GetPosition().y - m_DozedrakeHeadCol->GetPivotPos().y });
	m_Bubble->SetMoveDistMax(-320.f);
	m_Bubble->SetUpDistMax(-500.f);
	m_Bubble->SetMoveLerpSpeed(1.0f);
	m_Bubble->SetUpLerpSpeed(0.15f);
}

void Dozedrake::AttackBubbleCreate3()
{
	Dozedrake_AttackBubble* m_Bubble = GetScene()->CreateActor<Dozedrake_AttackBubble>();
	m_Bubble->SetPosition({ GetPosition().x - m_DozedrakeHeadCol->GetPivotPos().x, GetPosition().y - m_DozedrakeHeadCol->GetPivotPos().y });
	m_Bubble->SetMoveDistMax(-300.f);
	m_Bubble->SetUpDistMax(-500.f);
	m_Bubble->SetMoveLerpSpeed(1.0f);
	m_Bubble->SetUpLerpSpeed(0.16f);
}

void Dozedrake::DeathEffectStart()
{

}

void Dozedrake::DeathEffectStay()
{
	// 랜덤한 좌표에 이펙트를 생성한다.
	m_RandomPos = FLOAT4::ZERO;
	
	// 랜덤좌표위치구하기
	FLOAT4 RendererScale = m_AniDozedrake->GetRenderScale();
	RendererScale = FLOAT4(RendererScale.x * 0.5f, RendererScale.y * 0.5f);

	int X = rand() % RendererScale.ix();
	int Y = rand() % RendererScale.iy();

	m_RandomPos = FLOAT4(GetPosition().x + X, GetPosition().y - Y);
	
	// 이펙트 생성하기(이펙트 애니메이션 끝나면 이펙트액터는 소멸한다)
	Dozedrake_DeathEffect* DeathEffect = GetScene()->CreateActor<Dozedrake_DeathEffect>();
	DeathEffect->SetPosition(m_RandomPos);
}

void Dozedrake::DeathEffectEnd()
{
	// 타임이벤터 종료시 나는 죽는다.
	Death();
}

void Dozedrake::AttackBubbleCreateEnd()
{
	// 마지막까지 생성완료했으므로 상태변경
	m_DozedrakeFSM.ChangeState(L"Dozedrake_AttackComplate");
}

void Dozedrake::AttackComplete()
{
	m_AniDozedrake->ChangeAnimation(L"DozedrakeAttackEnd");
}

void Dozedrake::DebugRender()
{
	// 머리 앞부분 충돌체
	Col2DData HeadFrontColData;
	HeadFrontColData.m_Pos = GetCamPosition() - m_DozedrakeHeadCol->GetPivotPos();
	HeadFrontColData.m_Size = m_DozedrakeHeadCol->GetScale();
	RECT HeadFrontColRect = { HeadFrontColData.iLeft(), HeadFrontColData.iTop(), HeadFrontColData.iRight(), HeadFrontColData.iBottom() };
	if (true == m_DozedrakeHeadCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &HeadFrontColRect, SGameEngineWindow::GetGreenBrush());
	}

	// 몸체 충돌
	Col2DData BodyColData;
	BodyColData.m_Pos = GetCamPosition() - m_DozedrakeBodyCol->GetPivotPos();
	BodyColData.m_Size = m_DozedrakeBodyCol->GetScale();
	RECT BodyColRect = { BodyColData.iLeft(), BodyColData.iTop(), BodyColData.iRight(), BodyColData.iBottom() };
	if (true == m_DozedrakeBodyCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &BodyColRect, SGameEngineWindow::GetGreenBrush());
	}
}

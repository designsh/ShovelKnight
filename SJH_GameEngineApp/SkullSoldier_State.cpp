#include "SkullSoldier.h"
#include "DropGold.h"

// 플레이어 찾는 상태
void SkullSoldier::FindStart()
{
	ChangeAniMation(L"SkullFind");
}

void SkullSoldier::FindStay()
{
	FLOAT4 Dir = GlobalValue::MainPlayer->GetPosition() - GetPosition();
	if (600.0f >= FLOAT4::Len2D(Dir))
	{
		m_SkullSoldierFSM.ChangeState(L"Skull_Move");
	}
}

void SkullSoldier::FindEnd()
{

}

// 이동상태
void SkullSoldier::MoveStart()
{
	ChangeAniMation(L"SkullMove");
}

void SkullSoldier::MoveStay()
{
	// 이동중 플레이어와 나의 위치를 비교하여 이동방향을 갱신한다.
	MyPosOnBasePlayer();

	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_SkullSoldierInfo.GetMoveSpeed());
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_SkullSoldierInfo.GetMoveSpeed());
	}

	m_MovePos = m_DirectPos;

	// 이동중 체크
	MoveStateCheck();
}

void SkullSoldier::MoveEnd()
{
	m_bDirtBlockSmallCol = false;
}

// 백무브상태
void SkullSoldier::BackMoveStart()
{
	ChangeAniMation(L"SkullMove");

	// 백무브 상태 시작 Position 저장 및 최대이동거리 생성
	m_BackMoveStartPos = GetPosition();
	m_BackMoveMaxDistance = 200.f;
}

void SkullSoldier::BackMoveStay()
{
	// 기존 이동방향을 건들지않고 또다른 방향으로 백무브한다.
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_SkullSoldierInfo.GetMoveSpeed());
		m_BackMoveDir = GlobalValue::BasicMoveType::Right;
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_SkullSoldierInfo.GetMoveSpeed());
		m_BackMoveDir = GlobalValue::BasicMoveType::Left;
	}
	m_MovePos = m_DirectPos;

	BackMoveStateCheck();
}

void SkullSoldier::BackMoveEnd()
{

}

// 공격준비상태
void SkullSoldier::AttackIdleStart()
{
	ChangeAniMation(L"SkullAttackIdle");
}

void SkullSoldier::AttackIdleStay()
{
	MyPosOnBasePlayer();

	if (true == m_AniSkullSoldier->IsEnd())
	{
		m_SkullSoldierFSM.ChangeState(L"Skull_Attack");
	}
}

void SkullSoldier::AttackIdleEnd()
{

}

// 공격상태
void SkullSoldier::AttackStart()
{
	ChangeAniMation(L"SkullAttack");

	// 공격모션 충돌체 On
	m_SkullSoldierAttackCol->On();

	// 방향에 따라서 PivotPos 결정
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_SkullSoldierAttackCol->SetPivotPos({ 30.f, 0.f });
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_SkullSoldierAttackCol->SetPivotPos({ -30.f, 0.f });
	}
}

void SkullSoldier::AttackStay()
{
	if (true == m_AniSkullSoldier->IsEnd())
	{
		m_SkullSoldierFSM.ChangeState(L"Skull_BackMove");
	}
}

void SkullSoldier::AttackEnd()
{
	// 공격모션 충돌체 On
	m_SkullSoldierAttackCol->Off();
}

// 넉백상태
void SkullSoldier::KnockBackStart()
{
	ChangeAniMation(L"SkullMove");

	// 넉백 상태시 몬스터 무적상태
	m_SkullSoldierCol->Off();

	// 넉백 상태 시작 Position 저장 및 최대이동거리 생성
	m_KnockBackStartPos = GetPosition();
	m_KnockBackMaxDistance = 200.f;
}

void SkullSoldier::KnockBackStay()
{
	// 기존 이동방향을 건들지않고 또다른 방향으로 백무브한다.
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_SkullSoldierInfo.GetMoveSpeed());
		m_KnockBackMoveDir = GlobalValue::BasicMoveType::Right;
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_SkullSoldierInfo.GetMoveSpeed());
		m_KnockBackMoveDir = GlobalValue::BasicMoveType::Left;
	}
	m_MovePos = m_DirectPos;

	KnockBackStateCheck();
}

void SkullSoldier::KnockBackEnd()
{
	// 충돌체가 다시 On되며
	m_SkullSoldierCol->On();

	// Blink중에 넉백상태가 종료되었다면 모든 Blink관련 초기화
	m_bBlinkImage = false;
	m_fBlinkImageOnTime = 0.2f;
	m_fBlinkImageOffTime = 0.3f;
	m_fBlinkImageTotalTime = 1.f;

	m_BeShotLeftSkullSoldier->Off();
	m_BeShotRightSkullSoldier->Off();
}

// 몬스터 사라지는 모션
void SkullSoldier::DieMotionStart()
{
	m_AniSkullSoldier->ChangeAnimation(L"SkullDieMotion");

	m_SkullSoldierActionSound = SGameEngineSound::Play(L"Plains_Basic_Monster_Death.mp3", false, 0);
}

void SkullSoldier::DieMotionStay()
{
	if (true == m_AniSkullSoldier->IsEnd())
	{
		// 죽으면서 골드를 드랍한다.
		DropGold* CreateDropGold = GetScene()->CreateActor<DropGold>();
		CreateDropGold->SetDropGold(m_SkullSoldierInfo.GetDropCoin());
		CreateDropGold->SetMoveSpeed(50.f);
		CreateDropGold->SetPosition({ GetPosition().x, GetPosition().y - 30.f });

		// 나는 죽는다.
		Death();
	}
}

void SkullSoldier::DieMotionEnd()
{

}

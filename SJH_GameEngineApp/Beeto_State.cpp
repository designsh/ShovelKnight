#include "Beeto.h"
#include "ShovelKnight.h"
#include "DropGold.h"

// 정지상태(대기상태)
void Beeto::FindStart()
{
	ChangeAniMation(L"BeetoFind");
}

void Beeto::FindStay()
{
	// 카메라위치와 일정거리 가까워지면
	FLOAT4 Dir = GetCamPosition();

	// Beeto Move Start
	// 카메라 범위내 들어오면 
	if (1500.0f >= FLOAT4::Len2D(Dir))
	{
		// Move State Change
		m_BeetoFSM.ChangeState(L"Beeto_Move");
	}
}

void Beeto::FindEnd()
{

}

// 이동상태
void Beeto::MoveStart()
{
	ChangeAniMation(L"BeetoMove");
}

void Beeto::MoveStay()
{
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_BeetoBasicInfo.GetMoveSpeed());
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_BeetoBasicInfo.GetMoveSpeed());
	}

	m_MovePos = m_DirectPos;

	// 이동중 체크
	MoveStateCheck();
}

void Beeto::MoveEnd()
{

}

// 사망상태
void Beeto::DieStart()
{
	// 효과음 실행
	m_BeetoActionSound = SGameEngineSound::Play(L"Plains_Basic_Monster_Death.mp3", false, 0);

	ChangeAniMation(L"BeetoDie");

	// 죽을때 점프되므로 파워설정
	m_DeathPos = FLOAT4::ZERO;
	m_DeathPower = { 0.f, -300.f };
	m_DeathGravityPower = { 0.f, 1000.f };
}

void Beeto::DieStay()
{
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		// 이동방향 반대로 이동한다.
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(100.f);
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		// 이동방향 반대로 이동한다.
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(100.f);
	}

	m_DeathPower += m_DeathGravityPower * SGameEngineTimer::FDeltaTime();
	m_DeathPos = m_DeathPower * SGameEngineTimer::FDeltaTime();

	m_MovePos = m_DirectPos + m_DeathPos;

	DieStateCheck();
}

void Beeto::DieEnd()
{
	// 죽으면서 골드를 드랍한다.
	DropGold* CreateDropGold = GetScene()->CreateActor<DropGold>();
	CreateDropGold->SetDropGold(m_BeetoBasicInfo.GetDropCoin());
	CreateDropGold->SetMoveSpeed(50.f);
	CreateDropGold->SetPosition({ GetPosition().x, GetPosition().y - 30.f });
}

void Beeto::DieMotionStart()
{
	m_AniBeeto->ChangeAnimation(L"DieMotion");
}

void Beeto::DieMotionStay()
{
	if(true == m_AniBeeto->IsEnd())
	{
		Death();
	}
}

void Beeto::DieMotionEnd()
{

}

#include "ShovelKnight.h"

// 오브젝트 탑승상태 IDLE
void ShovelKnight::RideIdleStart()
{
	ChangeAniMation(L"PlayerNone");
}

void ShovelKnight::RideIdleStay()
{
	RideIdlePos_Check();

	RideIdleState_Check();
}

void ShovelKnight::RideIdleEnd()
{

}

// 오브젝트 탑승상태 Move
void ShovelKnight::RideMoveStart()
{
	ChangeAniMation(L"PlayerMove");
}

void ShovelKnight::RideMoveStay()
{
	RideMovePos_Check();

	RideMoveState_Check();
}

void ShovelKnight::RideMoveEnd()
{

}

// 오브젝트 탑승상태 Attack
void ShovelKnight::RideAttackStart()
{
	ChangeAniMation(L"PlayerAttack");

	// 충돌체 설정
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		m_AttackCol->SetPivotPos({ 60, 0 });
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		m_AttackCol->SetPivotPos({ -60, 0 });
	}

	// 충돌체 On
	m_AttackCol->On();
}

void ShovelKnight::RideAttackStay()
{
	// 충돌체 Off
	m_AttackCol->Off();

	// 마지막 모션까지 완료시 상태변경
	if (true == m_AniPlayer->IsEnd())
	{
		m_ShovelKnightFSM.ChangeState(L"Player_RideNone");
	}
}

void ShovelKnight::RideAttackEnd()
{

}

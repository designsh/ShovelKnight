#include "ShovelKnight.h"

// ������Ʈ ž�»��� IDLE
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

// ������Ʈ ž�»��� Move
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

// ������Ʈ ž�»��� Attack
void ShovelKnight::RideAttackStart()
{
	ChangeAniMation(L"PlayerAttack");

	// �浹ü ����
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		m_AttackCol->SetPivotPos({ 60, 0 });
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		m_AttackCol->SetPivotPos({ -60, 0 });
	}

	// �浹ü On
	m_AttackCol->On();
}

void ShovelKnight::RideAttackStay()
{
	// �浹ü Off
	m_AttackCol->Off();

	// ������ ��Ǳ��� �Ϸ�� ���º���
	if (true == m_AniPlayer->IsEnd())
	{
		m_ShovelKnightFSM.ChangeState(L"Player_RideNone");
	}
}

void ShovelKnight::RideAttackEnd()
{

}

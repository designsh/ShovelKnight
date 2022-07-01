#include "ShovelKnight.h"

void ShovelKnight::CreatePlayerFSMState()
{
	// �� ���º� ����
	m_ShovelKnightFSM.CreateState(L"Player_Appear", this, &ShovelKnight::AppearStay, &ShovelKnight::AppearStart, &ShovelKnight::AppearEnd);
	m_ShovelKnightFSM.CreateState(L"Player_None", this, &ShovelKnight::IdleStay, &ShovelKnight::IdleStart, &ShovelKnight::IdleEnd);
	m_ShovelKnightFSM.CreateState(L"Player_Falling", this, &ShovelKnight::FallingStay, &ShovelKnight::FallingStart, &ShovelKnight::FallingEnd);
	m_ShovelKnightFSM.CreateState(L"Player_Move", this, &ShovelKnight::MoveStay, &ShovelKnight::MoveStart, &ShovelKnight::MoveEnd);
	m_ShovelKnightFSM.CreateState(L"Player_Ladder", this, &ShovelKnight::LadderMoveStay, &ShovelKnight::LadderMoveStart, &ShovelKnight::LadderMoveEnd);
	m_ShovelKnightFSM.CreateState(L"Player_LadderJump", this, &ShovelKnight::LadderJumpStay, &ShovelKnight::LadderJumpStart, &ShovelKnight::LadderJumpEnd);
	m_ShovelKnightFSM.CreateState(L"Player_Jump", this, &ShovelKnight::JumpStay, &ShovelKnight::JumpStart, &ShovelKnight::JumpEnd);
	m_ShovelKnightFSM.CreateState(L"Player_JumpAttack", this, &ShovelKnight::JumpAttackStay, &ShovelKnight::JumpAttackStart, &ShovelKnight::JumpAttackEnd);
	m_ShovelKnightFSM.CreateState(L"Player_JumpAttackCol", this, &ShovelKnight::JumpAttackColStay, &ShovelKnight::JumpAttackColStart, &ShovelKnight::JumpAttackColEnd);
	m_ShovelKnightFSM.CreateState(L"Player_Attack", this, &ShovelKnight::AttackStay, &ShovelKnight::AttackStart, &ShovelKnight::AttackEnd);
	m_ShovelKnightFSM.CreateState(L"Player_KnockBack", this, &ShovelKnight::KnockBackStay, &ShovelKnight::KnockBackStart, &ShovelKnight::KnockBackEnd);
	m_ShovelKnightFSM.CreateState(L"Player_Victory", this, &ShovelKnight::BossVictoryStay, &ShovelKnight::BossVictoryStart, &ShovelKnight::BossVictoryEnd);

	// ������Ʈ�� �浹�� ���º� ����
	m_ShovelKnightFSM.CreateState(L"Player_RideNone", this, &ShovelKnight::RideIdleStay, &ShovelKnight::RideIdleStart, &ShovelKnight::RideIdleEnd);
	m_ShovelKnightFSM.CreateState(L"Player_RideMove", this, &ShovelKnight::RideMoveStay, &ShovelKnight::RideMoveStart, &ShovelKnight::RideMoveEnd);
	m_ShovelKnightFSM.CreateState(L"Player_RideAttack", this, &ShovelKnight::RideAttackStay, &ShovelKnight::RideAttackStart, &ShovelKnight::RideAttackEnd);

	// ������� ����
	m_ShovelKnightFSM.CreateState(L"Player_CheetFree", this, &ShovelKnight::CheetFreeStay, &ShovelKnight::CheetFreeStart, &ShovelKnight::CheetFreeEnd);

	// �ʱ� �������(����Ϸ�ñ��� ��� Ű�� �Էµ����ʴ´�)
	m_ShovelKnightFSM.ChangeState(L"Player_Appear");
	//m_ShovelKnightFSM.ChangeState(L"Player_None"); // �׽�Ʈ�� ���� Idle���·�

}

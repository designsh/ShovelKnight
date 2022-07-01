#include "Enchantress_ShovelKnight.h"

void Enchantress_ShovelKnight::CreatePlayerFSMState()
{
	m_ShovelKnightFSM.CreateState(L"Enchantress_Player_BossFindIDLE", this, &Enchantress_ShovelKnight::BossFindIdleStay, &Enchantress_ShovelKnight::BossFindIdleStart, &Enchantress_ShovelKnight::BossFindIdleEnd);
	m_ShovelKnightFSM.CreateState(L"Enchantress_Player_BossFindMOVE", this, &Enchantress_ShovelKnight::BossFindMoveStay, &Enchantress_ShovelKnight::BossFindMoveStart, &Enchantress_ShovelKnight::BossFindMoveEnd);
	m_ShovelKnightFSM.CreateState(L"Enchantress_Player_CamLerp", this, &Enchantress_ShovelKnight::CamLerpingIdleStay, &Enchantress_ShovelKnight::CamLerpingIdleStart, &Enchantress_ShovelKnight::CamLerpingIdleEnd);
	m_ShovelKnightFSM.CreateState(L"Enchantress_Player_None", this, &Enchantress_ShovelKnight::IdleStay, &Enchantress_ShovelKnight::IdleStart, &Enchantress_ShovelKnight::IdleEnd);
	m_ShovelKnightFSM.CreateState(L"Enchantress_Player_Move", this, &Enchantress_ShovelKnight::MoveStay, &Enchantress_ShovelKnight::MoveStart, &Enchantress_ShovelKnight::MoveEnd);
	m_ShovelKnightFSM.CreateState(L"Enchantress_Player_Jump", this, &Enchantress_ShovelKnight::JumpStay, &Enchantress_ShovelKnight::JumpStart, &Enchantress_ShovelKnight::JumpEnd);
	m_ShovelKnightFSM.CreateState(L"Enchantress_Player_JumpAttack", this, &Enchantress_ShovelKnight::JumpAttackStay, &Enchantress_ShovelKnight::JumpAttackStart, &Enchantress_ShovelKnight::JumpAttackEnd);
	m_ShovelKnightFSM.CreateState(L"Enchantress_Player_JumpAttackCol", this, &Enchantress_ShovelKnight::JumpAttackColStay, &Enchantress_ShovelKnight::JumpAttackColStart, &Enchantress_ShovelKnight::JumpAttackColEnd);
	m_ShovelKnightFSM.CreateState(L"Enchantress_Player_Attack", this, &Enchantress_ShovelKnight::AttackStay, &Enchantress_ShovelKnight::AttackStart, &Enchantress_ShovelKnight::AttackEnd);
	m_ShovelKnightFSM.CreateState(L"Enchantress_Player_KnockBack", this, &Enchantress_ShovelKnight::KnockBackStay, &Enchantress_ShovelKnight::KnockBackStart, &Enchantress_ShovelKnight::KnockBackEnd);
	m_ShovelKnightFSM.CreateState(L"Enchantress_Player_ShileKnightCol", this, &Enchantress_ShovelKnight::ShildKnightColStay, &Enchantress_ShovelKnight::ShildKnightColStart, &Enchantress_ShovelKnight::ShildKnightColEnd);
	m_ShovelKnightFSM.CreateState(L"Enchantress_Player_EndingSceneChange", this, &Enchantress_ShovelKnight::EndingSceneChangeStay, &Enchantress_ShovelKnight::EndingSceneChangeStart, &Enchantress_ShovelKnight::EndingSceneChangeEnd);

	// 초기 상태
	m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_BossFindIDLE");
}

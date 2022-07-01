#include "Enchantress_FinalBoss_AttackSkill.h"

// 타겟을 찾는 상태
void Enchantress_FinalBoss_AttackSkill::FindStart()
{
	// 타겟의 위치를 찾아내며 찾았을 경우 이동방향을 결정하며 상태를 전환한다.
	m_AniAttackSkill->ChangeAnimation(L"IDLE");
}

void Enchantress_FinalBoss_AttackSkill::FindStay()
{
	if (m_MoveDir != GlobalValue::BasicMoveType::None)
	{
		m_AttackSkillFSM.ChangeState(L"Enchantress_AttackSkill_Move");
	}
}

void Enchantress_FinalBoss_AttackSkill::FindEnd()
{

}

// 이동 상태
void Enchantress_FinalBoss_AttackSkill::MoveStart()
{
	// 방향에 따라 애니메이션 생성
	ChangeAniMation(L"Move");

	// 랜더러 On
	m_AniAttackSkill->On();

	// 충돌체 On
	m_AttackSkillCol->On();
}

void Enchantress_FinalBoss_AttackSkill::MoveStay()
{
	MovePos_Check();

	MoveState_Check();
}

void Enchantress_FinalBoss_AttackSkill::MoveEnd()
{

}

// 사망 상태
void Enchantress_FinalBoss_AttackSkill::DeathStart()
{
	// 바로 죽인다.
	Death();
}

void Enchantress_FinalBoss_AttackSkill::DeathStay()
{

}

void Enchantress_FinalBoss_AttackSkill::DeathEnd()
{

}

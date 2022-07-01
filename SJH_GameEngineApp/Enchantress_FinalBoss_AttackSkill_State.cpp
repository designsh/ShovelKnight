#include "Enchantress_FinalBoss_AttackSkill.h"

// Ÿ���� ã�� ����
void Enchantress_FinalBoss_AttackSkill::FindStart()
{
	// Ÿ���� ��ġ�� ã�Ƴ��� ã���� ��� �̵������� �����ϸ� ���¸� ��ȯ�Ѵ�.
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

// �̵� ����
void Enchantress_FinalBoss_AttackSkill::MoveStart()
{
	// ���⿡ ���� �ִϸ��̼� ����
	ChangeAniMation(L"Move");

	// ������ On
	m_AniAttackSkill->On();

	// �浹ü On
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

// ��� ����
void Enchantress_FinalBoss_AttackSkill::DeathStart()
{
	// �ٷ� ���δ�.
	Death();
}

void Enchantress_FinalBoss_AttackSkill::DeathStay()
{

}

void Enchantress_FinalBoss_AttackSkill::DeathEnd()
{

}

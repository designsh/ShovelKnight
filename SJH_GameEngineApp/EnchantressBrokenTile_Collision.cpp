#include "EnchantressBrokenTile.h"
#include "Enchantress_FinalBoss_AttackSkill.h"

void EnchantressBrokenTile::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// �÷��̾��� �������� or ���ݸ�� �浹 �� ������� ��ȯ
	if ((int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		m_BrokenObjectColFSM.ChangeState(L"BrokenObjectDeath");
	}
	// ������ ��ų���ݰ� �浹 �� ������� ��ȯ
	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder() && 1 == _Other->GetCheckData())
	{
		//----------------------------------------- �丶���ݽ�ų -----------------------------------------//
		Enchantress_FinalBoss_AttackSkill* CollisionEnchantressAttackSkill = dynamic_cast<Enchantress_FinalBoss_AttackSkill*>(_Other->GetActor());
		if (nullptr != CollisionEnchantressAttackSkill)
		{
			m_BrokenObjectColFSM.ChangeState(L"BrokenObjectDeath");
		}
	}

	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder() && 2 == _Other->GetCheckData())
	{
		//----------------------------------------- �丶������ų -----------------------------------------//
		//Enchantress_FinalBoss_AttackSkill* CollisionEnchantressAttackSkill = dynamic_cast<Enchantress_FinalBoss_AttackSkill*>(_Other->GetActor());
		//if (nullptr != CollisionEnchantressAttackSkill)
		//{
		//	m_BrokenObjectColFSM.ChangeState(L"BrokenObjectDeath");
		//}
	}
}

void EnchantressBrokenTile::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void EnchantressBrokenTile::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}
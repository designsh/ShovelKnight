#include "EnchantressBrokenTile.h"
#include "Enchantress_FinalBoss_AttackSkill.h"

void EnchantressBrokenTile::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 플레이어의 점프공격 or 공격모션 충돌 시 사망상태 전환
	if ((int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		m_BrokenObjectColFSM.ChangeState(L"BrokenObjectDeath");
	}
	// 몬스터의 스킬공격과 충돌 시 사망상태 전환
	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder() && 1 == _Other->GetCheckData())
	{
		//----------------------------------------- 요마공격스킬 -----------------------------------------//
		Enchantress_FinalBoss_AttackSkill* CollisionEnchantressAttackSkill = dynamic_cast<Enchantress_FinalBoss_AttackSkill*>(_Other->GetActor());
		if (nullptr != CollisionEnchantressAttackSkill)
		{
			m_BrokenObjectColFSM.ChangeState(L"BrokenObjectDeath");
		}
	}

	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder() && 2 == _Other->GetCheckData())
	{
		//----------------------------------------- 요마리젠스킬 -----------------------------------------//
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
#include "Enchantress_FinalBoss_AttackSkill.h"
#include "Enchantress_ShovelKnight.h"
#include "EnchantressBrokenTile.h"

void Enchantress_FinalBoss_AttackSkill::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		Enchantress_ShovelKnight* CollisionPlayer = dynamic_cast<Enchantress_ShovelKnight*>(_Other->GetActor());
		if (nullptr != CollisionPlayer)
		{
			m_AttackSkillFSM.ChangeState(L"Enchantress_AttackSkill_Death");
		}
	}
}

void Enchantress_FinalBoss_AttackSkill::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Enchantress_FinalBoss_AttackSkill::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

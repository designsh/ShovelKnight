#include "BlackKnight_SkillEffect.h"

#include "ShovelKnight.h"

void BlackKnight_SkillEffect::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 플레이어의 몸체 충돌하면 사망상태로 상태 변경
	if ((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder() && 0 == _Other->GetCheckData())
	{
		ShovelKnight* CollisionPlayer = dynamic_cast<ShovelKnight*>(_Other->GetActor());
		if (nullptr != CollisionPlayer)
		{
			// 충돌했으므로 충돌체는 먼저 죽는다.
			m_SkillEffectCol->Death();

			// 상태 변경한다.
			m_SkillEffectFSM.ChangeState(L"SkillEffect_Death");
		}
	}
}

void BlackKnight_SkillEffect::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void BlackKnight_SkillEffect::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

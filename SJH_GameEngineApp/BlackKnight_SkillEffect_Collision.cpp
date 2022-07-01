#include "BlackKnight_SkillEffect.h"

#include "ShovelKnight.h"

void BlackKnight_SkillEffect::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// �÷��̾��� ��ü �浹�ϸ� ������·� ���� ����
	if ((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder() && 0 == _Other->GetCheckData())
	{
		ShovelKnight* CollisionPlayer = dynamic_cast<ShovelKnight*>(_Other->GetActor());
		if (nullptr != CollisionPlayer)
		{
			// �浹�����Ƿ� �浹ü�� ���� �״´�.
			m_SkillEffectCol->Death();

			// ���� �����Ѵ�.
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

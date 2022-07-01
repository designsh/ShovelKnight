#include "Enchantress_FinalBoss.h"

void Enchantress_FinalBoss::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// �÷��̾��� �������� or ���ݸ�� �浹ü�� �浹�ϸ� ���� ü���� ��´�.
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		// �ǰ� �������Ƿ� Flag On
		m_bBlinkImage = true;

		// ���� ü���� ��´�.
		m_EnchantressInfo.SubtractHP(1);

		// ü���� ��� �����ϸ� ���� ���¸� �����Ѵ�.
		if (0 == m_EnchantressInfo.GetHP())
		{
			m_EnchantressFSM.ChangeState(L"Enchantress_Death");
		}
	}
}

void Enchantress_FinalBoss::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Enchantress_FinalBoss::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

#include "Enchantress_FinalBoss.h"

void Enchantress_FinalBoss::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 플레이어의 점프공격 or 공격모션 충돌체와 충돌하면 나의 체력을 깍는다.
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		// 피격 당했으므로 Flag On
		m_bBlinkImage = true;

		// 나의 체력은 깎는다.
		m_EnchantressInfo.SubtractHP(1);

		// 체력을 모두 소진하면 나는 상태를 변경한다.
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

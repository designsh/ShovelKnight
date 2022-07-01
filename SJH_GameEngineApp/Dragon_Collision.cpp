#include "Dragon.h"

void Dragon::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 플레이어의 공격모션 or 점프공격모션에 충돌하며
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		// 공격 받았으므로 내 체력을 깍는다.
		m_DragonInfo.SubtractHP(1);

		if (1 == m_DragonInfo.GetHP())
		{
			// BeShot Blink Image Flag On
			m_bBlinkImage = true;
		}
		else if (0 == m_DragonInfo.GetHP())
		{
			m_DragonFSM.ChangeState(L"Dragon_Death");
		}
	}
}

void Dragon::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Dragon::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

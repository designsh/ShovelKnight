#include "Dozedrake.h"

#include "ShovelKnight.h"

// 머리 충돌
void Dozedrake::HeadCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 플레이어 공격모션 or 점프공격모션 과 충돌하면 피격
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		// Blink Flag On
		m_bBlinkImage = true;

		// 공격받았을때 나의 체력을 깍는다.
		m_DozedrakeInfo.SubtractHP(1);

		// 공격받았을때 나의 체력이 0이면 나는 죽는다.
		if (0 == m_DozedrakeInfo.GetHP())
		{
			m_bBlinkImage = false;
			m_DozedrakeFSM.ChangeState(L"Dozedrake_Death");
		}
		else // 체력 0이 아닐때 내 위치를 판단하여 각 상태로 변경한다.(기본적으로 백무브상태)
		{
			if (false == m_LimitBackMove)
			{
				m_MoveDir = GlobalValue::BasicMoveType::Right;
				m_DozedrakeFSM.ChangeState(L"Dozedrake_BackMove");
			}
		}
	}
}

void Dozedrake::HeadCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Dozedrake::HeadCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

// 몸체 충돌
void Dozedrake::BodyCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		m_bBlinkImage = false;
		m_BeShotDozedrake->Off();
	}
}

void Dozedrake::BodyCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Dozedrake::BodyCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

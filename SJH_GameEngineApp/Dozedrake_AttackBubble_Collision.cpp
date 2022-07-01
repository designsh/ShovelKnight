#include "Dozedrake_AttackBubble.h"

void Dozedrake_AttackBubble::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if (((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder() && 0 == _Other->GetCheckData()) ||
		(int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		m_AttackBubbleFSM.ChangeState(L"Bubble_Death");
	}
}

void Dozedrake_AttackBubble::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Dozedrake_AttackBubble::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

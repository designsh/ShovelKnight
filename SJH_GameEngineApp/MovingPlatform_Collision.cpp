#include "MovingPlatform.h"

#include "ShovelKnight.h"

void MovingPlatform::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void MovingPlatform::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 플레이어의 하체충돌체와 충돌중이라면
	if ((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder() && 1 == _Other->GetCheckData())
	{
		// 나의 이동방향으로 플레이어를 이동시킨다.
		if (GlobalValue::BasicMoveType::Left == m_CurDirect)
		{
			_Other->GetActor()->MovePosition({ m_PlayerMovePos.x, 0.0f });
		}
		else if(GlobalValue::BasicMoveType::Right == m_CurDirect)
		{
			_Other->GetActor()->MovePosition({ m_PlayerMovePos.x, 0.0f });
		}
		else if (GlobalValue::BasicMoveType::Up == m_CurDirect)
		{
			_Other->GetActor()->MovePosition({ 0.0f, m_PlayerMovePos.y });
		}
		else if (GlobalValue::BasicMoveType::Down == m_CurDirect)
		{
			_Other->GetActor()->MovePosition({ 0.0f, m_PlayerMovePos.y });
		}
	}
}

void MovingPlatform::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

#include "MovingPlatform.h"

#include "ShovelKnight.h"

void MovingPlatform::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void MovingPlatform::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// �÷��̾��� ��ü�浹ü�� �浹���̶��
	if ((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder() && 1 == _Other->GetCheckData())
	{
		// ���� �̵��������� �÷��̾ �̵���Ų��.
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

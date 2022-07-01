#include "Slime.h"

#include "ShovelKnight.h"
#include "DirtBlock.h"
#include "DirtBlock_Small.h"

void Slime::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 플레이어 점프공격 or 일반공격과 충돌시 피격당함
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		m_bBlinkImage = true;

		// 현재 HP를 깎고
		m_SlimeInfo.SubtractHP(1);

		// 만약 나의 HP가 소멸됬다면 나는 죽는다.
		if (0 == m_SlimeInfo.GetHP())
		{
			m_SlimeFSM.ChangeState(L"Slime_Death");
		}
	}

	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		//----------------------------------------- 흙더미 -----------------------------------------//
		DirtBlock* CollisionDirtBlock = dynamic_cast<DirtBlock*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock)
		{
			if (GlobalValue::BasicMoveType::Left == m_MoveDir)
			{
				m_MoveDir = GlobalValue::BasicMoveType::Right;
			}
			else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
			{
				m_MoveDir = GlobalValue::BasicMoveType::Left;
			}

			m_DirtBlockCol = true;
		}

		//--------------------------------------- 작은 흙더미 ----------------------------------------//
		DirtBlock_Small* CollisionDirtBlock_Small = dynamic_cast<DirtBlock_Small*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock_Small)
		{
			if (GlobalValue::BasicMoveType::Left == m_MoveDir)
			{
				m_MoveDir = GlobalValue::BasicMoveType::Right;
			}
			else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
			{
				m_MoveDir = GlobalValue::BasicMoveType::Left;
			}

			m_DirtBlockSmallCol = true;
		}
	}
}

void Slime::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Slime::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		//----------------------------------------- 흙더미 -----------------------------------------//
		DirtBlock* CollisionDirtBlock = dynamic_cast<DirtBlock*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock)
		{
			m_DirtBlockCol = false;
		}

		//--------------------------------------- 작은 흙더미 ----------------------------------------//
		DirtBlock_Small* CollisionDirtBlock_Small = dynamic_cast<DirtBlock_Small*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock_Small)
		{
			m_DirtBlockSmallCol = false;
		}
	}
}

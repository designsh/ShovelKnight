#include "SkullSoldier.h"
#include "DirtBlock.h"
#include "DirtBlock_Small.h"

// 몬스터 몸체
void SkullSoldier::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 플레이어의 공격모션 or 점프공격모션에 충돌하며
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		// 공격받으면 나의 체력을 깍고
		m_SkullSoldierInfo.SubtractHP(1);

		// 한번 공격이면 넉백
		if (1 == m_SkullSoldierInfo.GetHP())
		{
			m_bBlinkImage = true;

			m_SkullSoldierFSM.ChangeState(L"Skull_KnockBack");
		}
		// 내 체력이 없으면 죽는다.
		else if (0 == m_SkullSoldierInfo.GetHP())
		{
			m_SkullSoldierFSM.ChangeState(L"Skull_DieMotion");
		}
	}

	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		//----------------------------------------- 흙더미 -----------------------------------------//
		DirtBlock* CollisionDirtBlock = dynamic_cast<DirtBlock*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock)
		{
			m_bDirtBlockCol = true;
		}

		//--------------------------------------- 작은 흙더미 ----------------------------------------//
		DirtBlock_Small* CollisionDirtBlock_Small = dynamic_cast<DirtBlock_Small*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock_Small)
		{
			// 방향을 전환한다.
			m_bDirtBlockSmallCol = true;
		}
	}
}

void SkullSoldier::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void SkullSoldier::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

// 몬스터 공격모션
void SkullSoldier::CollisionAttackStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void SkullSoldier::CollisionAttackStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void SkullSoldier::CollisionAttackEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

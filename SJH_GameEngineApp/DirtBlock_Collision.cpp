#include "DirtBlock.h"

void DirtBlock::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		// 플레이어의 공격 모션 or 점프 공격모션과 충돌시 나는 죽는다.
		m_DirtBlockFSM.ChangeState(L"DirtBlock_BeShot");
	}
}

void DirtBlock::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void DirtBlock::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

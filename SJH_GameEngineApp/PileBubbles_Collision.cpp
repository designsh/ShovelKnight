#include "PileBubbles.h"

void PileBubbles::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 플레이어의 공격모션, 점프공격모션, 몸체 충돌시 PileBubbles_BeShot 상태로 변경하며
	// 나의 충돌체는 죽는다.
	if (((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||                                                   // 플레이어 공격모션 충돌체인 경우
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder()) ||                                          // 플레이어 점프공격모션 충돌체인 경우
		((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder() && 0 == _Other->GetCheckData()))    // 플레이어이며 플레이어 몸체 충돌체인 경우
	{
		// 상태변경
		m_PileBubblesFSM.ChangeState(L"PileBubbles_BeShot");
	}
}

void PileBubbles::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void PileBubbles::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

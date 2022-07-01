#include "DropGold.h"
#include "ShovelKnight.h"

void DropGold::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 플레이어와 충돌하면 플레이어의 보유골드량에 충돌한 골드량을 합친다.
	if ((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		GlobalValue::MainPlayer->m_PlayerInfo.AddHoldingGold(m_DropGold);

		// 충돌한 즉시 사망한다.
		Death();
	}
}

void DropGold::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void DropGold::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

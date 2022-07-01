#include "GoldObject.h"
#include "ShovelKnight.h"

void GoldObject::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder())
	{
		// 플레이어의 보유골드량에 내 골드량을 더해주고
		GlobalValue::MainPlayer->m_PlayerInfo.AddHoldingGold(m_iGold);

		// 나는 죽는다.
		Death();
	}
}

void GoldObject::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void GoldObject::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

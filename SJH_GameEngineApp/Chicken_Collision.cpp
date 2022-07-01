#include "Chicken.h"
#include "ShovelKnight.h"

void Chicken::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder())
	{
		// 플레이어의 체력을 모두 채운다.
		GlobalValue::MainPlayer->m_PlayerInfo.SetCurHP(GlobalValue::MainPlayer->m_PlayerInfo.GetMaxHP());

		// 그리고 나는 죽는다.
		Death();
	}
}

void Chicken::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Chicken::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

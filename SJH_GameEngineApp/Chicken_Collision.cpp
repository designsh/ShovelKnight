#include "Chicken.h"
#include "ShovelKnight.h"

void Chicken::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder())
	{
		// �÷��̾��� ü���� ��� ä���.
		GlobalValue::MainPlayer->m_PlayerInfo.SetCurHP(GlobalValue::MainPlayer->m_PlayerInfo.GetMaxHP());

		// �׸��� ���� �״´�.
		Death();
	}
}

void Chicken::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Chicken::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

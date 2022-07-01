#include "DropGold.h"
#include "ShovelKnight.h"

void DropGold::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// �÷��̾�� �浹�ϸ� �÷��̾��� ������差�� �浹�� ��差�� ��ģ��.
	if ((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		GlobalValue::MainPlayer->m_PlayerInfo.AddHoldingGold(m_DropGold);

		// �浹�� ��� ����Ѵ�.
		Death();
	}
}

void DropGold::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void DropGold::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

#include "GoldObject.h"
#include "ShovelKnight.h"

void GoldObject::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder())
	{
		// �÷��̾��� ������差�� �� ��差�� �����ְ�
		GlobalValue::MainPlayer->m_PlayerInfo.AddHoldingGold(m_iGold);

		// ���� �״´�.
		Death();
	}
}

void GoldObject::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void GoldObject::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

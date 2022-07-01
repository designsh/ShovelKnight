#include "Dragon.h"

void Dragon::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// �÷��̾��� ���ݸ�� or �������ݸ�ǿ� �浹�ϸ�
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		// ���� �޾����Ƿ� �� ü���� ��´�.
		m_DragonInfo.SubtractHP(1);

		if (1 == m_DragonInfo.GetHP())
		{
			// BeShot Blink Image Flag On
			m_bBlinkImage = true;
		}
		else if (0 == m_DragonInfo.GetHP())
		{
			m_DragonFSM.ChangeState(L"Dragon_Death");
		}
	}
}

void Dragon::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Dragon::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

#include "Dozedrake.h"

#include "ShovelKnight.h"

// �Ӹ� �浹
void Dozedrake::HeadCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// �÷��̾� ���ݸ�� or �������ݸ�� �� �浹�ϸ� �ǰ�
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		// Blink Flag On
		m_bBlinkImage = true;

		// ���ݹ޾����� ���� ü���� ��´�.
		m_DozedrakeInfo.SubtractHP(1);

		// ���ݹ޾����� ���� ü���� 0�̸� ���� �״´�.
		if (0 == m_DozedrakeInfo.GetHP())
		{
			m_bBlinkImage = false;
			m_DozedrakeFSM.ChangeState(L"Dozedrake_Death");
		}
		else // ü�� 0�� �ƴҶ� �� ��ġ�� �Ǵ��Ͽ� �� ���·� �����Ѵ�.(�⺻������ �鹫�����)
		{
			if (false == m_LimitBackMove)
			{
				m_MoveDir = GlobalValue::BasicMoveType::Right;
				m_DozedrakeFSM.ChangeState(L"Dozedrake_BackMove");
			}
		}
	}
}

void Dozedrake::HeadCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Dozedrake::HeadCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

// ��ü �浹
void Dozedrake::BodyCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		m_bBlinkImage = false;
		m_BeShotDozedrake->Off();
	}
}

void Dozedrake::BodyCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Dozedrake::BodyCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

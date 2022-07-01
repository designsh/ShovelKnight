#include "SkullSoldier.h"
#include "DirtBlock.h"
#include "DirtBlock_Small.h"

// ���� ��ü
void SkullSoldier::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// �÷��̾��� ���ݸ�� or �������ݸ�ǿ� �浹�ϸ�
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		// ���ݹ����� ���� ü���� ���
		m_SkullSoldierInfo.SubtractHP(1);

		// �ѹ� �����̸� �˹�
		if (1 == m_SkullSoldierInfo.GetHP())
		{
			m_bBlinkImage = true;

			m_SkullSoldierFSM.ChangeState(L"Skull_KnockBack");
		}
		// �� ü���� ������ �״´�.
		else if (0 == m_SkullSoldierInfo.GetHP())
		{
			m_SkullSoldierFSM.ChangeState(L"Skull_DieMotion");
		}
	}

	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		//----------------------------------------- ����� -----------------------------------------//
		DirtBlock* CollisionDirtBlock = dynamic_cast<DirtBlock*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock)
		{
			m_bDirtBlockCol = true;
		}

		//--------------------------------------- ���� ����� ----------------------------------------//
		DirtBlock_Small* CollisionDirtBlock_Small = dynamic_cast<DirtBlock_Small*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock_Small)
		{
			// ������ ��ȯ�Ѵ�.
			m_bDirtBlockSmallCol = true;
		}
	}
}

void SkullSoldier::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void SkullSoldier::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

// ���� ���ݸ��
void SkullSoldier::CollisionAttackStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void SkullSoldier::CollisionAttackStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void SkullSoldier::CollisionAttackEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

#include "Slime.h"

#include "ShovelKnight.h"
#include "DirtBlock.h"
#include "DirtBlock_Small.h"

void Slime::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// �÷��̾� �������� or �Ϲݰ��ݰ� �浹�� �ǰݴ���
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		m_bBlinkImage = true;

		// ���� HP�� ���
		m_SlimeInfo.SubtractHP(1);

		// ���� ���� HP�� �Ҹ��ٸ� ���� �״´�.
		if (0 == m_SlimeInfo.GetHP())
		{
			m_SlimeFSM.ChangeState(L"Slime_Death");
		}
	}

	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		//----------------------------------------- ����� -----------------------------------------//
		DirtBlock* CollisionDirtBlock = dynamic_cast<DirtBlock*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock)
		{
			if (GlobalValue::BasicMoveType::Left == m_MoveDir)
			{
				m_MoveDir = GlobalValue::BasicMoveType::Right;
			}
			else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
			{
				m_MoveDir = GlobalValue::BasicMoveType::Left;
			}

			m_DirtBlockCol = true;
		}

		//--------------------------------------- ���� ����� ----------------------------------------//
		DirtBlock_Small* CollisionDirtBlock_Small = dynamic_cast<DirtBlock_Small*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock_Small)
		{
			if (GlobalValue::BasicMoveType::Left == m_MoveDir)
			{
				m_MoveDir = GlobalValue::BasicMoveType::Right;
			}
			else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
			{
				m_MoveDir = GlobalValue::BasicMoveType::Left;
			}

			m_DirtBlockSmallCol = true;
		}
	}
}

void Slime::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Slime::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		//----------------------------------------- ����� -----------------------------------------//
		DirtBlock* CollisionDirtBlock = dynamic_cast<DirtBlock*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock)
		{
			m_DirtBlockCol = false;
		}

		//--------------------------------------- ���� ����� ----------------------------------------//
		DirtBlock_Small* CollisionDirtBlock_Small = dynamic_cast<DirtBlock_Small*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock_Small)
		{
			m_DirtBlockSmallCol = false;
		}
	}
}

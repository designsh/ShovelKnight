#include "ShovelKnight.h"

// BackDrop
#include "MovingPlatform.h" // MovingPlatform

// Object
#include "StoneObject.h"      // �������(UI)
#include "DirtBlock.h"            // �����(UI) - Big
#include "DirtBlock_Small.h" // �����(UIT) - Small
#include "PileBubbles.h"        // ���Ұ�ǰ
#include "Dozedrake_AttackBubble.h" // Dozedrake �����浹ü
#include "BlackKnight_SkillEffect.h" // Black Knight �����浹ü
#include "DropGold.h"            // ������
#include "GoldObject.h"         // ��������Ʈ

// Monster
#include "Beeto.h"                 // Beeto(Monster)
#include "SkullSoldier.h"       // SkullSoldier(Monster)
#include "Slime.h"                 // Slime(Monster)
#include "Dragon.h"              // Dragon(Monster)
#include "Dozedrake.h"         // Dozedrake(MiddleBoss)
#include "BlackKnight.h"       // BlackKnight(FinalBoss)



// ����(0)
void ShovelKnight::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		//----------------------------------------- ����� -----------------------------------------//
		DirtBlock* CollisionDirtBlock = dynamic_cast<DirtBlock*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock)
		{
			m_bDirtBlockCollision = true;
		}
		//--------------------------------------- ���� ����� ----------------------------------------//
		DirtBlock_Small* CollisionDirtBlock_Small = dynamic_cast<DirtBlock_Small*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock_Small)
		{
			m_bDirtBlockCollision = true;
		}

		//----------------------------------------- ���Ұ�ǰ -----------------------------------------//
		PileBubbles* CollisionPileBubbles = dynamic_cast<PileBubbles*>(_Other->GetActor());
		if (nullptr != CollisionPileBubbles)
		{
			// ü�°���
			m_PlayerInfo.SubtractCurHP(1);

			// ��ü�� ������ �˹���°��ȴ�.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}
		//---------------------------------- Dozedrake�� ����ü(�����) -----------------------------------//
		Dozedrake_AttackBubble* CollisionAttackBubble = dynamic_cast<Dozedrake_AttackBubble*>(_Other->GetActor());
		if (nullptr != CollisionAttackBubble)
		{
			// ü�°���
			m_PlayerInfo.SubtractCurHP(1);

			// ��ü�� ������ �˹���°��ȴ�.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}
		//--------------------------------------- Black Knight�� ����ü --------------------------------------//
		BlackKnight_SkillEffect* CollisionSkillEffect = dynamic_cast<BlackKnight_SkillEffect*>(_Other->GetActor());
		if (nullptr != CollisionSkillEffect)
		{
			// ü�°���
			m_PlayerInfo.SubtractCurHP(1);

			// ��ü�� ������ �˹���°��ȴ�.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}
		//--------------------------------------- ������ ȹ�� --------------------------------------//
		DropGold* CollisionDropGold = dynamic_cast<DropGold*>(_Other->GetActor());
		if (nullptr != CollisionDropGold)
		{
			// ������ ȹ�� ȿ���� ���
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_GoldGet.mp3", false, 0);
		}
		//------------------------------------ ��������Ʈ ȹ�� ------------------------------------//
		GoldObject* CollisionGoldObject = dynamic_cast<GoldObject*>(_Other->GetActor());
		if (nullptr != CollisionGoldObject)
		{
			// ��������Ʈ ȹ�� ȿ���� ���
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_GoldGet.mp3", false, 0);
		}
	}
	// Monster���� �浹
	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder())
	{
		//----------------------------------------- Beeto -----------------------------------------//
		Beeto* CollisionBeeto = dynamic_cast<Beeto*>(_Other->GetActor());
		if (nullptr != CollisionBeeto)
		{
			// ü�°���
			m_PlayerInfo.SubtractCurHP(1);

			// �÷��̾��� ��ü�� ���Ͱ� �浹�ϸ� �÷��̾�� �˹��Ѵ�.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}

		//----------------------------------------- Skull Soldier -----------------------------------------//
		SkullSoldier* CollisionSkullSoldier = dynamic_cast<SkullSoldier*>(_Other->GetActor());
		if (nullptr != CollisionSkullSoldier)
		{
			// ü�°���
			m_PlayerInfo.SubtractCurHP(1);

			// �÷��̾��� ��ü�� ���Ͱ� �浹�ϸ� �÷��̾�� �˹��Ѵ�.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}

		//----------------------------------------- Slime -----------------------------------------//
		Slime* CollisionSlime = dynamic_cast<Slime*>(_Other->GetActor());
		if (nullptr != CollisionSlime)
		{
			// ü�°���
			m_PlayerInfo.SubtractCurHP(1);

			// �÷��̾��� ��ü�� ���Ͱ� �浹�ϸ� �÷��̾�� �˹��Ѵ�.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}

		//----------------------------------------- Dragon -----------------------------------------//
		Dragon* CollisionDragon = dynamic_cast<Dragon*>(_Other->GetActor());
		if (nullptr != CollisionDragon)
		{
			// ü�°���
			m_PlayerInfo.SubtractCurHP(1);

			// �÷��̾��� ��ü�� ���Ͱ� �浹�ϸ� �÷��̾�� �˹��Ѵ�.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}

		//----------------------------------------- Dozedrake -----------------------------------------//
		Dozedrake* CollisionDozedrake = dynamic_cast<Dozedrake*>(_Other->GetActor());
		if (nullptr != CollisionDozedrake)
		{
			// ü�°���
			m_PlayerInfo.SubtractCurHP(1);

			// �÷��̾��� ��ü�� ���Ͱ� �浹�ϸ� �÷��̾�� �˹��Ѵ�.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}

		//----------------------------------------- BlackKnight -----------------------------------------//
		BlackKnight* CollisionBlackKnight = dynamic_cast<BlackKnight*>(_Other->GetActor());
		if (nullptr != CollisionBlackKnight)
		{
			// ü�°���
			m_PlayerInfo.SubtractCurHP(1);

			// �÷��̾��� ��ü�� ���Ͱ� �浹�ϸ� �÷��̾�� �˹��Ѵ�.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}
	}
}

void ShovelKnight::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void ShovelKnight::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		//----------------------------------------- ����� -----------------------------------------//
		DirtBlock* CollisionDirtBlock = dynamic_cast<DirtBlock*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock)
		{
			m_bDirtBlockCollision = false;
		}
		//--------------------------------------- ���� ����� ----------------------------------------//
		DirtBlock_Small* CollisionDirtBlock_Small = dynamic_cast<DirtBlock_Small*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock_Small)
		{
			m_bDirtBlockCollision = false;
		}
	}
}

// �ٴ�(1)
void ShovelKnight::BottomCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		//----------------------------------------- ����� -----------------------------------------//
		DirtBlock* CollisionDirtBlock = dynamic_cast<DirtBlock*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock)
		{
			// ���� ȿ���� ���
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

			m_ShovelKnightFSM.ChangeState(L"Player_RideNone");
		}
		//--------------------------------------- ���� ����� ----------------------------------------//
		DirtBlock_Small* CollisionDirtBlock_Small = dynamic_cast<DirtBlock_Small*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock_Small)
		{
			// ���� ȿ���� ���
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

			m_ShovelKnightFSM.ChangeState(L"Player_RideNone");
		}
	}
	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder())
	{

	}
	if ((int)GlobalValue::CollisionGroup::MovingPlatform == _Other->GetOrder())
	{
		//----------------------------------------- �����÷��� -----------------------------------------//
		MovingPlatform* CollisionMovingPlatform = dynamic_cast<MovingPlatform*>(_Other->GetActor());
		if (nullptr != CollisionMovingPlatform)
		{
			// ���� ȿ���� ���
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

			// �÷��̾� ���º���
			m_ShovelKnightFSM.ChangeState(L"Player_RideNone");
		}
	}
}

void ShovelKnight::BottomCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void ShovelKnight::BottomCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		//----------------------------------------- ����� -----------------------------------------//
		DirtBlock* CollisionDirtBlock = dynamic_cast<DirtBlock*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock)
		{
			// ���� Ű�� �ȴ�����������
			if (true == SGameEngineInput::IsFree(L"JUMP"))
			{
				m_ShovelKnightFSM.ChangeState(L"Player_Falling");
			}
		}
		//--------------------------------------- ���� ����� ----------------------------------------//
		DirtBlock_Small* CollisionDirtBlock_Small = dynamic_cast<DirtBlock_Small*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock_Small)
		{
			// ���� Ű�� �ȴ�����������
			if (true == SGameEngineInput::IsFree(L"JUMP"))
			{
				m_ShovelKnightFSM.ChangeState(L"Player_Falling");
			}
		}
	}
	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder())
	{

	}
	if ((int)GlobalValue::CollisionGroup::MovingPlatform == _Other->GetOrder())
	{
		//----------------------------------------- �����÷��� -----------------------------------------//
		MovingPlatform* CollisionMovingPlatform = dynamic_cast<MovingPlatform*>(_Other->GetActor());
		if (nullptr != CollisionMovingPlatform)
		{
			if (true == SGameEngineInput::IsFree(L"JUMP"))
			{
				m_ShovelKnightFSM.ChangeState(L"Player_Falling");
			}
		}
	}
}

// ���ݸ��
void ShovelKnight::AttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// ������Ʈ�� �浹
	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		//----------------------------------------- ������� -----------------------------------------//
		StoneObject* CollisionStone = dynamic_cast<StoneObject*>(_Other->GetActor());
		if (nullptr != CollisionStone)
		{
			// �÷��̾��� ���ݸ�ǿ� ���� ������� �̹����� �����Ѵ�.
			CollisionStone->ChangeAnimation();
		}
		//--------------------------------------- ������ ȹ�� --------------------------------------//
		DropGold* CollisionDropGold = dynamic_cast<DropGold*>(_Other->GetActor());
		if (nullptr != CollisionDropGold)
		{
			// ������ ȹ�� ȿ���� ���
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_GoldGet.mp3", false, 0);
		}
		//------------------------------------ ��������Ʈ ȹ�� ------------------------------------//
		GoldObject* CollisionGoldObject = dynamic_cast<GoldObject*>(_Other->GetActor());
		if (nullptr != CollisionGoldObject)
		{
			// ��������Ʈ ȹ�� ȿ���� ���
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_GoldGet.mp3", false, 0);
		}
	}
}

void ShovelKnight::AttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void ShovelKnight::AttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

// �������ݸ��
void ShovelKnight::JumpAttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		// �������, ������, �������� ��ų���� �����Ѵ�.
		// ������� -> m_iCheckData = 0;
		// ������ -> m_iCheckData = 0;
		// �������� ���ͽ�ų -> m_iCheckData = 0;
		// �ٸ� UI -> m_iCheckData = 1;
		if (0 != _Other->GetCheckData())
		{
			// �������ݸ�� �浹ü�� �� ������Ʈ �浹�� ȿ���� �߻�
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpAttack_Col.mp3", false, 0);

			// �浹�� �� ����� �浹ü�� Death ������� ���� �÷��̾�� ���¸� �����Ѵ�.
			m_ShovelKnightFSM.ChangeState(L"Player_JumpAttackCol");
		}
	}
	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder())
	{
		m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpAttack_Col.mp3", false, 0);

		// �浹�� �� ����� �浹ü�� Death ������� ���� �÷��̾�� ���¸� �����Ѵ�.
		m_ShovelKnightFSM.ChangeState(L"Player_JumpAttackCol");
	}
}

void ShovelKnight::JumpAttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void ShovelKnight::JumpAttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}
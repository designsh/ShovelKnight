#include "ShovelKnight.h"

// BackDrop
#include "MovingPlatform.h" // MovingPlatform

// Object
#include "StoneObject.h"      // 광산더미(UI)
#include "DirtBlock.h"            // 흙더미(UI) - Big
#include "DirtBlock_Small.h" // 흙더미(UIT) - Small
#include "PileBubbles.h"        // 말뚝거품
#include "Dozedrake_AttackBubble.h" // Dozedrake 공격충돌체
#include "BlackKnight_SkillEffect.h" // Black Knight 공격충돌체
#include "DropGold.h"            // 드랍골드
#include "GoldObject.h"         // 골드오브젝트

// Monster
#include "Beeto.h"                 // Beeto(Monster)
#include "SkullSoldier.h"       // SkullSoldier(Monster)
#include "Slime.h"                 // Slime(Monster)
#include "Dragon.h"              // Dragon(Monster)
#include "Dozedrake.h"         // Dozedrake(MiddleBoss)
#include "BlackKnight.h"       // BlackKnight(FinalBoss)



// 몸통(0)
void ShovelKnight::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		//----------------------------------------- 흙더미 -----------------------------------------//
		DirtBlock* CollisionDirtBlock = dynamic_cast<DirtBlock*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock)
		{
			m_bDirtBlockCollision = true;
		}
		//--------------------------------------- 작은 흙더미 ----------------------------------------//
		DirtBlock_Small* CollisionDirtBlock_Small = dynamic_cast<DirtBlock_Small*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock_Small)
		{
			m_bDirtBlockCollision = true;
		}

		//----------------------------------------- 말뚝거품 -----------------------------------------//
		PileBubbles* CollisionPileBubbles = dynamic_cast<PileBubbles*>(_Other->GetActor());
		if (nullptr != CollisionPileBubbles)
		{
			// 체력감소
			m_PlayerInfo.SubtractCurHP(1);

			// 몸체가 닿으면 넉백상태가된다.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}
		//---------------------------------- Dozedrake의 공격체(물방울) -----------------------------------//
		Dozedrake_AttackBubble* CollisionAttackBubble = dynamic_cast<Dozedrake_AttackBubble*>(_Other->GetActor());
		if (nullptr != CollisionAttackBubble)
		{
			// 체력감소
			m_PlayerInfo.SubtractCurHP(1);

			// 몸체가 닿으면 넉백상태가된다.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}
		//--------------------------------------- Black Knight의 공격체 --------------------------------------//
		BlackKnight_SkillEffect* CollisionSkillEffect = dynamic_cast<BlackKnight_SkillEffect*>(_Other->GetActor());
		if (nullptr != CollisionSkillEffect)
		{
			// 체력감소
			m_PlayerInfo.SubtractCurHP(1);

			// 몸체가 닿으면 넉백상태가된다.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}
		//--------------------------------------- 드랍골드 획득 --------------------------------------//
		DropGold* CollisionDropGold = dynamic_cast<DropGold*>(_Other->GetActor());
		if (nullptr != CollisionDropGold)
		{
			// 드랍골드 획득 효과음 재생
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_GoldGet.mp3", false, 0);
		}
		//------------------------------------ 골드오브젝트 획득 ------------------------------------//
		GoldObject* CollisionGoldObject = dynamic_cast<GoldObject*>(_Other->GetActor());
		if (nullptr != CollisionGoldObject)
		{
			// 골드오브젝트 획득 효과음 재생
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_GoldGet.mp3", false, 0);
		}
	}
	// Monster와의 충돌
	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder())
	{
		//----------------------------------------- Beeto -----------------------------------------//
		Beeto* CollisionBeeto = dynamic_cast<Beeto*>(_Other->GetActor());
		if (nullptr != CollisionBeeto)
		{
			// 체력감소
			m_PlayerInfo.SubtractCurHP(1);

			// 플레이어의 몸체와 몬스터가 충돌하면 플레이어는 넉백한다.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}

		//----------------------------------------- Skull Soldier -----------------------------------------//
		SkullSoldier* CollisionSkullSoldier = dynamic_cast<SkullSoldier*>(_Other->GetActor());
		if (nullptr != CollisionSkullSoldier)
		{
			// 체력감소
			m_PlayerInfo.SubtractCurHP(1);

			// 플레이어의 몸체와 몬스터가 충돌하면 플레이어는 넉백한다.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}

		//----------------------------------------- Slime -----------------------------------------//
		Slime* CollisionSlime = dynamic_cast<Slime*>(_Other->GetActor());
		if (nullptr != CollisionSlime)
		{
			// 체력감소
			m_PlayerInfo.SubtractCurHP(1);

			// 플레이어의 몸체와 몬스터가 충돌하면 플레이어는 넉백한다.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}

		//----------------------------------------- Dragon -----------------------------------------//
		Dragon* CollisionDragon = dynamic_cast<Dragon*>(_Other->GetActor());
		if (nullptr != CollisionDragon)
		{
			// 체력감소
			m_PlayerInfo.SubtractCurHP(1);

			// 플레이어의 몸체와 몬스터가 충돌하면 플레이어는 넉백한다.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}

		//----------------------------------------- Dozedrake -----------------------------------------//
		Dozedrake* CollisionDozedrake = dynamic_cast<Dozedrake*>(_Other->GetActor());
		if (nullptr != CollisionDozedrake)
		{
			// 체력감소
			m_PlayerInfo.SubtractCurHP(1);

			// 플레이어의 몸체와 몬스터가 충돌하면 플레이어는 넉백한다.
			m_ShovelKnightFSM.ChangeState(L"Player_KnockBack");
		}

		//----------------------------------------- BlackKnight -----------------------------------------//
		BlackKnight* CollisionBlackKnight = dynamic_cast<BlackKnight*>(_Other->GetActor());
		if (nullptr != CollisionBlackKnight)
		{
			// 체력감소
			m_PlayerInfo.SubtractCurHP(1);

			// 플레이어의 몸체와 몬스터가 충돌하면 플레이어는 넉백한다.
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
		//----------------------------------------- 흙더미 -----------------------------------------//
		DirtBlock* CollisionDirtBlock = dynamic_cast<DirtBlock*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock)
		{
			m_bDirtBlockCollision = false;
		}
		//--------------------------------------- 작은 흙더미 ----------------------------------------//
		DirtBlock_Small* CollisionDirtBlock_Small = dynamic_cast<DirtBlock_Small*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock_Small)
		{
			m_bDirtBlockCollision = false;
		}
	}
}

// 바닥(1)
void ShovelKnight::BottomCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		//----------------------------------------- 흙더미 -----------------------------------------//
		DirtBlock* CollisionDirtBlock = dynamic_cast<DirtBlock*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock)
		{
			// 점프 효과음 재생
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

			m_ShovelKnightFSM.ChangeState(L"Player_RideNone");
		}
		//--------------------------------------- 작은 흙더미 ----------------------------------------//
		DirtBlock_Small* CollisionDirtBlock_Small = dynamic_cast<DirtBlock_Small*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock_Small)
		{
			// 점프 효과음 재생
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

			m_ShovelKnightFSM.ChangeState(L"Player_RideNone");
		}
	}
	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder())
	{

	}
	if ((int)GlobalValue::CollisionGroup::MovingPlatform == _Other->GetOrder())
	{
		//----------------------------------------- 무빙플랫폼 -----------------------------------------//
		MovingPlatform* CollisionMovingPlatform = dynamic_cast<MovingPlatform*>(_Other->GetActor());
		if (nullptr != CollisionMovingPlatform)
		{
			// 점프 효과음 재생
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

			// 플레이어 상태변경
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
		//----------------------------------------- 흙더미 -----------------------------------------//
		DirtBlock* CollisionDirtBlock = dynamic_cast<DirtBlock*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock)
		{
			// 점프 키가 안눌려져있을때
			if (true == SGameEngineInput::IsFree(L"JUMP"))
			{
				m_ShovelKnightFSM.ChangeState(L"Player_Falling");
			}
		}
		//--------------------------------------- 작은 흙더미 ----------------------------------------//
		DirtBlock_Small* CollisionDirtBlock_Small = dynamic_cast<DirtBlock_Small*>(_Other->GetActor());
		if (nullptr != CollisionDirtBlock_Small)
		{
			// 점프 키가 안눌려져있을때
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
		//----------------------------------------- 무빙플랫폼 -----------------------------------------//
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

// 공격모션
void ShovelKnight::AttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 오브젝트와 충돌
	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		//----------------------------------------- 광산더미 -----------------------------------------//
		StoneObject* CollisionStone = dynamic_cast<StoneObject*>(_Other->GetActor());
		if (nullptr != CollisionStone)
		{
			// 플레이어의 공격모션에 따라 광산더미 이미지를 변경한다.
			CollisionStone->ChangeAnimation();
		}
		//--------------------------------------- 드랍골드 획득 --------------------------------------//
		DropGold* CollisionDropGold = dynamic_cast<DropGold*>(_Other->GetActor());
		if (nullptr != CollisionDropGold)
		{
			// 드랍골드 획득 효과음 재생
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_GoldGet.mp3", false, 0);
		}
		//------------------------------------ 골드오브젝트 획득 ------------------------------------//
		GoldObject* CollisionGoldObject = dynamic_cast<GoldObject*>(_Other->GetActor());
		if (nullptr != CollisionGoldObject)
		{
			// 골드오브젝트 획득 효과음 재생
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

// 점프공격모션
void ShovelKnight::JumpAttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		// 광산더미, 드랍골드, 최종보스 스킬들은 제외한다.
		// 광산더미 -> m_iCheckData = 0;
		// 드랍골드 -> m_iCheckData = 0;
		// 최종보스 몬스터스킬 -> m_iCheckData = 0;
		// 다른 UI -> m_iCheckData = 1;
		if (0 != _Other->GetCheckData())
		{
			// 점프공격모션 충돌체와 각 오브제트 충돌시 효과음 발생
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpAttack_Col.mp3", false, 0);

			// 충돌시 각 상대편 충돌체는 Death 모션으로 가며 플레이어는 상태를 변경한다.
			m_ShovelKnightFSM.ChangeState(L"Player_JumpAttackCol");
		}
	}
	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder())
	{
		m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpAttack_Col.mp3", false, 0);

		// 충돌시 각 상대편 충돌체는 Death 모션으로 가며 플레이어는 상태를 변경한다.
		m_ShovelKnightFSM.ChangeState(L"Player_JumpAttackCol");
	}
}

void ShovelKnight::JumpAttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void ShovelKnight::JumpAttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}
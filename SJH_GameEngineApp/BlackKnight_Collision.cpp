#include "BlackKnight.h"

// 몸체 충돌
void BlackKnight::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 플레이어 공격모션 or 점프공격 모션과 충돌하면 
	// 이미지 Blink하며 넉백상태로 변경한다.
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		// 충돌시 이미지 1초 Blink On
		m_bBlinkImage = true;

		m_BlackKnightInfo.SubtractHP(1);

		// 나의 상태 변경
		m_BlackKnightFSM.ChangeState(L"BlackKnight_KnockBack");

		// 체력설정되면 Death상태변화 추가예정
		if (0 == m_BlackKnightInfo.GetHP())
		{
			m_BlackKnightFSM.ChangeState(L"BlackKnight_Death");
		}
	}
}

void BlackKnight::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void BlackKnight::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

// 일반공격 충돌
void BlackKnight::AttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void BlackKnight::AttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void BlackKnight::AttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

// 점프공격 충돌
void BlackKnight::JumpAttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder())
	{
		m_BlackKnightActionSound = SGameEngineSound::Play(L"Plains_BlackKnight_JumpAttack_Col.mp3", false, 0);
	}
}

void BlackKnight::JumpAttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void BlackKnight::JumpAttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

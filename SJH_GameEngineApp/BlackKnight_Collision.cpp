#include "BlackKnight.h"

// ��ü �浹
void BlackKnight::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// �÷��̾� ���ݸ�� or �������� ��ǰ� �浹�ϸ� 
	// �̹��� Blink�ϸ� �˹���·� �����Ѵ�.
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		// �浹�� �̹��� 1�� Blink On
		m_bBlinkImage = true;

		m_BlackKnightInfo.SubtractHP(1);

		// ���� ���� ����
		m_BlackKnightFSM.ChangeState(L"BlackKnight_KnockBack");

		// ü�¼����Ǹ� Death���º�ȭ �߰�����
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

// �Ϲݰ��� �浹
void BlackKnight::AttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void BlackKnight::AttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void BlackKnight::AttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

// �������� �浹
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

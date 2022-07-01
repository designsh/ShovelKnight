#include "Dozedrake.h"

#include "ShovelKnight.h"

// �÷��̾� ã�� ����
void Dozedrake::FindStart()
{
	m_AniDozedrake->ChangeAnimation(L"DozedrakeIdle");
	m_DozedrakeHeadCol->Off();
	m_DozedrakeBodyCol->Off();
}

void Dozedrake::FindStay()
{
	if (nullptr == GlobalValue::MainPlayer)
	{
		return;
	}

	FLOAT4 Dist = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	if (700.f >= FLOAT4::Len2D(Dist))
	{
		m_DozedrakeFSM.ChangeState(L"Dozedrake_Idle");
	}
}

void Dozedrake::FindEnd()
{
	m_DozedrakeHeadCol->On();
	m_DozedrakeBodyCol->On();

	// �ʱ���ġ�� �����Ѵ�(���� : �鹫���Ҷ� Limit������ ����)
	m_MaxBackPos = GetPosition();
}

// ������
void Dozedrake::IdleStart()
{
	m_AniDozedrake->ChangeAnimation(L"DozedrakeIdle");
}

void Dozedrake::IdleStay()
{
	if (true == m_AniDozedrake->IsEnd())
	{
		// ���ݸ��
		m_DozedrakeFSM.ChangeState(L"Dozedrake_AttackStart");
	}
}

void Dozedrake::IdleEnd()
{

}

// ������ �̵�
void Dozedrake::FrontMoveStart()
{
	m_DozedrakeSound = SGameEngineSound::Play(L"Plains_Dragon_Move.mp3", false, 0);

	m_AniDozedrake->ChangeAnimation(L"DozedrakeFrontMove");
}

void Dozedrake::FrontMoveStay()
{
	// �÷��̾�� �����Ÿ��̸� �̵������ʰ� ���ݸ������ �����Ѵ�.
	FLOAT4 Dir = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	if (500.f >= FLOAT4::Len2D(Dir))
	{
		m_DozedrakeFSM.ChangeState(L"Dozedrake_Idle");
		return;
	}

	MoveCheck();

	if (true == m_AniDozedrake->IsEnd())
	{
		// �⺻���·� �̵�
		m_DozedrakeFSM.ChangeState(L"Dozedrake_Idle");
	}
}

void Dozedrake::FrontMoveEnd()
{

}

// �ڷ� �̵�
void Dozedrake::BackMoveStart()
{
	m_DozedrakeSound = SGameEngineSound::Play(L"Plains_Dragon_Move.mp3", false, 0);

	m_AniDozedrake->ChangeAnimation(L"DozedrakeBackMove");
}

void Dozedrake::BackMoveStay()
{
	MoveCheck();

	if (true == m_AniDozedrake->IsEnd())
	{
		// �̶� �����������̸� Flag On
		if (0.0f <= GetPosition().x - m_MaxBackPos.x)
		{
			m_LimitBackMove = true;
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}

		// �⺻���·� �̵�
		m_DozedrakeFSM.ChangeState(L"Dozedrake_Idle");
	}
}

void Dozedrake::BackMoveEnd()
{

}

// ���ݸ�� ����(����� ����)
void Dozedrake::AttackStartStart()
{
	m_DozedrakeSound = SGameEngineSound::Play(L"Plains_Dragon_Shoot.mp3", false, 0);

	m_AniDozedrake->ChangeAnimation(L"DozedrakeAttack");

	// �ð����� ����� ������ ���� Ÿ���̺��� ����
	if (0 == m_BubbleEvent.IsEventSize())
	{
		m_BubbleEvent.CreateTimeEventEnd(0.1f, this, &Dozedrake::AttackBubbleCreate1);
		m_BubbleEvent.CreateTimeEventEnd(0.3f, this, &Dozedrake::AttackBubbleCreate2);
		m_BubbleEvent.CreateTimeEventEnd(0.5f, this, &Dozedrake::AttackBubbleCreate3);
		m_BubbleEvent.CreateTimeEventEnd(1.0f, this, &Dozedrake::AttackBubbleCreateEnd);
	}

	m_BubbleEvent.Reset();
}

void Dozedrake::AttackStartStay()
{
	m_BubbleEvent.Update();
}

void Dozedrake::AttackStartEnd()
{

}

// ���ݸ�� ����(�����ð� ������ �ִϸ��̼� �����Ѵ�.)
void Dozedrake::AttackComplateStart()
{
	if (0 == m_AttackEndEvent.IsEventSize())
	{
		m_AttackEndEvent.CreateTimeEventEnd(1.f, this, &Dozedrake::AttackComplete);
	}

	m_AttackEndEvent.Reset();
}

void Dozedrake::AttackComplateStay()
{
	m_AttackEndEvent.Update();

	if (true == m_AniDozedrake->IsEnd())
	{
		m_DozedrakeFSM.ChangeState(L"Dozedrake_FrontMove");
	}
}

void Dozedrake::AttackComplateEnd()
{
	
}

// �������
void Dozedrake::DeathStart()
{
	m_DozedrakeSound = SGameEngineSound::Play(L"Plains_Dragon_Death.mp3", false, 0);

	// ��� �浹ü�� �װ�, Ÿ�̸��̺�Ʈ�� �����Ѵ�.
	m_DozedrakeHeadCol->Death();
	m_DozedrakeBodyCol->Death();

	if (0 == m_DeathEvent.IsEventSize())
	{
		m_DeathEvent.CreateTimeEvent(0.5f, this, &Dozedrake::DeathEffectEnd, &Dozedrake::DeathEffectStart, &Dozedrake::DeathEffectStay);
	}

	m_DeathEvent.Reset();
}

void Dozedrake::DeathStay()
{
	// Ÿ���̺��͸� ����Ͽ� ������Ʈ�Ѵ�.
	m_DeathEvent.Update();
}

void Dozedrake::DeathEnd()
{

}

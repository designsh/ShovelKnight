#include "Slime.h"

#include "ShovelKnight.h"
#include "DropGold.h"

// ��������(������)
void Slime::FindStart()
{
	m_AniSlime->ChangeAnimation(L"SlimeFind");
	m_SlimeCol->Off();
}

void Slime::FindStay()
{
	if (nullptr == GlobalValue::MainPlayer)
	{
		return;
	}

	FLOAT4 Dist = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	if (500.f >= FLOAT4::Len2D(Dist))
	{
		m_SlimeFSM.ChangeState(L"Slime_Move");
	}
}

void Slime::FindEnd()
{
	m_SlimeCol->On();
}

// �̵�����
void Slime::MoveStart()
{
	m_AniSlime->ChangeAnimation(L"SlimeMove");

	// �����ð� �������� ���º����� ����
	if (0 == m_JumpEventer.IsEventSize())
	{
		m_JumpEventer.CreateTimeEventEnd(m_JumpTime, this, &Slime::JumpAttackChange);
	}

	m_JumpEventer.Reset();
}

void Slime::MoveStay()
{
	// �����Ÿ� �����̴ٰ� �����ð��� �Ǹ� ����������� �����Ѵ�.
	DirPosCheck();

	m_JumpEventer.Update();
}

void Slime::MoveEnd()
{

}

// ���� ���ݻ���
void Slime::JumpAttackStart()
{
	m_AniSlime->ChangeAnimation(L"SlimeMove");

	// ���� �Ŀ�����
	m_JumpPos = FLOAT4::ZERO;
	m_JumpPower = FLOAT4({ 0.0f, -600.0f });

	m_GravityPos = FLOAT4::ZERO;
	m_GravityPower = FLOAT4({ 0.0f, 3000.0f });

	// �÷��̾�� ���� ��ġ ��
	FLOAT4 MyPos = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPos.Normalize();
	if (0.0f >= MyPos.x)
	{
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}
	else
	{
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
}

void Slime::JumpAttackStay()
{
	// �÷��̾ ���ؼ� �����̵��Ѵ�.
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_Speed * 3.f);
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_Speed * 3.f);
	}

	m_JumpPower += m_GravityPower * SGameEngineTimer::FDeltaTime();
	m_JumpPos = m_JumpPower * SGameEngineTimer::FDeltaTime();

	m_MovePos = m_DirectPos + m_JumpPos;

	// �̶� �ȼ�üũ�Ѵ�.
	SlimePixcelCol();

	// ���� �ȼ�üũ �� ���� �浹�� ������ȯ
	JumpAttackCheck();

	MovePosition(m_MovePos);
}

void Slime::JumpAttackEnd()
{

}

// �������
void Slime::DieStart()
{
	m_AniSlime->ChangeAnimation(L"SlimeDie");

	m_SlimeActionSound = SGameEngineSound::Play(L"Plains_Basic_Monster_Death.mp3", false, 0);

	// Ȥ�� Blink ȿ�����̶�� ����
	m_bBlinkImage = false;
	m_BeShotSlime->Off();
}

void Slime::DieStay()
{
	if (true == m_AniSlime->IsEnd())
	{
		// �����鼭 ��带 ����Ѵ�.(5���)
		DropGold* CreateDropGold5 = GetScene()->CreateActor<DropGold>();
		CreateDropGold5->SetDropGold(5);
		CreateDropGold5->SetMoveSpeed(50.f);
		CreateDropGold5->SetPosition({ GetPosition().x, GetPosition().y - 30.f });

		// �����鼭 ��带 ����Ѵ�.(10���)
		DropGold* CreateDropGold10 = GetScene()->CreateActor<DropGold>();
		CreateDropGold10->SetDropGold(10);
		CreateDropGold10->SetMoveSpeed(70.f);
		CreateDropGold10->SetPosition({ GetPosition().x, GetPosition().y - 30.f });

		Death();
	}
}

void Slime::DieEnd()
{

}

#include "Beeto.h"
#include "ShovelKnight.h"
#include "DropGold.h"

// ��������(������)
void Beeto::FindStart()
{
	ChangeAniMation(L"BeetoFind");
}

void Beeto::FindStay()
{
	// ī�޶���ġ�� �����Ÿ� ���������
	FLOAT4 Dir = GetCamPosition();

	// Beeto Move Start
	// ī�޶� ������ ������ 
	if (1500.0f >= FLOAT4::Len2D(Dir))
	{
		// Move State Change
		m_BeetoFSM.ChangeState(L"Beeto_Move");
	}
}

void Beeto::FindEnd()
{

}

// �̵�����
void Beeto::MoveStart()
{
	ChangeAniMation(L"BeetoMove");
}

void Beeto::MoveStay()
{
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_BeetoBasicInfo.GetMoveSpeed());
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_BeetoBasicInfo.GetMoveSpeed());
	}

	m_MovePos = m_DirectPos;

	// �̵��� üũ
	MoveStateCheck();
}

void Beeto::MoveEnd()
{

}

// �������
void Beeto::DieStart()
{
	// ȿ���� ����
	m_BeetoActionSound = SGameEngineSound::Play(L"Plains_Basic_Monster_Death.mp3", false, 0);

	ChangeAniMation(L"BeetoDie");

	// ������ �����ǹǷ� �Ŀ�����
	m_DeathPos = FLOAT4::ZERO;
	m_DeathPower = { 0.f, -300.f };
	m_DeathGravityPower = { 0.f, 1000.f };
}

void Beeto::DieStay()
{
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		// �̵����� �ݴ�� �̵��Ѵ�.
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(100.f);
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		// �̵����� �ݴ�� �̵��Ѵ�.
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(100.f);
	}

	m_DeathPower += m_DeathGravityPower * SGameEngineTimer::FDeltaTime();
	m_DeathPos = m_DeathPower * SGameEngineTimer::FDeltaTime();

	m_MovePos = m_DirectPos + m_DeathPos;

	DieStateCheck();
}

void Beeto::DieEnd()
{
	// �����鼭 ��带 ����Ѵ�.
	DropGold* CreateDropGold = GetScene()->CreateActor<DropGold>();
	CreateDropGold->SetDropGold(m_BeetoBasicInfo.GetDropCoin());
	CreateDropGold->SetMoveSpeed(50.f);
	CreateDropGold->SetPosition({ GetPosition().x, GetPosition().y - 30.f });
}

void Beeto::DieMotionStart()
{
	m_AniBeeto->ChangeAnimation(L"DieMotion");
}

void Beeto::DieMotionStay()
{
	if(true == m_AniBeeto->IsEnd())
	{
		Death();
	}
}

void Beeto::DieMotionEnd()
{

}

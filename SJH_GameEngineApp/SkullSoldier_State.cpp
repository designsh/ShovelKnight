#include "SkullSoldier.h"
#include "DropGold.h"

// �÷��̾� ã�� ����
void SkullSoldier::FindStart()
{
	ChangeAniMation(L"SkullFind");
}

void SkullSoldier::FindStay()
{
	FLOAT4 Dir = GlobalValue::MainPlayer->GetPosition() - GetPosition();
	if (600.0f >= FLOAT4::Len2D(Dir))
	{
		m_SkullSoldierFSM.ChangeState(L"Skull_Move");
	}
}

void SkullSoldier::FindEnd()
{

}

// �̵�����
void SkullSoldier::MoveStart()
{
	ChangeAniMation(L"SkullMove");
}

void SkullSoldier::MoveStay()
{
	// �̵��� �÷��̾�� ���� ��ġ�� ���Ͽ� �̵������� �����Ѵ�.
	MyPosOnBasePlayer();

	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_SkullSoldierInfo.GetMoveSpeed());
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_SkullSoldierInfo.GetMoveSpeed());
	}

	m_MovePos = m_DirectPos;

	// �̵��� üũ
	MoveStateCheck();
}

void SkullSoldier::MoveEnd()
{
	m_bDirtBlockSmallCol = false;
}

// �鹫�����
void SkullSoldier::BackMoveStart()
{
	ChangeAniMation(L"SkullMove");

	// �鹫�� ���� ���� Position ���� �� �ִ��̵��Ÿ� ����
	m_BackMoveStartPos = GetPosition();
	m_BackMoveMaxDistance = 200.f;
}

void SkullSoldier::BackMoveStay()
{
	// ���� �̵������� �ǵ����ʰ� �Ǵٸ� �������� �鹫���Ѵ�.
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_SkullSoldierInfo.GetMoveSpeed());
		m_BackMoveDir = GlobalValue::BasicMoveType::Right;
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_SkullSoldierInfo.GetMoveSpeed());
		m_BackMoveDir = GlobalValue::BasicMoveType::Left;
	}
	m_MovePos = m_DirectPos;

	BackMoveStateCheck();
}

void SkullSoldier::BackMoveEnd()
{

}

// �����غ����
void SkullSoldier::AttackIdleStart()
{
	ChangeAniMation(L"SkullAttackIdle");
}

void SkullSoldier::AttackIdleStay()
{
	MyPosOnBasePlayer();

	if (true == m_AniSkullSoldier->IsEnd())
	{
		m_SkullSoldierFSM.ChangeState(L"Skull_Attack");
	}
}

void SkullSoldier::AttackIdleEnd()
{

}

// ���ݻ���
void SkullSoldier::AttackStart()
{
	ChangeAniMation(L"SkullAttack");

	// ���ݸ�� �浹ü On
	m_SkullSoldierAttackCol->On();

	// ���⿡ ���� PivotPos ����
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_SkullSoldierAttackCol->SetPivotPos({ 30.f, 0.f });
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_SkullSoldierAttackCol->SetPivotPos({ -30.f, 0.f });
	}
}

void SkullSoldier::AttackStay()
{
	if (true == m_AniSkullSoldier->IsEnd())
	{
		m_SkullSoldierFSM.ChangeState(L"Skull_BackMove");
	}
}

void SkullSoldier::AttackEnd()
{
	// ���ݸ�� �浹ü On
	m_SkullSoldierAttackCol->Off();
}

// �˹����
void SkullSoldier::KnockBackStart()
{
	ChangeAniMation(L"SkullMove");

	// �˹� ���½� ���� ��������
	m_SkullSoldierCol->Off();

	// �˹� ���� ���� Position ���� �� �ִ��̵��Ÿ� ����
	m_KnockBackStartPos = GetPosition();
	m_KnockBackMaxDistance = 200.f;
}

void SkullSoldier::KnockBackStay()
{
	// ���� �̵������� �ǵ����ʰ� �Ǵٸ� �������� �鹫���Ѵ�.
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_SkullSoldierInfo.GetMoveSpeed());
		m_KnockBackMoveDir = GlobalValue::BasicMoveType::Right;
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_SkullSoldierInfo.GetMoveSpeed());
		m_KnockBackMoveDir = GlobalValue::BasicMoveType::Left;
	}
	m_MovePos = m_DirectPos;

	KnockBackStateCheck();
}

void SkullSoldier::KnockBackEnd()
{
	// �浹ü�� �ٽ� On�Ǹ�
	m_SkullSoldierCol->On();

	// Blink�߿� �˹���°� ����Ǿ��ٸ� ��� Blink���� �ʱ�ȭ
	m_bBlinkImage = false;
	m_fBlinkImageOnTime = 0.2f;
	m_fBlinkImageOffTime = 0.3f;
	m_fBlinkImageTotalTime = 1.f;

	m_BeShotLeftSkullSoldier->Off();
	m_BeShotRightSkullSoldier->Off();
}

// ���� ������� ���
void SkullSoldier::DieMotionStart()
{
	m_AniSkullSoldier->ChangeAnimation(L"SkullDieMotion");

	m_SkullSoldierActionSound = SGameEngineSound::Play(L"Plains_Basic_Monster_Death.mp3", false, 0);
}

void SkullSoldier::DieMotionStay()
{
	if (true == m_AniSkullSoldier->IsEnd())
	{
		// �����鼭 ��带 ����Ѵ�.
		DropGold* CreateDropGold = GetScene()->CreateActor<DropGold>();
		CreateDropGold->SetDropGold(m_SkullSoldierInfo.GetDropCoin());
		CreateDropGold->SetMoveSpeed(50.f);
		CreateDropGold->SetPosition({ GetPosition().x, GetPosition().y - 30.f });

		// ���� �״´�.
		Death();
	}
}

void SkullSoldier::DieMotionEnd()
{

}

#include "ShovelKnight.h"

// ���� ����
void ShovelKnight::AppearStart()
{
	ChangeAniMation(L"PlayerAppear");
}

void ShovelKnight::AppearStay()
{
	m_fAngle += SGameEngineTimer::FDeltaTime(45.f);
	FLOAT4 Dir = FLOAT4::AngleToDir2DDeg(m_fAngle);
	if (175.f > m_fAngle)
	{
		m_AniPlayer->SetPivotPos(Dir * -100.f);
	}

	// ���� �ִϸ��̼��������� ������ �ִϸ��̼��������̸� ����Ϸ�
	// �Ϻη� ����� �ִϸ��̼Ǻ��� 1���� ũ�� ����
	// ���� ����� ( 36, 42 ) -> ������ ( 36, 43 )
	if (false == m_bAppearIdle) // �ӽ� ���� ����ǰ��� isplayingüũ�� �ؾ��ϱ� ������
	{
		if (true == m_AniPlayer->IsEnd())
		{
			// ����׼� ������ ���� ���
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_AppearEnd.mp3", false, 0);
			m_bAppearIdle = true;
		}
	}

	if (true == m_bAppearIdle)
	{
		if (false == m_ActionSound.IsPlaying(m_bEffectSound))
		{
			m_ShovelKnightFSM.ChangeState(L"Player_None");
		}
	}
}

void ShovelKnight::AppearEnd()
{
	// �÷��̾���ġ�� �÷��̾�üũ��ġ�� ������ 
	m_AniPlayer->SetPivotPos({ 0.0f, 0.0f });
	SetPosition(FLOAT4({ 230.f, 2749.f }));

	// ������� ����(��������� �ݺ��ϴ� ������ �����Ѵ�)
	m_StageBgm = SGameEngineSound::Play(L"Stage.mp3", true, 100);
}

// ���(����) ����
void ShovelKnight::IdleStart()
{
	ChangeAniMation(L"PlayerNone");
}

void ShovelKnight::IdleStay()
{
	// ���� ���� ����
	IdlePos_Check();

	// �̵��� ���� �ȼ� �� üũ
	IdleState_Check();
}

void ShovelKnight::IdleEnd()
{

}

// Falling ����
void ShovelKnight::FallingStart()
{
	ChangeAniMation(L"PlayerJumpStay");
}

void ShovelKnight::FallingStay()
{
	FallingPos_Check();

	FallingState_Check();
}

void ShovelKnight::FallingEnd()
{
	m_GravityPos = FLOAT4::ZERO;
}

// �⺻�̵� ����(��, ��)
void ShovelKnight::MoveStart()
{
	ChangeAniMation(L"PlayerMove");
}

void ShovelKnight::MoveStay()
{
	MovePos_Check();

	MoveState_Check();
}

void ShovelKnight::MoveEnd()
{
	// �̵����� �ʱ�ȭ(Ȥ�ø���)
	m_DirectPos = FLOAT4::ZERO;
}

// ��ٸ��̵� ����(��, ��)
void ShovelKnight::LadderMoveStart()
{
	m_AniPlayer->ChangeAnimation(L"PlayerLadderMove");
}

void ShovelKnight::LadderMoveStay()
{
	LadderMovePos_Check();

	LadderMoveState_Check();
}

void ShovelKnight::LadderMoveEnd()
{
	m_LadderPrevMoveDir = GlobalValue::BasicMoveType::None;
	m_bLadderCollision = false;
	m_DirectPos = FLOAT4::ZERO;
}

// ��ٸ� �̵��� ����
void ShovelKnight::LadderJumpStart()
{
	// �ִϸ��̼� ����
	ChangeAniMation(L"PlayerJumpStay");

	// ���� ȿ���� ���
	m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpStart.mp3", false, 0);
}

void ShovelKnight::LadderJumpStay()
{
	LadderJumpPos_Check();

	LadderJumpState_Check();
}

void ShovelKnight::LadderJumpEnd()
{

}

// ���� ����
void ShovelKnight::HighJumpCheckEvent()
{
	if (true == SGameEngineInput::IsPress(L"JUMP"))
	{
		m_JumpPower.y = -800.0f;
	}

	if (m_JumpPower.y <= -800.0f)
	{
		m_JumpPower.y = -800.0f;
	}
}

void ShovelKnight::LowJumpCheckEvent()
{
	if (true == SGameEngineInput::IsPress(L"JUMP"))
	{
		m_JumpPower.y = -400.0f;
	}

	if (m_JumpPower.y <= -400.0f)
	{
		m_JumpPower.y = -400.0f;
	}
}

void ShovelKnight::JumpStart()
{
	// �ִϸ��̼� ����
	ChangeAniMation(L"PlayerJumpStart");

	// ���� ȿ���� ���
	m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpStart.mp3", false, 0);

	// ����, �߷� ����
	m_JumpPos = FLOAT4::ZERO;
	m_JumpPower = FLOAT4({ 0.0f, -600.0f });

	m_GravityPos = FLOAT4::ZERO;
	m_JumpGravityPowerPos = FLOAT4({ 0.0f, 3000.0f });

	// �������������� Ÿ���̺��ͻ���
	if (0 == m_JumpEventer.IsEventSize())
	{
		m_JumpEventer.CreateTimeEventStay(0.1f, this, &ShovelKnight::LowJumpCheckEvent);
		m_JumpEventer.CreateTimeEventStay(0.1f, this, &ShovelKnight::HighJumpCheckEvent);
	}
	m_JumpEventer.Reset();
}

void ShovelKnight::JumpStay()
{
	m_JumpEventer.Update();

	JumpPos_Check();

	JumpState_Check();
}

void ShovelKnight::JumpEnd()
{

}

// �������� ����
void ShovelKnight::JumpAttackStart()
{
	ChangeAniMation(L"PlayerJumpAttack");

	// �浹ü ����
	m_JumpAttackCol->SetPivotPos({ 0, -50 });

	// �������ݸ�� �浹ü On
	m_JumpAttackCol->On();

	// 
	m_JumpPos = FLOAT4(0.f, -200.f);
	m_JumpGravityPowerPos = FLOAT4({ 0.0f, 3000.0f });
}

void ShovelKnight::JumpAttackStay()
{
	JumpAttackPos_Check();

	JumpAttackState_Check();
}

void ShovelKnight::JumpAttackEnd()
{
	// �������ݸ�� �浹ü Off
	m_JumpAttackCol->Off();
}

// ��������(Object or Monster �浹)
void ShovelKnight::JumpAttackColStart()
{
	// ����, �߷� ����
	m_JumpPos = FLOAT4::ZERO;
	m_JumpPower = FLOAT4({ 0.0f, -1000.0f });

	m_GravityPos = FLOAT4::ZERO;
	m_JumpGravityPowerPos = FLOAT4({ 0.0f, 3000.0f });

	// ���� �ݸ��� On
	m_JumpAttackCol->On();
}

void ShovelKnight::JumpAttackColStay()
{
	JumpAttackColPos_Check();

	JumpAttackColState_Check();
}

void ShovelKnight::JumpAttackColEnd()
{
	m_JumpAttackCol->Off();
}

// �⺻���� ����
void ShovelKnight::AttackStart()
{
	ChangeAniMation(L"PlayerAttack");

	// ���� ȿ���� ���
	m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_Attack.mp3", false, 0);

	// �浹ü ����
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		m_AttackCol->SetPivotPos({ 60, 0 });
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		m_AttackCol->SetPivotPos({ -60, 0 });
	}

	// �浹ü On
	m_AttackCol->On();
}

void ShovelKnight::AttackStay()
{
	// �浹ü Off
	m_AttackCol->Off();

	// ���� �߿� ���û��·� ����Ǿ��ٸ�
	if (true == m_bJumping)
	{
		m_JumpPower += m_JumpGravityPowerPos * SGameEngineTimer::FDeltaTime();
		m_JumpPos = m_JumpPower * SGameEngineTimer::FDeltaTime();

		m_MovePos = m_JumpPos;

		JumpState_Check();
		return;
	}

	// ������ ��Ǳ��� �Ϸ�� ���º���
	if (true == m_AniPlayer->IsEnd())
	{
		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}
}

void ShovelKnight::AttackEnd()
{
	m_bJumping = false;
}

// �˹� ����
// ���İ� ����
void ShovelKnight::HitAlphaInStart()
{
	m_AniPlayer->SetAlpha(100);
}
void ShovelKnight::HitAlphaInStay()
{

}
void ShovelKnight::HitAlphaInEnd()
{
	m_AniPlayer->SetAlpha(255);
}

void ShovelKnight::HitAlphaOutStart()
{
	m_AniPlayer->SetAlpha(255);
}
void ShovelKnight::HitAlphaOutStay()
{

}
void ShovelKnight::HitAlphaOutEnd()
{
	m_AniPlayer->SetAlpha(100);
}

void ShovelKnight::KnockBackStart()
{
	// ȿ���� ����
	m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_KnockBack.mp3", false, 0);

	// �˹� �Ŀ��� ����
	m_KnockBackPos = FLOAT4::ZERO;
	m_KnockBackPower = FLOAT4({ 0.0f, -300.0f });
	m_KnockBackGravityPowerPos = FLOAT4({ 0.0f, 1000.0f });

	// �浹ü Off
	m_PlayerCol->Off();

	// �ִϸ��̼� ����
	ChangeAniMation(L"PlayerKnockBack");

	// ���� ����(�����Ÿ�)
	if (0 == m_KnockBackEventer.IsEventSize())
	{
		m_KnockBackEventer.CreateTimeEvent(0.1f, this, &ShovelKnight::HitAlphaInEnd, &ShovelKnight::HitAlphaInStart, &ShovelKnight::HitAlphaInStay);
		m_KnockBackEventer.CreateTimeEvent(0.1f, this, &ShovelKnight::HitAlphaOutEnd, &ShovelKnight::HitAlphaOutStart, &ShovelKnight::HitAlphaOutStay);
		m_KnockBackEventer.LoopOn();
	}
}

void ShovelKnight::KnockBackStay()
{
	m_KnockBackEventer.Update();

	KnockBackPos_Check();

	KnockBackState_Check();
}

void ShovelKnight::KnockBackEnd()
{
	// �˹�Ϸ�Ǹ� �浹ü On
	m_PlayerCol->On();

	// ���ĺ귻�� �������
	m_AniPlayer->SetAlpha(255);
}

// ����óġ(�¸�)
void ShovelKnight::BossVictoryStart()
{
	// �ӽ� ��ġ����
	m_AniPlayer->SetPivotPos({ 0.f, -10.f });

	ChangeAniMation(L"PlayerVictory");
}

void ShovelKnight::BossVictoryStay()
{
	// ���������� �ð�����Ͽ� ��带 ������Ų��.
	int AddGold = static_cast<int>(SGameEngineTimer::FDeltaTime(200.f));
	m_PlayerInfo.AddHoldingGold(AddGold);

	// ���� ����� ���¸� �����Ѵ�.
	if (false == m_StageBgm.IsPlaying(false))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}
}

void ShovelKnight::BossVictoryEnd()
{
	m_AniPlayer->SetPivotPos({ 0.f, 0.f });
}

void ShovelKnight::CheetFreeStart()
{
	ChangeAniMation(L"PlayerNone");
}

void ShovelKnight::CheetFreeStay()
{
	// ��� ����, ��� ������Ʈ�� �����ϰ� �̵��Ѵ�.
	// �ʷϻ��� ������ �����ϸ� �������� ������ �̵��� �Ұ��ϰ� �ȴ�.
	m_DirectPos = FLOAT4::ZERO;
	if (true == SGameEngineInput::IsPress(L"LEFT"))
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Left;

		m_LadderPrevMoveDir = GlobalValue::BasicMoveType::None;
	}
	else if (true == SGameEngineInput::IsPress(L"RIGHT"))
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Right;

		m_LadderPrevMoveDir = GlobalValue::BasicMoveType::None;
	}

	if (true == SGameEngineInput::IsPress(L"LADDERUP"))
	{
		m_DirectPos += FLOAT4::UP * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_LadderPrevMoveDir = GlobalValue::BasicMoveType::Up;
	}
	else if (true == SGameEngineInput::IsPress(L"LADDERDOWN"))
	{
		m_DirectPos += FLOAT4::DOWN * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_LadderPrevMoveDir = GlobalValue::BasicMoveType::Down;
	}

	m_MovePos = m_DirectPos;

	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		// �������� ������ ����Ұ�
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
		// �ʷϻ��� ������ ī�޶� ����
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_bWallCollision = true;
		}
		// ����Ÿ�� ������ ������ ����
		if (RGB(255, 0, 255) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_bWallCollision = true;
			m_bFinalBossRoom = true;
		}
	}
	if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		// �������� ������ ����Ұ�
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
		// �ʷϻ��� ������ ī�޶� ����
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_bWallCollision = true;
		}
		// ����Ÿ�� ������ ������ ����
		if (RGB(255, 0, 255) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_bWallCollision = true;
			m_bFinalBossRoom = true;
		}
	}
	if (m_LadderPrevMoveDir == GlobalValue::BasicMoveType::Up)
	{
		// �������� ������ ����Ұ�
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Top])
		{
			m_MovePos.y = 0.0f;
		}

		// �ʷϻ��� ������ ī�޶� ����
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Top])
		{
			m_bWallCollision = true;
		}
	}
	else if (m_LadderPrevMoveDir == GlobalValue::BasicMoveType::Down)
	{
		// �������� ������ ����Ұ�
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			m_MovePos.y = 0.0f;
		}

		// �ʷϻ��� ������ ī�޶� ����
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			m_bWallCollision = true;
		}
	}
}

void ShovelKnight::CheetFreeEnd()
{
	m_PlayerInfo.SetMoveSpeed(200.f);
	m_LadderPrevMoveDir = GlobalValue::BasicMoveType::None;
}

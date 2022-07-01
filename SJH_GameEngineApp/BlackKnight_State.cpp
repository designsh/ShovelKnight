#include "BlackKnight.h"
#include "BlackKnight_SkillEffect.h"

// �����Ÿ��� ī�޶� ã���ִ� ����
void BlackKnight::FindStart()
{
	ChangeAniMation(L"BlackKnight_Laugh");
	m_BlackKnightCol->Off();
}

void BlackKnight::FindStay()
{
	// �÷��̾�� �����Ÿ��� �Ǹ� ü�� ��������
	FLOAT4 Dir = GlobalValue::MainPlayer->GetPosition() - GetPosition();
	if (800.0f >= FLOAT4::Len2D(Dir))
	{
		if (false == m_bFirstAppear)
		{
			m_BlackKnightActionSound = SGameEngineSound::Play(L"Plains_BlackKnight_laugh.mp3", false, 0);
			m_bFirstAppear = true;
		}

		// ü�� ����
		m_HPChargeTime -= SGameEngineTimer::FDeltaTime();
		if (0.0f >= m_HPChargeTime)
		{
			m_BlackKnightInfo.AddHP(2);
			if (m_BlackKnightInfo.GetHP() == m_BlackKnightInfo.GetMaxHP())
			{
				m_BlackKnightFSM.ChangeState(L"BlackKnight_Idle");
			}

			m_HPChargeTime = 0.5f;
		}
	}
}

void BlackKnight::FindEnd()
{
	m_BlackKnightCol->On();
}

// ������
void BlackKnight::IdleStart()
{
	ChangeAniMation(L"BlackKnight_Idle");
}

void BlackKnight::IdleStay()
{
	if (true == m_AniBlackKnight->IsEnd())
	{
		m_BlackKnightFSM.ChangeState(L"BlackKnight_Move");
	}
}

void BlackKnight::IdleEnd()
{

}

// �������
void BlackKnight::MoveStart()
{
	ChangeAniMation(L"BlackKnight_Move");
}

void BlackKnight::MoveStay()
{
	// �̵�
	MovePosCheck();

	// �̵� �� üũ
	MoveStateCheck();
}

void BlackKnight::MoveEnd()
{

}

// ������ ����
void BlackKnight::BackJumpStart()
{
	// ȿ���� ����
	m_BlackKnightActionSound = SGameEngineSound::Play(L"Plains_BlackKnight_BackStep.mp3", false, 0);

	// �������� �÷��̾��� Ÿ�ݹ���(�÷��̾� ��ġ�� ����ġ)�� ���Ͽ�
	// �������Ѵ�.
	BackJumpDirectCheck();

	// ������������ �������Ŀ��� �����Ѵ�.
	m_BackJumpPos = FLOAT4::ZERO;
	m_BackJumpPower = FLOAT4({ 0.0f, -300.0f });
	m_BackJumpGravityPower = FLOAT4({ 0.0f, 1000.0f });
}

void BlackKnight::BackJumpStay()
{
	// ������ �̵�
	BackJumpPosCheck();

	// ������ �̵��� üũ
	BackJumpStateCheck();
}

void BlackKnight::BackJumpEnd()
{
	
}

// ����»���
void BlackKnight::LaughStart()
{
	m_BlackKnightActionSound = SGameEngineSound::Play(L"Plains_BlackKnight_laugh.mp3", false, 0);

	if (GlobalValue::BasicMoveType::Left == m_BackJumpMoveDir)
	{
		m_AniBlackKnight->ChangeAnimation(L"Right_BlackKnight_Laugh");
	}
	else if (GlobalValue::BasicMoveType::Right == m_BackJumpMoveDir)
	{
		m_AniBlackKnight->ChangeAnimation(L"Left_BlackKnight_Laugh");
	}

	// Ÿ���̺��� ����
	if (0 == m_LaughEventer.IsEventSize())
	{
		// 0.5�ʵ��� �ش� ���� ������ ���� 0.5�� �� ���º���
		m_LaughEventer.CreateTimeEventEnd(0.5f, this, &BlackKnight::LaughTimeEventerEnd);
		m_LaughEventer.LoopOn();
	}
}

void BlackKnight::LaughStay()
{
	m_LaughEventer.Update();
}

void BlackKnight::LaughEnd()
{

}

// �������� ����
void BlackKnight::JumpAttackStart()
{
	m_BlackKnightActionSound = SGameEngineSound::Play(L"Plains_BlackKnight_JumpAttack.mp3", false, 0);

	ChangeAniMation(L"BlackKnight_JumpStart");

	// �÷��̾� ��ġ�� ���� ��ġ ��
	FLOAT4 MyPos = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPos.Normalize();
	if (0.0f <= MyPos.x) // �÷��̾�� ���� ���ʿ� ��ġ
	{
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
	else // �÷��̾�� ���� �����ʿ� ��ġ
	{
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}

	// �����Ŀ� ����
	m_JumpAttackPos = FLOAT4::ZERO;
	m_JumpAttackPower = FLOAT4({ 0.0f, -1000.0f });
	m_JumpAttackGravityPower = FLOAT4({ 0.0f, 2000.0f });
}

void BlackKnight::JumpAttackStay()
{
	// �̵� üũ(�������� ~ �ְ���)
	JumpAttackPosCheck();

	// �̵��� �ȼ�üũ
	JumpAttackStateCheck();
}

void BlackKnight::JumpAttackEnd()
{

}

// �������� �ְ������� ������� ����
void BlackKnight::JumpAttackHighPointStart()
{
	ChangeAniMation(L"BlackKnight_JumpHighPoint");

	// �������鼭 �������� �浹ü On
	m_BlackKnightJumpAttackCol->On();
}

void BlackKnight::JumpAttackHighPointStay()
{
	// �̵� üũ(�ְ��� ~ �ٴ�)
	JumpAttackHighPosCheck();

	// �̵��� �ȼ�üũ
	JumpAttackEndCheck();
}

void BlackKnight::JumpAttackHighPointEnd()
{
	m_BlackKnightJumpAttackCol->Off();
}

// �Ϲݰ��ݻ���
void BlackKnight::NomalAttackStart()
{
	ChangeAniMation(L"BlackKnight_NomalAttack");

	// ���� �浹ü On
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_BlackKnightNomalAttackCol->SetPivotPos({50.f, 0.f});
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_BlackKnightNomalAttackCol->SetPivotPos({-50.f, 0.f});
	}
	m_BlackKnightNomalAttackCol->On();
}

void BlackKnight::NomalAttackStay()
{
	// ���ݸ�� ���� �� ��� ����Ǹ� ���º���
	if (true == m_AniBlackKnight->IsEnd())
	{
		FLOAT4 StateDist = GetPosition() - GlobalValue::MainPlayer->GetPosition();
		if (100.f >= FLOAT4::Len2D(StateDist))
		{
			m_BlackKnightFSM.ChangeState(L"BlackKnight_BackJump");
		}
		else
		{
			m_BlackKnightFSM.ChangeState(L"BlackKnight_Idle");
		}
	}
}

void BlackKnight::NomalAttackEnd()
{
	m_BlackKnightNomalAttackCol->Off();
}

// ��ų������¡ ����
void BlackKnight::SkillChargingStart()
{
	ChangeAniMation(L"BlackKnight_SkillCharging");
}

void BlackKnight::SkillChargingStay()
{
	// ��¡����� ������ ��ų�������� ���º�ȯ
	if (true == m_AniBlackKnight->IsEnd())
	{
		m_BlackKnightFSM.ChangeState(L"BlackKnight_SkillAttack");
	}
}

void BlackKnight::SkillChargingEnd()
{

}

// ��ų������ ����
void BlackKnight::SkillAttackStart()
{
	// 
	m_BlackKnightActionSound = SGameEngineSound::Play(L"Plains_BlackKnight_SkillShot.mp3", false, 0);

	ChangeAniMation(L"BlackKnight_SkillAttack");

	// Skill Effect ����
	BlackKnight_SkillEffect* SkillEffect = GetScene()->CreateActor<BlackKnight_SkillEffect>();
	SkillEffect->SetSkillEffectDirect(m_MoveDir);
	SkillEffect->SetPosition(GetPosition());
}

void BlackKnight::SkillAttackStay()
{
	if (true == m_AniBlackKnight->IsEnd())
	{
		FLOAT4 StateDist = GetPosition() - GlobalValue::MainPlayer->GetPosition();
		if (100.f >= FLOAT4::Len2D(StateDist))
		{
			m_BlackKnightFSM.ChangeState(L"BlackKnight_BackJump");
		}
		else
		{
			m_BlackKnightFSM.ChangeState(L"BlackKnight_Idle");
		}
	}
}

void BlackKnight::SkillAttackEnd()
{

}

// �˹����(�÷��̾����κ��� �ǰݽ�)
void BlackKnight::KnockBackStart()
{
	ChangeAniMation(L"BlackKnight_KnockBack");

	// �˹�����϶� �浹ü�� Off ���°� �ȴ�.
	// ��, ��������
	m_BlackKnightCol->Off();

	// �˹�� �÷��̾��� Ÿ�ݹ���(�÷��̾� ��ġ�� ����ġ)�� ���Ͽ�
	// �˹��Ѵ�.
	KnockBackDirectCheck();

	// �˹������� �˹��Ŀ��� �����Ѵ�.
	m_KnockBackPos = FLOAT4::ZERO;
	m_KnockBackPower = FLOAT4({ 0.0f, -300.0f });
	m_KnockBackGravityPower = FLOAT4({ 0.0f, 1000.0f });
}

void BlackKnight::KnockBackStay()
{
	// �˹� �̵�
	KnockBackPosCheck();

	// �˹� �̵��� üũ
	KnockBackStateCheck();
}

void BlackKnight::KnockBackEnd()
{
	// �˹� ����� �ٽ� �浹ü�� On���°� �ȴ�.
	m_BlackKnightCol->On();

	// Ȥ�� �𸣴� �ǰ� �̹��� Off
	m_BeShotLeftBlackKnight->Off();
	m_BeShotRightBlackKnight->Off();
	m_bBlinkImage = false;
	m_fBlinkImageTotalTime = 1.f;
}

// ������� ����(�̶� �浹ü ���)
void BlackKnight::DeathStart()
{
	// �浹ü�� ����ϸ�
	m_BlackKnightCol->Death();

	// �ִϸ��̼��� �����ϰ�
	ChangeAniMation(L"BlackKnight_Death");

	DeathDirectCheck();

	// �����ϹǷ� DeathJump �Ŀ��� �����ϰ�
	m_DeathPos = FLOAT4::ZERO;
	m_DeathPower = FLOAT4({ 0.0f, -300.0f });
	m_DeathGravityPower = FLOAT4({ 0.0f, 1000.0f });
}

void BlackKnight::DeathStay()
{
	// �̵� üũ
	DeathPosCheck();

	// �̵��� üũ
	DeathStateCheck();
}

void BlackKnight::DeathEnd()
{

}

// ������ ������ ����
void BlackKnight::DeathMotionStart()
{
	ChangeAniMation(L"BlackKnight_DeathMotion");
}

void BlackKnight::DeathMotionStay()
{
	// �ִϸ��̼� ����� �ش� ���ʹ� ����Ѵ�.
	if (true == m_AniBlackKnight->IsEnd())
	{
		// ������ ��������� ���� �¸������������ ��ü ��
		GlobalValue::MainPlayer->m_StageBgm.Stop();
		GlobalValue::MainPlayer->m_StageBgm = SGameEngineSound::Play(L"Plains_BossBattle_Victory.mp3", true, 0);

		// �÷��̾� ���� ����
		GlobalValue::MainPlayer->BossVictoryStateChagne();
		GlobalValue::MainPlayer->m_bFinalBossDeath = true;

		// �� �ڽ��� �״´�.
		Death();
	}
}

void BlackKnight::DeathMotionEnd()
{

}

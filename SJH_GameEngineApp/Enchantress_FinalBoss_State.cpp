#include "Enchantress_FinalBoss.h"
#include "Enchantress_FinalBoss_AttackSkill.h"
#include "Enchantress_ShovelKnight.h"

// ī�޶� ã�� �� ����
void Enchantress_FinalBoss::FindStart()
{
	ChangeAniMation(L"Boss_Find");
}

void Enchantress_FinalBoss::FindStay()
{
	// ī�޶�� �����Ÿ��� �Ǹ� ī�޶� ã�� ���·� ����
	FLOAT4 CamDir = GetCamPosition();
	if (710.f >= FLOAT4::Len2D(CamDir))  // ī�޶� ������
	{
		// �����ð� �ڿ� ���� ����
		m_fStateChangeDelay -= SGameEngineTimer::FDeltaTime();
		if (0.0f >= m_fStateChangeDelay)
		{
			m_EnchantressFSM.ChangeState(L"Enchantress_CamFound");
			m_fStateChangeDelay = 3.f;
		}
	}
}

void Enchantress_FinalBoss::FindEnd()
{ 

}

// ī�޶� ã�� ����
void Enchantress_FinalBoss::CamFoundStart()
{
	ChangeAniMation(L"Boss_CamFound");
}

void Enchantress_FinalBoss::CamFoundStay()
{
	if (true == m_AniEnchantress->IsEnd())
	{
		m_EnchantressFSM.ChangeState(L"Enchantress_Appear");
	}
}

void Enchantress_FinalBoss::CamFoundEnd()
{

}

// ���� ����
void Enchantress_FinalBoss::AppearStart()
{
	ChangeAniMation(L"Boss_Appear");
}

void Enchantress_FinalBoss::AppearStay()
{
	if (true == m_AniEnchantress->IsEnd())
	{
		// �ִϸ��̼��� �����ϰ�
		m_CamMoveDir = GlobalValue::BasicMoveType::Down;
		m_MoveDir = GlobalValue::BasicMoveType::Left;
		ChangeAniMation(L"Boss_Idle");
		m_bAppearMove = true;
	}

	if (true == m_bAppearMove)
	{
		// ���� �̵���Ű�� ī�޶���� �̵���Ų��.

		m_DirectPos = FLOAT4::ZERO;
		m_DirectPos = FLOAT4::DOWN * SGameEngineTimer::FDeltaTime(m_EnchantressInfo.GetMoveSpeed());

		MovePosition(m_DirectPos);
		GetScene()->SetCamMove(m_DirectPos);
		// ���⼭ ī�޶�� �ȼ��浹�ϸ� ���̻� ���������ʴ´�.
		AppearCamPixelCheck();

		// ���⼭ ������ �ش� ��ġ��ŭ �̵��ϸ� ���¸� �����Ѵ�.
		if (1372.f <= GetPosition().y)
		{
			m_EnchantressFSM.ChangeState(L"Enchantress_Idle");
		}
	}
}

void Enchantress_FinalBoss::AppearEnd()
{

}

// ���(����) ����
void Enchantress_FinalBoss::IdleStart()
{
	ChangeAniMation(L"Boss_Idle");
}

void Enchantress_FinalBoss::IdleStay()
{
	IdleState_MovePosCheck();

	IdleState_StateCheck();
}

void Enchantress_FinalBoss::IdleEnd()
{

}

// �̵� ����
void Enchantress_FinalBoss::MoveStart()
{
	ChangeAniMation(L"Boss_Move");
}

void Enchantress_FinalBoss::MoveStay()
{
	MoveState_MovePosCheck();

	MoveState_StateCheck();
}

void Enchantress_FinalBoss::MoveEnd()
{

}

// ���ݽ�ų ���� ����
void Enchantress_FinalBoss::AttackSkillChargingStart()
{
	m_FinalBossSound = SGameEngineSound::Play(L"The_Enchantress_Boss_SkillCharging.mp3", false, 0);

	ChangeAniMation(L"Boss_AttackSkillCharging");
}

void Enchantress_FinalBoss::AttackSkillChargingStay()
{
	AttackSkillChargingState_MovePosCheck();

	AttackSkillChargingState_StateCheck();
}

void Enchantress_FinalBoss::AttackSkillChargingEnd()
{

}

// ���ݽ�ų ���� ����(�Ʒ�)
void Enchantress_FinalBoss::DownAttackSkillChargingStart()
{
	m_FinalBossSound = SGameEngineSound::Play(L"The_Enchantress_Boss_SkillCharging.mp3", false, 0);

	ChangeAniMation(L"Boss_AttackSkillCharging");
}

void Enchantress_FinalBoss::DownAttackSkillChargingStay()
{
	DownAttackSkillChargingState_MovePosCheck();

	DownAttackSkillChargingState_StateCheck();
}

void Enchantress_FinalBoss::DownAttackSkillChargingEnd()
{

}

// ���ݽ�ų ���� ����(��)
void Enchantress_FinalBoss::UpAttackSkillChargingStart()
{
	m_FinalBossSound = SGameEngineSound::Play(L"The_Enchantress_Boss_SkillCharging.mp3", false, 0);

	ChangeAniMation(L"Boss_AttackSkillCharging");
}

void Enchantress_FinalBoss::UpAttackSkillChargingStay()
{
	UpAttackSkillChargingState_MovePosCheck();

	UpAttackSkillChargingState_StateCheck();
}

void Enchantress_FinalBoss::UpAttackSkillChargingEnd()
{

}

// ���� ��ų ��Ÿ���� ����(��, ��)
void Enchantress_FinalBoss::BasicAttackSkillShotStart()
{
	m_FinalBossSound = SGameEngineSound::Play(L"The_Enchantress_Boss_SkillShot.mp3", false, 0);

	ChangeAniMation(L"Boss_AttackSkill");
}

void Enchantress_FinalBoss::BasicAttackSkillShotStay()
{
	AttackSkillShotState_MovePosCheck();

	AttackSkillShotState_StateCheck();
}

void Enchantress_FinalBoss::BasicAttackSkillShotEnd()
{

}

// ���� ��ų �Ʒ��ΰ��� ����
void Enchantress_FinalBoss::DownAttackSkillShotStart()
{
	m_FinalBossSound = SGameEngineSound::Play(L"The_Enchantress_Boss_SkillShot.mp3", false, 0);

	ChangeAniMation(L"Boss_DownAttackSkill");
}

void Enchantress_FinalBoss::DownAttackSkillShotStay()
{
	DownAttackSkillShotState_MovePosCheck();

	DownAttackSkillShotState_StateCheck();
}

void Enchantress_FinalBoss::DownAttackSkillShotEnd()
{

}

// ���� ��ų ���ΰ��� ����
void Enchantress_FinalBoss::UpAttackSkillShotStart()
{
	m_FinalBossSound = SGameEngineSound::Play(L"The_Enchantress_Boss_SkillShot.mp3", false, 0);

	ChangeAniMation(L"Boss_UpAttackSkill");
}

void Enchantress_FinalBoss::UpAttackSkillShotStay()
{
	UpAttackSkillShotState_MovePosCheck();

	UpAttackSkillShotState_StateCheck();
}

void Enchantress_FinalBoss::UpAttackSkillShotEnd()
{

}

// ���� ��ų �Ʒ��� ���� �� �̵�����
void Enchantress_FinalBoss::DownAttackSkillShotMoveStart()
{
	ChangeAniMation(L"Boss_Idle");

	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DownShotMove = GetPosition() + FLOAT4(-100.f, 0.f);
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DownShotMove = GetPosition() + FLOAT4(100.f, 0.f);
	}
}

void Enchantress_FinalBoss::DownAttackSkillShotMoveStay()
{
	DownAttackSkillShotMoveState_MovePosCheck();

	DownAttackSkillShotMoveState_StateCheck();
}

void Enchantress_FinalBoss::DownAttackSkillShotMoveEnd()
{

}

// ���� ��ų ���� ���� �� �̵�����
void Enchantress_FinalBoss::UpAttackSkillShotMoveStart()
{
	ChangeAniMation(L"Boss_Idle");

	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_UpShotMove = GetPosition() + FLOAT4(-100.f, 0.f);
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_UpShotMove = GetPosition() + FLOAT4(100.f, 0.f);
	}
}

void Enchantress_FinalBoss::UpAttackSkillShotMoveStay()
{
	UpAttackSkillShotMoveState_MovePosCheck();

	UpAttackSkillShotMoveState_StateCheck();
}

void Enchantress_FinalBoss::UpAttackSkillShotMoveEnd()
{

}

// ���� ��ų ���� ����
void Enchantress_FinalBoss::BlockRegenSkillChargingStart()
{
	m_FinalBossSound = SGameEngineSound::Play(L"The_Enchantress_Boss_SkillCharging.mp3", false, 0);

	ChangeAniMation(L"Boss_RegenSkillCharging");
}

void Enchantress_FinalBoss::BlockRegenSkillChargingStay()
{
	RegenSkillChargingState_MovePosCheck();

	RegenSkillChargingState_StateCheck();
}

void Enchantress_FinalBoss::BlockRegenSkillChargingEnd()
{
	
}

// ���� ��ų �ߵ��� ������
void Enchantress_FinalBoss::BlockRegenSkillIdleStart()
{
	ChangeAniMation(L"Boss_Idle");
}

void Enchantress_FinalBoss::BlockRegenSkillIdleStay()
{
	// Ÿ�� ������ �Ϸ�Ǹ� ������ȯ
	if (false == m_bRegenSkilling)
	{
		m_EnchantressFSM.ChangeState(L"Enchantress_Idle");
	}
}

void Enchantress_FinalBoss::BlockRegenSkillIdleEnd()
{

}

// ��� ����
void Enchantress_FinalBoss::DeathStart()
{
	ChangeAniMation(L"Boss_Death");

	// �浹ü Off ����
	m_EnchantressCol->Off();
}

void Enchantress_FinalBoss::DeathStay()
{
	// �ִϸ��̼� ����Ǹ� �̵� ����
	if (true == m_AniEnchantress->IsEnd())
	{
		m_EnchantressFSM.ChangeState(L"Enchantress_DeathMove");
	}
}

void Enchantress_FinalBoss::DeathEnd()
{

}

// ��� ���� ~ ��ǥ�����̵�
void Enchantress_FinalBoss::DeathMoveStart()
{
	ChangeAniMation(L"Boss_Death");

	// ī�޶� ���� ����
	m_DeathCamMoveStartPos = GetScene()->GetCamPos();
	m_DeathCamMoveEndPos = FLOAT4(0.f, 0.f);

	// ���� ���� ����
	m_DeathMoveStartPos = GetPosition();
	m_DeathMoveEndPos = FLOAT4(637.f, 250.f);
	m_DeathLerpStart = true;
}

void Enchantress_FinalBoss::DeathMoveStay()
{
	// Ÿ�� ��ġ���� �̵��Ѵ�.
	if (true == m_DeathLerpStart)
	{
		m_DeathLerpTime += SGameEngineTimer::MainTimer.FDeltaTime(0.2f);
		m_DeathLerpPos = FLOAT4::Lerp2D(m_DeathMoveStartPos, m_DeathMoveEndPos, m_DeathLerpTime);
		m_DeathCamLerpPos = FLOAT4::Lerp2D(m_DeathCamMoveStartPos, m_DeathCamMoveEndPos, m_DeathLerpTime);

		GetScene()->SetCamPos(m_DeathCamLerpPos);
		SetPosition(m_DeathLerpPos);

		if (1.0f < m_DeathLerpTime)
		{
			// �����Ϸ�� ��� �� �ʱ�ȭ
			m_DeathLerpPos = FLOAT4::ZERO;
			m_DeathCamLerpPos = FLOAT4::ZERO;
			m_DeathLerpTime = 0.0f;
			m_DeathLerpStart = false;

			// Ÿ�� ��ġ���� �̵��Ϸ��ϸ� ���� ����(ī�޶� ����ũ �߰��ϸ� ī�޶� ����ũ ���·� ��ȯ����)
			m_EnchantressFSM.ChangeState(L"Enchantress_DeathCamShake");
			//m_EnchantressFSM.ChangeState(L"Enchantress_DeathEffect");
		}
		return;
	}
}

void Enchantress_FinalBoss::DeathMoveEnd()
{

}

// ī�޶� ����ũ ȿ�� ����
void Enchantress_FinalBoss::DeathCamShakeEffectStart()
{
	ChangeAniMation(L"Boss_Death");

	// ī�޶� ����ũ Ÿ���̺��� ����
	if (0 == m_DeathCamShake.IsEventSize())
	{
		m_DeathCamShake.CreateTimeEvent(0.2f, this, &Enchantress_FinalBoss::CamShakeEnd, &Enchantress_FinalBoss::CamShakeStart, &Enchantress_FinalBoss::CamShakeStay);
		m_DeathCamShake.LoopOn();
	}

	m_DeathCamShake.Reset();
}

void Enchantress_FinalBoss::DeathCamShakeEffectStay()
{
	// ���⼭ ī�޶� ����ũ ȿ�� ����
	m_DeathCamShake.Update();

	// �����ð� ������ ���� ü����
	m_fCamShakeTime -= SGameEngineTimer::FDeltaTime();
	if (0.0f >= m_fCamShakeTime)
	{
		m_fCamShakeTime = 3.f;
		m_EnchantressFSM.ChangeState(L"Enchantress_DeathEffect");
	}
}

void Enchantress_FinalBoss::DeathCamShakeEffectEnd()
{
	// ī�޶� ������
	GetScene()->SetCamPos({ 0.f, 0.f });
}

// ī�޶� ����ũ ȿ�� ������ �̹��� ������
void Enchantress_FinalBoss::DeathEffectStart()
{
	ChangeAniMation(L"Boss_ImageChange");
	m_AniShildKnight->ChangeAnimation(L"ShildKnight_Appear");

	if (0 == m_DeathImageChange.IsEventSize())
	{
		m_DeathImageChange.CreateTimeEvent(0.2f, this, &Enchantress_FinalBoss::FinalBossImageEnd, &Enchantress_FinalBoss::FinalBossImageStart, &Enchantress_FinalBoss::FinalBossImageStay);
		m_DeathImageChange.CreateTimeEvent(0.2f, this, &Enchantress_FinalBoss::ShildKnightImageEnd, &Enchantress_FinalBoss::ShildKnightImageStart, &Enchantress_FinalBoss::ShildKnightImageStay);
		m_DeathImageChange.LoopOn();
	}

	if (0 == m_DeathImageChangeEnd.IsEventSize())
	{
		m_DeathImageChangeEnd.CreateTimeEventEnd(3.f, this, &Enchantress_FinalBoss::ImageChangeEnd);
	}
}

void Enchantress_FinalBoss::DeathEffectStay()
{
	m_DeathImageChange.Update();
	m_DeathImageChangeEnd.Update();
}

void Enchantress_FinalBoss::DeathEffectEnd()
{

}

// ȿ�� ���� �� �̵�
void Enchantress_FinalBoss::DeathEffectMoveStart()
{
	m_AniShildKnight->ChangeAnimation(L"ShildKnight_MoveIdle");

	// �̶� �浹ü On
	m_EnchantressCol->On();

	// Flag On
	m_bBossFalling = true;
}

void Enchantress_FinalBoss::DeathEffectMoveStay()
{
	m_DirectPos = FLOAT4::ZERO;
	m_DirectPos += FLOAT4::DOWN * SGameEngineTimer::FDeltaTime(m_EnchantressInfo.GetMoveSpeed());
	if (false == m_bDeathEffectMove) // ���� �ѹ��� üũ�ϱ� ���ؼ�
	{
		if (500.f <= GetPosition().y + m_DirectPos.y)
		{
			GetScene()->SetCamPos(FLOAT4(0.f, 2160.f));
			GlobalValue::FinalStage_MainPlayer->SetPosition(FLOAT4(GlobalValue::FinalStage_MainPlayer->GetPosition().x, 2750.f));
			m_bDeathEffectMove = true;
		}
	}

	m_MovePos = m_DirectPos;
}

void Enchantress_FinalBoss::DeathEffectMoveEnd()
{

}

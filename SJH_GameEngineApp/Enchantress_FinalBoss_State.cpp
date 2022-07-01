#include "Enchantress_FinalBoss.h"
#include "Enchantress_FinalBoss_AttackSkill.h"
#include "Enchantress_ShovelKnight.h"

// 카메라 찾는 중 상태
void Enchantress_FinalBoss::FindStart()
{
	ChangeAniMation(L"Boss_Find");
}

void Enchantress_FinalBoss::FindStay()
{
	// 카메라와 일정거리가 되면 카메라 찾음 상태로 변경
	FLOAT4 CamDir = GetCamPosition();
	if (710.f >= FLOAT4::Len2D(CamDir))  // 카메라 도착후
	{
		// 일정시간 뒤에 상태 변경
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

// 카메라 찾음 상태
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

// 등장 상태
void Enchantress_FinalBoss::AppearStart()
{
	ChangeAniMation(L"Boss_Appear");
}

void Enchantress_FinalBoss::AppearStay()
{
	if (true == m_AniEnchantress->IsEnd())
	{
		// 애니메이션을 변경하고
		m_CamMoveDir = GlobalValue::BasicMoveType::Down;
		m_MoveDir = GlobalValue::BasicMoveType::Left;
		ChangeAniMation(L"Boss_Idle");
		m_bAppearMove = true;
	}

	if (true == m_bAppearMove)
	{
		// 나를 이동시키며 카메라또한 이동시킨다.

		m_DirectPos = FLOAT4::ZERO;
		m_DirectPos = FLOAT4::DOWN * SGameEngineTimer::FDeltaTime(m_EnchantressInfo.GetMoveSpeed());

		MovePosition(m_DirectPos);
		GetScene()->SetCamMove(m_DirectPos);
		// 여기서 카메라는 픽셀충돌하면 더이상 진행하지않는다.
		AppearCamPixelCheck();

		// 여기서 보스가 해당 위치만큼 이동하면 상태를 변경한다.
		if (1372.f <= GetPosition().y)
		{
			m_EnchantressFSM.ChangeState(L"Enchantress_Idle");
		}
	}
}

void Enchantress_FinalBoss::AppearEnd()
{

}

// 대기(정지) 상태
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

// 이동 상태
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

// 공격스킬 장전 상태
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

// 공격스킬 장전 상태(아래)
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

// 공격스킬 장전 상태(위)
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

// 공격 스킬 평타공격 상태(왼, 우)
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

// 공격 스킬 아래로공격 상태
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

// 공격 스킬 위로공격 상태
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

// 공격 스킬 아래로 공격 중 이동상태
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

// 공격 스킬 위로 공격 중 이동상태
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

// 리젠 스킬 장전 상태
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

// 리젠 스킬 발동중 대기상태
void Enchantress_FinalBoss::BlockRegenSkillIdleStart()
{
	ChangeAniMation(L"Boss_Idle");
}

void Enchantress_FinalBoss::BlockRegenSkillIdleStay()
{
	// 타일 리젠이 완료되면 상태전환
	if (false == m_bRegenSkilling)
	{
		m_EnchantressFSM.ChangeState(L"Enchantress_Idle");
	}
}

void Enchantress_FinalBoss::BlockRegenSkillIdleEnd()
{

}

// 사망 상태
void Enchantress_FinalBoss::DeathStart()
{
	ChangeAniMation(L"Boss_Death");

	// 충돌체 Off 상태
	m_EnchantressCol->Off();
}

void Enchantress_FinalBoss::DeathStay()
{
	// 애니메이션 종료되면 이동 시작
	if (true == m_AniEnchantress->IsEnd())
	{
		m_EnchantressFSM.ChangeState(L"Enchantress_DeathMove");
	}
}

void Enchantress_FinalBoss::DeathEnd()
{

}

// 사망 상태 ~ 목표지점이동
void Enchantress_FinalBoss::DeathMoveStart()
{
	ChangeAniMation(L"Boss_Death");

	// 카메라 러프 설정
	m_DeathCamMoveStartPos = GetScene()->GetCamPos();
	m_DeathCamMoveEndPos = FLOAT4(0.f, 0.f);

	// 보스 러프 설정
	m_DeathMoveStartPos = GetPosition();
	m_DeathMoveEndPos = FLOAT4(637.f, 250.f);
	m_DeathLerpStart = true;
}

void Enchantress_FinalBoss::DeathMoveStay()
{
	// 타겟 위치까지 이동한다.
	if (true == m_DeathLerpStart)
	{
		m_DeathLerpTime += SGameEngineTimer::MainTimer.FDeltaTime(0.2f);
		m_DeathLerpPos = FLOAT4::Lerp2D(m_DeathMoveStartPos, m_DeathMoveEndPos, m_DeathLerpTime);
		m_DeathCamLerpPos = FLOAT4::Lerp2D(m_DeathCamMoveStartPos, m_DeathCamMoveEndPos, m_DeathLerpTime);

		GetScene()->SetCamPos(m_DeathCamLerpPos);
		SetPosition(m_DeathLerpPos);

		if (1.0f < m_DeathLerpTime)
		{
			// 러프완료시 모든 값 초기화
			m_DeathLerpPos = FLOAT4::ZERO;
			m_DeathCamLerpPos = FLOAT4::ZERO;
			m_DeathLerpTime = 0.0f;
			m_DeathLerpStart = false;

			// 타겟 위치까지 이동완료하면 상태 변경(카메라 쉐이크 추가하면 카메라 쉐이크 상태로 전환예정)
			m_EnchantressFSM.ChangeState(L"Enchantress_DeathCamShake");
			//m_EnchantressFSM.ChangeState(L"Enchantress_DeathEffect");
		}
		return;
	}
}

void Enchantress_FinalBoss::DeathMoveEnd()
{

}

// 카메라 쉐이크 효과 상태
void Enchantress_FinalBoss::DeathCamShakeEffectStart()
{
	ChangeAniMation(L"Boss_Death");

	// 카메라 쉐이크 타임이벤터 생성
	if (0 == m_DeathCamShake.IsEventSize())
	{
		m_DeathCamShake.CreateTimeEvent(0.2f, this, &Enchantress_FinalBoss::CamShakeEnd, &Enchantress_FinalBoss::CamShakeStart, &Enchantress_FinalBoss::CamShakeStay);
		m_DeathCamShake.LoopOn();
	}

	m_DeathCamShake.Reset();
}

void Enchantress_FinalBoss::DeathCamShakeEffectStay()
{
	// 여기서 카메라 쉐이크 효과 실행
	m_DeathCamShake.Update();

	// 일정시간 지나면 상태 체인지
	m_fCamShakeTime -= SGameEngineTimer::FDeltaTime();
	if (0.0f >= m_fCamShakeTime)
	{
		m_fCamShakeTime = 3.f;
		m_EnchantressFSM.ChangeState(L"Enchantress_DeathEffect");
	}
}

void Enchantress_FinalBoss::DeathCamShakeEffectEnd()
{
	// 카메라 재조정
	GetScene()->SetCamPos({ 0.f, 0.f });
}

// 카메라 쉐이크 효과 종료후 이미지 깜빡임
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

// 효과 종료 후 이동
void Enchantress_FinalBoss::DeathEffectMoveStart()
{
	m_AniShildKnight->ChangeAnimation(L"ShildKnight_MoveIdle");

	// 이때 충돌체 On
	m_EnchantressCol->On();

	// Flag On
	m_bBossFalling = true;
}

void Enchantress_FinalBoss::DeathEffectMoveStay()
{
	m_DirectPos = FLOAT4::ZERO;
	m_DirectPos += FLOAT4::DOWN * SGameEngineTimer::FDeltaTime(m_EnchantressInfo.GetMoveSpeed());
	if (false == m_bDeathEffectMove) // 최초 한번만 체크하기 위해서
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

#include "BlackKnight.h"
#include "BlackKnight_SkillEffect.h"

// 일정거리내 카메라를 찾고있는 상태
void BlackKnight::FindStart()
{
	ChangeAniMation(L"BlackKnight_Laugh");
	m_BlackKnightCol->Off();
}

void BlackKnight::FindStay()
{
	// 플레이어와 일정거리가 되면 체력 충전시작
	FLOAT4 Dir = GlobalValue::MainPlayer->GetPosition() - GetPosition();
	if (800.0f >= FLOAT4::Len2D(Dir))
	{
		if (false == m_bFirstAppear)
		{
			m_BlackKnightActionSound = SGameEngineSound::Play(L"Plains_BlackKnight_laugh.mp3", false, 0);
			m_bFirstAppear = true;
		}

		// 체력 충전
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

// 대기상태
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

// 무브상태
void BlackKnight::MoveStart()
{
	ChangeAniMation(L"BlackKnight_Move");
}

void BlackKnight::MoveStay()
{
	// 이동
	MovePosCheck();

	// 이동 중 체크
	MoveStateCheck();
}

void BlackKnight::MoveEnd()
{

}

// 백점프 상태
void BlackKnight::BackJumpStart()
{
	// 효과음 실행
	m_BlackKnightActionSound = SGameEngineSound::Play(L"Plains_BlackKnight_BackStep.mp3", false, 0);

	// 백점프시 플레이어의 타격방향(플레이어 위치와 내위치)을 비교하여
	// 백점프한다.
	BackJumpDirectCheck();

	// 백점프를위해 백점프파워를 설정한다.
	m_BackJumpPos = FLOAT4::ZERO;
	m_BackJumpPower = FLOAT4({ 0.0f, -300.0f });
	m_BackJumpGravityPower = FLOAT4({ 0.0f, 1000.0f });
}

void BlackKnight::BackJumpStay()
{
	// 백점프 이동
	BackJumpPosCheck();

	// 백점프 이동중 체크
	BackJumpStateCheck();
}

void BlackKnight::BackJumpEnd()
{
	
}

// 비웃는상태
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

	// 타임이벤터 생성
	if (0 == m_LaughEventer.IsEventSize())
	{
		// 0.5초동안 해당 상태 유지를 위해 0.5초 후 상태변경
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

// 점프어택 상태
void BlackKnight::JumpAttackStart()
{
	m_BlackKnightActionSound = SGameEngineSound::Play(L"Plains_BlackKnight_JumpAttack.mp3", false, 0);

	ChangeAniMation(L"BlackKnight_JumpStart");

	// 플레이어 위치와 나의 위치 비교
	FLOAT4 MyPos = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPos.Normalize();
	if (0.0f <= MyPos.x) // 플레이어는 나의 왼쪽에 위치
	{
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
	else // 플레이어는 나의 오른쪽에 위치
	{
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}

	// 점프파워 설정
	m_JumpAttackPos = FLOAT4::ZERO;
	m_JumpAttackPower = FLOAT4({ 0.0f, -1000.0f });
	m_JumpAttackGravityPower = FLOAT4({ 0.0f, 2000.0f });
}

void BlackKnight::JumpAttackStay()
{
	// 이동 체크(점프시작 ~ 최고점)
	JumpAttackPosCheck();

	// 이동중 픽셀체크
	JumpAttackStateCheck();
}

void BlackKnight::JumpAttackEnd()
{

}

// 점프어택 최고점에서 내려찍는 상태
void BlackKnight::JumpAttackHighPointStart()
{
	ChangeAniMation(L"BlackKnight_JumpHighPoint");

	// 내려오면서 점프공격 충돌체 On
	m_BlackKnightJumpAttackCol->On();
}

void BlackKnight::JumpAttackHighPointStay()
{
	// 이동 체크(최고점 ~ 바닥)
	JumpAttackHighPosCheck();

	// 이동중 픽셀체크
	JumpAttackEndCheck();
}

void BlackKnight::JumpAttackHighPointEnd()
{
	m_BlackKnightJumpAttackCol->Off();
}

// 일반공격상태
void BlackKnight::NomalAttackStart()
{
	ChangeAniMation(L"BlackKnight_NomalAttack");

	// 공격 충돌체 On
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
	// 공격모션 실행 후 모션 종료되면 상태변경
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

// 스킬공격차징 상태
void BlackKnight::SkillChargingStart()
{
	ChangeAniMation(L"BlackKnight_SkillCharging");
}

void BlackKnight::SkillChargingStay()
{
	// 차징모션이 끝나면 스킬공격으로 상태변환
	if (true == m_AniBlackKnight->IsEnd())
	{
		m_BlackKnightFSM.ChangeState(L"BlackKnight_SkillAttack");
	}
}

void BlackKnight::SkillChargingEnd()
{

}

// 스킬공격중 상태
void BlackKnight::SkillAttackStart()
{
	// 
	m_BlackKnightActionSound = SGameEngineSound::Play(L"Plains_BlackKnight_SkillShot.mp3", false, 0);

	ChangeAniMation(L"BlackKnight_SkillAttack");

	// Skill Effect 생성
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

// 넉백상태(플레이어으로부터 피격시)
void BlackKnight::KnockBackStart()
{
	ChangeAniMation(L"BlackKnight_KnockBack");

	// 넉백상태일때 충돌체는 Off 상태가 된다.
	// 즉, 무적상태
	m_BlackKnightCol->Off();

	// 넉백시 플레이어의 타격방향(플레이어 위치와 내위치)을 비교하여
	// 넉백한다.
	KnockBackDirectCheck();

	// 넉백을위해 넉백파워를 설정한다.
	m_KnockBackPos = FLOAT4::ZERO;
	m_KnockBackPower = FLOAT4({ 0.0f, -300.0f });
	m_KnockBackGravityPower = FLOAT4({ 0.0f, 1000.0f });
}

void BlackKnight::KnockBackStay()
{
	// 넉백 이동
	KnockBackPosCheck();

	// 넉백 이동중 체크
	KnockBackStateCheck();
}

void BlackKnight::KnockBackEnd()
{
	// 넉백 종료시 다시 충돌체는 On상태가 된다.
	m_BlackKnightCol->On();

	// 혹시 모르니 피격 이미지 Off
	m_BeShotLeftBlackKnight->Off();
	m_BeShotRightBlackKnight->Off();
	m_bBlinkImage = false;
	m_fBlinkImageTotalTime = 1.f;
}

// 사망시작 상태(이때 충돌체 사망)
void BlackKnight::DeathStart()
{
	// 충돌체가 사망하며
	m_BlackKnightCol->Death();

	// 애니메이션을 변경하고
	ChangeAniMation(L"BlackKnight_Death");

	DeathDirectCheck();

	// 점프하므로 DeathJump 파워를 설정하고
	m_DeathPos = FLOAT4::ZERO;
	m_DeathPower = FLOAT4({ 0.0f, -300.0f });
	m_DeathGravityPower = FLOAT4({ 0.0f, 1000.0f });
}

void BlackKnight::DeathStay()
{
	// 이동 체크
	DeathPosCheck();

	// 이동중 체크
	DeathStateCheck();
}

void BlackKnight::DeathEnd()
{

}

// 사망모션 진행중 상태
void BlackKnight::DeathMotionStart()
{
	ChangeAniMation(L"BlackKnight_DeathMotion");
}

void BlackKnight::DeathMotionStay()
{
	// 애니메이션 종료시 해당 액터는 사망한다.
	if (true == m_AniBlackKnight->IsEnd())
	{
		// 죽을때 배경음악을 끄고 승리배경음악으로 교체 후
		GlobalValue::MainPlayer->m_StageBgm.Stop();
		GlobalValue::MainPlayer->m_StageBgm = SGameEngineSound::Play(L"Plains_BossBattle_Victory.mp3", true, 0);

		// 플레이어 상태 변경
		GlobalValue::MainPlayer->BossVictoryStateChagne();
		GlobalValue::MainPlayer->m_bFinalBossDeath = true;

		// 나 자신은 죽는다.
		Death();
	}
}

void BlackKnight::DeathMotionEnd()
{

}

#include "ShovelKnight.h"

// 등장 상태
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

	// 현재 애니메이션프레임이 마지막 애니메이션프레임이면 등장완료
	// 일부러 등장씬 애니메이션보다 1개더 크게 잡힘
	// 원래 등장씬 ( 36, 42 ) -> 변경후 ( 36, 43 )
	if (false == m_bAppearIdle) // 임시 방편 재생되고나서 isplaying체크를 해야하기 때문에
	{
		if (true == m_AniPlayer->IsEnd())
		{
			// 등장액션 마무리 사운드 재생
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
	// 플레이어위치와 플레이어체크위치를 맞춰줌 
	m_AniPlayer->SetPivotPos({ 0.0f, 0.0f });
	SetPosition(FLOAT4({ 230.f, 2749.f }));

	// 배경음악 실행(배경음악은 반복하는 루프가 존재한다)
	m_StageBgm = SGameEngineSound::Play(L"Stage.mp3", true, 100);
}

// 대기(정지) 상태
void ShovelKnight::IdleStart()
{
	ChangeAniMation(L"PlayerNone");
}

void ShovelKnight::IdleStay()
{
	// 벡터 통합 관련
	IdlePos_Check();

	// 이동에 따른 픽셀 등 체크
	IdleState_Check();
}

void ShovelKnight::IdleEnd()
{

}

// Falling 상태
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

// 기본이동 상태(왼, 우)
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
	// 이동벡터 초기화(혹시몰라서)
	m_DirectPos = FLOAT4::ZERO;
}

// 사다리이동 상태(상, 하)
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

// 사다리 이동중 점프
void ShovelKnight::LadderJumpStart()
{
	// 애니메이션 변경
	ChangeAniMation(L"PlayerJumpStay");

	// 점프 효과음 재생
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

// 점프 상태
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
	// 애니메이션 변경
	ChangeAniMation(L"PlayerJumpStart");

	// 점프 효과음 재생
	m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpStart.mp3", false, 0);

	// 점프, 중력 설정
	m_JumpPos = FLOAT4::ZERO;
	m_JumpPower = FLOAT4({ 0.0f, -600.0f });

	m_GravityPos = FLOAT4::ZERO;
	m_JumpGravityPowerPos = FLOAT4({ 0.0f, 3000.0f });

	// 높이조절을위해 타임이벤터생성
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

// 점프공격 상태
void ShovelKnight::JumpAttackStart()
{
	ChangeAniMation(L"PlayerJumpAttack");

	// 충돌체 설정
	m_JumpAttackCol->SetPivotPos({ 0, -50 });

	// 점프공격모션 충돌체 On
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
	// 점프공격모션 충돌체 Off
	m_JumpAttackCol->Off();
}

// 점프공격(Object or Monster 충돌)
void ShovelKnight::JumpAttackColStart()
{
	// 점프, 중력 설정
	m_JumpPos = FLOAT4::ZERO;
	m_JumpPower = FLOAT4({ 0.0f, -1000.0f });

	m_GravityPos = FLOAT4::ZERO;
	m_JumpGravityPowerPos = FLOAT4({ 0.0f, 3000.0f });

	// 점프 콜리전 On
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

// 기본공격 상태
void ShovelKnight::AttackStart()
{
	ChangeAniMation(L"PlayerAttack");

	// 공격 효과음 재생
	m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_Attack.mp3", false, 0);

	// 충돌체 설정
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		m_AttackCol->SetPivotPos({ 60, 0 });
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		m_AttackCol->SetPivotPos({ -60, 0 });
	}

	// 충돌체 On
	m_AttackCol->On();
}

void ShovelKnight::AttackStay()
{
	// 충돌체 Off
	m_AttackCol->Off();

	// 점프 중에 어택상태로 변경되었다면
	if (true == m_bJumping)
	{
		m_JumpPower += m_JumpGravityPowerPos * SGameEngineTimer::FDeltaTime();
		m_JumpPos = m_JumpPower * SGameEngineTimer::FDeltaTime();

		m_MovePos = m_JumpPos;

		JumpState_Check();
		return;
	}

	// 마지막 모션까지 완료시 상태변경
	if (true == m_AniPlayer->IsEnd())
	{
		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}
}

void ShovelKnight::AttackEnd()
{
	m_bJumping = false;
}

// 넉백 상태
// 알파값 조절
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
	// 효과음 실행
	m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_KnockBack.mp3", false, 0);

	// 넉백 파워를 설정
	m_KnockBackPos = FLOAT4::ZERO;
	m_KnockBackPower = FLOAT4({ 0.0f, -300.0f });
	m_KnockBackGravityPowerPos = FLOAT4({ 0.0f, 1000.0f });

	// 충돌체 Off
	m_PlayerCol->Off();

	// 애니메이션 변경
	ChangeAniMation(L"PlayerKnockBack");

	// 알파 설정(깜빡거림)
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
	// 넉백완료되면 충돌체 On
	m_PlayerCol->On();

	// 알파브렌딩 원래대로
	m_AniPlayer->SetAlpha(255);
}

// 보스처치(승리)
void ShovelKnight::BossVictoryStart()
{
	// 임시 위치조정
	m_AniPlayer->SetPivotPos({ 0.f, -10.f });

	ChangeAniMation(L"PlayerVictory");
}

void ShovelKnight::BossVictoryStay()
{
	// 프레임으로 시간계산하여 골드를 증가시킨다.
	int AddGold = static_cast<int>(SGameEngineTimer::FDeltaTime(200.f));
	m_PlayerInfo.AddHoldingGold(AddGold);

	// 사운드 종료시 상태를 변경한다.
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
	// 모든 상태, 모든 오브젝트를 무시하고 이동한다.
	// 초록색을 만나면 러프하며 검은색을 만나면 이동이 불가하게 된다.
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

	// 픽셀 체크한다.
	PlayerPixelCheck();

	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		// 검은색을 만나면 진행불가
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
		// 초록색을 만나면 카메라 러프
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_bWallCollision = true;
		}
		// 마젠타를 만나면 보스방 입장
		if (RGB(255, 0, 255) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_bWallCollision = true;
			m_bFinalBossRoom = true;
		}
	}
	if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		// 검은색을 만나면 진행불가
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
		// 초록색을 만나면 카메라 러프
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_bWallCollision = true;
		}
		// 마젠타를 만나면 보스방 입장
		if (RGB(255, 0, 255) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_bWallCollision = true;
			m_bFinalBossRoom = true;
		}
	}
	if (m_LadderPrevMoveDir == GlobalValue::BasicMoveType::Up)
	{
		// 검은색을 만나면 진행불가
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Top])
		{
			m_MovePos.y = 0.0f;
		}

		// 초록색을 만나면 카메라 러프
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Top])
		{
			m_bWallCollision = true;
		}
	}
	else if (m_LadderPrevMoveDir == GlobalValue::BasicMoveType::Down)
	{
		// 검은색을 만나면 진행불가
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			m_MovePos.y = 0.0f;
		}

		// 초록색을 만나면 카메라 러프
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

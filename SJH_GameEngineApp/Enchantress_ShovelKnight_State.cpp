#include "Enchantress_ShovelKnight.h"
#include <SGameEngineInput.h>

#include "FadeInOutActor.h"
#include "SGameCore.h"

// 보스찾는 상태(일정거리 이동하면 상태변경)
void Enchantress_ShovelKnight::BossFindIdleStart()
{
	ChangeAniMation(L"PlayerNone");
}

void Enchantress_ShovelKnight::BossFindIdleStay()
{
	BossFindIDLE_MovePosCheck();

	BossFindIDLE_StateCheck();
}

void Enchantress_ShovelKnight::BossFindIdleEnd()
{

}

// 보스 찾는 무브상태((일정거리 이동하면 상태변경)
void Enchantress_ShovelKnight::BossFindMoveStart()
{
	ChangeAniMation(L"PlayerMove");
}

void Enchantress_ShovelKnight::BossFindMoveStay()
{
	BossFindMOVE_MovePosCheck();

	BossFindMOVE_StateCheck();
}

void Enchantress_ShovelKnight::BossFindMoveEnd()
{

}

// 카메라러프 대기상태(카메라는 몬스터를 찾는다.)
void Enchantress_ShovelKnight::CamLerpingIdleStart()
{
	ChangeAniMation(L"PlayerBossFind");

	// 카메라 러프를 위해 설정 및 러프 시작
	m_CamMoveDir = GlobalValue::BasicMoveType::Up;
	m_bWallCollision = true;
}

void Enchantress_ShovelKnight::CamLerpingIdleStay()
{
	if (false == m_bWallCollision) // 카메라 러프완료시 상태 변경
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_None");
	}
}

void Enchantress_ShovelKnight::CamLerpingIdleEnd()
{

}

// 대기(정지) 상태
void Enchantress_ShovelKnight::IdleStart()
{
	ChangeAniMation(L"PlayerNone");
}

void Enchantress_ShovelKnight::IdleStay()
{
	Idle_MovePosCheck();

	Idle_StateCheck();
}

void Enchantress_ShovelKnight::IdleEnd()
{

}

// 기본이동 상태(왼, 우)
void Enchantress_ShovelKnight::MoveStart()
{
	ChangeAniMation(L"PlayerMove");
}

void Enchantress_ShovelKnight::MoveStay()
{
	Move_MovePosCheck();

	Move_StateCheck();
}

void Enchantress_ShovelKnight::MoveEnd()
{

}

// 점프 상태
void Enchantress_ShovelKnight::HighJumpCheckEvent()
{
	if (true == SGameEngineInput::IsPress(L"PLAYER_JUMP"))
	{
		m_JumpPower.y = -800.0f;
	}

	if (m_JumpPower.y <= -800.0f)
	{
		m_JumpPower.y = -800.0f;
	}
}

void Enchantress_ShovelKnight::LowJumpCheckEvent()
{
	if (true == SGameEngineInput::IsPress(L"PLAYER_JUMP"))
	{
		m_JumpPower.y = -400.0f;
	}

	if (m_JumpPower.y <= -400.0f)
	{
		m_JumpPower.y = -400.0f;
	}
}

void Enchantress_ShovelKnight::JumpStart()
{
	m_EnchantressPlayerSound = SGameEngineSound::Play(L"ShovelKnight_JumpStart.mp3", false, 0);

	ChangeAniMation(L"PlayerJumpStart");

	// 점프, 중력 설정
	m_JumpPos = FLOAT4::ZERO;
	m_JumpPower = FLOAT4({ 0.0f, -300.0f });
	m_JumpGravityPowerPos = FLOAT4({ 0.0f, 3000.0f });

	// 높이조절을위해 타임이벤터생성
	if (0 == m_JumpEventer.IsEventSize())
	{
		m_JumpEventer.CreateTimeEventStay(0.1f, this, &Enchantress_ShovelKnight::LowJumpCheckEvent);
		m_JumpEventer.CreateTimeEventStay(0.1f, this, &Enchantress_ShovelKnight::HighJumpCheckEvent);
	}
	m_JumpEventer.Reset();

	// 점프중 Flag On
	m_bJumping = true;
}

void Enchantress_ShovelKnight::JumpStay()
{
	m_JumpEventer.Update();

	Jump_MovePosCheck();

	Jump_StateCheck();
}

void Enchantress_ShovelKnight::JumpEnd()
{

}

// 점프공격 상태
void Enchantress_ShovelKnight::JumpAttackStart()
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

void Enchantress_ShovelKnight::JumpAttackStay()
{
	JumpAttack_MovePosCheck();

	JumpAttack_StateCheck();
}

void Enchantress_ShovelKnight::JumpAttackEnd()
{
	// 점프공격모션 충돌체 Off
	m_JumpAttackCol->Off();
}

// 점프공격(Object 충돌)
void Enchantress_ShovelKnight::JumpAttackColStart()
{
	m_EnchantressPlayerSound = SGameEngineSound::Play(L"ShovelKnight_JumpAttack_Col.mp3", false, 0);

	ChangeAniMation(L"PlayerJumpAttack");

	// 점프, 중력 설정
	m_JumpPos = FLOAT4::ZERO;
	m_JumpPower = FLOAT4({ 0.0f, -1000.0f });
	m_JumpGravityPowerPos = FLOAT4({ 0.0f, 3000.0f });

	// 점프 콜리전 On
	m_JumpAttackCol->On();
}

void Enchantress_ShovelKnight::JumpAttackColStay()
{
	JumpAttackCol_MovePosCheck();

	JumpAttackCol_StateCheck();
}

void Enchantress_ShovelKnight::JumpAttackColEnd()
{
	m_JumpAttackCol->Off();
}

// 기본공격 상태
void Enchantress_ShovelKnight::AttackStart()
{
	m_EnchantressPlayerSound = SGameEngineSound::Play(L"ShovelKnight_Attack.mp3", false, 0);

	ChangeAniMation(L"PlayerAttack");

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

void Enchantress_ShovelKnight::AttackStay()
{
	// 충돌체 Off
	m_AttackCol->Off();

	// 점프중 Attack했을시
	if (true == m_bJumping)
	{
		m_JumpPower += m_JumpGravityPowerPos * SGameEngineTimer::FDeltaTime();
		m_JumpPos = m_JumpPower * SGameEngineTimer::FDeltaTime();

		m_MovePos = m_JumpPos;

		Jump_StateCheck();
		return;
	}

	// 마지막 모션까지 완료시 상태변경
	if (true == m_AniPlayer->IsEnd())
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_None");
	}
}

void Enchantress_ShovelKnight::AttackEnd()
{

}

// 넉백 상태
// 알파값 조절
void Enchantress_ShovelKnight::HitAlphaInStart()
{
	m_AniPlayer->SetAlpha(100);
}
void Enchantress_ShovelKnight::HitAlphaInStay()
{

}
void Enchantress_ShovelKnight::HitAlphaInEnd()
{
	m_AniPlayer->SetAlpha(255);
}

void Enchantress_ShovelKnight::HitAlphaOutStart()
{
	m_AniPlayer->SetAlpha(255);
}
void Enchantress_ShovelKnight::HitAlphaOutStay()
{

}
void Enchantress_ShovelKnight::HitAlphaOutEnd()
{
	m_AniPlayer->SetAlpha(100);
}

void Enchantress_ShovelKnight::KnockBackStart()
{
	m_EnchantressPlayerSound = SGameEngineSound::Play(L"ShovelKnight_KnockBack.mp3", false, 0);

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
		m_KnockBackEventer.CreateTimeEvent(0.1f, this, &Enchantress_ShovelKnight::HitAlphaInEnd, &Enchantress_ShovelKnight::HitAlphaInStart, &Enchantress_ShovelKnight::HitAlphaInStay);
		m_KnockBackEventer.CreateTimeEvent(0.1f, this, &Enchantress_ShovelKnight::HitAlphaOutEnd, &Enchantress_ShovelKnight::HitAlphaOutStart, &Enchantress_ShovelKnight::HitAlphaOutStay);
		m_KnockBackEventer.LoopOn();
	}
}

void Enchantress_ShovelKnight::KnockBackStay()
{
	m_KnockBackEventer.Update();

	KnockBack_MovePosCheck();

	KnockBack_StateCheck();
}

void Enchantress_ShovelKnight::KnockBackEnd()
{
	// 넉백완료되면 충돌체 On
	m_PlayerCol->On();

	// 알파브렌딩 원래대로
	m_AniPlayer->SetAlpha(255);
}

// 방패기사를 받아내는 상태
void Enchantress_ShovelKnight::ShildKnightColStart()
{
	ChangeAniMation(L"PlayerShildKnightCol");
}

void Enchantress_ShovelKnight::ShildKnightColStay()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	// 검은색을 상태전환
	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_MovePos.y = 0.0f;
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_EndingSceneChange");
	}

	// 밑으로 계속이동한다.
	m_DirectPos = FLOAT4::ZERO;
	m_DirectPos += FLOAT4::DOWN * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());

	m_MovePos = m_DirectPos;
}

void Enchantress_ShovelKnight::ShildKnightColEnd()
{

}

// 엔딩씬전환 상태
void Enchantress_ShovelKnight::EndingSceneChangeStart()
{
	ChangeAniMation(L"PlayerShildKnightColIdle");

	//
	FadeInOutActor::FadeStartFlagOn();
}

void Enchantress_ShovelKnight::EndingSceneChangeStay()
{
	if (true == FadeInOutActor::GetFadeEnd())
	{
		// 페이드 인 종료시 씬 체인지
		SGameCore::SceneManager.ChangeScene(L"EndingCredit");
	}
}

void Enchantress_ShovelKnight::EndingSceneChangeEnd()
{

}

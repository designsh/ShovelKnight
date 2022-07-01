#include "ShovelKnight.h"
#include "DeathScreen.h"
#include "BlackKnight.h"
#include "SGameCore.h"

// 대기(정지)상태 체크
void ShovelKnight::IdleState_Check()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	// 바닥이 검은색이 아니게 되면 Falling상태로 변경
	if (RGB(0, 0, 0) != m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] &&
		RGB(0, 0, 255) != m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_MovePos.y = 0.0f;
		m_ShovelKnightFSM.ChangeState(L"Player_Falling");
	}

	// 이동 체크
	if (true == SGameEngineInput::IsPress(L"LEFT") ||
		true == SGameEngineInput::IsPress(L"RIGHT"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_Move");
	}

	// 점프 체크
	if (true == SGameEngineInput::IsDown(L"JUMP"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_Jump");
	}

	// 기본공격 체크
	if (true == SGameEngineInput::IsDown(L"DEFAULTATTACK"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_Attack");
	}

	// 사다리체크
	if (true == m_bLadderCollision)
	{
		if (true == SGameEngineInput::IsPress(L"LADDERUP") ||
			true == SGameEngineInput::IsPress(L"LADDERDOWN"))
		{
			m_ShovelKnightFSM.ChangeState(L"Player_Ladder");
		}
	}
}

// Falling 상태 체크
void ShovelKnight::FallingState_Check()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	// 바닥이 빨간색이면 DeathScreen On
	if (RGB(255, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] && false == m_bInvincibility)
	{
		m_MovePos.y = 0.0f;
		GlobalValue::PlayerDeathScreen->On();
	}

	// 바닥이 검은색과 닿으면 None상태로 변경
	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] ||
		RGB(0, 0, 255) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		// 점프 효과음 재생
		m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}

	// Falling 상태중 LADDERDOWN 키를 누르면 상태 변경
	if (true == SGameEngineInput::IsPress(L"LADDERDOWN"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_JumpAttack");
	}
}

// 기본이동 상태 체크
void ShovelKnight::MoveState_Check()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	if (true == m_bDirtBlockCollision)
	{
		// 같은방향으로는 이동불가
		// 방향이 바뀌면 이동가능
		if (m_MoveDir == m_PrevMoveDir)
		{
			m_MovePos.x = 0.f;
		}
		else
		{
			m_bDirtBlockCollision = false;
		}
	}

	// 바닥이 검은색이면 벡터.y는 0.0이 되어 움직이지 않는다.
	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] ||
		RGB(0, 0, 255) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_MovePos.y = 0.0f;
	}

	// 이동방향별 픽셀체크를 부여한다.
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
		// 노란색을 만나면 씬체인지(단 보스 처치해야됨)
		if (RGB(255, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			//if (true == GlobalValue::FinalBoss->IsDeath())
			if(true == m_bFinalBossDeath)
			{
				SGameCore::SceneManager.ChangeScene(L"LevelMap");
			}
		}
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
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
		// 노란색을 만나면 씬체인지(단 보스 처치해야됨)
		if (RGB(255, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			//if (true == GlobalValue::FinalBoss->IsDeath())
			if (true == m_bFinalBossDeath)
			{
				SGameCore::SceneManager.ChangeScene(L"LevelMap");
			}
		}
	}

	// 센터픽셀이 파란색을 만나면 사다리를 탈수 있음
	if (RGB(0, 0, 255) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Center])
	{
		m_bLadderCollision = true;
	}

	// 키가 떨어지면 IDLE상태로 전환된다.
	if (true == SGameEngineInput::IsUp(L"LEFT") || true == SGameEngineInput::IsUp(L"RIGHT"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_None");
		return;
	}

	// 이동중 Attack키를 누르면 Attack 상태로 변경
	if (true == SGameEngineInput::IsDown(L"DEFAULTATTACK"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_Attack");
	}

	// 이동중 Jump키를 누르면 Jump 상태로 변경
	if (true == SGameEngineInput::IsDown(L"JUMP"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_Jump");
	}

	// 이동중 LADDERUP or LADDERDOWN 키를 누르면 사다리상태로 변경
	if (true == m_bLadderCollision)
	{
		if (true == SGameEngineInput::IsPress(L"LADDERUP") ||
			true == SGameEngineInput::IsPress(L"LADDERDOWN"))
		{
			m_ShovelKnightFSM.ChangeState(L"Player_Ladder");
		}
	}
}

// 사다리 상태 체크
void ShovelKnight::LadderMoveState_Check()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	// 이동방향별 픽셀체크를 부여한다.
	if (m_LadderPrevMoveDir == GlobalValue::BasicMoveType::Up)
	{
		// 초록색을 만나면 카메라 러프
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Top])
		{
			m_bWallCollision = true;
		}
	}
	else if (m_LadderPrevMoveDir == GlobalValue::BasicMoveType::Down)
	{
		// 초록색을 만나면 카메라 러프
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			m_bWallCollision = true;
		}
	}

	// 센터픽셀이 흰색이 되면 상태변경
	if (RGB(255, 255, 255) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Center])
	{
		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}

	// 땅에 닿으면 상태변경
	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}

	// 
	if (true == SGameEngineInput::IsDown(L"JUMP"))
	{
		if (true == SGameEngineInput::IsPress(L"LEFT"))
		{
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}
		else if (true == SGameEngineInput::IsPress(L"RIGHT"))
		{
			m_MoveDir = GlobalValue::BasicMoveType::Right;
		}
		m_ShovelKnightFSM.ChangeState(L"Player_LadderJump");
	}
}

// 사다리 이동중 점프 상태 체크
void ShovelKnight::LadderJumpState_Check()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0;
		}
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			// 점프 효과음 재생
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

			m_bLadderCollision = false;
			m_ShovelKnightFSM.ChangeState(L"Player_None");
		}
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			m_bWallCollision = true;
			m_ShovelKnightFSM.ChangeState(L"Player_None");
		}
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0;
		}
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			// 점프 효과음 재생
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

			m_bLadderCollision = false;
			m_ShovelKnightFSM.ChangeState(L"Player_None");
		}
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			m_bWallCollision = true;
			m_ShovelKnightFSM.ChangeState(L"Player_None");
		}
	}

	// 점프어택키를 누르면 점프어택으로 상태변경
	if (true == SGameEngineInput::IsPress(L"LADDERDOWN"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_JumpAttack");
	}
}

// 점프 상태 체크
void ShovelKnight::JumpState_Check()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	// 바닥이 빨간색이면 DeathScreen On
	if (RGB(255, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] && false == m_bInvincibility)
	{
		m_MovePos.y = 0.0f;
		GlobalValue::PlayerDeathScreen->On();
	}

	if (true == m_bDirtBlockCollision)
	{
		// 같은방향으로는 이동불가
		// 방향이 바뀌면 이동가능
		if (m_MoveDir == m_PrevMoveDir)
		{
			m_MovePos.x = 0.f;
		}
		else
		{
			m_bDirtBlockCollision = false;
		}
	}

	// 바닥면 체크
	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] ||
		RGB(0, 0, 255) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_JumpGravityPowerPos = FLOAT4::ZERO;
		m_JumpPos = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		// 점프 효과음 재생
		m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}

	// 머리 체크
	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Top])
	{
		m_JumpGravityPowerPos = FLOAT4::ZERO;
		m_JumpPos = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		m_ShovelKnightFSM.ChangeState(L"Player_Falling");
	}

	// 방향에따라 픽셀체크
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
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
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
	}

	// 점프중 Attack키를 누르면 Attack 상태로 변경
	if (true == SGameEngineInput::IsDown(L"DEFAULTATTACK"))
	{
		// 모션이 끝난뒤 계속해서 점프상태를 유지하기 위해 Flag설정
		m_bJumping = true;

		m_ShovelKnightFSM.ChangeState(L"Player_Attack");
	}

	// 점프중 LADDERDOWN Key를 Press할시 모션 변경
	if (true == SGameEngineInput::IsPress(L"LADDERDOWN"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_JumpAttack");
	}
}

// 점프 공격 상태 체크
void ShovelKnight::JumpAttackState_Check()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	// 바닥이 빨간색이면 DeathScreen On
	if (RGB(255, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] && false == m_bInvincibility)
	{
		m_MovePos.y = 0.0f;
		GlobalValue::PlayerDeathScreen->On();
	}

	if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_bWallCollision = true;
		m_LadderPrevMoveDir = GlobalValue::BasicMoveType::Down;
	}

	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_JumpGravityPowerPos = FLOAT4::ZERO;
		m_JumpPos = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		// 점프 효과음 재생
		m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}

	// 점프 어택중일때 Attack 가능 점프어택상태 해제
	if (true == SGameEngineInput::IsDown(L"DEFAULTATTACK"))
	{
		m_bJumping = true;
		m_ShovelKnightFSM.ChangeState(L"Player_Attack");
	}
}

// 점프 공격(Object or Monster 충돌)
void ShovelKnight::JumpAttackColState_Check()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_bWallCollision = true;
		m_LadderPrevMoveDir = GlobalValue::BasicMoveType::Down;
	}

	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_JumpGravityPowerPos = FLOAT4::ZERO;
		m_JumpPos = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}

	// 점프 어택중일때 Attack 가능 점프어택상태 해제
	if (true == SGameEngineInput::IsDown(L"DEFAULTATTACK"))
	{
		m_bJumping = true;
		m_ShovelKnightFSM.ChangeState(L"Player_Attack");
	}
}

// 넉백 상태 체크
void ShovelKnight::KnockBackState_Check()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_KnockBackPos = FLOAT4::ZERO;
		m_KnockBackPower = FLOAT4::ZERO;
		m_KnockBackGravityPowerPos = FLOAT4::ZERO;
		m_GravityPos = FLOAT4::ZERO;
		m_JumpPos = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;
		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}

	// 바닥이 빨간색이면 DeathScreen On
	if (RGB(255, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] && false == m_bInvincibility)
	{
		m_MovePos.y = 0.0f;
		GlobalValue::PlayerDeathScreen->On();
	}

	// 이동방향 반대방향으로 픽셀체크
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right] ||
			RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
			m_DirectPos = FLOAT4::ZERO;
		}
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left] ||
			RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
			m_DirectPos = FLOAT4::ZERO;
		}
	}
}


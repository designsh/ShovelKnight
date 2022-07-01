#include "BlackKnight.h"

// 기본 이동 체크
void BlackKnight::MoveStateCheck()
{
	// 픽셀체크를 한다.
	BlackKnightPixelCheck();

	// 이동방향으로 진행중 벽과 만나면 방향을 전환한다.
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		// 왼쪽 이동중이라면 왼쪽 픽셀 체크하여 방향전환
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MoveDir = GlobalValue::BasicMoveType::Right;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		// 오른쪽 이동중이라면 오른쪽 픽셀체크하여 방향전환
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}
	}

	// 플레이어와 일정거리가 되면 랜덤 상태지정
	// 랜덤으로 상태 변경한다. 
	FLOAT4 StateDist = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	if (200.f >= FLOAT4::Len2D(StateDist))
	{
		m_RandomState = (rand() % 2) + 1;

		if (m_PrevRandomState != m_RandomState) // 이전패턴과 같으면 패턴 진행안함
		{
			switch (m_RandomState)
			{
				case 1:
				{
					m_BlackKnightFSM.ChangeState(L"BlackKnight_JumpAttack");
					break;
				}

				case 2:
				{
					m_BlackKnightFSM.ChangeState(L"BlackKnight_SkillCharging");
					break;
				}
			}

			// 상태패턴 저장
			m_PrevRandomState = m_RandomState;
		}
	}
}

// 넉백 체크
void BlackKnight::KnockBackStateCheck()
{
	// 픽셀체크를 한다.
	BlackKnightPixelCheck();

	// 이동방향으로 진행중 벽을 만나면 m_MovePos.x는 '0.f'가 된다.
	if (GlobalValue::BasicMoveType::Left == m_KnockBackMoveDir)
	{
		// 왼쪽 이동중이라면 왼쪽 픽셀 체크하여 방향전환
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_KnockBackMoveDir)
	{
		// 오른쪽 이동중이라면 오른쪽 픽셀체크하여 m_MovePos.x는 '0.f'가 된다.
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
	}

	// 바닥에 닿으면 넉백을 종료하며 상태를 변경한다.
	if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		// KnockBack Pos관련 모두 초기화
		m_KnockBackMoveDir = GlobalValue::BasicMoveType::None;
		m_KnockBackPos = FLOAT4::ZERO;
		m_KnockBackPower = FLOAT4::ZERO;
		m_KnockBackGravityPower = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		// 상태변경
		m_BlackKnightFSM.ChangeState(L"BlackKnight_Idle");
	}
}

// 백점프 체크
void BlackKnight::BackJumpStateCheck()
{
	// 픽셀체크를 한다.
	BlackKnightPixelCheck();

	// 이동방향으로 진행중 벽을 만나면 m_MovePos.x는 '0.f'가 된다.
	if (GlobalValue::BasicMoveType::Left == m_BackJumpMoveDir)
	{
		// 왼쪽 이동중이라면 왼쪽 픽셀 체크하여 방향전환
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_BackJumpMoveDir)
	{
		// 오른쪽 이동중이라면 오른쪽 픽셀체크하여 m_MovePos.x는 '0.f'가 된다.
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
	}

	// 바닥에 닿으면 백점프을 종료하며 상태를 변경한다.
	if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		// KnockBack Pos관련 모두 초기화
		m_BackJumpPos = FLOAT4::ZERO;
		m_BackJumpPower = FLOAT4::ZERO;
		m_BackJumpGravityPower = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		// 종료시점에 플레이어와의 거리를 체크하여 상황에 따라 상태변경
		FLOAT4 StateDist = GetPosition() - GlobalValue::MainPlayer->GetPosition();
		if (50.f >= FLOAT4::Len2D(StateDist))
		{
			m_BlackKnightFSM.ChangeState(L"BlackKnight_NomalAttack");
		}
		else
		{
			m_BlackKnightFSM.ChangeState(L"BlackKnight_Laugh");
		}
	}
}

// 점프공격시작 체크
void BlackKnight::JumpAttackStateCheck()
{
	// 픽셀체크를 한다.
	BlackKnightPixelCheck();

	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		// 왼쪽 이동중이라면 왼쪽 픽셀 체크하여 방향전환
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
			m_MoveDir = GlobalValue::BasicMoveType::Right;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		// 오른쪽 이동중이라면 오른쪽 픽셀체크하여 m_MovePos.x는 '0.f'가 된다.
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}
	}
}

void BlackKnight::JumpAttackEndCheck()
{
	// 픽셀체크를 한다.
	BlackKnightPixelCheck();

	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		// 왼쪽 이동중이라면 왼쪽 픽셀 체크하여 방향전환
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
			m_MoveDir = GlobalValue::BasicMoveType::Right;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		// 오른쪽 이동중이라면 오른쪽 픽셀체크하여 m_MovePos.x는 '0.f'가 된다.
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}
	}

	// 바닥에 닿으면 상태 변경
	if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		// Pos관련 모두 초기화
		m_JumpAttackPos = FLOAT4::ZERO;
		m_JumpAttackPower = FLOAT4::ZERO;
		m_JumpAttackGravityPower = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		// 4번 반복이 끝나면 Idle상태
		// 4번 반복이 안끝난상태면 JumpAttack상태
		if (4 == m_JumpAttackCnt)
		{
			// 점프공격이 끝난 뒤 플레이어와의 거리가 50이하이면 백점프로 상태변경
			// 아니면 대기상태로 상태변경한다.
			FLOAT4 StateDist = GetPosition() - GlobalValue::MainPlayer->GetPosition();
			if (50.f >= FLOAT4::Len2D(StateDist))
			{
				m_BlackKnightFSM.ChangeState(L"BlackKnight_BackJump");
			}
			else
			{
				m_BlackKnightFSM.ChangeState(L"BlackKnight_Idle");
			}

			m_JumpAttackCnt = 0;
		}
		else
		{
			m_BlackKnightFSM.ChangeState(L"BlackKnight_JumpAttack");
			m_JumpAttackCnt++;
		}
	}
}

void BlackKnight::DeathStateCheck()
{
	// 픽셀체크를 한다.
	BlackKnightPixelCheck();

	if (GlobalValue::BasicMoveType::Left == m_DeathMoveDir)
	{
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_DeathMoveDir)
	{
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
	}

	// 바닥에 닿으면 상태 변경
	if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		// Pos관련 모두 초기화
		m_DeathPos = FLOAT4::ZERO;
		m_DeathPower = FLOAT4::ZERO;
		m_DeathGravityPower = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		m_BlackKnightFSM.ChangeState(L"BlackKnight_DeathMotion");
	}
}

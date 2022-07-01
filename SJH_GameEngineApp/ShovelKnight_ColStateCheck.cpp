#include "ShovelKnight.h"

// 오브젝트 충돌 중 대기상태 체크
void ShovelKnight::RideIdleState_Check()
{
	// 이동 체크
	if (true == SGameEngineInput::IsPress(L"LEFT") ||
		true == SGameEngineInput::IsPress(L"RIGHT"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_RideMove");
	}

	// 점프 체크
	if (true == SGameEngineInput::IsDown(L"JUMP"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_Jump");
	}

	// 기본공격 체크
	if (true == SGameEngineInput::IsDown(L"DEFAULTATTACK"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_RideAttack");
	}
}

// 오브젝트 충돌 중 무브상태 체크
void ShovelKnight::RideMoveState_Check()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

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

	// 키가 떨어지면 IDLE상태로 전환된다.
	if (true == SGameEngineInput::IsUp(L"LEFT") || true == SGameEngineInput::IsUp(L"RIGHT"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_RideNone");
		return;
	}

	// 이동중 Attack키를 누르면 Attack 상태로 변경
	if (true == SGameEngineInput::IsDown(L"DEFAULTATTACK"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_RideAttack");
	}

	// 이동중 Jump키를 누르면 Jump 상태로 변경
	if (true == SGameEngineInput::IsDown(L"JUMP"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_Jump");
	}
}

void RideAttackState_Check()
{

}

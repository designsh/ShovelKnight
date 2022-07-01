#include "ShovelKnight.h"

// 대기(정지) 위치이동
void ShovelKnight::IdlePos_Check()
{

}

// Falling 이동
void ShovelKnight::FallingPos_Check()
{
	// 이동력을 가한다
	m_DirectPos = FLOAT4::ZERO;
	if (true == SGameEngineInput::IsPress(L"LEFT"))
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
	else if (true == SGameEngineInput::IsPress(L"RIGHT"))
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}

	// 중력을 가한다.
	m_GravityPos = FLOAT4(0.f, 3.0f);

	m_MovePos = m_DirectPos + m_GravityPos;
}

// 기본 이동
void ShovelKnight::MovePos_Check()
{
	// 이동 벡터
	m_DirectPos = FLOAT4::ZERO;
	if (true == SGameEngineInput::IsPress(L"LEFT"))
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Left;

		// 이동중에 바닥픽셀이 검은색 and 파란색이 아니면 상태 전환한다.
		if (RGB(0, 0, 0) != m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] &&
			RGB(0,0,255) != m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			m_ShovelKnightFSM.ChangeState(L"Player_Falling");
		}
	}
	else if (true == SGameEngineInput::IsPress(L"RIGHT"))
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Right;

		// 이동중에 바닥픽셀이 검은색 and 파란색이 아니면 상태 전환한다.
		if (RGB(0, 0, 0) != m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] &&
			RGB(0, 0, 255) != m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			m_ShovelKnightFSM.ChangeState(L"Player_Falling");
		}
	}

	// 중력을 가한다.
	m_GravityPos = FLOAT4(0.f, 3.0f);

	m_MovePos = m_DirectPos + m_GravityPos;
}

// 사다리 이동
void ShovelKnight::LadderMovePos_Check()
{
	m_DirectPos = FLOAT4::ZERO;
	if (true == m_bLadderCollision)
	{
		if (true == SGameEngineInput::IsPress(L"LADDERUP"))
		{
			m_DirectPos += FLOAT4::UP * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
			m_LadderPrevMoveDir = GlobalValue::BasicMoveType::Up;
			m_AniPlayer->SetLoop(true);
		}
		else if (true == SGameEngineInput::IsPress(L"LADDERDOWN"))
		{
			m_DirectPos += FLOAT4::DOWN * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
			m_LadderPrevMoveDir = GlobalValue::BasicMoveType::Down;
			m_AniPlayer->SetLoop(true);
		}
	}

	m_MovePos = m_DirectPos;
}

// 사다리 이동중 점프
void ShovelKnight::LadderJumpPos_Check()
{
	m_DirectPos = FLOAT4::ZERO;
	if (true == SGameEngineInput::IsPress(L"LEFT"))
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
	else if (true == SGameEngineInput::IsPress(L"RIGHT"))
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}

	// 중력을 가한다.
	m_GravityPos = FLOAT4(0.f, 3.0f);

	m_MovePos = m_DirectPos + m_GravityPos;
}

// 점프
void ShovelKnight::JumpPos_Check()
{
	// 이동 벡터
	m_DirectPos = FLOAT4::ZERO;
	if (true == SGameEngineInput::IsPress(L"LEFT"))
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
	else if (true == SGameEngineInput::IsPress(L"RIGHT"))
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}

	// 점프는 중력에의해 점차 감소한다.
	if (true == m_JumpEventer.IsEnd())
	{
		m_JumpPower += m_JumpGravityPowerPos * SGameEngineTimer::FDeltaTime();
	}

	m_JumpPos = m_JumpPower * SGameEngineTimer::FDeltaTime();

	m_MovePos = m_DirectPos + m_JumpPos;
}

// 점프 공격
void ShovelKnight::JumpAttackPos_Check()
{
	// 이동 벡터
	m_DirectPos = FLOAT4::ZERO;
	if (true == SGameEngineInput::IsPress(L"LEFT"))
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
	else if (true == SGameEngineInput::IsPress(L"RIGHT"))
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}

	m_JumpPower += m_JumpGravityPowerPos * SGameEngineTimer::FDeltaTime();
	m_JumpPos = m_JumpPower * SGameEngineTimer::FDeltaTime();

	m_MovePos = m_DirectPos + m_JumpPos;
}

// 점프 공격(Object or Monster 충돌)
void ShovelKnight::JumpAttackColPos_Check()
{
	// 이동 벡터
	m_DirectPos = FLOAT4::ZERO;
	if (true == SGameEngineInput::IsPress(L"LEFT"))
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
	else if (true == SGameEngineInput::IsPress(L"RIGHT"))
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}

	m_JumpPower += m_JumpGravityPowerPos * SGameEngineTimer::FDeltaTime();
	m_JumpPos = m_JumpPower * SGameEngineTimer::FDeltaTime();

	m_MovePos = m_DirectPos + m_JumpPos;
}

// 넉백 이동
void ShovelKnight::KnockBackPos_Check()
{
	m_DirectPos = FLOAT4::ZERO;
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(100.f);
	}
	else if(m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(100.f);
	}

	m_KnockBackPower += m_KnockBackGravityPowerPos * SGameEngineTimer::FDeltaTime();
	m_KnockBackPos = m_KnockBackPower * SGameEngineTimer::FDeltaTime();

	m_MovePos = m_DirectPos + m_KnockBackPos;
}


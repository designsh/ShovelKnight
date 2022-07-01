#include "BlackKnight.h"

// 기본 이동
void BlackKnight::MovePosCheck()
{
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_Speed);
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_Speed);
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}

	// 여기서 모든 벡터의 값을 더한다.
	m_MovePos = m_DirectPos;
}

// 넉백이동
void BlackKnight::KnockBackPosCheck()
{
	// 기존 방향은 건들지않고 이동만한다.
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_KnockBackMoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_Speed);
	}
	else if (GlobalValue::BasicMoveType::Right == m_KnockBackMoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_Speed);
	}

	// 중력적용
	m_KnockBackPower += m_KnockBackGravityPower * SGameEngineTimer::FDeltaTime();
	m_KnockBackPos = m_KnockBackPower * SGameEngineTimer::FDeltaTime();

	// 여기서 모든 벡터의 값을 더한다.
	m_MovePos = m_DirectPos + m_KnockBackPos;
}

// 백점프이동
void BlackKnight::BackJumpPosCheck()
{
	// 기존 방향은 건들지않고 이동만한다.
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_BackJumpMoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_Speed);
	}
	else if (GlobalValue::BasicMoveType::Right == m_BackJumpMoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_Speed);
	}

	// 중력적용
	m_BackJumpPower += m_BackJumpGravityPower * SGameEngineTimer::FDeltaTime();
	m_BackJumpPos = m_BackJumpPower * SGameEngineTimer::FDeltaTime();

	// 여기서 모든 벡터의 값을 더한다.
	m_MovePos = m_DirectPos + m_BackJumpPos;
}

// 점프 공격
void BlackKnight::JumpAttackPosCheck()
{
	// 기존 방향은 건들지않고 이동만한다.
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_Speed);
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_Speed);
	}

	// 중력적용
	m_JumpAttackPower += m_JumpAttackGravityPower * SGameEngineTimer::FDeltaTime();
	m_JumpAttackPos = m_JumpAttackPower * SGameEngineTimer::FDeltaTime();

	// 여기서 모든 벡터의 값을 더한다.
	m_MovePos = m_DirectPos + m_JumpAttackPos;

	// 최고점도달시 상태변경
	if (0.0f <= m_JumpAttackPower.y)
	{
		m_BlackKnightFSM.ChangeState(L"BlackKnight_JumpAttackHightPoint");
	}
}

// 점프어택 최고점 내려찍기 상태
void BlackKnight::JumpAttackHighPosCheck()
{
	// 중력적용(단, 가속한다.)
	m_JumpAttackPower += m_JumpAttackGravityPower * SGameEngineTimer::FDeltaTime();
	m_JumpAttackPos = m_JumpAttackPower * SGameEngineTimer::FDeltaTime();

	// 여기서 모든 벡터의 값을 더한다.
	m_MovePos = m_JumpAttackPos;
}

// 사망시작시 상태
void BlackKnight::DeathPosCheck()
{
	// 기존 방향은 건들지않고 이동만한다.
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_DeathMoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_Speed);
	}
	else if (GlobalValue::BasicMoveType::Right == m_DeathMoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_Speed);
	}

	// 중력적용
	m_DeathPower += m_DeathGravityPower * SGameEngineTimer::FDeltaTime();
	m_DeathPos = m_DeathPower * SGameEngineTimer::FDeltaTime();

	// 여기서 모든 벡터의 값을 더한다.
	m_MovePos = m_DirectPos + m_DeathPos;
}

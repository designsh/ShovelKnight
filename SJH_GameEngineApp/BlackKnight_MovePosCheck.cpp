#include "BlackKnight.h"

// �⺻ �̵�
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

	// ���⼭ ��� ������ ���� ���Ѵ�.
	m_MovePos = m_DirectPos;
}

// �˹��̵�
void BlackKnight::KnockBackPosCheck()
{
	// ���� ������ �ǵ����ʰ� �̵����Ѵ�.
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_KnockBackMoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_Speed);
	}
	else if (GlobalValue::BasicMoveType::Right == m_KnockBackMoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_Speed);
	}

	// �߷�����
	m_KnockBackPower += m_KnockBackGravityPower * SGameEngineTimer::FDeltaTime();
	m_KnockBackPos = m_KnockBackPower * SGameEngineTimer::FDeltaTime();

	// ���⼭ ��� ������ ���� ���Ѵ�.
	m_MovePos = m_DirectPos + m_KnockBackPos;
}

// �������̵�
void BlackKnight::BackJumpPosCheck()
{
	// ���� ������ �ǵ����ʰ� �̵����Ѵ�.
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_BackJumpMoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_Speed);
	}
	else if (GlobalValue::BasicMoveType::Right == m_BackJumpMoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_Speed);
	}

	// �߷�����
	m_BackJumpPower += m_BackJumpGravityPower * SGameEngineTimer::FDeltaTime();
	m_BackJumpPos = m_BackJumpPower * SGameEngineTimer::FDeltaTime();

	// ���⼭ ��� ������ ���� ���Ѵ�.
	m_MovePos = m_DirectPos + m_BackJumpPos;
}

// ���� ����
void BlackKnight::JumpAttackPosCheck()
{
	// ���� ������ �ǵ����ʰ� �̵����Ѵ�.
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_Speed);
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_Speed);
	}

	// �߷�����
	m_JumpAttackPower += m_JumpAttackGravityPower * SGameEngineTimer::FDeltaTime();
	m_JumpAttackPos = m_JumpAttackPower * SGameEngineTimer::FDeltaTime();

	// ���⼭ ��� ������ ���� ���Ѵ�.
	m_MovePos = m_DirectPos + m_JumpAttackPos;

	// �ְ������޽� ���º���
	if (0.0f <= m_JumpAttackPower.y)
	{
		m_BlackKnightFSM.ChangeState(L"BlackKnight_JumpAttackHightPoint");
	}
}

// �������� �ְ��� ������� ����
void BlackKnight::JumpAttackHighPosCheck()
{
	// �߷�����(��, �����Ѵ�.)
	m_JumpAttackPower += m_JumpAttackGravityPower * SGameEngineTimer::FDeltaTime();
	m_JumpAttackPos = m_JumpAttackPower * SGameEngineTimer::FDeltaTime();

	// ���⼭ ��� ������ ���� ���Ѵ�.
	m_MovePos = m_JumpAttackPos;
}

// ������۽� ����
void BlackKnight::DeathPosCheck()
{
	// ���� ������ �ǵ����ʰ� �̵����Ѵ�.
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_DeathMoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_Speed);
	}
	else if (GlobalValue::BasicMoveType::Right == m_DeathMoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_Speed);
	}

	// �߷�����
	m_DeathPower += m_DeathGravityPower * SGameEngineTimer::FDeltaTime();
	m_DeathPos = m_DeathPower * SGameEngineTimer::FDeltaTime();

	// ���⼭ ��� ������ ���� ���Ѵ�.
	m_MovePos = m_DirectPos + m_DeathPos;
}

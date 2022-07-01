#include "ShovelKnight.h"

// ���(����) ��ġ�̵�
void ShovelKnight::IdlePos_Check()
{

}

// Falling �̵�
void ShovelKnight::FallingPos_Check()
{
	// �̵����� ���Ѵ�
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

	// �߷��� ���Ѵ�.
	m_GravityPos = FLOAT4(0.f, 3.0f);

	m_MovePos = m_DirectPos + m_GravityPos;
}

// �⺻ �̵�
void ShovelKnight::MovePos_Check()
{
	// �̵� ����
	m_DirectPos = FLOAT4::ZERO;
	if (true == SGameEngineInput::IsPress(L"LEFT"))
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Left;

		// �̵��߿� �ٴ��ȼ��� ������ and �Ķ����� �ƴϸ� ���� ��ȯ�Ѵ�.
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

		// �̵��߿� �ٴ��ȼ��� ������ and �Ķ����� �ƴϸ� ���� ��ȯ�Ѵ�.
		if (RGB(0, 0, 0) != m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] &&
			RGB(0, 0, 255) != m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			m_ShovelKnightFSM.ChangeState(L"Player_Falling");
		}
	}

	// �߷��� ���Ѵ�.
	m_GravityPos = FLOAT4(0.f, 3.0f);

	m_MovePos = m_DirectPos + m_GravityPos;
}

// ��ٸ� �̵�
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

// ��ٸ� �̵��� ����
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

	// �߷��� ���Ѵ�.
	m_GravityPos = FLOAT4(0.f, 3.0f);

	m_MovePos = m_DirectPos + m_GravityPos;
}

// ����
void ShovelKnight::JumpPos_Check()
{
	// �̵� ����
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

	// ������ �߷¿����� ���� �����Ѵ�.
	if (true == m_JumpEventer.IsEnd())
	{
		m_JumpPower += m_JumpGravityPowerPos * SGameEngineTimer::FDeltaTime();
	}

	m_JumpPos = m_JumpPower * SGameEngineTimer::FDeltaTime();

	m_MovePos = m_DirectPos + m_JumpPos;
}

// ���� ����
void ShovelKnight::JumpAttackPos_Check()
{
	// �̵� ����
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

// ���� ����(Object or Monster �浹)
void ShovelKnight::JumpAttackColPos_Check()
{
	// �̵� ����
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

// �˹� �̵�
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


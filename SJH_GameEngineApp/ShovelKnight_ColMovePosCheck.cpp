#include "ShovelKnight.h"

// ������Ʈ �浹 �� ������ üũ
void ShovelKnight::RideIdlePos_Check()
{

}

// ������Ʈ �浹 �� ������� üũ
void ShovelKnight::RideMovePos_Check()
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

	m_MovePos = m_DirectPos;
}

void ShovelKnight::RideAttackPos_Check()
{

}

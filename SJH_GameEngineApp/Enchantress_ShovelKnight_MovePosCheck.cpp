#include "Enchantress_ShovelKnight.h"
#include <SGameEngineInput.h>

// 보스를 찾는중 정지된 상태
void Enchantress_ShovelKnight::BossFindIDLE_MovePosCheck()
{

}

// 보스를 찾기 위해 이동 상태
void Enchantress_ShovelKnight::BossFindMOVE_MovePosCheck()
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

	m_MovePos = m_DirectPos;
}

// 대기(정지)상태
void Enchantress_ShovelKnight::Idle_MovePosCheck()
{

}

// 이동 상태
void Enchantress_ShovelKnight::Move_MovePosCheck()
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

	m_MovePos = m_DirectPos;
}

// 점프 상태
void Enchantress_ShovelKnight::Jump_MovePosCheck()
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

// 점프 공격 상태
void Enchantress_ShovelKnight::JumpAttack_MovePosCheck()
{
	// 이동 벡터
	m_DirectPos = FLOAT4::ZERO;
	if (true == SGameEngineInput::IsPress(L"PLAYER_LEFT"))
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
	else if (true == SGameEngineInput::IsPress(L"PLAYER_RIGHT"))
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}

	m_JumpPower += m_JumpGravityPowerPos * SGameEngineTimer::FDeltaTime();
	m_JumpPos = m_JumpPower * SGameEngineTimer::FDeltaTime();

	m_MovePos = m_DirectPos + m_JumpPos;
}

// 점프공격중 오브젝트와 충돌 상태
void Enchantress_ShovelKnight::JumpAttackCol_MovePosCheck()
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

// 넉백상태
void Enchantress_ShovelKnight::KnockBack_MovePosCheck()
{
	m_DirectPos = FLOAT4::ZERO;
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(200.f);
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(200.f);
	}

	m_KnockBackPower += m_KnockBackGravityPowerPos * SGameEngineTimer::FDeltaTime();
	m_KnockBackPos = m_KnockBackPower * SGameEngineTimer::FDeltaTime();

	m_MovePos = m_DirectPos + m_KnockBackPos;
}

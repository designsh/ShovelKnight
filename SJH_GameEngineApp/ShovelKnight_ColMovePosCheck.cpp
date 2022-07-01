#include "ShovelKnight.h"

// 오브젝트 충돌 중 대기상태 체크
void ShovelKnight::RideIdlePos_Check()
{

}

// 오브젝트 충돌 중 무브상태 체크
void ShovelKnight::RideMovePos_Check()
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

void ShovelKnight::RideAttackPos_Check()
{

}

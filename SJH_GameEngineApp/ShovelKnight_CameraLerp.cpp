#include "ShovelKnight.h"

void ShovelKnight::LerpCamMove()
{
	// 해당 함수는 플레이어의 픽셀이 초록색과 충돌하면
	// 러프시작점과 러프목표점을 구하여
	// 델타시간에 따른 비율을 계산하여 러프를 진행한다.
	if (true == m_LerpStartMove)
	{
		m_LerpTime += SGameEngineTimer::MainTimer.FDeltaTime();
		m_LerpCamPos = FLOAT4::Lerp2D(m_LerpStartPos, m_LerpEndPos, m_LerpTime);

		GetScene()->SetCamPos(m_LerpCamPos);

		if (1.0f <= m_LerpTime)
		{
			// 러프완료시 모든 값 초기화
			m_LerpCamPos = FLOAT4::ZERO;
			m_LerpStartPos = FLOAT4::ZERO;
			m_LerpEndPos = FLOAT4::ZERO;
			m_LerpTime = 0.0f;
			m_bWallCollision = false;
			m_LerpStartMove = false;
		}
		return;
	}

	if (true == m_bWallCollision)
	{
		m_LerpStartPos = GetScene()->GetCamPos();
		m_LerpEndPos = GetScene()->GetCamPos();

		if (m_LadderPrevMoveDir == GlobalValue::BasicMoveType::Up)
		{
			m_LerpEndPos += FLOAT4::UP * m_WindowSize.y;
			m_LerpTime = 0.0f;
			m_LerpStartMove = true;
			m_LadderPrevMoveDir = GlobalValue::BasicMoveType::None;

			// 픽셀충돌때문에 플레이어 위치보정
			SetPosition({ GetPosition().x, GetPosition().y - 90.f });
		}
		else if (m_LadderPrevMoveDir == GlobalValue::BasicMoveType::Down)
		{
			m_LerpEndPos += FLOAT4::DOWN * m_WindowSize.y;
			m_LerpTime = 0.0f;
			m_LerpStartMove = true;
			m_LadderPrevMoveDir = GlobalValue::BasicMoveType::None;

			// 픽셀충돌때문에 플레이어 위치보정
			SetPosition({ GetPosition().x, GetPosition().y + 90.f });
		}
		else if (m_MoveDir == GlobalValue::BasicMoveType::Left)
		{
			m_LerpEndPos += FLOAT4::LEFT * m_WindowSize.x;
			m_LerpTime = 0.0f;
			m_LerpStartMove = true;

			// 픽셀충돌때문에 플레이어 위치보정
			SetPosition({ GetPosition().x - 90.f, GetPosition().y });
		}
		else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
		{
			m_LerpEndPos += FLOAT4::RIGHT * m_WindowSize.x;
			m_LerpTime = 0.0f;
			m_LerpStartMove = true;

			// 픽셀충돌때문에 플레이어 위치보정
			SetPosition({ GetPosition().x + 90.f, GetPosition().y });
		}
	}
}
#include "Enchantress_ShovelKnight.h"

void Enchantress_ShovelKnight::LerpCamMove()
{
	// �ش� �Լ��� �÷��̾��� �ȼ��� �ʷϻ��� �浹�ϸ�
	// ������������ ������ǥ���� ���Ͽ�
	// ��Ÿ�ð��� ���� ������ ����Ͽ� ������ �����Ѵ�.
	if (true == m_LerpStartMove)
	{
		m_LerpTime += SGameEngineTimer::MainTimer.FDeltaTime(0.4f);
		m_LerpCamPos = FLOAT4::Lerp2D(m_LerpStartPos, m_LerpEndPos, m_LerpTime);

		GetScene()->SetCamPos(m_LerpCamPos);

		if (1.0f <= m_LerpTime)
		{
			// �����Ϸ�� ��� �� �ʱ�ȭ
			m_LerpCamPos = FLOAT4::ZERO;
			m_LerpTime = 0.0f;
			m_bWallCollision = false;
			m_LerpStartMove = false;
			m_CamMoveDir = GlobalValue::BasicMoveType::None;
		}
		return;
	}

	if (true == m_bWallCollision)
	{
		m_LerpStartPos = GetScene()->GetCamPos();
		m_LerpEndPos = GetScene()->GetCamPos();

		if (m_CamMoveDir == GlobalValue::BasicMoveType::Up)
		{
			m_LerpEndPos += FLOAT4::UP * m_WindowSize.y;
			m_LerpTime = 0.0f;
			m_LerpStartMove = true;
		}
		else if (m_CamMoveDir == GlobalValue::BasicMoveType::Down)
		{
			m_LerpEndPos += FLOAT4::DOWN * m_WindowSize.y;
			m_LerpTime = 0.0f;
			m_LerpStartMove = true;
		}
	}
}

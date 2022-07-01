#include "Dozedrake_AttackBubble.h"

// �̵�����
void Dozedrake_AttackBubble::MoveStart()
{
	m_AniAttackBubble->ChangeAnimation(L"BubbleMove");
}

void Dozedrake_AttackBubble::MoveStay()
{
	if (false == m_bFirstMoveGet)
	{
		// ���� ��ġ�� �����ͼ� �������� ���Ѵ�.
		m_MoveStartPos = GetPosition();

		// �ִ�����Ÿ���ŭ�� ũ��� ��ǥ������ ���Ѵ�.
		m_MoveEndPos = FLOAT4(m_MoveStartPos.x + m_fMoveDistMax, m_MoveStartPos.y);

		m_bFirstMoveGet = true;
	}

	// ���� �ִ�Ÿ����� �����ϸ� �����Ϸ�� ���º����Ѵ�.
	m_fLerpTime += SGameEngineTimer::MainTimer.FDeltaTime(m_fMoveLerpSpeed);
	m_MovePos = FLOAT4::Lerp2D(m_MoveStartPos, m_MoveEndPos, m_fLerpTime);

	// ���� ��ġ�� ���ŵȴ�.
	SetPosition(m_MovePos);

	// 1�ʺ��� Ŀ���� 1�ʰ� �����ٰ� �Ǵ�
	if (1.0f < m_fLerpTime)
	{
		m_MovePos = FLOAT4::ZERO;
		m_fLerpTime = 0.0f;
		m_AttackBubbleFSM.ChangeState(L"Bubble_UpMove");
	}
}

void Dozedrake_AttackBubble::MoveEnd()
{

}

// ���οö󰡴»���
void Dozedrake_AttackBubble::UpMoveStart()
{
	m_AniAttackBubble->ChangeAnimation(L"BubbleMove");
}

void Dozedrake_AttackBubble::UpMoveStay()
{
	if (false == m_bFirstUpGet)
	{
		m_UpMoveEndPos = FLOAT4(m_MoveEndPos.x, m_MoveEndPos.y + m_fUpDistMax);
		m_bFirstUpGet = true;
	}

	// ������ �ִ�Ÿ����� �����ϸ� �����Ϸ�� ���º����Ѵ�.
	m_fLerpTime += SGameEngineTimer::MainTimer.FDeltaTime(m_fUpLerpSpeed);
	m_MovePos = FLOAT4::Lerp2D(m_MoveEndPos, m_UpMoveEndPos, m_fLerpTime);

	// ���� ��ġ�� ���ŵȴ�.
	SetPosition(m_MovePos);

	// 1�ʺ��� Ŀ���� 1�ʰ� �����ٰ� �Ǵ�
	if (1.0f < m_fLerpTime)
	{
		m_MovePos = FLOAT4::ZERO;
		m_fLerpTime = 0.0f;
		m_AttackBubbleFSM.ChangeState(L"Bubble_Death");
	}
}

void Dozedrake_AttackBubble::UpMoveEnd()
{

}

// �״� ����
void Dozedrake_AttackBubble::DeathStart()
{
	m_AniAttackBubble->ChangeAnimation(L"BubbleDeath");
}

void Dozedrake_AttackBubble::DeathStay()
{
	if (true == m_AniAttackBubble->IsEnd())
	{
		Death();
	}
}

void Dozedrake_AttackBubble::DeathEnd()
{

}
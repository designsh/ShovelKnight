#include "Dozedrake_AttackBubble.h"

// 이동상태
void Dozedrake_AttackBubble::MoveStart()
{
	m_AniAttackBubble->ChangeAnimation(L"BubbleMove");
}

void Dozedrake_AttackBubble::MoveStay()
{
	if (false == m_bFirstMoveGet)
	{
		// 최초 위치를 가져와서 시자점을 정한다.
		m_MoveStartPos = GetPosition();

		// 최대사정거리만큼의 크기로 목표지점을 정한다.
		m_MoveEndPos = FLOAT4(m_MoveStartPos.x + m_fMoveDistMax, m_MoveStartPos.y);

		m_bFirstMoveGet = true;
	}

	// 무브 최대거리까지 러프하며 러프완료시 상태변경한다.
	m_fLerpTime += SGameEngineTimer::MainTimer.FDeltaTime(m_fMoveLerpSpeed);
	m_MovePos = FLOAT4::Lerp2D(m_MoveStartPos, m_MoveEndPos, m_fLerpTime);

	// 나의 위치는 갱신된다.
	SetPosition(m_MovePos);

	// 1초보다 커지면 1초가 지났다고 판단
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

// 위로올라가는상태
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

	// 업무브 최대거리까지 러프하며 러프완료시 상태변경한다.
	m_fLerpTime += SGameEngineTimer::MainTimer.FDeltaTime(m_fUpLerpSpeed);
	m_MovePos = FLOAT4::Lerp2D(m_MoveEndPos, m_UpMoveEndPos, m_fLerpTime);

	// 나의 위치는 갱신된다.
	SetPosition(m_MovePos);

	// 1초보다 커지면 1초가 지났다고 판단
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

// 죽는 상태
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
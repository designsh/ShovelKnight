#include "PileBubbles.h"

#include "ShovelKnight.h"

// 플레이어 찾는 상태
void PileBubbles::FindStart()
{
	
}

void PileBubbles::FindStay()
{
	// 상태 시작시 현재 나의 위치를 가져와서 러프 시작점으로 설정한다.
	if (m_MoveStartPos == FLOAT4::ZERO)
	{
		SetMoveStartPos(GetPosition());
	}

	if (nullptr == GlobalValue::MainPlayer)
	{
		return;
	}

	// 플레이어와 나의 거리가 일정거리가 되면 등장상태로 변경
	FLOAT4 Dir = GlobalValue::MainPlayer->GetPosition() - GetPosition();

	// Beeto Move Start
	if (630.0f >= FLOAT4::Len2D(Dir))
	{
		// Move State Change
		m_PileBubblesFSM.ChangeState(L"PilBubbles_Appear");
	}
}

void PileBubbles::FindEnd()
{

}

// 등장상태
void PileBubbles::AppearStart()
{
	// 플레이어를 찾으면 등장시작
	m_AniPileBubbles->ChangeAnimation(L"PILEBUBBLESAPPEAR");

	m_AniPileBubbles->On();
}

void PileBubbles::AppearStay()
{
	// 애니메이션 초기위치에서 계속 무브하여 등장
	m_LerpMoveTime += SGameEngineTimer::MainTimer.FDeltaTime(m_LerpSpeed);
	m_MovePos = FLOAT4::Lerp2D(m_MoveStartPos, m_MoveTargetPos, m_LerpMoveTime);

	// 나의 위치는 갱신된다.
	SetPosition(m_MovePos);

	// 1초보다 커지면 1초가 지났다고 판단하여 
	// 나의 상태를 대기상태로 변경한다.
	if (1.0f < m_LerpMoveTime)
	{
		// 러프완료시 모든 값 초기화
		m_MovePos = FLOAT4::ZERO;
		m_LerpMoveTime = 0.0f;
		m_PileBubblesFSM.ChangeState(L"PileBubbles_None");
	}
}

void PileBubbles::AppearEnd()
{

}

// 대기상태
void PileBubbles::IDLEStart()
{
	m_AniPileBubbles->ChangeAnimation(L"PILEBUBBLESAPPEAR");
}

void PileBubbles::IDLEStay()
{

}

void PileBubbles::IDLEEnd()
{

}

// 플레이어가 나를 공격한 상태
void PileBubbles::BeShotStart()
{
	m_AniPileBubbles->ChangeAnimation(L"PILEBUBBLESATT");
}

void PileBubbles::BeShotStay()
{
	// 현재 프레임이 마지막 프레임은 자신은 죽는다.
	if (true == m_AniPileBubbles->IsEnd())
	{
		Death();
	}
}

void PileBubbles::BeShotEnd()
{
	
}

#include "MovingPlatform.h"

#include "ShovelKnight.h"

// Find 상태(플레이어와의 거리를 알아내는상태)
void MovingPlatform::PlatformFindStart()
{

}

void MovingPlatform::PlatformFindStay()
{
	// 상태 시작시 현재 나의 위치를 가져와서 러프 시작점으로 설정한다.
	if (m_MoveStartPos == FLOAT4::ZERO)
	{
		// 러프 시작위치 설정
		SetMoveStartPos(GetPosition());

		// 방향설정
		SetCurLerpDirect(m_MoveStartPos, m_MoveTargetPos);
	}

	// 일정거리내 플레이어가 존재한다면 대기상태로 변경
	if (nullptr == GlobalValue::MainPlayer)
	{
		return;
	}

	// 카메라와 일정거리이면 상태변경
	FLOAT4 Dir = GetCamPosition();
	if (1500.0f >= FLOAT4::Len2D(Dir))
	{
		// Move State Change
		m_MovingPlatformFSM.ChangeState(L"MOVINGMOVE");
	}
}

void MovingPlatform::PlatformFindEnd()
{
	// 충돌체, 랜더러 On
	m_AniMovingPlatform->On();
}

// Idle 상태(대기상태)
void MovingPlatform::PlatformIdleStart()
{
	// 목표지점과 시작지점 교환으로 이동방향을 전환
	FLOAT4 PosTemp = FLOAT4::ZERO;
	PosTemp = m_MoveStartPos;
	m_MoveStartPos = m_MoveTargetPos;
	m_MoveTargetPos = PosTemp;

	// 현재 진행방향을 설정
	SetCurLerpDirect(m_MoveStartPos, m_MoveTargetPos);
}

void MovingPlatform::PlatformIdleStay()
{
	m_MovingPlatformFSM.ChangeState(L"MOVINGMOVE");
}

void MovingPlatform::PlatformIdleEnd()
{

}

// Move 상태(계속하여 러프하며 방향전환)
void MovingPlatform::PlatformMoveStart()
{
	// 플레이어를 찾으면 무브시작
	m_AniMovingPlatform->ChangeAnimation(L"MOVINGIDLE");
}

void MovingPlatform::PlatformMoveStay()
{
	// 애니메이션 초기위치에서 계속 무브하여 등장
	m_LerpMoveTime += SGameEngineTimer::MainTimer.FDeltaTime(m_fLerpSpeed);
	m_MovePos = FLOAT4::LerpMax(m_MoveStartPos, m_MoveTargetPos, m_LerpMoveTime);

	// 플레이어 이동량을 구한다.
	m_PlayerMovePos.x = ((1 - m_LerpMoveTime) * m_MoveStartPos.x + m_LerpMoveTime * m_MoveTargetPos.x) - GetPosition().x;
	m_PlayerMovePos.y = ((1 - m_LerpMoveTime) * m_MoveStartPos.y + m_LerpMoveTime * m_MoveTargetPos.y) - GetPosition().y;

	// 나의 위치는 갱신된다.
	SetPosition(m_MovePos);

	// 1초보다 커지면 1초가 지났다고 판단하여 
	// 나의 상태를 대기상태로 변경한다.
	if (1.0f < m_LerpMoveTime)
	{
		// 러프완료시 모든 값 초기화
		//m_MovePos = FLOAT4::ZERO;
		m_LerpMoveTime = 0.0f;
		
		// 목표지점과 시작점을 교환하기 위해 Idle상태로 이동
		m_MovingPlatformFSM.ChangeState(L"MOVINGIDLE");
	}
}

void MovingPlatform::PlatformMoveEnd()
{

}

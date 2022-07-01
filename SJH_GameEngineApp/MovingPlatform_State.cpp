#include "MovingPlatform.h"

#include "ShovelKnight.h"

// Find ����(�÷��̾���� �Ÿ��� �˾Ƴ��»���)
void MovingPlatform::PlatformFindStart()
{

}

void MovingPlatform::PlatformFindStay()
{
	// ���� ���۽� ���� ���� ��ġ�� �����ͼ� ���� ���������� �����Ѵ�.
	if (m_MoveStartPos == FLOAT4::ZERO)
	{
		// ���� ������ġ ����
		SetMoveStartPos(GetPosition());

		// ���⼳��
		SetCurLerpDirect(m_MoveStartPos, m_MoveTargetPos);
	}

	// �����Ÿ��� �÷��̾ �����Ѵٸ� �����·� ����
	if (nullptr == GlobalValue::MainPlayer)
	{
		return;
	}

	// ī�޶�� �����Ÿ��̸� ���º���
	FLOAT4 Dir = GetCamPosition();
	if (1500.0f >= FLOAT4::Len2D(Dir))
	{
		// Move State Change
		m_MovingPlatformFSM.ChangeState(L"MOVINGMOVE");
	}
}

void MovingPlatform::PlatformFindEnd()
{
	// �浹ü, ������ On
	m_AniMovingPlatform->On();
}

// Idle ����(������)
void MovingPlatform::PlatformIdleStart()
{
	// ��ǥ������ �������� ��ȯ���� �̵������� ��ȯ
	FLOAT4 PosTemp = FLOAT4::ZERO;
	PosTemp = m_MoveStartPos;
	m_MoveStartPos = m_MoveTargetPos;
	m_MoveTargetPos = PosTemp;

	// ���� ��������� ����
	SetCurLerpDirect(m_MoveStartPos, m_MoveTargetPos);
}

void MovingPlatform::PlatformIdleStay()
{
	m_MovingPlatformFSM.ChangeState(L"MOVINGMOVE");
}

void MovingPlatform::PlatformIdleEnd()
{

}

// Move ����(����Ͽ� �����ϸ� ������ȯ)
void MovingPlatform::PlatformMoveStart()
{
	// �÷��̾ ã���� �������
	m_AniMovingPlatform->ChangeAnimation(L"MOVINGIDLE");
}

void MovingPlatform::PlatformMoveStay()
{
	// �ִϸ��̼� �ʱ���ġ���� ��� �����Ͽ� ����
	m_LerpMoveTime += SGameEngineTimer::MainTimer.FDeltaTime(m_fLerpSpeed);
	m_MovePos = FLOAT4::LerpMax(m_MoveStartPos, m_MoveTargetPos, m_LerpMoveTime);

	// �÷��̾� �̵����� ���Ѵ�.
	m_PlayerMovePos.x = ((1 - m_LerpMoveTime) * m_MoveStartPos.x + m_LerpMoveTime * m_MoveTargetPos.x) - GetPosition().x;
	m_PlayerMovePos.y = ((1 - m_LerpMoveTime) * m_MoveStartPos.y + m_LerpMoveTime * m_MoveTargetPos.y) - GetPosition().y;

	// ���� ��ġ�� ���ŵȴ�.
	SetPosition(m_MovePos);

	// 1�ʺ��� Ŀ���� 1�ʰ� �����ٰ� �Ǵ��Ͽ� 
	// ���� ���¸� �����·� �����Ѵ�.
	if (1.0f < m_LerpMoveTime)
	{
		// �����Ϸ�� ��� �� �ʱ�ȭ
		//m_MovePos = FLOAT4::ZERO;
		m_LerpMoveTime = 0.0f;
		
		// ��ǥ������ �������� ��ȯ�ϱ� ���� Idle���·� �̵�
		m_MovingPlatformFSM.ChangeState(L"MOVINGIDLE");
	}
}

void MovingPlatform::PlatformMoveEnd()
{

}

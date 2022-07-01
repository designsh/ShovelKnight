#include "PileBubbles.h"

#include "ShovelKnight.h"

// �÷��̾� ã�� ����
void PileBubbles::FindStart()
{
	
}

void PileBubbles::FindStay()
{
	// ���� ���۽� ���� ���� ��ġ�� �����ͼ� ���� ���������� �����Ѵ�.
	if (m_MoveStartPos == FLOAT4::ZERO)
	{
		SetMoveStartPos(GetPosition());
	}

	if (nullptr == GlobalValue::MainPlayer)
	{
		return;
	}

	// �÷��̾�� ���� �Ÿ��� �����Ÿ��� �Ǹ� ������·� ����
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

// �������
void PileBubbles::AppearStart()
{
	// �÷��̾ ã���� �������
	m_AniPileBubbles->ChangeAnimation(L"PILEBUBBLESAPPEAR");

	m_AniPileBubbles->On();
}

void PileBubbles::AppearStay()
{
	// �ִϸ��̼� �ʱ���ġ���� ��� �����Ͽ� ����
	m_LerpMoveTime += SGameEngineTimer::MainTimer.FDeltaTime(m_LerpSpeed);
	m_MovePos = FLOAT4::Lerp2D(m_MoveStartPos, m_MoveTargetPos, m_LerpMoveTime);

	// ���� ��ġ�� ���ŵȴ�.
	SetPosition(m_MovePos);

	// 1�ʺ��� Ŀ���� 1�ʰ� �����ٰ� �Ǵ��Ͽ� 
	// ���� ���¸� �����·� �����Ѵ�.
	if (1.0f < m_LerpMoveTime)
	{
		// �����Ϸ�� ��� �� �ʱ�ȭ
		m_MovePos = FLOAT4::ZERO;
		m_LerpMoveTime = 0.0f;
		m_PileBubblesFSM.ChangeState(L"PileBubbles_None");
	}
}

void PileBubbles::AppearEnd()
{

}

// ������
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

// �÷��̾ ���� ������ ����
void PileBubbles::BeShotStart()
{
	m_AniPileBubbles->ChangeAnimation(L"PILEBUBBLESATT");
}

void PileBubbles::BeShotStay()
{
	// ���� �������� ������ �������� �ڽ��� �״´�.
	if (true == m_AniPileBubbles->IsEnd())
	{
		Death();
	}
}

void PileBubbles::BeShotEnd()
{
	
}

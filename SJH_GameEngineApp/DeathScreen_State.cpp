#include "DeathScreen.h"

// ó�� ����
void DeathScreen::IDLEStart()
{
	m_AniPlayerMarker->ChangeAnimation(L"MakerIdle");

	// �� ������Ʈ �̹��� Load
	m_AniSavePoint1->ChangeAnimation(L"SavePoint1Idle");
	m_AniSavePoint2->ChangeAnimation(L"SavePoint2Idle");
	m_AniSavePoint3->ChangeAnimation(L"SavePoint3Idle");
	m_AniSavePoint4->ChangeAnimation(L"SavePoint4Idle");
}

void DeathScreen::IDLEStay()
{
	// ��� �غ� ������ Move���·� �����Ѵ�.
	m_DeathScreenFSM.ChangeState(L"DeathScreen_MakerMove");
}

void DeathScreen::IDLEEnd()
{

}

// �÷��̾� ������ �̵�
void DeathScreen::MakerMoveStart()
{
	// ó������� ȿ���� �ߵ�
	m_DeathScreenSound = SGameEngineSound::Play(L"ShovelKnight_Death.mp3", false, 0);

	// �÷��̾� ����� �� ���°� �Ǹ�
	// ���⼭ ���� Ȱ��ȭ�� ���̺�����Ʈ(������Ȱ��ȭ����Ʈ)�� �ε����� �����´�.
	m_iLastSavePointIndex = SavePoint::GetLastSaveData().m_iActiveSavePoint;
	if (4 < m_iLastSavePointIndex)
	{
		// ������ ����ó��(���� ������ȵ�)
		SGameEngineDebug::AssertMsg(L"if (4 < m_iLastSavePointIndex)");
		return;
	}

	// Maker ��ġ�� �˾Ƴ���.
	// Ȱ��ȭ Index�� 0�̸� ù��° ���̺�����Ʈ�� ���ٰ� �׾��⶧����
	// ù��°���̺�����Ʈ�� ��ġ�� Maker�� �ʱ���ġ�� �ȴ�.
	m_AniPlayerMarker->SetPivotPos(m_LinePos[m_iLastSavePointIndex + 1]);

	// ���̺�����Ʈ Ȱ��ȭ �ε��������� �� �ִϸ��̼�
	// �ִϸ��̼� ����(�ϴ� �ܼ��ϰ� if������)
	if (1 == m_iLastSavePointIndex)
	{
		m_AniSavePoint1->ChangeAnimation(L"SavePoint1Active");
	}
	else if (2 == m_iLastSavePointIndex)
	{
		m_AniSavePoint1->ChangeAnimation(L"SavePoint1Active");
		m_AniSavePoint2->ChangeAnimation(L"SavePoint2Active");
	}
	else if (3 == m_iLastSavePointIndex)
	{
		m_AniSavePoint1->ChangeAnimation(L"SavePoint1Active");
		m_AniSavePoint2->ChangeAnimation(L"SavePoint2Active");
		m_AniSavePoint3->ChangeAnimation(L"SavePoint3Active");
	}
	else if (4 == m_iLastSavePointIndex)
	{
		m_AniSavePoint1->ChangeAnimation(L"SavePoint1Active");
		m_AniSavePoint2->ChangeAnimation(L"SavePoint2Active");
		m_AniSavePoint3->ChangeAnimation(L"SavePoint3Active");
		m_AniSavePoint4->ChangeAnimation(L"SavePoint4Active");
	}

	// �÷��̾� ��Ŀ ������������ �ִϸ��̼� ����
	m_AniPlayerMarker->ChangeAnimation(L"MakerMove");
}

void DeathScreen::MakerMoveStay()
{
	// �÷��̾� ��Ŀ��������
	m_LerpMoveTime += SGameEngineTimer::MainTimer.FDeltaTime(m_LerpSpeed);
	m_MovePos = FLOAT4::Lerp2D(m_LinePos[m_iLastSavePointIndex + 1], m_LinePos[m_iLastSavePointIndex], m_LerpMoveTime);

	// ���� ��ġ�� ���ŵȴ�.
	m_AniPlayerMarker->SetPivotPos(m_MovePos);

	// ���� ����� ��� ���� �ʱ�ȭ�ϸ�
	// GoldDisplay ���·� ����
	if (1.0f < m_LerpMoveTime)
	{
		// �����Ϸ�� ��� �� �ʱ�ȭ
		m_MovePos = FLOAT4::ZERO;
		m_LerpMoveTime = 0.0f;
		m_AniPlayerMarker->ChangeAnimation(L"MakerIdle");
		m_DeathScreenFSM.ChangeState(L"DeathScreen_GoldDisplay");
	}
}

void DeathScreen::MakerMoveEnd()
{
	
}

// ���� ��� ǥ��
void DeathScreen::GoldDisplayStart()
{
	// ���⼭ Ÿ���̺��� ����
	if (0 == m_LostGoldEventer.IsEventSize())
	{
		// TimeEventerEnd�� �Ͽ� �ð��� Display ����
		//m_LostGoldEventer.CreateTimeEventEnd(0.2f, this, &DeathScreen::FirstLostGoldInfo);
		//m_LostGoldEventer.CreateTimeEventEnd(0.4f, this, &DeathScreen::SecondLostGoldInfo);
		//m_LostGoldEventer.CreateTimeEventEnd(0.6f, this, &DeathScreen::ThirdLostGoldInfo);
		m_LostGoldEventer.CreateTimeEventEnd(0.3f, this, &DeathScreen::DeathScreenEnd);
	}

	m_LostGoldEventer.Reset();
}

void DeathScreen::GoldDisplayStay()
{
	// �ð����� ���� ��差�� ȭ�鿡 �������� �Բ� ǥ���Ѵ�.
	// ��� ǥ���ϸ� �����ð� �� �����÷��̾��� ������ �����ѵ� ���� ���ʹ� Off�ȴ�.
	m_LostGoldEventer.Update();
}

void DeathScreen::GoldDisplayEnd()
{

}

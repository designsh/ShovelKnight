#include "SavePoint.h"

// ������
void SavePoint::IDLEStart()
{
	m_AniSavePoint->ChangeAnimation(L"SavePoint_None");
}

void SavePoint::IDLEStay()
{

}

void SavePoint::IDLEEnd()
{

}

// �浹����
void SavePoint::ColStart()
{
	// �ִϸ��̼��� �����ϰ�
	m_AniSavePoint->ChangeAnimation(L"SavePoint_Collision");
}

void SavePoint::ColStay()
{
	// �浹�ִϸ��̼��� ������ ���º���
	if (true == m_AniSavePoint->IsEnd())
	{
		m_SavePointFSM.ChangeState(L"SavePointActivation");
	}
}

void SavePoint::ColEnd()
{
	// Ȱ��ȭ ������� �Ѿ�� ��������� 
	// ���� ��ġ�� ī�޶���ġ�� �Ѱ��ش�.(�÷��̾� ��Ȱ�� ����)

}

// Ȱ��ȭ����
void SavePoint::ActiveStart()
{
	m_AniSavePoint->ChangeAnimation(L"SavePoint_Activation");
}

void SavePoint::ActiveStay()
{

}

void SavePoint::ActiveEnd()
{

}

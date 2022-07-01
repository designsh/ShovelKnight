#include "SavePoint.h"

void SavePoint::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// �÷��̾� ��ü or �÷��̾���ݸ�ǰ� �浹�ϸ� �浹���·� ����
	if (false == m_bFirstCollision)
	{
		if (((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder() && 0 == _Other->GetCheckData()) ||
			(int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder())
		{
			// �浹�ѹ��ϸ� Ȱ��ȭ�� ���̻� ��ü or ���ݸ�ǰ� �浹�����ʴ´�.
			m_bFirstCollision = true;

			// �浹���·� �����ϰ�
			m_SavePointFSM.ChangeState(L"SavePointCollision");

			// ���� �⺻ ������ �����Ѵ�.
			// ���� ���� ������ũ�⸸ŭ�� Index�� x:18, y:6
			// ī�޶������� �����ʿ���(�� ����Ʈ���� ī�޶���ġ�� �ٸ��⶧����)
			// ���� ��ġ�� ������ ũ��� ������ ���°����� ������ũ�⸦ ���ؼ� ī�޶� ��ġ�� ���Ѵ�.
			FLOAT4 SetCamPos = FLOAT4::ZERO;
			SetCamPos.x = (floor(GetPosition().x / m_WindowSize.x)) * m_WindowSize.x;
			SetCamPos.y = (floor(GetPosition().y / m_WindowSize.y)) * m_WindowSize.y;
			m_MySaveData.m_CamPos = SetCamPos;
			m_MySaveData.m_SavePointPos = GetPosition();

			// ���������� ���̺�����Ʈ�� �� �������� Ŀ���ٸ� �����Ѵ�.
			if (SAVEPOINTMAX < m_LastSaveData.m_iActiveSavePoint + 1)
			{
				return;
			}
			m_MySaveData.m_iActiveSavePoint = m_LastSaveData.m_iActiveSavePoint + 1;

			// �ռ� ����� ���� ������ static m_LastSaveData�� �־�д�.
			m_LastSaveData = m_MySaveData;
		}
	}
}

void SavePoint::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void SavePoint::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

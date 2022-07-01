#include "SavePoint.h"

void SavePoint::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 플레이어 상체 or 플레이어공격모션과 충돌하면 충돌상태로 변경
	if (false == m_bFirstCollision)
	{
		if (((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder() && 0 == _Other->GetCheckData()) ||
			(int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder())
		{
			// 충돌한번하면 활성화가 더이상 상체 or 공격모션과 충돌하지않는다.
			m_bFirstCollision = true;

			// 충돌상태로 변경하고
			m_SavePointFSM.ChangeState(L"SavePointCollision");

			// 나의 기본 정보를 저장한다.
			// 현재 맵의 윈도우크기만큼의 Index는 x:18, y:6
			// 카메라정보는 보정필요함(각 포인트마다 카메라위치가 다르기때문에)
			// 나의 위치를 윈도우 크기로 나누고 나온값에서 윈도우크기를 곱해서 카메라 위치를 구한다.
			FLOAT4 SetCamPos = FLOAT4::ZERO;
			SetCamPos.x = (floor(GetPosition().x / m_WindowSize.x)) * m_WindowSize.x;
			SetCamPos.y = (floor(GetPosition().y / m_WindowSize.y)) * m_WindowSize.y;
			m_MySaveData.m_CamPos = SetCamPos;
			m_MySaveData.m_SavePointPos = GetPosition();

			// 오류로인해 세이브포인트의 총 개수보다 커진다면 리턴한다.
			if (SAVEPOINTMAX < m_LastSaveData.m_iActiveSavePoint + 1)
			{
				return;
			}
			m_MySaveData.m_iActiveSavePoint = m_LastSaveData.m_iActiveSavePoint + 1;

			// 앞서 저장된 나의 정보를 static m_LastSaveData에 넣어둔다.
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

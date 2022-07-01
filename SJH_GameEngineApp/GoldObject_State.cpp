#include "GoldObject.h"

void GoldObject::FindStart()
{
	
}

void GoldObject::FindStay()
{
	// 카메라위치와 일정거리 가까워지면
	FLOAT4 Dir = GetCamPosition();

	// Beeto Move Start
	// 카메라 범위내 들어오면 
	if (1500.0f >= FLOAT4::Len2D(Dir))
	{
		m_AniGoldObject->On();

		// Move State Change
		m_GoldObjectFSM.ChangeState(L"GoldObject_Idle");
	}
}

void GoldObject::FindEnd()
{

}

void GoldObject::IdleStart()
{
	ChangeAniMation(L"Gold");
}

void GoldObject::IdleStay()
{

}

void GoldObject::IdleEnd()
{

}

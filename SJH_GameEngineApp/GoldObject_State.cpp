#include "GoldObject.h"

void GoldObject::FindStart()
{
	
}

void GoldObject::FindStay()
{
	// ī�޶���ġ�� �����Ÿ� ���������
	FLOAT4 Dir = GetCamPosition();

	// Beeto Move Start
	// ī�޶� ������ ������ 
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

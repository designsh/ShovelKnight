#include "SavePoint.h"

// 대기상태
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

// 충돌상태
void SavePoint::ColStart()
{
	// 애니메이션을 변경하고
	m_AniSavePoint->ChangeAnimation(L"SavePoint_Collision");
}

void SavePoint::ColStay()
{
	// 충돌애니메이션이 끝나면 상태변경
	if (true == m_AniSavePoint->IsEnd())
	{
		m_SavePointFSM.ChangeState(L"SavePointActivation");
	}
}

void SavePoint::ColEnd()
{
	// 활성화 모션으로 넘어갈때 현재씬에게 
	// 나의 위치와 카메라위치를 넘겨준다.(플레이어 부활을 위해)

}

// 활성화상태
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

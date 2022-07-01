#include "BlackKnight.h"

// Laugh 타임이벤터
void BlackKnight::LaughTimeEventerEnd()
{
	// 종료될때 플레이어를 찾아내서 방향을 설정한다.
	LaughDirectCheck();

	// 종료되면 상태 변경한다.
	m_BlackKnightFSM.ChangeState(L"BlackKnight_Idle");
}

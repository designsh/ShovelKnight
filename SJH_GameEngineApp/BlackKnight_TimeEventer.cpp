#include "BlackKnight.h"

// Laugh Ÿ���̺���
void BlackKnight::LaughTimeEventerEnd()
{
	// ����ɶ� �÷��̾ ã�Ƴ��� ������ �����Ѵ�.
	LaughDirectCheck();

	// ����Ǹ� ���� �����Ѵ�.
	m_BlackKnightFSM.ChangeState(L"BlackKnight_Idle");
}

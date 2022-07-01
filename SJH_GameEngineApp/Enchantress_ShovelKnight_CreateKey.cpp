#include "Enchantress_ShovelKnight.h"
#include <SGameEngineInput.h>

void Enchantress_ShovelKnight::CreateActionKey()
{
	SGameEngineInput::CreateKey(L"PLAYER_LEFT", VK_LEFT);                                          // �� -> ���� �̵�
	SGameEngineInput::CreateKey(L"PLAYER_RIGHT", VK_RIGHT);                                    // �� -> �������̵�
	SGameEngineInput::CreateKey(L"PLAYER_JUMP", VK_SPACE);                                     // Space -> ����
	SGameEngineInput::CreateKey(L"PLAYER_LADDERDOWN", VK_DOWN);                    // �� -> �Ʒ��̵�(��ٸ��� Ÿ��������)
	SGameEngineInput::CreateKey(L"PLAYER_LADDERUP", VK_UP);                                  // �� -> �����̵�(��ٸ��� Ÿ��������)
	SGameEngineInput::CreateKey(L"PLAYER_JUMPATTACK", VK_DOWN, VK_SPACE);  // �� + Space -> �������
	SGameEngineInput::CreateKey(L"PLAYER_DEFAULTATTACK", 'A');                             // 'a' or 'A' -> ����

	// ���� ���ų(ġƮ)
	SGameEngineInput::CreateKey(L"PLAYER_ENCHANTRESSKILL", 'B');                           // ���� ���
}

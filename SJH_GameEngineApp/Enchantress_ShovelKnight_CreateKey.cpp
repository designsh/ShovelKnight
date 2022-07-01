#include "Enchantress_ShovelKnight.h"
#include <SGameEngineInput.h>

void Enchantress_ShovelKnight::CreateActionKey()
{
	SGameEngineInput::CreateKey(L"PLAYER_LEFT", VK_LEFT);                                          // ← -> 왼쪽 이동
	SGameEngineInput::CreateKey(L"PLAYER_RIGHT", VK_RIGHT);                                    // → -> 오른쪽이동
	SGameEngineInput::CreateKey(L"PLAYER_JUMP", VK_SPACE);                                     // Space -> 점프
	SGameEngineInput::CreateKey(L"PLAYER_LADDERDOWN", VK_DOWN);                    // ↓ -> 아래이동(사다리를 타고있을때)
	SGameEngineInput::CreateKey(L"PLAYER_LADDERUP", VK_UP);                                  // ↑ -> 위로이동(사다리를 타고있을때)
	SGameEngineInput::CreateKey(L"PLAYER_JUMPATTACK", VK_DOWN, VK_SPACE);  // ↓ + Space -> 내려찍기
	SGameEngineInput::CreateKey(L"PLAYER_DEFAULTATTACK", 'A');                             // 'a' or 'A' -> 공격

	// 보스 즉시킬(치트)
	SGameEngineInput::CreateKey(L"PLAYER_ENCHANTRESSKILL", 'B');                           // 보스 즉사
}

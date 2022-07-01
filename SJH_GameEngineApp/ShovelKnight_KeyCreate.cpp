#include "ShovelKnight.h"

// 플레이어 이동 및 액션을 위한 키를 생성한다.
void ShovelKnight::CreateActionKey()
{
	// 플레이어 기본 액션
	SGameEngineInput::CreateKey(L"LEFT", VK_LEFT);                                          // ← -> 왼쪽 이동
	SGameEngineInput::CreateKey(L"RIGHT", VK_RIGHT);                                    // → -> 오른쪽이동
	SGameEngineInput::CreateKey(L"JUMP", VK_SPACE);                                     // Space -> 점프
	SGameEngineInput::CreateKey(L"LADDERDOWN", VK_DOWN);                    // ↓ -> 아래이동(사다리를 타고있을때)
	SGameEngineInput::CreateKey(L"LADDERUP", VK_UP);                                  // ↑ -> 위로이동(사다리를 타고있을때)
	SGameEngineInput::CreateKey(L"JUMPATTACK", VK_DOWN, VK_SPACE);  // ↓ + Space -> 내려찍기
	SGameEngineInput::CreateKey(L"DEFAULTATTACK", 'A');                             // 'a' or 'A' -> 공격

	// 플레이어 치트 키
	SGameEngineInput::CreateKey(L"Player_InvincibilityOn", 'L');                         // 무적모드(몬스터로 공격은 받고 체력은 깎이나 죽지는않음) On
	SGameEngineInput::CreateKey(L"Player_InvincibilityOff", 'K');                        // 무적모드 Off
	SGameEngineInput::CreateKey(L"Player_SpeedUp", 'J');                                 // 스피드 증가(2배)
	SGameEngineInput::CreateKey(L"Player_SpeedDown", 'H');                           // 스피드 원상복귀
	SGameEngineInput::CreateKey(L"Player_Teleportation", 'M');                        // 플레이어 텔레포트(보스방 이전지점)
	SGameEngineInput::CreateKey(L"Player_PrevTeleportation", 'N');                 // 플레이어 텔레포트 전 위치로 복귀
	SGameEngineInput::CreateKey(L"Player_BossKill", 'B');                                  // 보스 즉사(보스가 살아있고 보스의 체력이 남아있는경우 발동가능)

	SGameEngineInput::CreateKey(L"Player_FreeModeOn", 'F');                         // 치트 프리모드로 모든 오브젝트를 무시하고 이동한다.
	SGameEngineInput::CreateKey(L"Player_FreeModeOff", 'G');                       // 프리모드 해제
}

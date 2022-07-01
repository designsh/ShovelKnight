#include "ShovelKnight.h"

// �÷��̾� �̵� �� �׼��� ���� Ű�� �����Ѵ�.
void ShovelKnight::CreateActionKey()
{
	// �÷��̾� �⺻ �׼�
	SGameEngineInput::CreateKey(L"LEFT", VK_LEFT);                                          // �� -> ���� �̵�
	SGameEngineInput::CreateKey(L"RIGHT", VK_RIGHT);                                    // �� -> �������̵�
	SGameEngineInput::CreateKey(L"JUMP", VK_SPACE);                                     // Space -> ����
	SGameEngineInput::CreateKey(L"LADDERDOWN", VK_DOWN);                    // �� -> �Ʒ��̵�(��ٸ��� Ÿ��������)
	SGameEngineInput::CreateKey(L"LADDERUP", VK_UP);                                  // �� -> �����̵�(��ٸ��� Ÿ��������)
	SGameEngineInput::CreateKey(L"JUMPATTACK", VK_DOWN, VK_SPACE);  // �� + Space -> �������
	SGameEngineInput::CreateKey(L"DEFAULTATTACK", 'A');                             // 'a' or 'A' -> ����

	// �÷��̾� ġƮ Ű
	SGameEngineInput::CreateKey(L"Player_InvincibilityOn", 'L');                         // �������(���ͷ� ������ �ް� ü���� ���̳� �����¾���) On
	SGameEngineInput::CreateKey(L"Player_InvincibilityOff", 'K');                        // ������� Off
	SGameEngineInput::CreateKey(L"Player_SpeedUp", 'J');                                 // ���ǵ� ����(2��)
	SGameEngineInput::CreateKey(L"Player_SpeedDown", 'H');                           // ���ǵ� ���󺹱�
	SGameEngineInput::CreateKey(L"Player_Teleportation", 'M');                        // �÷��̾� �ڷ���Ʈ(������ ��������)
	SGameEngineInput::CreateKey(L"Player_PrevTeleportation", 'N');                 // �÷��̾� �ڷ���Ʈ �� ��ġ�� ����
	SGameEngineInput::CreateKey(L"Player_BossKill", 'B');                                  // ���� ���(������ ����ְ� ������ ü���� �����ִ°�� �ߵ�����)

	SGameEngineInput::CreateKey(L"Player_FreeModeOn", 'F');                         // ġƮ �������� ��� ������Ʈ�� �����ϰ� �̵��Ѵ�.
	SGameEngineInput::CreateKey(L"Player_FreeModeOff", 'G');                       // ������� ����
}

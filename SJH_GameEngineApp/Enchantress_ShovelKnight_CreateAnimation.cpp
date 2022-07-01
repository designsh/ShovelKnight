#include "Enchantress_ShovelKnight.h"

void Enchantress_ShovelKnight::CreatePlayerAnimation()
{
	// �⺻ �÷��̾� �ִϸ��̼�
	m_AniPlayer = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Player);
	m_AniPlayer->SetRenderScale({ 300, 300 });

	// 1. Left Animation
	m_AniPlayer->CreateAnimation(L"Left_PlayerNone", L"Left_Enchantress_Player.bmp", 0, 4, 0.5f, false);                       // �����̵� �� ��������
	m_AniPlayer->CreateAnimation(L"Left_PlayerMove", L"Left_Enchantress_Player.bmp", 5, 10);                                       // �������� �̵�
	m_AniPlayer->CreateAnimation(L"Left_PlayerBossFind", L"Left_Enchantress_Player.bmp", 24, 26, 0.1f, false);             // ���� ������ ���� ī�޶� ����
	m_AniPlayer->CreateAnimation(L"Left_PlayerAttack", L"Left_Enchantress_Player.bmp", 18, 23, 0.1f, false);                 // �����̵� �� ����
	m_AniPlayer->CreateAnimation(L"Left_PlayerJumpStart", L"Left_Enchantress_Player.bmp", 57, 57);                             // �����̵� �� �������� ~ �ְ�������
	m_AniPlayer->CreateAnimation(L"Left_PlayerJumpStay", L"Left_Enchantress_Player.bmp", 58, 58);                             // �����̵� �� �����ְ��� ~ 
	m_AniPlayer->CreateAnimation(L"Left_PlayerJumpAttack", L"Left_Enchantress_Player.bmp", 46, 46);                          // �����̵� �� �������϶� �Ʒ�Ű����
	m_AniPlayer->CreateAnimation(L"Left_PlayerKnockBack", L"Left_Enchantress_Player.bmp", 50, 50);                            // ���Ϳ����� �˹�
	m_AniPlayer->CreateAnimation(L"Left_PlayerShildKnightCol", L"Left_Enchantress_Player.bmp", 33, 34, 0.1f, false);   // ���б��� �浹
	m_AniPlayer->CreateAnimation(L"Left_PlayerShildKnightColIdle", L"Left_Enchantress_Player.bmp", 59, 59);               // ���б��� �浹 �� ����������

	// 2. Right Animation
	m_AniPlayer->CreateAnimation(L"Right_PlayerNone", L"Right_Enchantress_Player.bmp", 0, 4, 0.5f, false);                   // �������̵� �� ��������
	m_AniPlayer->CreateAnimation(L"Right_PlayerMove", L"Right_Enchantress_Player.bmp", 5, 10);                                   // ���������� �̵�
	m_AniPlayer->CreateAnimation(L"Right_PlayerBossFind", L"Right_Enchantress_Player.bmp", 24, 26, 0.1f, false);         // ���� ������ ���� ī�޶� ����
	m_AniPlayer->CreateAnimation(L"Right_PlayerAttack", L"Right_Enchantress_Player.bmp", 18, 23, 0.1f, false);             // �������̵� �� ����
	m_AniPlayer->CreateAnimation(L"Right_PlayerJumpStart", L"Right_Enchantress_Player.bmp", 57, 57);                          // �������̵� �� �������� ~ �ְ�������
	m_AniPlayer->CreateAnimation(L"Right_PlayerJumpStay", L"Right_Enchantress_Player.bmp", 58, 58);                          // �������̵� �� �����ְ��� ~ 
	m_AniPlayer->CreateAnimation(L"Right_PlayerJumpAttack", L"Right_Enchantress_Player.bmp", 46, 46);                      // �������̵� �� �������϶� �Ʒ�Ű����
	m_AniPlayer->CreateAnimation(L"Right_PlayerKnockBack", L"Right_Enchantress_Player.bmp", 50, 50);                        // ���Ϳ����� �˹�
	m_AniPlayer->CreateAnimation(L"Right_PlayerShildKnightCol", L"Right_Enchantress_Player.bmp", 33, 34, 0.1f, false);// ���б��� �浹
	m_AniPlayer->CreateAnimation(L"Right_PlayerShildKnightColIdle", L"Right_Enchantress_Player.bmp", 59, 59);            // ���б��� �浹 �� ����������
}

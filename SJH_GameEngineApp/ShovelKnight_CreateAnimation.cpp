#include "ShovelKnight.h"

void ShovelKnight::CreatePlayerAnimation()
{
	// �⺻ �÷��̾� �ִϸ��̼�
	m_AniPlayer = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Player);
	m_AniPlayer->SetRenderScale({ 300, 300 });

	// 1. Left Animation
	m_AniPlayer->CreateAnimation(L"LeftPlayerNone", L"Player Left Move.bmp", 0, 4, 0.5f, false);                       // �����̵� �� ��������
	m_AniPlayer->CreateAnimation(L"LeftPlayerMove", L"Player Left Move.bmp", 5, 10);                                       // �������� �̵�
	m_AniPlayer->CreateAnimation(L"LeftPlayerAttack", L"Player Left Move.bmp", 18, 23, 0.1f, false);                 // �����̵� �� ����
	m_AniPlayer->CreateAnimation(L"LeftPlayerJumpStart", L"Player Left Move.bmp", 57, 57);                             // �����̵� �� �������� ~ �ְ�������
	m_AniPlayer->CreateAnimation(L"LeftPlayerJumpStay", L"Player Left Move.bmp", 58, 58);                             // �����̵� �� �����ְ��� ~ 
	m_AniPlayer->CreateAnimation(L"LeftPlayerJumpAttack", L"Player Left Move.bmp", 46, 46);                          // �����̵� �� �������϶� �Ʒ�Ű����
	m_AniPlayer->CreateAnimation(L"LeftPlayerAppear", L"Player Left Move.bmp", 36, 42, 1.f, false);				  // Stage Start�� �÷��̾� �����ʿ��� �������� �����
	m_AniPlayer->CreateAnimation(L"LeftPlayerKnockBack", L"Player Left Move.bmp", 50, 50);                            // ���Ϳ����� �˹�
	m_AniPlayer->CreateAnimation(L"LeftPlayerVictory", L"Player Left Move.bmp", 42, 42);                                  // ����óġ

	// 2. Right Animation
	m_AniPlayer->CreateAnimation(L"RightPlayerNone", L"Player Right Move.bmp", 0, 4, 0.5f, false);                   // �������̵� �� ��������
	m_AniPlayer->CreateAnimation(L"RightPlayerMove", L"Player Right Move.bmp", 5, 10);                                   // ���������� �̵�
	m_AniPlayer->CreateAnimation(L"RightPlayerAttack", L"Player Right Move.bmp", 18, 23, 0.1f, false);             // �������̵� �� ����
	m_AniPlayer->CreateAnimation(L"RightPlayerJumpStart", L"Player Right Move.bmp", 57, 57);                          // �������̵� �� �������� ~ �ְ�������
	m_AniPlayer->CreateAnimation(L"RightPlayerJumpStay", L"Player Right Move.bmp", 58, 58);                          // �������̵� �� �����ְ��� ~ 
	m_AniPlayer->CreateAnimation(L"RightPlayerJumpAttack", L"Player Right Move.bmp", 46, 46);                      // �������̵� �� �������϶� �Ʒ�Ű����
	m_AniPlayer->CreateAnimation(L"RightPlayerAppear", L"Player Right Move.bmp", 36, 42, 1.f, false);             // Stage Start�� �÷��̾� ���ʿ��� ���������� �����
	m_AniPlayer->CreateAnimation(L"RightPlayerKnockBack", L"Player Right Move.bmp", 50, 50);                        // ���Ϳ����� �˹�
	m_AniPlayer->CreateAnimation(L"RightPlayerVictory", L"Player Right Move.bmp", 42, 42);                               // ����óġ

	// 3. ����� ������� Animation
	m_AniPlayer->CreateAnimation(L"PlayerLadderStart", L"Player Right Move.bmp", 45, 45);								  // �÷��̾� ��ٸ��� ó�� �浹�ؼ� �ö�������
	m_AniPlayer->CreateAnimation(L"PlayerLadderMove", L"Player Right Move.bmp", 43, 44, 0.5f, true);            // �÷��̾� ��ٸ������� �̵�
}
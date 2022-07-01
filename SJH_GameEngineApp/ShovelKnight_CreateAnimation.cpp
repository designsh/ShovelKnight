#include "ShovelKnight.h"

void ShovelKnight::CreatePlayerAnimation()
{
	// 기본 플레이어 애니메이션
	m_AniPlayer = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Player);
	m_AniPlayer->SetRenderScale({ 300, 300 });

	// 1. Left Animation
	m_AniPlayer->CreateAnimation(L"LeftPlayerNone", L"Player Left Move.bmp", 0, 4, 0.5f, false);                       // 왼쪽이동 중 정지상태
	m_AniPlayer->CreateAnimation(L"LeftPlayerMove", L"Player Left Move.bmp", 5, 10);                                       // 왼쪽으로 이동
	m_AniPlayer->CreateAnimation(L"LeftPlayerAttack", L"Player Left Move.bmp", 18, 23, 0.1f, false);                 // 왼쪽이동 중 공격
	m_AniPlayer->CreateAnimation(L"LeftPlayerJumpStart", L"Player Left Move.bmp", 57, 57);                             // 왼쪽이동 중 점프시작 ~ 최고점까지
	m_AniPlayer->CreateAnimation(L"LeftPlayerJumpStay", L"Player Left Move.bmp", 58, 58);                             // 왼쪽이동 중 점프최고점 ~ 
	m_AniPlayer->CreateAnimation(L"LeftPlayerJumpAttack", L"Player Left Move.bmp", 46, 46);                          // 왼쪽이동 중 점프중일때 아래키공격
	m_AniPlayer->CreateAnimation(L"LeftPlayerAppear", L"Player Left Move.bmp", 36, 42, 1.f, false);				  // Stage Start시 플레이어 오른쪽에서 왼쪽으로 등장씬
	m_AniPlayer->CreateAnimation(L"LeftPlayerKnockBack", L"Player Left Move.bmp", 50, 50);                            // 몬스터에의해 넉백
	m_AniPlayer->CreateAnimation(L"LeftPlayerVictory", L"Player Left Move.bmp", 42, 42);                                  // 보스처치

	// 2. Right Animation
	m_AniPlayer->CreateAnimation(L"RightPlayerNone", L"Player Right Move.bmp", 0, 4, 0.5f, false);                   // 오른쪽이동 중 정지상태
	m_AniPlayer->CreateAnimation(L"RightPlayerMove", L"Player Right Move.bmp", 5, 10);                                   // 오른쪽으로 이동
	m_AniPlayer->CreateAnimation(L"RightPlayerAttack", L"Player Right Move.bmp", 18, 23, 0.1f, false);             // 오른쪽이동 중 공격
	m_AniPlayer->CreateAnimation(L"RightPlayerJumpStart", L"Player Right Move.bmp", 57, 57);                          // 오른쪽이동 중 점프시작 ~ 최고점까지
	m_AniPlayer->CreateAnimation(L"RightPlayerJumpStay", L"Player Right Move.bmp", 58, 58);                          // 오른쪽이동 중 점프최고점 ~ 
	m_AniPlayer->CreateAnimation(L"RightPlayerJumpAttack", L"Player Right Move.bmp", 46, 46);                      // 오른쪽이동 중 점프중일때 아래키공격
	m_AniPlayer->CreateAnimation(L"RightPlayerAppear", L"Player Right Move.bmp", 36, 42, 1.f, false);             // Stage Start시 플레이어 왼쪽에서 오른쪽으로 등장씬
	m_AniPlayer->CreateAnimation(L"RightPlayerKnockBack", L"Player Right Move.bmp", 50, 50);                        // 몬스터에의해 넉백
	m_AniPlayer->CreateAnimation(L"RightPlayerVictory", L"Player Right Move.bmp", 42, 42);                               // 보스처치

	// 3. 방향과 상관없는 Animation
	m_AniPlayer->CreateAnimation(L"PlayerLadderStart", L"Player Right Move.bmp", 45, 45);								  // 플레이어 사다리에 처음 충돌해서 올라탔을때
	m_AniPlayer->CreateAnimation(L"PlayerLadderMove", L"Player Right Move.bmp", 43, 44, 0.5f, true);            // 플레이어 사다리에서의 이동
}
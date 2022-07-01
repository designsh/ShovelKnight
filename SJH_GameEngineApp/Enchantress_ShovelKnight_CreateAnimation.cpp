#include "Enchantress_ShovelKnight.h"

void Enchantress_ShovelKnight::CreatePlayerAnimation()
{
	// 기본 플레이어 애니메이션
	m_AniPlayer = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Player);
	m_AniPlayer->SetRenderScale({ 300, 300 });

	// 1. Left Animation
	m_AniPlayer->CreateAnimation(L"Left_PlayerNone", L"Left_Enchantress_Player.bmp", 0, 4, 0.5f, false);                       // 왼쪽이동 중 정지상태
	m_AniPlayer->CreateAnimation(L"Left_PlayerMove", L"Left_Enchantress_Player.bmp", 5, 10);                                       // 왼쪽으로 이동
	m_AniPlayer->CreateAnimation(L"Left_PlayerBossFind", L"Left_Enchantress_Player.bmp", 24, 26, 0.1f, false);             // 보스 등장을 위해 카메라 러프
	m_AniPlayer->CreateAnimation(L"Left_PlayerAttack", L"Left_Enchantress_Player.bmp", 18, 23, 0.1f, false);                 // 왼쪽이동 중 공격
	m_AniPlayer->CreateAnimation(L"Left_PlayerJumpStart", L"Left_Enchantress_Player.bmp", 57, 57);                             // 왼쪽이동 중 점프시작 ~ 최고점까지
	m_AniPlayer->CreateAnimation(L"Left_PlayerJumpStay", L"Left_Enchantress_Player.bmp", 58, 58);                             // 왼쪽이동 중 점프최고점 ~ 
	m_AniPlayer->CreateAnimation(L"Left_PlayerJumpAttack", L"Left_Enchantress_Player.bmp", 46, 46);                          // 왼쪽이동 중 점프중일때 아래키공격
	m_AniPlayer->CreateAnimation(L"Left_PlayerKnockBack", L"Left_Enchantress_Player.bmp", 50, 50);                            // 몬스터에의해 넉백
	m_AniPlayer->CreateAnimation(L"Left_PlayerShildKnightCol", L"Left_Enchantress_Player.bmp", 33, 34, 0.1f, false);   // 방패기사와 충돌
	m_AniPlayer->CreateAnimation(L"Left_PlayerShildKnightColIdle", L"Left_Enchantress_Player.bmp", 59, 59);               // 방패기사와 충돌 후 엔딩대기상태

	// 2. Right Animation
	m_AniPlayer->CreateAnimation(L"Right_PlayerNone", L"Right_Enchantress_Player.bmp", 0, 4, 0.5f, false);                   // 오른쪽이동 중 정지상태
	m_AniPlayer->CreateAnimation(L"Right_PlayerMove", L"Right_Enchantress_Player.bmp", 5, 10);                                   // 오른쪽으로 이동
	m_AniPlayer->CreateAnimation(L"Right_PlayerBossFind", L"Right_Enchantress_Player.bmp", 24, 26, 0.1f, false);         // 보스 등장을 위해 카메라 러프
	m_AniPlayer->CreateAnimation(L"Right_PlayerAttack", L"Right_Enchantress_Player.bmp", 18, 23, 0.1f, false);             // 오른쪽이동 중 공격
	m_AniPlayer->CreateAnimation(L"Right_PlayerJumpStart", L"Right_Enchantress_Player.bmp", 57, 57);                          // 오른쪽이동 중 점프시작 ~ 최고점까지
	m_AniPlayer->CreateAnimation(L"Right_PlayerJumpStay", L"Right_Enchantress_Player.bmp", 58, 58);                          // 오른쪽이동 중 점프최고점 ~ 
	m_AniPlayer->CreateAnimation(L"Right_PlayerJumpAttack", L"Right_Enchantress_Player.bmp", 46, 46);                      // 오른쪽이동 중 점프중일때 아래키공격
	m_AniPlayer->CreateAnimation(L"Right_PlayerKnockBack", L"Right_Enchantress_Player.bmp", 50, 50);                        // 몬스터에의해 넉백
	m_AniPlayer->CreateAnimation(L"Right_PlayerShildKnightCol", L"Right_Enchantress_Player.bmp", 33, 34, 0.1f, false);// 방패기사와 충돌
	m_AniPlayer->CreateAnimation(L"Right_PlayerShildKnightColIdle", L"Right_Enchantress_Player.bmp", 59, 59);            // 방패기사와 충돌 후 엔딩대기상태
}

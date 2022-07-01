#include "Enchantress_FinalBoss.h"

void Enchantress_FinalBoss::Create_BossAnimation()
{
	m_AniEnchantress = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Monster);
	m_AniEnchantress->SetRenderScale({ 350, 350 });

	// 왼쪽이동
	m_AniEnchantress->CreateAnimation(L"Left_Boss_Find", L"Left_The_Enchantress.bmp", 52, 52);                          // 카메라 찾는중
	m_AniEnchantress->CreateAnimation(L"Left_Boss_CamFound", L"Left_The_Enchantress.bmp", 52, 55);               // 카메라 발견
	m_AniEnchantress->CreateAnimation(L"Left_Boss_Appear", L"Left_The_Enchantress.bmp", 56, 79, 0.3f);            // 등장
	m_AniEnchantress->CreateAnimation(L"Left_Boss_Idle", L"Left_The_Enchantress.bmp", 0, 3);                               // 대기
	m_AniEnchantress->CreateAnimation(L"Left_Boss_Move", L"Left_The_Enchantress.bmp", 4, 7);                            // 이동
	m_AniEnchantress->CreateAnimation(L"Left_Boss_AttackSkillCharging", L"Left_The_Enchantress.bmp", 8, 21, 0.1f, false);   // 공격스킬 장전
	m_AniEnchantress->CreateAnimation(L"Left_Boss_AttackSkill", L"Left_The_Enchantress.bmp", 21, 25);                // 공격스킬 왼쪽으로공격
	m_AniEnchantress->CreateAnimation(L"Left_Boss_DownAttackSkill", L"Left_The_Enchantress.bmp", 26, 29);      // 공격스킬 아래쪽으로공격
	m_AniEnchantress->CreateAnimation(L"Left_Boss_UpAttackSkill", L"Left_The_Enchantress.bmp", 30, 33);           // 공격스킬 위쪽으로공격
	m_AniEnchantress->CreateAnimation(L"Left_Boss_RegenSkillCharging", L"Left_The_Enchantress.bmp", 34, 47); // 블록 리젠 스킬 장전
	m_AniEnchantress->CreateAnimation(L"Left_Boss_Death", L"Left_The_Enchantress.bmp", 48, 50);                       // 사망
	m_AniEnchantress->CreateAnimation(L"Left_Boss_ImageChange", L"Left_The_Enchantress.bmp", 80, 83);          // 이미지 체인지


	// 오른쪽이동
	m_AniEnchantress->CreateAnimation(L"Right_Boss_Find", L"Right_The_Enchantress.bmp", 52, 52);                          // 카메라 찾는중
	m_AniEnchantress->CreateAnimation(L"Right_Boss_CamFound", L"Right_The_Enchantress.bmp", 52, 55);               // 카메라 발견
	m_AniEnchantress->CreateAnimation(L"Right_Boss_Appear", L"Right_The_Enchantress.bmp", 56, 79, 0.3f);            // 등장
	m_AniEnchantress->CreateAnimation(L"Right_Boss_Idle", L"Right_The_Enchantress.bmp", 0, 3);                               // 대기
	m_AniEnchantress->CreateAnimation(L"Right_Boss_Move", L"Right_The_Enchantress.bmp", 4, 7);                            // 이동
	m_AniEnchantress->CreateAnimation(L"Right_Boss_AttackSkillCharging", L"Right_The_Enchantress.bmp", 8, 21, 0.1f, false);   // 공격스킬 장전
	m_AniEnchantress->CreateAnimation(L"Right_Boss_AttackSkill", L"Right_The_Enchantress.bmp", 21, 25);                // 공격스킬 왼쪽으로공격
	m_AniEnchantress->CreateAnimation(L"Right_Boss_DownAttackSkill", L"Right_The_Enchantress.bmp", 26, 29);      // 공격스킬 아래쪽으로공격
	m_AniEnchantress->CreateAnimation(L"Right_Boss_UpAttackSkill", L"Right_The_Enchantress.bmp", 30, 33);           // 공격스킬 위쪽으로공격
	m_AniEnchantress->CreateAnimation(L"Right_Boss_RegenSkillCharging", L"Right_The_Enchantress.bmp", 34, 47); // 블록 리젠 스킬 장전
	m_AniEnchantress->CreateAnimation(L"Right_Boss_Death", L"Right_The_Enchantress.bmp", 48, 50);                       // 사망
	m_AniEnchantress->CreateAnimation(L"Right_Boss_ImageChange", L"Right_The_Enchantress.bmp", 80, 83);          // 이미지 체인지

	// 방패기사 애니메이션
	m_AniShildKnight = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Monster);
	m_AniShildKnight->SetRenderScale({ 300, 300 });
	m_AniShildKnight->SetPivotPos({ 10.f, 0.f });
	m_AniShildKnight->CreateAnimation(L"ShildKnight_Appear", L"Shild_Knight.bmp", 0, 0);
	m_AniShildKnight->CreateAnimation(L"ShildKnight_MoveStart", L"Shild_Knight.bmp", 1, 2, 0.1f, false);
	m_AniShildKnight->CreateAnimation(L"ShildKnight_MoveIdle", L"Shild_Knight.bmp", 2, 2);
	m_AniShildKnight->Off();
}

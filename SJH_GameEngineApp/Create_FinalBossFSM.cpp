#include "Enchantress_FinalBoss.h"

void Enchantress_FinalBoss::Create_BossFSMState()
{
	m_EnchantressFSM.CreateState(L"Enchantress_Find", this, &Enchantress_FinalBoss::FindStay, &Enchantress_FinalBoss::FindStart, &Enchantress_FinalBoss::FindEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_CamFound", this, &Enchantress_FinalBoss::CamFoundStay, &Enchantress_FinalBoss::CamFoundStart, &Enchantress_FinalBoss::CamFoundEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_Appear", this, &Enchantress_FinalBoss::AppearStay, &Enchantress_FinalBoss::AppearStart, &Enchantress_FinalBoss::AppearEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_Idle", this, &Enchantress_FinalBoss::IdleStay, &Enchantress_FinalBoss::IdleStart, &Enchantress_FinalBoss::IdleEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_Move", this, &Enchantress_FinalBoss::MoveStay, &Enchantress_FinalBoss::MoveStart, &Enchantress_FinalBoss::MoveEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_AttackSkillCharging", this, &Enchantress_FinalBoss::AttackSkillChargingStay, &Enchantress_FinalBoss::AttackSkillChargingStart, &Enchantress_FinalBoss::AttackSkillChargingEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_DownAttackSkillCharging", this, &Enchantress_FinalBoss::DownAttackSkillChargingStay, &Enchantress_FinalBoss::DownAttackSkillChargingStart, &Enchantress_FinalBoss::DownAttackSkillChargingEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_UpAttackSkillCharging", this, &Enchantress_FinalBoss::UpAttackSkillChargingStay, &Enchantress_FinalBoss::UpAttackSkillChargingStart, &Enchantress_FinalBoss::UpAttackSkillChargingEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_BasicAttackSkillShot", this, &Enchantress_FinalBoss::BasicAttackSkillShotStay, &Enchantress_FinalBoss::BasicAttackSkillShotStart, &Enchantress_FinalBoss::BasicAttackSkillShotEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_DownAttackSkillShot", this, &Enchantress_FinalBoss::DownAttackSkillShotStay, &Enchantress_FinalBoss::DownAttackSkillShotStart, &Enchantress_FinalBoss::DownAttackSkillShotEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_UpAttackSkillShot", this, &Enchantress_FinalBoss::UpAttackSkillShotStay, &Enchantress_FinalBoss::UpAttackSkillShotStart, &Enchantress_FinalBoss::UpAttackSkillShotEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_DownAttackSkillShotMove", this, &Enchantress_FinalBoss::DownAttackSkillShotMoveStay, &Enchantress_FinalBoss::DownAttackSkillShotMoveStart, &Enchantress_FinalBoss::DownAttackSkillShotMoveEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_UpAttackSkillShotMove", this, &Enchantress_FinalBoss::UpAttackSkillShotMoveStay, &Enchantress_FinalBoss::UpAttackSkillShotMoveStart, &Enchantress_FinalBoss::UpAttackSkillShotMoveEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_BlockRegetSkillCharging", this, &Enchantress_FinalBoss::BlockRegenSkillChargingStay, &Enchantress_FinalBoss::BlockRegenSkillChargingStart, &Enchantress_FinalBoss::BlockRegenSkillChargingEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_BlockRegetSkillShotIdle", this, &Enchantress_FinalBoss::BlockRegenSkillIdleStay, &Enchantress_FinalBoss::BlockRegenSkillIdleStart, &Enchantress_FinalBoss::BlockRegenSkillIdleEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_Death", this, &Enchantress_FinalBoss::DeathStay, &Enchantress_FinalBoss::DeathStart, &Enchantress_FinalBoss::DeathEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_DeathMove", this, &Enchantress_FinalBoss::DeathMoveStay, &Enchantress_FinalBoss::DeathMoveStart, &Enchantress_FinalBoss::DeathMoveEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_DeathCamShake", this, &Enchantress_FinalBoss::DeathCamShakeEffectStay, &Enchantress_FinalBoss::DeathCamShakeEffectStart, &Enchantress_FinalBoss::DeathCamShakeEffectEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_DeathEffect", this, &Enchantress_FinalBoss::DeathEffectStay, &Enchantress_FinalBoss::DeathEffectStart, &Enchantress_FinalBoss::DeathEffectEnd);
	m_EnchantressFSM.CreateState(L"Enchantress_DeathEffectMove", this, &Enchantress_FinalBoss::DeathEffectMoveStay, &Enchantress_FinalBoss::DeathEffectMoveStart, &Enchantress_FinalBoss::DeathEffectMoveEnd);

	// 초기상태 지정
	m_EnchantressFSM.ChangeState(L"Enchantress_Find");
}

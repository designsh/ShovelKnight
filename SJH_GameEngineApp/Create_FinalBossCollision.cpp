#include "Enchantress_FinalBoss.h"

void Enchantress_FinalBoss::Create_BossCollision()
{
	// 中宜端 持失
	m_EnchantressCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Monster);
	m_EnchantressCol->SetScale({ 50, 50 });
	m_EnchantressCol->SetPivotPos({ 10.f, 20.f });
	m_EnchantressCol->AddStartEvent(this, &Enchantress_FinalBoss::CollisionStart);
	m_EnchantressCol->AddStayEvent(this, &Enchantress_FinalBoss::CollisionStay);
	m_EnchantressCol->AddEndEvent(this, &Enchantress_FinalBoss::CollisionEnd);
	m_EnchantressCol->SetCheckData(0);
}

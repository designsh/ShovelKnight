#include "Enchantress.h"
#include "Enchantress_FinalBoss.h"

void Enchantress::EnchantressCreateMonster()
{
	m_FinalBoss = CreateActor<Enchantress_FinalBoss>();
	m_FinalBoss->SetPosition({ 637.f, 290.f });
	GlobalValue::FinalStage_FinalBoss = m_FinalBoss;
}

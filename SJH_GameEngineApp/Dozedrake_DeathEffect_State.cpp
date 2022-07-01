#include "Dozedrake_DeathEffect.h"

void Dozedrake_DeathEffect::IdleStart()
{
	m_AniDeathEffect->ChangeAnimation(L"DozeDeathEffectIdle");
}

void Dozedrake_DeathEffect::IdleStay()
{
	if (true == m_AniDeathEffect->IsEnd())
	{
		Death();
	}
}

void Dozedrake_DeathEffect::IdleEnd()
{

}

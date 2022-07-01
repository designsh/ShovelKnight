#include "Plains_IconEffect.h"

// Idle»óÅÂ
void Plains_IconEffect::IdleStart()
{
	m_AniClearEffect->ChangeAnimation(L"ClearIdle");
}

void Plains_IconEffect::IdleStay()
{
	if (true == m_AniClearEffect->IsEnd())
	{
		Death();
	}
}

void Plains_IconEffect::IdleEnd()
{

}

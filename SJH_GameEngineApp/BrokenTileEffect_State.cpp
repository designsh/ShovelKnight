#include "BrokenTileEffect.h"

void BrokenTileEffect::DeathStart()
{
	// �ױ� �����Ҷ� ȿ���� ���
	m_BrokenTileSound = SGameEngineSound::Play(L"DirtBlock_Break.mp3", false, 0);

	m_AniBrokenTileEffect->ChangeAnimation(L"EffectDeath");
}

void BrokenTileEffect::DeathStay()
{
	if (true == m_AniBrokenTileEffect->IsEnd())
	{
		Death();
	}
}

void BrokenTileEffect::DeathEnd()
{

}

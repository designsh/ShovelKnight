#include "DirtBlock.h"
#include "DropGold.h"

// 대기상태
void DirtBlock::IDLEStart()
{
	m_AniDirtBlock->ChangeAnimation(L"DIRTBLOCKIDLE");
}

void DirtBlock::IDLEStay()
{

}

void DirtBlock::IDLEEnd()
{

}

// 플레이어가 나를 공격한 상태
void DirtBlock::BeShotStart()
{
	m_AniDirtBlock->ChangeAnimation(L"DIRTBLOCKATT");

	m_DritBlockSound = SGameEngineSound::Play(L"DirtBlock_Break.mp3", false, 0);
}

void DirtBlock::BeShotStay()
{
	// 현재 프레임이 마지막 프레임은 자신은 죽는다.
	if(true == m_AniDirtBlock->IsEnd())
	{
		if (true == m_bDropCoin)
		{
			// 드랍하는 골드가 있다
			DropGold* DropGold1 = GetScene()->CreateActor<DropGold>();
			DropGold1->SetDropGold(20);
			DropGold1->SetMoveSpeed(30.f);
			DropGold1->SetPosition({ GetPosition().x, GetPosition().y - 30.f });

			m_DritBlockSound = SGameEngineSound::Play(L"DirtBlock_GoldDrop.mp3", false, 0);
		}

		Death();
	}
}

void DirtBlock::BeShotEnd()
{
	
}


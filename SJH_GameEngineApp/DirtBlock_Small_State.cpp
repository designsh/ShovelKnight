#include "DirtBlock_Small.h"
#include "DropGold.h"

// 대기상태
void DirtBlock_Small::IDLEStart()
{
	m_AniDirtBlock->ChangeAnimation(L"DIRTSMALLIDLE");
}

void DirtBlock_Small::IDLEStay()
{

}

void DirtBlock_Small::IDLEEnd()
{

}

// 플레이어가 나를 공격한 상태
void DirtBlock_Small::BeShotStart()
{
	m_AniDirtBlock->ChangeAnimation(L"DIRTSMALLATT");

	m_DritBlockSmallSound = SGameEngineSound::Play(L"DirtBlock_Break.mp3", false, 0);
}

void DirtBlock_Small::BeShotStay()
{
	// 현재 프레임이 마지막 프레임은 자신은 죽는다.
	if (true == m_AniDirtBlock->IsEnd())
	{
		if (true == m_bDropCoin)
		{
			// 드랍하는 골드가 있다
			DropGold* DropGold1 = GetScene()->CreateActor<DropGold>();
			DropGold1->SetDropGold(10);
			DropGold1->SetMoveSpeed(30.f);
			DropGold1->SetPosition({ GetPosition().x, GetPosition().y - 30.f });

			m_DritBlockSmallSound = SGameEngineSound::Play(L"DirtBlock_GoldDrop.mp3", false, 0);
		}

		Death();
	}
}

void DirtBlock_Small::BeShotEnd()
{

}
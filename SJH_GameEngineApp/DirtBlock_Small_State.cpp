#include "DirtBlock_Small.h"
#include "DropGold.h"

// ������
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

// �÷��̾ ���� ������ ����
void DirtBlock_Small::BeShotStart()
{
	m_AniDirtBlock->ChangeAnimation(L"DIRTSMALLATT");

	m_DritBlockSmallSound = SGameEngineSound::Play(L"DirtBlock_Break.mp3", false, 0);
}

void DirtBlock_Small::BeShotStay()
{
	// ���� �������� ������ �������� �ڽ��� �״´�.
	if (true == m_AniDirtBlock->IsEnd())
	{
		if (true == m_bDropCoin)
		{
			// ����ϴ� ��尡 �ִ�
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
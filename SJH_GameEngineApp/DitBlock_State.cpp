#include "DirtBlock.h"
#include "DropGold.h"

// ������
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

// �÷��̾ ���� ������ ����
void DirtBlock::BeShotStart()
{
	m_AniDirtBlock->ChangeAnimation(L"DIRTBLOCKATT");

	m_DritBlockSound = SGameEngineSound::Play(L"DirtBlock_Break.mp3", false, 0);
}

void DirtBlock::BeShotStay()
{
	// ���� �������� ������ �������� �ڽ��� �״´�.
	if(true == m_AniDirtBlock->IsEnd())
	{
		if (true == m_bDropCoin)
		{
			// ����ϴ� ��尡 �ִ�
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


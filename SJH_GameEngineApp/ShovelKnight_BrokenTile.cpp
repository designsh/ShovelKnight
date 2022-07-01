#include "ShovelKnight.h"
#include <SGameEngineResMgr.h>
#include <SGameEngineCollision.h>

#include "PlainsTileMap.h"
#include "BrokenTileEffect.h"

// BrokenTile ������ ���Ϸκ��� �о�´�.
void ShovelKnight::LoadBrokenTileMap()
{
	// Broken TileMap File ���
	m_BrokenTileFilePath.MoveParentsFolder(L"ShovelKnight");
	m_BrokenTileFilePath.MoveChildFolder(L"Resource");
	m_BrokenTileFilePath.MoveChildFolder(L"Image");
	m_BrokenTileFilePath.MoveChildFolder(L"Stage");
	m_BrokenTileFilePath.MoveChildFolder(L"TileSet");

	// ���Ͽ� ����� Ÿ������ ��������
	m_BrokenTile = CreateRenderer<SGameEngineRendererTile>((int)GlobalValue::RenderGroup::BrokenTile);
	m_BrokenTile->TileMapStart(L"Plains_Broken_Tile.bmp", { 32.f, 32.f }, { 32.f, 32.f }, 720, 135);
	SGameEngineString LoadPath = m_BrokenTileFilePath.GetPath();
	LoadPath += L"Stage1BrokenTile.dat";
	m_BrokenTile->LoadTile(LoadPath);

	// �⺻������ Off ����
	m_BrokenTile->Off();
}

void ShovelKnight::RightFind(FLOAT4 _StartIndex)
{
	// �ش� ����Ʈ�� ���� ����.
	m_BrokenAllTile.clear();

	// ����Ÿ���ε����� ���ʿ��� Ÿ���� �����ϴ��� ã�´�.
	FLOAT4 CurIndexX = _StartIndex;
	while (true)
	{
		int ImageIndex = m_BrokenTile->GetTileImageIndex(CurIndexX);
		if (-1 == ImageIndex)
		{
			break;
		}
		CurIndexX.x = CurIndexX.x - 1;
	}
	CurIndexX.x += 1;

	// ����Ÿ���� ��� ã������ ���� �̵�
	FLOAT4 CurPos = CurIndexX;
	while (true)
	{
		int ImageIndex = m_BrokenTile->GetTileImageIndex(CurPos);
		if (-1 == ImageIndex)
		{
			break;
		}
		CurPos.y = CurPos.y - 1.f;
	}
	CurPos.y += 1.f;

	// ����Ÿ���� ��� ã������ �Ʒ��� �̵�
	FLOAT4 CheckSize = CurPos;
	while (true)
	{
		int ImageIndex = m_BrokenTile->GetTileImageIndex(CheckSize);
		if (-1 == ImageIndex)
		{
			break;
		}
		CheckSize.y = CheckSize.y + 1.f;
	}

	// Y�� ũ�⸦ ���Ѵ�. 
	int YSize = CheckSize.iy() - CurPos.iy();

	// ��� ������ Ÿ���� ã�����Ƿ�
	CheckSize = CurPos;
	while (true)
	{
		int Check = m_BrokenTile->GetTileImageIndex(CheckSize);
		if (-1 == Check)
		{
			break;
		}

		m_BrokenAllTile.push_back(std::vector<FLOAT4>(YSize));
		std::vector<FLOAT4>& NewLine = m_BrokenAllTile.back();
		for (size_t i = 0; i < YSize; i++)
		{
			NewLine[i].x = CheckSize.x;
			NewLine[i].y = CheckSize.y + i;
		}
		CheckSize.x += 1;
	}
}

void ShovelKnight::LeftFind(FLOAT4 _StartIndex)
{
	// �ش� ����Ʈ�� ���� ����.
	m_BrokenAllTile.clear();

	// ����Ÿ���ε����� �����ʿ��� Ÿ���� �����ϴ��� ã�´�.
	FLOAT4 CurIndexX = _StartIndex;
	while (true)
	{
		int ImageIndex = m_BrokenTile->GetTileImageIndex(CurIndexX);
		if (-1 == ImageIndex)
		{
			break;
		}
		CurIndexX.x = CurIndexX.x + 1;
	}
	CurIndexX.x -= 1;

	// ����Ÿ���� ��� ã������ ���� �̵�
	FLOAT4 CurPos = CurIndexX;
	while (true)
	{
		int ImageIndex = m_BrokenTile->GetTileImageIndex(CurPos);
		if (-1 == ImageIndex)
		{
			break;
		}
		CurPos.y = CurPos.y - 1.f;
	}
	CurPos.y += 1.f;

	// ����Ÿ���� ��� ã������ �Ʒ��� �̵�
	FLOAT4 CheckSize = CurPos;
	while (true)
	{
		int ImageIndex = m_BrokenTile->GetTileImageIndex(CheckSize);
		if (-1 == ImageIndex)
		{
			break;
		}
		CheckSize.y = CheckSize.y + 1.f;
	}

	// Y�� ũ�⸦ ���Ѵ�. 
	int YSize = CheckSize.iy() - CurPos.iy();

	// ��� ������ Ÿ���� ã�����Ƿ�
	CheckSize = CurPos;
	while (true)
	{
		int Check = m_BrokenTile->GetTileImageIndex(CheckSize);
		if (-1 == Check)
		{
			break;
		}

		m_BrokenAllTile.push_back(std::vector<FLOAT4>(YSize));
		std::vector<FLOAT4>& NewLine = m_BrokenAllTile.back();
		for (size_t i = 0; i < YSize; i++)
		{
			NewLine[i].x = CheckSize.x;
			NewLine[i].y = CheckSize.y + i;
		}
		CheckSize.x -= 1;
	}
}

void ShovelKnight::BrokenTileStay()
{
	if (0 != m_BrokenAllTile.size())
	{
		std::vector<FLOAT4>& CurDestroyTile = m_BrokenAllTile.front();
		for (size_t i = 0; i < CurDestroyTile.size(); i++)
		{
			// ����Ÿ�ϸ� ����
			GlobalValue::MainTileMap->m_TileMap->DelTileIndex(CurDestroyTile[i]);

			// �μ����� Ÿ�ϸ� ����
			m_BrokenTile->DelTileIndex(CurDestroyTile[i]);

			FLOAT4 CreateActorPos = GlobalValue::MainTileMap->m_TileMap->GetCurIndexToPos(CurDestroyTile[i]);

			// �ش� Ÿ���� �����ǰ� ��������Ʈ�� �����ȴ�
			// �� Ÿ���� ���������̿��Ͽ� ����Ʈ ���͸� �����Ѵ�.
			BrokenTileEffect* TileEffect = GetScene()->CreateActor<BrokenTileEffect>();
			TileEffect->SetPosition(CreateActorPos);
		}

		m_BrokenAllTile.pop_front();
	}
}

int ShovelKnight::GetBrokenTileImageIndex(const FLOAT4& _CheckPos)
{
	return m_BrokenTile->GetTileImageIndex({ _CheckPos.ix(), _CheckPos.iy() });
}

void ShovelKnight::SetPlayerPosIndex()
{
	// Ÿ���̺��� ����
	m_BrokenEventer.Update();

	// �÷��̾� ��ġ ��� ����
	m_PlayerPosIndex = { GetPosition().x / 32.f, GetPosition().y / 32.f };

	// ���ý��۽� On ����, ��������� Off ����
	if (true == m_AttackCol->IsOn())
	{
		m_PlayerAttackPosIndex = { (GetPosition().x - m_AttackCol->GetPivotPos().x) / 32.f, (GetPosition().y - m_AttackCol->GetPivotPos().y) / 32.f };
		int CheckImageIndex = m_BrokenTile->GetTileImageIndex(m_PlayerAttackPosIndex);
		if (0 == CheckImageIndex) // �����ʹ������� Break
		{
			RightFind(m_PlayerAttackPosIndex);
		}
		else if (1 == CheckImageIndex) // ���ʹ������� Break
		{
			LeftFind(m_PlayerAttackPosIndex);
		}
	}
}

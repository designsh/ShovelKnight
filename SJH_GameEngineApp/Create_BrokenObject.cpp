#include "Enchantress_FinalBoss.h"
#include <SGameEngineActor.h>

void Enchantress_FinalBoss::BrokenObjectSetting()
{
	// Ÿ�ϸ� �ε�
	LoadBrokenTile();

	// �ڷᱸ�� ũ�⼳��
	DataStructSetting();

	// ���� ���� �� �ڷᱸ�� ����
	CreateBrokenObject();
}

void Enchantress_FinalBoss::DataStructSetting()
{
	for (int y = 0; y < m_BrokenTile->GetTileMaxIndex().iy(); y++)
	{
		int ImageIndex = m_BrokenTile->GetTileImageIndex(FLOAT4(0, y));
		if (-1 != ImageIndex)
		{
			// -1�� �ƴϸ� Ÿ���� �����Ѵٴ� ������ �ش� �ε����� ���ϰ� Break;
			m_iYSearchIndex = y;
			break;
		}
	}

	for (int x = 0; x < m_BrokenTile->GetTileMaxIndex().ix(); x++)
	{
		int ImageIndex = m_BrokenTile->GetTileImageIndex(FLOAT4(x, m_iYSearchIndex));
		if (-1 != ImageIndex)
		{
			m_iDataStructXSize++;
		}
	}

	// ���� ũ�� ����
	// x�� ũ�⸸ ���Ѵ�.
	// ���� y���� Push_back�ؼ� �����͸� �ִ´�.
	m_BrokenObject.resize(m_iDataStructXSize);
}

void Enchantress_FinalBoss::LoadBrokenTile()
{
	// Broken TileMap File ���
	m_BrokenTileFilePath.MoveParentsFolder(L"ShovelKnight");
	m_BrokenTileFilePath.MoveChildFolder(L"Resource");
	m_BrokenTileFilePath.MoveChildFolder(L"Image");
	m_BrokenTileFilePath.MoveChildFolder(L"Enchantress");
	m_BrokenTileFilePath.MoveChildFolder(L"TileSet");

	// ���Ͽ� ����� Ÿ������ ��������
	m_BrokenTile = CreateRenderer<SGameEngineRendererTile>((int)GlobalValue::RenderGroup::BrokenTile);
	m_BrokenTile->TileMapStart(L"Enchantress_TotalBrokenTile.bmp", { 32.f, 32.f }, { 32.f, 32.f }, 40, 90);
	SGameEngineString LoadPath = m_BrokenTileFilePath.GetPath();
	LoadPath += L"EnchantressBrokenTile.dat";
	m_BrokenTile->LoadTile(LoadPath);

	// �⺻������ Off ����
	m_BrokenTile->Off();
}

void Enchantress_FinalBoss::CreateBrokenObject()
{
	// �ε��� Ÿ�� �������� �̹����ε����� -1�� �ƴ� ���� �浹ü�� ������Ʈ�� �����Ѵ�.
	for (int x = 0; x < m_BrokenTile->GetTileMaxIndex().ix(); x++)
	{
		int IndexY = 0;
		for (int y = 0; y < m_BrokenTile->GetTileMaxIndex().iy(); y++)
		{
			int ImageIndex = m_BrokenTile->GetTileImageIndex(FLOAT4(x, y));
			if (-1 != ImageIndex)
			{
				// �ش� �ε����� ��ġ�� �����Ѵ�.
				FLOAT4 CurTilePos = m_BrokenTile->GetCurIndexToPos(FLOAT4(x, y));

				// �ش� ���͸� �����ϰ� �ڷᱸ���� �����Ѵ�.
				EnchantressBrokenTile* NewBrokenObject = GetScene()->CreateActor<EnchantressBrokenTile>();
				NewBrokenObject->SetPosition(CurTilePos);
				NewBrokenObject->SetMyIndex(x, IndexY);

				// �ش� ���͵��� �����ϴ� �ڷᱸ���� �����Ѵ�.
				// [x][y] ���·� ���� ������� �������[x][4] �浹�ϸ� x��° ������Ʈ�� �������̰� �츮�� �ɵ�
				m_BrokenObject[x].push_back(NewBrokenObject);

				IndexY++;
			}
		}
	}
}


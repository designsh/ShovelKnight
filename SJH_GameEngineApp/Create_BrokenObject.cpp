#include "Enchantress_FinalBoss.h"
#include <SGameEngineActor.h>

void Enchantress_FinalBoss::BrokenObjectSetting()
{
	// 타일맵 로드
	LoadBrokenTile();

	// 자료구조 크기설정
	DataStructSetting();

	// 액터 생성 및 자료구조 저장
	CreateBrokenObject();
}

void Enchantress_FinalBoss::DataStructSetting()
{
	for (int y = 0; y < m_BrokenTile->GetTileMaxIndex().iy(); y++)
	{
		int ImageIndex = m_BrokenTile->GetTileImageIndex(FLOAT4(0, y));
		if (-1 != ImageIndex)
		{
			// -1이 아니면 타일이 존재한다는 것으로 해당 인덱스만 구하고 Break;
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

	// 벡터 크기 정함
	// x의 크기만 구한다.
	// 추후 y값은 Push_back해서 데이터를 넣는다.
	m_BrokenObject.resize(m_iDataStructXSize);
}

void Enchantress_FinalBoss::LoadBrokenTile()
{
	// Broken TileMap File 경로
	m_BrokenTileFilePath.MoveParentsFolder(L"ShovelKnight");
	m_BrokenTileFilePath.MoveChildFolder(L"Resource");
	m_BrokenTileFilePath.MoveChildFolder(L"Image");
	m_BrokenTileFilePath.MoveChildFolder(L"Enchantress");
	m_BrokenTileFilePath.MoveChildFolder(L"TileSet");

	// 파일에 저장된 타일정보 가져오기
	m_BrokenTile = CreateRenderer<SGameEngineRendererTile>((int)GlobalValue::RenderGroup::BrokenTile);
	m_BrokenTile->TileMapStart(L"Enchantress_TotalBrokenTile.bmp", { 32.f, 32.f }, { 32.f, 32.f }, 40, 90);
	SGameEngineString LoadPath = m_BrokenTileFilePath.GetPath();
	LoadPath += L"EnchantressBrokenTile.dat";
	m_BrokenTile->LoadTile(LoadPath);

	// 기본적으로 Off 상태
	m_BrokenTile->Off();
}

void Enchantress_FinalBoss::CreateBrokenObject()
{
	// 로드한 타일 정보에서 이미지인덱스가 -1이 아닌 곳에 충돌체와 오브젝트를 생성한다.
	for (int x = 0; x < m_BrokenTile->GetTileMaxIndex().ix(); x++)
	{
		int IndexY = 0;
		for (int y = 0; y < m_BrokenTile->GetTileMaxIndex().iy(); y++)
		{
			int ImageIndex = m_BrokenTile->GetTileImageIndex(FLOAT4(x, y));
			if (-1 != ImageIndex)
			{
				// 해당 인덱스를 위치로 변경한다.
				FLOAT4 CurTilePos = m_BrokenTile->GetCurIndexToPos(FLOAT4(x, y));

				// 해당 액터를 생성하고 자료구조에 저장한다.
				EnchantressBrokenTile* NewBrokenObject = GetScene()->CreateActor<EnchantressBrokenTile>();
				NewBrokenObject->SetPosition(CurTilePos);
				NewBrokenObject->SetMyIndex(x, IndexY);

				// 해당 액터들을 관리하는 자료구조에 저장한다.
				// [x][y] 형태로 저장 재생성시 예를들어[x][4] 충돌하면 x번째 오브젝트를 전부죽이고 살리면 될듯
				m_BrokenObject[x].push_back(NewBrokenObject);

				IndexY++;
			}
		}
	}
}


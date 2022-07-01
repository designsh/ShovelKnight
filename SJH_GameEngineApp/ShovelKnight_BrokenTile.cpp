#include "ShovelKnight.h"
#include <SGameEngineResMgr.h>
#include <SGameEngineCollision.h>

#include "PlainsTileMap.h"
#include "BrokenTileEffect.h"

// BrokenTile 정보를 파일로부터 읽어온다.
void ShovelKnight::LoadBrokenTileMap()
{
	// Broken TileMap File 경로
	m_BrokenTileFilePath.MoveParentsFolder(L"ShovelKnight");
	m_BrokenTileFilePath.MoveChildFolder(L"Resource");
	m_BrokenTileFilePath.MoveChildFolder(L"Image");
	m_BrokenTileFilePath.MoveChildFolder(L"Stage");
	m_BrokenTileFilePath.MoveChildFolder(L"TileSet");

	// 파일에 저장된 타일정보 가져오기
	m_BrokenTile = CreateRenderer<SGameEngineRendererTile>((int)GlobalValue::RenderGroup::BrokenTile);
	m_BrokenTile->TileMapStart(L"Plains_Broken_Tile.bmp", { 32.f, 32.f }, { 32.f, 32.f }, 720, 135);
	SGameEngineString LoadPath = m_BrokenTileFilePath.GetPath();
	LoadPath += L"Stage1BrokenTile.dat";
	m_BrokenTile->LoadTile(LoadPath);

	// 기본적으로 Off 상태
	m_BrokenTile->Off();
}

void ShovelKnight::RightFind(FLOAT4 _StartIndex)
{
	// 해당 리스트를 먼저 비운다.
	m_BrokenAllTile.clear();

	// 시작타일인덱스의 왼쪽에도 타일이 존재하는지 찾는다.
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

	// 근접타일을 모두 찾기위해 위로 이동
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

	// 근접타일을 모두 찾기위해 아래로 이동
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

	// Y의 크기를 구한다. 
	int YSize = CheckSize.iy() - CurPos.iy();

	// 모든 삭제할 타일을 찾았으므로
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
	// 해당 리스트를 먼저 비운다.
	m_BrokenAllTile.clear();

	// 시작타일인덱스의 오른쪽에도 타일이 존재하는지 찾는다.
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

	// 근접타일을 모두 찾기위해 위로 이동
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

	// 근접타일을 모두 찾기위해 아래로 이동
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

	// Y의 크기를 구한다. 
	int YSize = CheckSize.iy() - CurPos.iy();

	// 모든 삭제할 타일을 찾았으므로
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
			// 메인타일맵 삭제
			GlobalValue::MainTileMap->m_TileMap->DelTileIndex(CurDestroyTile[i]);

			// 부서지는 타일맵 삭제
			m_BrokenTile->DelTileIndex(CurDestroyTile[i]);

			FLOAT4 CreateActorPos = GlobalValue::MainTileMap->m_TileMap->GetCurIndexToPos(CurDestroyTile[i]);

			// 해당 타일이 삭제되고 삭제이펙트가 생성된다
			// 각 타일의 포지션을이용하여 이펙트 액터를 생성한다.
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
	// 타임이벤터 갱신
	m_BrokenEventer.Update();

	// 플레이어 위치 계속 갱신
	m_PlayerPosIndex = { GetPosition().x / 32.f, GetPosition().y / 32.f };

	// 어택시작시 On 상태, 어택종료시 Off 상태
	if (true == m_AttackCol->IsOn())
	{
		m_PlayerAttackPosIndex = { (GetPosition().x - m_AttackCol->GetPivotPos().x) / 32.f, (GetPosition().y - m_AttackCol->GetPivotPos().y) / 32.f };
		int CheckImageIndex = m_BrokenTile->GetTileImageIndex(m_PlayerAttackPosIndex);
		if (0 == CheckImageIndex) // 오른쪽방향으로 Break
		{
			RightFind(m_PlayerAttackPosIndex);
		}
		else if (1 == CheckImageIndex) // 왼쪽방향으로 Break
		{
			LeftFind(m_PlayerAttackPosIndex);
		}
	}
}

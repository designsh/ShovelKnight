#include "PlayerMaker.h"
#include "GlobalValue.h"

void PlayerMaker::CreateMoveTileMap()
{
	// Broken TileMap File 경로
	m_MoveTileFilePath.MoveParentsFolder(L"ShovelKnight");
	m_MoveTileFilePath.MoveChildFolder(L"Resource");
	m_MoveTileFilePath.MoveChildFolder(L"Image");
	m_MoveTileFilePath.MoveChildFolder(L"LevelMap");
	m_MoveTileFilePath.MoveChildFolder(L"TileSet");

	// 파일에 저장된 타일정보 가져오기
	m_MoveTile = CreateRenderer<SGameEngineRendererTile>((int)GlobalValue::RenderGroup::MoveTile);
	m_MoveTile->TileMapStart(L"LevelMapMoveTile.bmp", { 32.f, 32.f }, { 32.f, 32.f }, 40, 23);
	SGameEngineString LoadPath = m_MoveTileFilePath.GetPath();
	LoadPath += L"LevelMapMoveTile.dat";
	m_MoveTile->LoadTile(LoadPath);

	// 기본적으로 Off 상태
	m_MoveTile->Off();
}

int PlayerMaker::GetBrokenTileImageIndex(const FLOAT4& _CheckPos)
{
	// 원하는 인덱스의 이미지인덱스 정보 가져오기
	return m_MoveTile->GetTileImageIndex({ _CheckPos.ix(), _CheckPos.iy() });
}

void PlayerMaker::SetPlayerPosIndex()
{
	// 플레이어 위치 계속 갱신
	m_PlayerPosIndex = { GetPosition().x / 32.f, GetPosition().y / 32.f };
}


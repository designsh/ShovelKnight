#include "LevelMap.h"
#include <SGameEngineResMgr.h>

#include "LevelMapBackDrop.h"
#include "LevelMapCollisionMap.h"
#include "LevelMapTileMap.h"

void LevelMap::LevelMapCreateBackDrop()
{
	//---------------------------------------------- BackDrop ----------------------------------------------//
	m_BackDrop = CreateActor<LevelMapBackDrop>();

	//---------------------------------------------- Pixel Col Map ----------------------------------------------//
	m_CollisionMap = CreateActor<LevelMapCollisionMap>();

	//---------------------------------------------- Tile Map ----------------------------------------------//
	// 타일셋 이미지 컷

	// 최초시작시 타일맵 경로를 찾아간다.
	m_TileFilePath.MoveParentsFolder(L"ShovelKnight");
	m_TileFilePath.MoveChildFolder(L"Resource");
	m_TileFilePath.MoveChildFolder(L"Image");
	m_TileFilePath.MoveChildFolder(L"LevelMap");
	m_TileFilePath.MoveChildFolder(L"TileSet");

	// 타일맵 관련
	// 전체 맵(Default : On)
	m_TileMap = CreateActor<LevelMapTileMap>();
	m_TileMap->LoadTileBlockImage(L"WolrdMapTile.bmp");
	SGameEngineString LoadPath = m_TileFilePath.GetPath();
	LoadPath += L"LevelMapTileMap.dat";
	m_TileMap->m_TileMap->LoadTile(LoadPath);
}

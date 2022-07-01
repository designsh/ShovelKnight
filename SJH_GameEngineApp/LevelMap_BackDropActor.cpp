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
	// Ÿ�ϼ� �̹��� ��

	// ���ʽ��۽� Ÿ�ϸ� ��θ� ã�ư���.
	m_TileFilePath.MoveParentsFolder(L"ShovelKnight");
	m_TileFilePath.MoveChildFolder(L"Resource");
	m_TileFilePath.MoveChildFolder(L"Image");
	m_TileFilePath.MoveChildFolder(L"LevelMap");
	m_TileFilePath.MoveChildFolder(L"TileSet");

	// Ÿ�ϸ� ����
	// ��ü ��(Default : On)
	m_TileMap = CreateActor<LevelMapTileMap>();
	m_TileMap->LoadTileBlockImage(L"WolrdMapTile.bmp");
	SGameEngineString LoadPath = m_TileFilePath.GetPath();
	LoadPath += L"LevelMapTileMap.dat";
	m_TileMap->m_TileMap->LoadTile(LoadPath);
}

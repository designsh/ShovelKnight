#include "Enchantress.h"
#include <SGameEngineResMgr.h>

#include "Enchantress_ShovelKnight.h"
#include "EnchantressBackDrop.h"
#include "EnchantressCollisionMap.h"
#include "EnchantressTileMap.h"
#include "Enchantress_StateBar.h"
#include "FadeInOutActor.h"

void Enchantress::EnchantressCreateBackDrop()
{
	//m_BackDrop(nullptr), m_ColMap(nullptr), m_TileMap(nullptr)

	//---------------------------------------------- BackDrop ----------------------------------------------//
	m_BackDrop = CreateActor<EnchantressBackDrop>();

	//---------------------------------------------- Pixel Col Map ----------------------------------------------//
	m_ColMap = CreateActor<EnchantressCollisionMap>();

	//---------------------------------------------- Tile Map ----------------------------------------------//
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_TotalTileSet.bmp")->SetTransColor(RGB(255, 0, 255));
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_TotalTileSet.bmp")->ImageCut(25, 5);

	// 최초시작시 타일맵 경로를 찾아간다.
	m_TileFilePath.MoveParentsFolder(L"ShovelKnight");
	m_TileFilePath.MoveChildFolder(L"Resource");
	m_TileFilePath.MoveChildFolder(L"Image");
	m_TileFilePath.MoveChildFolder(L"Enchantress");
	m_TileFilePath.MoveChildFolder(L"TileSet");

	// 타일맵 관련
	// 전체 맵(Default : On)
	m_TileMap = CreateActor<EnchantressTileMap>();
	m_TileMap->LoadTileBlockImage(L"Enchantress_TotalTileSet.bmp");
	SGameEngineString LoadPath = m_TileFilePath.GetPath();
	LoadPath += L"EnchantressTile.dat";
	m_TileMap->m_TileMap->LoadTile(LoadPath);

	// 타일의 기준점(카메라위치정보)과 랜더링 인덱스크기를 정한다.
	// 인덱스 -> 윈도우너비      (1280.f) / 타일크기(32.f)
	//                 윈도우높이2배(1440.f) / 타일크기(32.f)
	//                 만약 Max를 넘어가면 Max값으로 초기화한다.
	m_TileMap->m_TileMap->SetCullActor(m_Player, { 40.f, 45.f });

	//---------------------------------------------- StateTopBar ----------------------------------------------//
	m_StateBar = CreateActor<Enchantress_StateBar>();

	//--------------------------------------- SceneChange FadeInOut -------------------------------------//
	m_FadeInOut = CreateActor<FadeInOutActor>();
	m_FadeInOut->SetFadeType(FADE_TYPE::FADEIN);
}

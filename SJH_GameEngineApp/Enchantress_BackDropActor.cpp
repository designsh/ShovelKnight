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

	// ���ʽ��۽� Ÿ�ϸ� ��θ� ã�ư���.
	m_TileFilePath.MoveParentsFolder(L"ShovelKnight");
	m_TileFilePath.MoveChildFolder(L"Resource");
	m_TileFilePath.MoveChildFolder(L"Image");
	m_TileFilePath.MoveChildFolder(L"Enchantress");
	m_TileFilePath.MoveChildFolder(L"TileSet");

	// Ÿ�ϸ� ����
	// ��ü ��(Default : On)
	m_TileMap = CreateActor<EnchantressTileMap>();
	m_TileMap->LoadTileBlockImage(L"Enchantress_TotalTileSet.bmp");
	SGameEngineString LoadPath = m_TileFilePath.GetPath();
	LoadPath += L"EnchantressTile.dat";
	m_TileMap->m_TileMap->LoadTile(LoadPath);

	// Ÿ���� ������(ī�޶���ġ����)�� ������ �ε���ũ�⸦ ���Ѵ�.
	// �ε��� -> ������ʺ�      (1280.f) / Ÿ��ũ��(32.f)
	//                 ���������2��(1440.f) / Ÿ��ũ��(32.f)
	//                 ���� Max�� �Ѿ�� Max������ �ʱ�ȭ�Ѵ�.
	m_TileMap->m_TileMap->SetCullActor(m_Player, { 40.f, 45.f });

	//---------------------------------------------- StateTopBar ----------------------------------------------//
	m_StateBar = CreateActor<Enchantress_StateBar>();

	//--------------------------------------- SceneChange FadeInOut -------------------------------------//
	m_FadeInOut = CreateActor<FadeInOutActor>();
	m_FadeInOut->SetFadeType(FADE_TYPE::FADEIN);
}

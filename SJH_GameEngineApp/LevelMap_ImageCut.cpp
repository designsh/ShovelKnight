#include "LevelMap.h"
#include <SGameEngineResMgr.h>

void LevelMap::LevelMapImageCut()
{
	// ���ҽ� ���� ��ü ������
	m_ResPath.MoveParentsFolder(L"ShovelKnight");
	m_ResPath.MoveChildFolder(L"Resource");
	m_ResPath.MoveChildFolder(L"Image");
	m_ResPath.MoveChildFolder(L"LevelMap");

	// ���� ����� Ȯ���� .bmp�� �̹����� ���δ� �����ͼ� Vector�� ����
	std::vector<SGameEngineFile> AllImageFile = m_ResPath.FindDirectoryAllFileToVector(L"*.bmp");
	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		SGameEngineResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	//---------------------------------------------------------- Tile Set -------------------------------------------------------------//
	SGameEngineResMgr::Inst().FindImage(L"WolrdMapTile.bmp")->SetTransColor(RGB(255, 0, 255));
	SGameEngineResMgr::Inst().FindImage(L"WolrdMapTile.bmp")->ImageCut(25, 5);
	SGameEngineResMgr::Inst().FindImage(L"LevelMapMoveTile.bmp")->SetTransColor(RGB(0, 0, 0));
	SGameEngineResMgr::Inst().FindImage(L"LevelMapMoveTile.bmp")->ImageCut(25, 5);


	//------------------------------------------------------------- UI ----------------------------------------------------------------//
	SGameEngineResMgr::Inst().FindImage(L"ClearEffect.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"ClearEffect.bmp")->ImageCut(5, 1);


	//---------------------------------------------------------- Object -------------------------------------------------------------//
	SGameEngineResMgr::Inst().FindImage(L"Plains_Icon.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Plains_Icon.bmp")->ImageCut(1, 1);
	SGameEngineResMgr::Inst().FindImage(L"None_Icon.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"None_Icon.bmp")->ImageCut(1, 1);
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_Icon.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_Icon.bmp")->ImageCut(1, 1);
	SGameEngineResMgr::Inst().FindImage(L"LevelMap_Cloud.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"LevelMap_Cloud.bmp")->ImageCut(1, 1);

	//---------------------------------------------------------- Player -------------------------------------------------------------//
	SGameEngineResMgr::Inst().FindImage(L"LevelMap_Player.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"LevelMap_Player.bmp")->ImageCut(2, 1);


}

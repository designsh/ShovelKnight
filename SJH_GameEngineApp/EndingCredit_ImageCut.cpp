#include "EndingCredit.h"
#include <SGameEngineResMgr.h>
#include <SGameEngineFile.h>

void EndingCredit::EndingCreditImageCut()
{
	// ���ҽ� ���� ��ü ������
	m_ResPath.MoveParentsFolder(L"ShovelKnight");
	m_ResPath.MoveChildFolder(L"Resource");
	m_ResPath.MoveChildFolder(L"Image");
	m_ResPath.MoveChildFolder(L"Ending");

	// ���� ����� Ȯ���� .bmp�� �̹����� ���δ� �����ͼ� Vector�� ����
	std::vector<SGameEngineFile> AllImageFile = m_ResPath.FindDirectoryAllFileToVector(L"*.bmp");
	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		SGameEngineResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	// ---------------------------------------------------- CampFire BackDrop ------------------------------------------------------------//
	SGameEngineResMgr::Inst().FindImage(L"Ending_Tree1.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Ending_Tree1.bmp")->ImageCut(1, 1);
	SGameEngineResMgr::Inst().FindImage(L"Ending_Tree2.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Ending_Tree2.bmp")->ImageCut(1, 1);

	// ---------------------------------------------------- Ending Text Object -------------------------------------------------------------//
	SGameEngineResMgr::Inst().FindImage(L"TheEnd_TextImage.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"TheEnd_TextImage.bmp")->ImageCut(10, 10);

	// ---------------------------------------------------------- CampFire -------------------------------------------------------------------//
	SGameEngineResMgr::Inst().FindImage(L"CampFire.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"CampFire.bmp")->ImageCut(3, 1);

	// --------------------------------------------------- Ending Player Object ------------------------------------------------------------//
	SGameEngineResMgr::Inst().FindImage(L"Ending_ShovelKnight.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Ending_ShovelKnight.bmp")->ImageCut(2, 1);

}

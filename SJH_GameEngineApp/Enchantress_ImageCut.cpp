#include "Enchantress.h"
#include <SGameEngineResMgr.h>

void Enchantress::EnchantressImageCut()
{
	// ���ҽ� ���� ��ü ������
	m_ResPath.MoveParentsFolder(L"ShovelKnight");
	m_ResPath.MoveChildFolder(L"Resource");
	m_ResPath.MoveChildFolder(L"Image");
	m_ResPath.MoveChildFolder(L"Enchantress");

	// ���� ����� Ȯ���� .bmp�� �̹����� ���δ� �����ͼ� Vector�� ����
	std::vector<SGameEngineFile> AllImageFile = m_ResPath.FindDirectoryAllFileToVector(L"*.bmp");
	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		SGameEngineResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	// ----------------------------------------------------------- UI -------------------------------------------------------------------------//
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_NumberText.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_NumberText.bmp")->ImageCut(10, 1);
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_NumberTextColor.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_NumberTextColor.bmp")->ImageCut(10, 1);
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_PlayerHP.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_PlayerHP.bmp")->ImageCut(3, 1);
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_FinalBossHP.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_FinalBossHP.bmp")->ImageCut(3, 1);

	// ------------------------------------------------------ Broken Object -------------------------------------------------------------------//
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_TotalBrokenTile.bmp")->SetTransColor(RGB(255, 255, 255));
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_TotalBrokenTile.bmp")->ImageCut(25, 5);
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_BlockSmall.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_BlockSmall.bmp")->ImageCut(4, 1);

	// ---------------------------------------------------------- Monster ------------------------------------------------------------------------//
	// Final Boss ��ü(�⺻)
	SGameEngineResMgr::Inst().FindImage(L"Left_The_Enchantress.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Left_The_Enchantress.bmp")->ImageCut(4, 21);
	SGameEngineResMgr::Inst().FindImage(L"Right_The_Enchantress.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Right_The_Enchantress.bmp")->ImageCut(4, 21);

	// Final Boss ��ü(�ǰ�)
	SGameEngineResMgr::Inst().FindImage(L"Left_The_Enchantress_BeShot.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Left_The_Enchantress_BeShot.bmp")->ImageCut(4, 21);
	SGameEngineResMgr::Inst().FindImage(L"Right_The_Enchantress_BeShot.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Right_The_Enchantress_BeShot.bmp")->ImageCut(4, 21);

	// Final Boss ���ݽ�ų
	SGameEngineResMgr::Inst().FindImage(L"FinalStage_Boss_AttackSkill.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"FinalStage_Boss_AttackSkill.bmp")->ImageCut(4, 8);

	// Final Boss Ÿ�ϸ��� ��ų
	SGameEngineResMgr::Inst().FindImage(L"Boss_RegenSkill.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Boss_RegenSkill.bmp")->ImageCut(6, 3);

	// ���б��
	SGameEngineResMgr::Inst().FindImage(L"Shild_Knight.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Shild_Knight.bmp")->ImageCut(3, 1);

	// ----------------------------------------------------------- Player -------------------------------------------------------------------------//
	SGameEngineResMgr::Inst().FindImage(L"Left_Enchantress_Player.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Left_Enchantress_Player.bmp")->ImageCut(5, 12);
	SGameEngineResMgr::Inst().FindImage(L"Right_Enchantress_Player.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Right_Enchantress_Player.bmp")->ImageCut(5, 12);

	// -------------------------------------------------------- FadeInOut -----------------------------------------------------------------------//
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_FadeInOut.bmp")->SetTransColor(RGB(255, 0, 255));
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_FadeInOut.bmp")->ImageCut(1, 1);

}

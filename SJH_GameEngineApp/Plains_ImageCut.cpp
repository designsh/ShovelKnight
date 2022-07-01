#include "Plains.h"
#include <SGameEngineResMgr.h>

void Plains::PlainsImageCut()
{
	// ���ҽ� ���� ��ü ������
	m_ResPath.MoveParentsFolder(L"ShovelKnight");
	m_ResPath.MoveChildFolder(L"Resource");
	m_ResPath.MoveChildFolder(L"Image");
	m_ResPath.MoveChildFolder(L"Stage");

	// ���� ����� Ȯ���� .bmp�� �̹����� ���δ� �����ͼ� Vector�� ����
	std::vector<SGameEngineFile> AllImageFile = m_ResPath.FindDirectoryAllFileToVector(L"*.bmp");
	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		SGameEngineResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	// �μ����� Ÿ�ϰ���
	SGameEngineResMgr::Inst().FindImage(L"Plains_Broken_Tile.bmp")->SetTransColor(RGB(255, 0, 255));
	SGameEngineResMgr::Inst().FindImage(L"Plains_Broken_Tile.bmp")->ImageCut(25, 5);
	SGameEngineResMgr::Inst().FindImage(L"BrokenTile_Poof.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"BrokenTile_Poof.bmp")->ImageCut(7, 1);

	// �����ũ�� ����
	SGameEngineResMgr::Inst().FindImage(L"skMapMarker.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"skMapMarker.bmp")->ImageCut(2, 1);
	SGameEngineResMgr::Inst().FindImage(L"DeathScreen_SavePoint.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"DeathScreen_SavePoint.bmp")->ImageCut(4, 1);

	//------------------------------------------------------------ UI -------------------------------------------------------------//
	// ��� ���¹�
	SGameEngineResMgr::Inst().FindImage(L"NumberText.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"NumberText.bmp")->ImageCut(10, 1);
	SGameEngineResMgr::Inst().FindImage(L"NumberTextColor.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"NumberTextColor.bmp")->ImageCut(10, 1);
	SGameEngineResMgr::Inst().FindImage(L"PlayerHP.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"PlayerHP.bmp")->ImageCut(3, 1);
	SGameEngineResMgr::Inst().FindImage(L"FinalBossHP.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"FinalBossHP.bmp")->ImageCut(3, 1);

	//---------------------------------------------------------- Player ----------------------------------------------------------//
	SGameEngineResMgr::Inst().FindImage(L"Player Left Move.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Player Left Move.bmp")->ImageCut(5, 12);
	SGameEngineResMgr::Inst().FindImage(L"Player Right Move.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Player Right Move.bmp")->ImageCut(5, 12);

	//--------------------------------------------------------- Object -----------------------------------------------------------//
	// ���� ����
	SGameEngineResMgr::Inst().FindImage(L"Stone_Object.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Stone_Object.bmp")->ImageCut(7, 1);
	SGameEngineResMgr::Inst().FindImage(L"Fragments_Type1.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Fragments_Type1.bmp")->ImageCut(1, 1);
	SGameEngineResMgr::Inst().FindImage(L"Fragments_Type2.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Fragments_Type2.bmp")->ImageCut(1, 1);

	// �����
	SGameEngineResMgr::Inst().FindImage(L"dirtBlock.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"dirtBlock.bmp")->ImageCut(4, 1);

	// �����(����������)
	SGameEngineResMgr::Inst().FindImage(L"dirtBlock_small.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"dirtBlock_small.bmp")->ImageCut(4, 1);

	// ���� ��ǰ
	SGameEngineResMgr::Inst().FindImage(L"digPileBubbles.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"digPileBubbles.bmp")->ImageCut(4, 2);

	// �����̴� ������Ʈ(Ÿ��)
	SGameEngineResMgr::Inst().FindImage(L"Moving_Platform.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Moving_Platform.bmp")->ImageCut(1, 1);

	// üũ����Ʈ(SavePoint)
	SGameEngineResMgr::Inst().FindImage(L"SavePoint_TotalState.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"SavePoint_TotalState.bmp")->ImageCut(5, 3);

	// ��� ���
	SGameEngineResMgr::Inst().FindImage(L"Gold.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Gold.bmp")->ImageCut(6, 1);

	// ��� ������Ʈ
	SGameEngineResMgr::Inst().FindImage(L"GoldObject.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"GoldObject.bmp")->ImageCut(6, 1);

	// Platter(ü�¹ڽ�)
	SGameEngineResMgr::Inst().FindImage(L"platter1.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"platter1.bmp")->ImageCut(1, 1);
	SGameEngineResMgr::Inst().FindImage(L"platter2.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"platter2.bmp")->ImageCut(1, 1);
	SGameEngineResMgr::Inst().FindImage(L"platter3.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"platter3.bmp")->ImageCut(1, 1);

	// Chicken(ü��ȸ��)
	SGameEngineResMgr::Inst().FindImage(L"chicken.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"chicken.bmp")->ImageCut(1, 1);

	//-------------------------------------------------------- Monster ---------------------------------------------------------//
	// �����̹���(����� ���)
	SGameEngineResMgr::Inst().FindImage(L"poofs.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"poofs.bmp")->ImageCut(5, 1);

	// Beeto
	SGameEngineResMgr::Inst().FindImage(L"Beeto_Left.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Beeto_Left.bmp")->ImageCut(6, 1);
	SGameEngineResMgr::Inst().FindImage(L"Beeto_Right.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Beeto_Right.bmp")->ImageCut(6, 1);

	// Skull Soldier
	SGameEngineResMgr::Inst().FindImage(L"Skull_soldier_Left.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Skull_soldier_Left.bmp")->ImageCut(6, 2);
	SGameEngineResMgr::Inst().FindImage(L"Skull_soldier_Right.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Skull_soldier_Right.bmp")->ImageCut(6, 2);
	SGameEngineResMgr::Inst().FindImage(L"BeShot_Skull_soldier_Left.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"BeShot_Skull_soldier_Left.bmp")->ImageCut(6, 2);
	SGameEngineResMgr::Inst().FindImage(L"BeShot_Skull_soldier_Right.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"BeShot_Skull_soldier_Right.bmp")->ImageCut(6, 2);

	// Slime
	SGameEngineResMgr::Inst().FindImage(L"Slime.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Slime.bmp")->ImageCut(4, 1);
	SGameEngineResMgr::Inst().FindImage(L"BeShotSlime.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"BeShotSlime.bmp")->ImageCut(4, 1);

	// Dragon
	SGameEngineResMgr::Inst().FindImage(L"Dragon_Left.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Dragon_Left.bmp")->ImageCut(5, 3);
	SGameEngineResMgr::Inst().FindImage(L"Dragon_Right.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Dragon_Right.bmp")->ImageCut(5, 3);
	SGameEngineResMgr::Inst().FindImage(L"BeShot_Dragon_Left.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"BeShot_Dragon_Left.bmp")->ImageCut(5, 3);
	SGameEngineResMgr::Inst().FindImage(L"BeShot_Dragon_Right.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"BeShot_Dragon_Right.bmp")->ImageCut(5, 3);

	// Dozedrake(Middle Boss)
	SGameEngineResMgr::Inst().FindImage(L"explosionSmall.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"explosionSmall.bmp")->ImageCut(5, 1);
	SGameEngineResMgr::Inst().FindImage(L"Dozedrake_State.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Dozedrake_State.bmp")->ImageCut(6, 5);
	SGameEngineResMgr::Inst().FindImage(L"Dozedrake_BeShot.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Dozedrake_BeShot.bmp")->ImageCut(6, 5);
	SGameEngineResMgr::Inst().FindImage(L"Dozedrake_Attack.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Dozedrake_Attack.bmp")->ImageCut(4, 2);

	// BlackKnight(Final Boss)
	SGameEngineResMgr::Inst().FindImage(L"Left_BeShotBlackKnight.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Left_BeShotBlackKnight.bmp")->ImageCut(4, 9);
	SGameEngineResMgr::Inst().FindImage(L"Left_BlackKnight_Skill.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Left_BlackKnight_Skill.bmp")->ImageCut(4, 1);
	SGameEngineResMgr::Inst().FindImage(L"Left_BlackKnight.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Left_BlackKnight.bmp")->ImageCut(4, 9);
	SGameEngineResMgr::Inst().FindImage(L"Right_BeShotBlackKnight.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Right_BeShotBlackKnight.bmp")->ImageCut(4, 9);
	SGameEngineResMgr::Inst().FindImage(L"Right_BlackKnight_Skill.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Right_BlackKnight_Skill.bmp")->ImageCut(4, 1);
	SGameEngineResMgr::Inst().FindImage(L"Right_BlackKnight.bmp")->SetTransColor(RGB(0, 255, 0));
	SGameEngineResMgr::Inst().FindImage(L"Right_BlackKnight.bmp")->ImageCut(4, 9);
}

#include "Plains.h"
#include "PlainsTileMap.h"           // �������� Ÿ�ϸ�
#include "ShovelKnight.h"            // �������(�÷��̾�)
#include "PlainsBackDrop.h"         // �������� ���
#include "PlainsCollisionMap.h"   // �������� �浹��

#include "MovingPlatform.h"       // �����̴� �浹ü
#include "StateTopBar.h"              // �÷��̾� ���¹�(��ܹ�)
#include "DeathScreen.h"             // �÷��̾� �����ũ��

#include <SGameEngineResMgr.h>

void Plains::PlainsCreateBackDrop()
{
	//---------------------------------------------- BackDrop ----------------------------------------------//
	m_BackDrop = CreateActor<PlainsBackDrop>();

	//---------------------------------------------- Pixel Col Map ----------------------------------------------//
	m_CollisionMap = CreateActor<PlainsCollisionMap>();

	//---------------------------------------------- Tile Map ----------------------------------------------//
	SGameEngineResMgr::Inst().FindImage(L"Plains_Total_Tile.bmp")->SetTransColor(RGB(255, 0, 255));
	SGameEngineResMgr::Inst().FindImage(L"Plains_Total_Tile.bmp")->ImageCut(25, 5);

	// ���ʽ��۽� Ÿ�ϸ� ��θ� ã�ư���.
	m_TileFilePath.MoveParentsFolder(L"ShovelKnight");
	m_TileFilePath.MoveChildFolder(L"Resource");
	m_TileFilePath.MoveChildFolder(L"Image");
	m_TileFilePath.MoveChildFolder(L"Stage");
	m_TileFilePath.MoveChildFolder(L"TileSet");

	// Ÿ�ϸ� ����
	// ��ü ��(Default : On)
	m_TileMap = CreateActor<PlainsTileMap>();
	m_TileMap->LoadTileBlockImage(L"Plains_Total_Tile.bmp");
	SGameEngineString LoadPath = m_TileFilePath.GetPath();
	LoadPath += L"Stage1TileMap.dat";
	m_TileMap->m_TileMap->LoadTile(LoadPath);

	// Ÿ���� ������(ī�޶���ġ����)�� ������ �ε���ũ�⸦ ���Ѵ�.
	// �ε��� -> ������ʺ�2��(2560.f) / Ÿ��ũ��(32.f)
	//                 ���������2��(1440.f) / Ÿ��ũ��(32.f)
	//                 ���� Max�� �Ѿ�� Max������ �ʱ�ȭ�Ѵ�.
	m_TileMap->m_TileMap->SetCullActor(m_Player, { 60.f, 34.f });

	//---------------------------------------------- MovingPlatform ----------------------------------------------//
	m_MovingPlatform1 = CreateActor<MovingPlatform>();
	m_MovingPlatform1->SetPosition({ 6780.f, 1805.f });
	m_MovingPlatform1->SetMoveTargetPos({ 7200.f, 1805.f });
	m_MovingPlatform1->SetLerpSpeed(0.2f);

	m_MovingPlatform2 = CreateActor<MovingPlatform>();
	m_MovingPlatform2->SetPosition({ 8205.f, 2030.f });
	m_MovingPlatform2->SetMoveTargetPos({ 8550.f, 2030.f });
	m_MovingPlatform2->SetLerpSpeed(0.2f);

	m_MovingPlatform3 = CreateActor<MovingPlatform>();
	m_MovingPlatform3->SetPosition({ 13213.f, 3274.f });
	m_MovingPlatform3->SetMoveTargetPos({ 13650.f, 3274.f });
	m_MovingPlatform3->SetLerpSpeed(0.2f);

	m_MovingPlatform4 = CreateActor<MovingPlatform>();
	m_MovingPlatform4->SetPosition({ 12978.f, 3274.f });
	m_MovingPlatform4->SetMoveTargetPos({ 12978.f, 3450.f });
	m_MovingPlatform4->SetLerpSpeed(0.2f);

	m_MovingPlatform5 = CreateActor<MovingPlatform>();
	m_MovingPlatform5->SetPosition({ 15822.f, 1742.f });
	m_MovingPlatform5->SetMoveTargetPos({ 15822.f, 2092.f });
	m_MovingPlatform5->SetLerpSpeed(0.2f);

	//---------------------------------------------- StateTopBar ----------------------------------------------//
	m_TopBar = CreateActor<StateTopBar>();

	//------------------------------------------------ Inventory ------------------------------------------------//


	//---------------------------------------------- DeathScreen ----------------------------------------------//
	m_DeathScreen = CreateActor<DeathScreen>();
	m_DeathScreen->Off();
}

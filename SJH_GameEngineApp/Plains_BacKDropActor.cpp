#include "Plains.h"
#include "PlainsTileMap.h"           // 스테이지 타일맵
#include "ShovelKnight.h"            // 삽질기사(플레이어)
#include "PlainsBackDrop.h"         // 스테이지 배경
#include "PlainsCollisionMap.h"   // 스테이지 충돌맵

#include "MovingPlatform.h"       // 움직이는 충돌체
#include "StateTopBar.h"              // 플레이어 상태바(상단바)
#include "DeathScreen.h"             // 플레이어 사망스크린

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

	// 최초시작시 타일맵 경로를 찾아간다.
	m_TileFilePath.MoveParentsFolder(L"ShovelKnight");
	m_TileFilePath.MoveChildFolder(L"Resource");
	m_TileFilePath.MoveChildFolder(L"Image");
	m_TileFilePath.MoveChildFolder(L"Stage");
	m_TileFilePath.MoveChildFolder(L"TileSet");

	// 타일맵 관련
	// 전체 맵(Default : On)
	m_TileMap = CreateActor<PlainsTileMap>();
	m_TileMap->LoadTileBlockImage(L"Plains_Total_Tile.bmp");
	SGameEngineString LoadPath = m_TileFilePath.GetPath();
	LoadPath += L"Stage1TileMap.dat";
	m_TileMap->m_TileMap->LoadTile(LoadPath);

	// 타일의 기준점(카메라위치정보)과 랜더링 인덱스크기를 정한다.
	// 인덱스 -> 윈도우너비2배(2560.f) / 타일크기(32.f)
	//                 윈도우높이2배(1440.f) / 타일크기(32.f)
	//                 만약 Max를 넘어가면 Max값으로 초기화한다.
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

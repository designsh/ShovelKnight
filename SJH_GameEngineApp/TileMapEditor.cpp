#include "TileMapEditor.h"
#include "EditorBackDrop.h"
#include "EditorTileBackDrop.h"
#include "SGameCore.h"

#include <SGameEngineInput.h>
#include <SGameEngineResMgr.h>

// Static Var

// Static Func

// member Var
TileMapEditor::TileMapEditor() 
	: m_ResPath(), m_EditorDrop(nullptr), m_RenderTile(nullptr),
	m_CamPos(FLOAT4(0.f, 2160.f)), m_Pos(FLOAT4::ZERO), m_TileFilePath(),
	m_Speed(1000.f), m_DelSearch(false), m_TileIndex(0)
{

}

TileMapEditor::~TileMapEditor()
{

}

// member Func
void TileMapEditor::Start()
{
	// 메인화면 돌아가기
	SGameEngineInput::CreateKey(L"TitleBack", VK_ESCAPE);

	// 디버그랜더러 On/Off 키 설정
	SGameEngineInput::CreateKey(L"EditorDebugOff", 'P');
	SGameEngineInput::CreateKey(L"EditorDebugOn", 'O');

	// 현재 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 충돌 링크 생성


	// 해당 이미지 모두 가져오기
	m_ResPath.MoveParentsFolder(L"ShovelKnight");
	m_ResPath.MoveChildFolder(L"Resource");
	m_ResPath.MoveChildFolder(L"Image");
	m_ResPath.MoveChildFolder(L"MapEditor");

	// 현재 경로의 확장자 .bmp인 이미지를 전부다 가져와서 Vector에 저장
	std::vector<SGameEngineFile> AllImageFile = m_ResPath.FindDirectoryAllFileToVector(L"*.bmp");
	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		SGameEngineResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	// 맵에디터 이미지 컷
	SGameEngineResMgr::Inst().FindImage(L"Total_Stage1_Tile.bmp")->SetTransColor(RGB(255, 0, 255));
	SGameEngineResMgr::Inst().FindImage(L"Total_Stage1_Tile.bmp")->ImageCut(25, 5);
	SGameEngineResMgr::Inst().FindImage(L"Broken_Tile.bmp")->SetTransColor(RGB(0, 0, 0));
	SGameEngineResMgr::Inst().FindImage(L"Broken_Tile.bmp")->ImageCut(25, 5);
	SGameEngineResMgr::Inst().FindImage(L"LevelMap_TileSet.bmp")->SetTransColor(RGB(255, 0, 255));
	SGameEngineResMgr::Inst().FindImage(L"LevelMap_TileSet.bmp")->ImageCut(25, 5);
	SGameEngineResMgr::Inst().FindImage(L"MakerMove_Tile.bmp")->SetTransColor(RGB(0, 0, 0));
	SGameEngineResMgr::Inst().FindImage(L"MakerMove_Tile.bmp")->ImageCut(25, 5);
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_TileSet.bmp")->SetTransColor(RGB(255, 0, 255));
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_TileSet.bmp")->ImageCut(25, 5);
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_BrokenTile.bmp")->SetTransColor(RGB(255, 255, 255));
	SGameEngineResMgr::Inst().FindImage(L"Enchantress_BrokenTile.bmp")->ImageCut(25, 5);

	// 사용할 키 설정
	// 마우스를 사용하여 타일을 만들어내고, 지운다.
	SGameEngineInput::CreateKey(L"TileCreate", VK_LBUTTON);
	SGameEngineInput::CreateKey(L"TileDelete", VK_RBUTTON);

	// 키보드 키를 이용하여 현재 생성된 맵을 저장하고 이전에 저장해놓은 맵을 불러온다.
	SGameEngineInput::CreateKey(L"TileMapSave", VK_CONTROL, 'S');
	SGameEngineInput::CreateKey(L"TileMapOpen", VK_CONTROL, 'O');

	// 캠이동을 위한 키
	// 윈도우 크기별로 이동
	SGameEngineInput::CreateKey(L"CamUp", VK_UP);
	SGameEngineInput::CreateKey(L"CamDown", VK_DOWN);
	SGameEngineInput::CreateKey(L"CamLeft", VK_LEFT);
	SGameEngineInput::CreateKey(L"CamRight", VK_RIGHT);

	// 1000픽셀씩 이동
	SGameEngineInput::CreateKey(L"Up", 'W');
	SGameEngineInput::CreateKey(L"Down", 'S');
	SGameEngineInput::CreateKey(L"Left", 'A');
	SGameEngineInput::CreateKey(L"Right", 'D');

	// 현재 선택된 타일의 이전과 이후 타일로 바꿔주는 키
	SGameEngineInput::CreateKey(L"NextTile", 'M');
	SGameEngineInput::CreateKey(L"PrevTile", 'N');

	// 맵에디터 종료후 메인화면이동
	SGameEngineInput::CreateKey(L"Exit", VK_ESCAPE);

	// 캠의 초기위치설정
	SetCamMove(m_CamPos);

	// 액터 생성
	m_EditorDrop = CreateActor<EditorBackDrop>();
	m_RenderTile = CreateActor<EditorTileBackDrop>();
}

void TileMapEditor::SceneUpdate()
{
	m_Pos = FLOAT4::ZERO;
	FLOAT4 TilePos = SGameEngineWindow::MousePos() + GetCamPos();

	// 파일 저장
	if (true == SGameEngineInput::IsPress(L"TileMapSave"))
	{
		m_TileFilePath.MoveParentsFolder(L"ShovelKnight");
		m_TileFilePath.MoveChildFolder(L"Resource");
		m_TileFilePath.MoveChildFolder(L"TileMap");

		// Plains
		SGameEngineString SavePath = m_TileFilePath.GetPath();
		SavePath += L"Stage1TileMap.dat";
		m_RenderTile->m_Tile->SaveTile(SavePath);

		// Plains_BrokenTile
		//SGameEngineString BrokenSavePath = m_TileFilePath.GetPath();
		//BrokenSavePath += L"Stage1BrokenTile.dat";
		//m_RenderTile->m_BrokenTile->SaveTile(BrokenSavePath);

		// LevelMap
		//SGameEngineString SavePath = m_TileFilePath.GetPath();
		//SavePath += L"LevelMapTileMap.dat";
		//m_RenderTile->m_LevelMapTile->SaveTile(SavePath);

		// LevelMap MoveTile
		//SGameEngineString SavePath = m_TileFilePath.GetPath();
		//SavePath += L"LevelMapMoveTile.dat";
		//m_RenderTile->m_LevelMapMoveTile->SaveTile(SavePath);

		// EnchantressMap
		//SGameEngineString SavePath = m_TileFilePath.GetPath();
		//SavePath += L"EnchantressTile.dat";
		//m_RenderTile->m_EnchantressTile->SaveTile(SavePath);

		// EnchantressMap Broken Tile
		//SGameEngineString SavePath = m_TileFilePath.GetPath();
		//SavePath += L"EnchantressBrokenTile.dat";
		//m_RenderTile->m_EnchantressBrokenTile->SaveTile(SavePath);
	}

	// 파일 Load
	if (true == SGameEngineInput::IsPress(L"TileMapOpen"))
	{
		m_TileFilePath.MoveParentsFolder(L"ShovelKnight");
		m_TileFilePath.MoveChildFolder(L"Resource");
		m_TileFilePath.MoveChildFolder(L"TileMap");

		// Plains
		SGameEngineString LoadPath = m_TileFilePath.GetPath();
		LoadPath += L"Stage1TileMap.dat";
		m_RenderTile->m_Tile->LoadTile(LoadPath);

		// Plains_BrokenTile
		//SGameEngineString BrokenLoadPath = m_TileFilePath.GetPath();
		//BrokenLoadPath += L"Stage1BrokenTile.dat";
		//m_RenderTile->m_BrokenTile->LoadTile(BrokenLoadPath);

		// LevelMap
		//SGameEngineString BrokenLoadPath = m_TileFilePath.GetPath();
		//BrokenLoadPath += L"LevelMapTileMap.dat";
		//m_RenderTile->m_LevelMapTile->LoadTile(BrokenLoadPath);

		// LevelMap MoveTile
		//SGameEngineString LevelMapMoveLoadPath = m_TileFilePath.GetPath();
		//LevelMapMoveLoadPath += L"LevelMapMoveTile.dat";
		//m_RenderTile->m_LevelMapMoveTile->LoadTile(LevelMapMoveLoadPath);

		//// EnchantressMap Tile
		//SGameEngineString EnchantressMapLoadPath = m_TileFilePath.GetPath();
		//EnchantressMapLoadPath += L"EnchantressTile.dat";
		//m_RenderTile->m_EnchantressTile->LoadTile(EnchantressMapLoadPath);

		//// EnchantressMap Broken Tile
		//SGameEngineString EnchantressMapBrokenLoadPath = m_TileFilePath.GetPath();
		//EnchantressMapBrokenLoadPath += L"EnchantressBrokenTile.dat";
		//m_RenderTile->m_EnchantressBrokenTile->LoadTile(EnchantressMapBrokenLoadPath);
	}

	// 타일 생성
	if (true == SGameEngineInput::IsPress(L"TileCreate"))
	{
		FLOAT4 TilePos = SGameEngineWindow::MousePos() + GetCamPos();
		//if (TilePos.x >= 1280.f || TilePos.y >= 720.f || TilePos.y < 0.0f || TilePos.x < 0.0f)
		//if (TilePos.x >= 1280.f || TilePos.y < 0.0f || TilePos.x < 0.0f)
		//{
		//	return;
		//}

		// Plains
		m_RenderTile->m_Tile->SetTile(TilePos, m_TileIndex);
		
		// Plains_BrokenTile
		//m_RenderTile->m_BrokenTile->SetTile(TilePos, m_TileIndex);

		// LevelMap
		//m_RenderTile->m_LevelMapTile->SetTile(TilePos, m_TileIndex);

		// LevelMap MoveTile
		//m_RenderTile->m_LevelMapMoveTile->SetTile(TilePos, m_TileIndex);

		// EnchantressMap
		//m_RenderTile->m_EnchantressTile->SetTile(TilePos, m_TileIndex);

		// EnchantressMap BrokenTile
		//m_RenderTile->m_EnchantressBrokenTile->SetTile(TilePos, m_TileIndex);
	}
	// 타일 삭제
	else if (true == SGameEngineInput::IsPress(L"TileDelete"))
	{
		// Plains
		m_RenderTile->m_Tile->DelTile(TilePos);

		// Plains_BrokenTile
		//m_RenderTile->m_BrokenTile->DelTile(TilePos);

		// LevelMap
		//m_RenderTile->m_LevelMapTile->DelTile(TilePos);

		// LevelMap MoveTile
		//m_RenderTile->m_LevelMapMoveTile->DelTile(TilePos);

		// EnchantressMap
		//m_RenderTile->m_EnchantressTile->DelTile(TilePos);

		// EnchantressMap BrokenTile
		//m_RenderTile->m_EnchantressBrokenTile->DelTile(TilePos);
	}

	// 카메라 무브
	if (true == SGameEngineInput::IsDown(L"CamUp"))
	{
		SetCamMove({ 0.f, -720.f });
	}
	if (true == SGameEngineInput::IsDown(L"CamDown"))
	{
		SetCamMove({ 0.f, +720.f });
	}
	if (true == SGameEngineInput::IsDown(L"CamLeft"))
	{
		SetCamMove({ -1280.f, 0.f });
	}
	if (true == SGameEngineInput::IsDown(L"CamRight"))
	{
		SetCamMove({ 1280.f, 0.f });
	}

	if (true == SGameEngineInput::IsPress(L"Up"))
	{
		m_Pos += FLOAT4::UP * SGameEngineTimer::FDeltaTime(m_Speed);
	}
	if (true == SGameEngineInput::IsPress(L"Down"))
	{
		m_Pos += FLOAT4::DOWN * SGameEngineTimer::FDeltaTime(m_Speed);
	}
	if (true == SGameEngineInput::IsPress(L"Left"))
	{
		m_Pos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_Speed);
	}
	if (true == SGameEngineInput::IsPress(L"Right"))
	{
		m_Pos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_Speed);
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 현재 타일의 다음 인덱스로 넘기기
	if (SGameEngineInput::IsDown(L"NextTile"))
	{
		++m_TileIndex;
		if (125 <= m_TileIndex)
		{
			m_TileIndex = 125;
		}
	}
	// 현재 타일의 이전 인덱스로 넘기기
	else if (SGameEngineInput::IsDown(L"PrevTile"))
	{
		--m_TileIndex;

		if (m_TileIndex < 0)
			m_TileIndex = 0;
	}

	SetCamMove(m_Pos);

	// 디버그 랜더 On/Off Key Down
	if (true == SGameEngineInput::IsDown(L"EditorDebugOff"))
	{
		IsDebugRenderOff();
	}
	else if (true == SGameEngineInput::IsDown(L"EditorDebugOn"))
	{
		IsDebugRenderOn();
	}

	if (true == SGameEngineInput::IsDown(L"TitleBack"))
	{
		//SGameCore::SceneManager.ChangeScene(L"ShovelKnigthTitle");
	}
}

void TileMapEditor::SceneDebugRender()
{
	FLOAT4 MousePos = SGameEngineWindow::MousePos();
	SGameEngineString MousePosText = L"MousePos";
	MousePosText += L"X : ";
	MousePosText += SGameEngineString::ToString(MousePos.ix());
	MousePosText += L"Y : ";
	MousePosText += SGameEngineString::ToString(MousePos.iy());
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 80, MousePosText.c_str(), lstrlen(MousePosText.c_str()));
}

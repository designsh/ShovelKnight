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
	// ����ȭ�� ���ư���
	SGameEngineInput::CreateKey(L"TitleBack", VK_ESCAPE);

	// ����׷����� On/Off Ű ����
	SGameEngineInput::CreateKey(L"EditorDebugOff", 'P');
	SGameEngineInput::CreateKey(L"EditorDebugOn", 'O');

	// ���� ������ ũ�� ��������
	m_WindowSize = SGameEngineWindow::GetSize();

	// �浹 ��ũ ����


	// �ش� �̹��� ��� ��������
	m_ResPath.MoveParentsFolder(L"ShovelKnight");
	m_ResPath.MoveChildFolder(L"Resource");
	m_ResPath.MoveChildFolder(L"Image");
	m_ResPath.MoveChildFolder(L"MapEditor");

	// ���� ����� Ȯ���� .bmp�� �̹����� ���δ� �����ͼ� Vector�� ����
	std::vector<SGameEngineFile> AllImageFile = m_ResPath.FindDirectoryAllFileToVector(L"*.bmp");
	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		SGameEngineResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	// �ʿ����� �̹��� ��
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

	// ����� Ű ����
	// ���콺�� ����Ͽ� Ÿ���� ������, �����.
	SGameEngineInput::CreateKey(L"TileCreate", VK_LBUTTON);
	SGameEngineInput::CreateKey(L"TileDelete", VK_RBUTTON);

	// Ű���� Ű�� �̿��Ͽ� ���� ������ ���� �����ϰ� ������ �����س��� ���� �ҷ��´�.
	SGameEngineInput::CreateKey(L"TileMapSave", VK_CONTROL, 'S');
	SGameEngineInput::CreateKey(L"TileMapOpen", VK_CONTROL, 'O');

	// ķ�̵��� ���� Ű
	// ������ ũ�⺰�� �̵�
	SGameEngineInput::CreateKey(L"CamUp", VK_UP);
	SGameEngineInput::CreateKey(L"CamDown", VK_DOWN);
	SGameEngineInput::CreateKey(L"CamLeft", VK_LEFT);
	SGameEngineInput::CreateKey(L"CamRight", VK_RIGHT);

	// 1000�ȼ��� �̵�
	SGameEngineInput::CreateKey(L"Up", 'W');
	SGameEngineInput::CreateKey(L"Down", 'S');
	SGameEngineInput::CreateKey(L"Left", 'A');
	SGameEngineInput::CreateKey(L"Right", 'D');

	// ���� ���õ� Ÿ���� ������ ���� Ÿ�Ϸ� �ٲ��ִ� Ű
	SGameEngineInput::CreateKey(L"NextTile", 'M');
	SGameEngineInput::CreateKey(L"PrevTile", 'N');

	// �ʿ����� ������ ����ȭ���̵�
	SGameEngineInput::CreateKey(L"Exit", VK_ESCAPE);

	// ķ�� �ʱ���ġ����
	SetCamMove(m_CamPos);

	// ���� ����
	m_EditorDrop = CreateActor<EditorBackDrop>();
	m_RenderTile = CreateActor<EditorTileBackDrop>();
}

void TileMapEditor::SceneUpdate()
{
	m_Pos = FLOAT4::ZERO;
	FLOAT4 TilePos = SGameEngineWindow::MousePos() + GetCamPos();

	// ���� ����
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

	// ���� Load
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

	// Ÿ�� ����
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
	// Ÿ�� ����
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

	// ī�޶� ����
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

	// ���� Ÿ���� ���� �ε����� �ѱ��
	if (SGameEngineInput::IsDown(L"NextTile"))
	{
		++m_TileIndex;
		if (125 <= m_TileIndex)
		{
			m_TileIndex = 125;
		}
	}
	// ���� Ÿ���� ���� �ε����� �ѱ��
	else if (SGameEngineInput::IsDown(L"PrevTile"))
	{
		--m_TileIndex;

		if (m_TileIndex < 0)
			m_TileIndex = 0;
	}

	SetCamMove(m_Pos);

	// ����� ���� On/Off Key Down
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

#include "EditorTileBackDrop.h"
#include <SGameEngineWindow.h>
#include <SGameEngineString.h>

// Static Var

// Static Func

// member Var
EditorTileBackDrop::EditorTileBackDrop()
	: m_Tile(nullptr), m_BrokenTile(nullptr), m_LevelMapTile(nullptr), m_LevelMapMoveTile(nullptr), m_EnchantressTile(nullptr), m_EnchantressBrokenTile(nullptr)

{

}

EditorTileBackDrop::~EditorTileBackDrop()
{

}

// member Func
void EditorTileBackDrop::Start()
{
	// Ÿ�� ����
	// Layer 7 ����, ��� ����(23040 x 4320)
	m_Tile = CreateRenderer<SGameEngineRendererTile>(7);
	m_Tile->TileMapStart(L"Total_Stage1_Tile.bmp", { 32.f, 32.f }, { 32.f, 32.f }, 720, 135);

	// �μ����� Ÿ��(23040 x 4320)
	m_BrokenTile = CreateRenderer<SGameEngineRendererTile>(8);
	m_BrokenTile->TileMapStart(L"Broken_Tile.bmp", { 32.f, 32.f }, { 32.f, 32.f }, 720, 135);

	// ����� Ÿ��(1280 x 720)
	m_LevelMapTile = CreateRenderer<SGameEngineRendererTile>(7);
	m_LevelMapTile->TileMapStart(L"LevelMap_TileSet.bmp", { 32.f, 32.f }, { 32.f, 32.f }, 40, 90);

	// ����� �̵�����Ÿ��(1280 x 720)
	m_LevelMapMoveTile = CreateRenderer<SGameEngineRendererTile>(8);
	m_LevelMapMoveTile->TileMapStart(L"MakerMove_Tile.bmp", { 32.f, 32.f }, { 32.f, 32.f }, 40, 23);

	// ���̳κ����� Ÿ��(1280 x 2880)
	m_EnchantressTile = CreateRenderer<SGameEngineRendererTile>(7);
	m_EnchantressTile->TileMapStart(L"Enchantress_TileSet.bmp", { 32.f, 32.f }, { 32.f, 32.f }, 40, 90);

	// ���̳κ��� �μ����� Ÿ��
	m_EnchantressBrokenTile = CreateRenderer<SGameEngineRendererTile>(8);
	m_EnchantressBrokenTile->TileMapStart(L"Enchantress_BrokenTile.bmp", { 32.f, 32.f }, { 32.f, 32.f }, 40, 90);
}

void EditorTileBackDrop::Update()
{

}

void EditorTileBackDrop::DebugRender()
{
	//FLOAT4 CamPos = GetScene()->GetCamPos();
	//FLOAT4 MousePos = SGameEngineWindow::MousePos();
	//
	//SGameEngineString	CamX = L"CamX : ";
	//CamX += SGameEngineString::ToString(CamPos.x);
	//SGameEngineString	CamY = L"CamY : ";
	//CamY += SGameEngineString::ToString(CamPos.y);
	//SGameEngineString	MouseX = L"MouseX : ";
	//MouseX += SGameEngineString::ToString(MousePos.x);
	//SGameEngineString	MouseY = L"MouseY : ";
	//MouseY += SGameEngineString::ToString(MousePos.y);

	//TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 640, CamX.c_str(), lstrlen(CamX.c_str()));
	//TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 660, CamY.c_str(), lstrlen(CamY.c_str()));
	//TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 680, MouseX.c_str(), lstrlen(MouseX.c_str()));
	//TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 700, MouseY.c_str(), lstrlen(MouseY.c_str()));
}
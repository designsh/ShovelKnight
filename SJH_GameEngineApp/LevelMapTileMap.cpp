#include "LevelMapTileMap.h"
#include <SGameEngineWindow.h>

// Static Var

// Static Func

// member Var
LevelMapTileMap::LevelMapTileMap()
	: m_WindowSize(FLOAT4::ZERO),
	m_TileMap(nullptr)
{

}

LevelMapTileMap::~LevelMapTileMap()
{

}

// member Func
void LevelMapTileMap::Start()
{
	m_WindowSize = SGameEngineWindow::GetSize();

	SGameEngineInput::CreateKey(L"LevelMap_TileMapOff", 'Z');
	SGameEngineInput::CreateKey(L"LevelMap_TileMapOn", 'X');
}

void LevelMapTileMap::Update()
{
	if (true == SGameEngineInput::IsPress(L"LevelMap_TileMapOff"))
	{
		m_TileMap->Off();
	}

	if (true == SGameEngineInput::IsPress(L"LevelMap_TileMapOn"))
	{
		m_TileMap->On();
	}
}

void LevelMapTileMap::LoadTileBlockImage(const SGameEngineString& _TileImageName, int _RenderGroup)
{
	// 액터 생성후 이미지 이름을 받아 처리한다.
	m_TileMap = CreateRenderer<SGameEngineRendererTile>(_RenderGroup);
	m_TileMap->TileMapStart(_TileImageName, { 32.f, 32.f }, { 32.f, 32.f }, 40, 24);
}

void LevelMapTileMap::DebugRender()
{

}

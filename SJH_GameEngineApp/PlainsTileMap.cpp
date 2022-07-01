#include "PlainsTileMap.h"
#include <SGameEngineResMgr.h>
#include <SGameEngineWindow.h>
#include <SGameEngineDebug.h>
#include <Windows.h>

#include "GlobalValue.h"

// Static Var

// Static Func

// member Var
PlainsTileMap::PlainsTileMap()
	: m_WindowSize(FLOAT4::ZERO), m_TileMap(nullptr)
{

}

PlainsTileMap::~PlainsTileMap()
{

}

// member Func
void PlainsTileMap::Start()
{
	m_WindowSize = SGameEngineWindow::GetSize();
}

void PlainsTileMap::Update()
{

}

void PlainsTileMap::LoadTileBlockImage(const SGameEngineString& _TileImageName, int _RenderGroup)
{
	// 액터 생성후 이미지 이름을 받아 처리한다.
	m_TileMap = CreateRenderer<SGameEngineRendererTile>(_RenderGroup);
	m_TileMap->TileMapStart(_TileImageName, { 32.f, 32.f }, { 32.f, 32.f }, 720, 135);
}

void PlainsTileMap::DebugRender()
{
#ifdef DEBUG

	


#endif // DEBUG
}
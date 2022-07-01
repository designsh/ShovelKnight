#include "EnchantressTileMap.h"
#include <SGameEngineWindow.h>

// Static Var

// Static Func

// member Var
EnchantressTileMap::EnchantressTileMap()
	: m_WindowSize(FLOAT4::ZERO),
	m_TileMap(nullptr)
{

}

EnchantressTileMap::~EnchantressTileMap()
{

}

// member Func
void EnchantressTileMap::Start()
{
	m_WindowSize = SGameEngineWindow::GetSize();
}

void EnchantressTileMap::Update()
{

}

void EnchantressTileMap::LoadTileBlockImage(const SGameEngineString& _TileImageName, int _RenderGroup)
{
	// ���� ������ �̹��� �̸��� �޾� ó���Ѵ�.
	m_TileMap = CreateRenderer<SGameEngineRendererTile>(_RenderGroup);
	m_TileMap->TileMapStart(_TileImageName, { 32.f, 32.f }, { 32.f, 32.f }, 40, 68);
}

void EnchantressTileMap::DebugRender()
{

}

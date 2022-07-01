#include "LevelMapCollisionMap.h"
#include <SGameEngineInput.h>
#include <SGameEngineWindow.h>

#include "GlobalValue.h"

// Static Var

// Static Func

// member Var
LevelMapCollisionMap::LevelMapCollisionMap()
	: m_WindowSize(FLOAT4::ZERO), 
	m_CollistionMap(nullptr)
{

}

LevelMapCollisionMap::~LevelMapCollisionMap()
{

}

// member Func
void LevelMapCollisionMap::Start()
{
	// 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 0, 0을 맞추는 충돌배경
	m_CollistionMap = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::CollistionMap);
	m_CollistionMap->TransCenterSetting(L"LevelMap_ColMap.bmp", { 1280, 720 });
	m_CollistionMap->SetPivotPos({ 1280.f * 0.5f, 720.f * 0.5f });
	m_CollistionMap->Off();
}

void LevelMapCollisionMap::Update()
{

}

void LevelMapCollisionMap::DebugRender()
{

}

#include "PlainsCollisionMap.h"
#include <SGameEngineResMgr.h>
#include <SGameEngineWindow.h>
#include <SGameEngineDebug.h>
#include <Windows.h>

#include "GlobalValue.h"

// Static Var

// Static Func

// member Var
PlainsCollisionMap::PlainsCollisionMap() 
	: m_WindowSize(FLOAT4::ZERO), m_CollistionMap(nullptr)
{

}

PlainsCollisionMap::~PlainsCollisionMap()
{

}

// member Func
void PlainsCollisionMap::Start()
{
	// Ű����
	SGameEngineInput::CreateKey(L"CollisionMapOff", 'Z');
	SGameEngineInput::CreateKey(L"CollisionMapOn", 'X');

	// ������ ũ�� ��������
	m_WindowSize = SGameEngineWindow::GetSize();

	// 0, 0�� ���ߴ� �浹���
	m_CollistionMap = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::CollistionMap);
	m_CollistionMap->TransCenterSetting(L"Plains.bmp", { 23040, 4320 });
	m_CollistionMap->SetPivotPos({ 23040 * 0.5f, 4320 * 0.5f });

	// �ʱⰪ Off
	m_CollistionMap->Off();
}

void PlainsCollisionMap::Update()
{
	if (true == SGameEngineInput::IsPress(L"CollisionMapOff"))
	{
		m_CollistionMap->Off();
	}

	if (true == SGameEngineInput::IsPress(L"CollisionMapOn"))
	{
		m_CollistionMap->On();
	}
}

void PlainsCollisionMap::DebugRender()
{

}

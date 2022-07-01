#include "Inventory.h"
#include <SGameEngineWindow.h>

// Static Var

// Static Func

// member Var
Inventory::Inventory()
	: m_WindowSize(FLOAT4::ZERO),
	m_Inventory(nullptr), m_RelicsText(nullptr), m_EquipmentText(nullptr), m_InventoryCursor(nullptr), m_InventoryItem1(nullptr), m_InventoryItem2(nullptr)
{

}

Inventory::~Inventory()
{

}

// member Func
void Inventory::Start()
{
	m_WindowSize = SGameEngineWindow::GetSize();

	// 인벤토리 창 생성
	m_Inventory = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::StateBar);
	m_Inventory->TransCenterSetting(L"inventory.bmp", { 454, 148 });
	m_Inventory->SetPivotPos({ m_WindowSize.x * 0.5f, m_WindowSize.y * 0.5f });
	m_Inventory->SetCutData(0);
	m_Inventory->CamEffectOff();
}

void Inventory::Update()
{

}

void Inventory::DebugRender()
{

}

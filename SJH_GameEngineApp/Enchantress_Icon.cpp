#include "Enchantress_Icon.h"
#include <SGameEngineWindow.h>

#include "GlobalValue.h"

// Static Var

// Static Func

// member Var
Enchantress_Icon::Enchantress_Icon()
	: m_WindowSize(FLOAT4::ZERO),
	m_EnchantressIcon(nullptr)
{

}

Enchantress_Icon::~Enchantress_Icon()
{

}

// member Func
void Enchantress_Icon::Start()
{
	m_WindowSize = SGameEngineWindow::GetSize();

	// 랜더러 생성
	m_EnchantressIcon = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::UI);
	m_EnchantressIcon->TransCenterSetting(L"Enchantress_Icon.bmp", { 48, 48 });
}

void Enchantress_Icon::Update()
{

}

void Enchantress_Icon::DebugRender()
{

}

#include "None_Icon.h"
#include <SGameEngineWindow.h>

#include "GlobalValue.h"

// Static Var

// Static Func

// member Var
None_Icon::None_Icon()
	: m_WindowSize(FLOAT4::ZERO),
	m_NoneIcon(nullptr)
{

}

None_Icon::~None_Icon()
{

}

// member Func
void None_Icon::Start()
{
	m_WindowSize = SGameEngineWindow::GetSize();

	// 랜더러 생성
	m_NoneIcon = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::UI);
	m_NoneIcon->TransCenterSetting(L"Plains_Icon.bmp", { 48, 48 });
}

void None_Icon::Update()
{

}

void None_Icon::DebugRender()
{

}

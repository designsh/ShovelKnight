#include "Plains_Icon.h"
#include <SGameEngineWindow.h>

#include "GlobalValue.h"
#include "Plains_IconEffect.h"

// Static Var

// Static Func

// member Var
Plains_Icon::Plains_Icon()
	: m_WindowSize(FLOAT4::ZERO),
	m_PlainsIcon(nullptr), m_bFistEffect(false)
{

}

Plains_Icon::~Plains_Icon()
{

}

// member Func
void Plains_Icon::Start()
{
	m_WindowSize = SGameEngineWindow::GetSize();

	// 랜더러 생성
	m_PlainsIcon = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::UI);
	m_PlainsIcon->TransCenterSetting(L"None_Icon.bmp", { 48, 48 });
}

void Plains_Icon::Update()
{
	if (false == m_bFistEffect)
	{
		// 이펙트 생성
		Plains_IconEffect* ClearEffect = GetScene()->CreateActor<Plains_IconEffect>();
		ClearEffect->SetPosition(GetPosition());
		m_bFistEffect = true;
	}
}

void Plains_Icon::DebugRender()
{

}

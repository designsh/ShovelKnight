#include "Plains_IconEffect.h"
#include <SGameEngineWindow.h>

// Static Var

// Static Func

// member Var
Plains_IconEffect::Plains_IconEffect()
	: m_WindowSize(FLOAT4::ZERO),
	m_AniClearEffect(nullptr), m_ClearEffectFSM()
{

}

Plains_IconEffect::~Plains_IconEffect()
{

}

// member Func
void Plains_IconEffect::Start()
{
	// 현재 윈도우 크기를 가져온다.
	m_WindowSize = SGameEngineWindow::GetSize();

	// 애니메이션 생성
	m_AniClearEffect = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::ClearEffect);
	m_AniClearEffect->SetRenderScale({ 300, 300 });
	m_AniClearEffect->CreateAnimation(L"ClearIdle", L"ClearEffect.bmp", 0, 4, 0.3f);

	// FSM 상태 생성
	m_ClearEffectFSM.CreateState(L"Plains_ClearIdle", this, &Plains_IconEffect::IdleStay, &Plains_IconEffect::IdleStart, &Plains_IconEffect::IdleEnd);
	m_ClearEffectFSM.ChangeState(L"Plains_ClearIdle");
}

void Plains_IconEffect::Update()
{
	m_ClearEffectFSM.Update();
}

void Plains_IconEffect::DebugRender()
{

}

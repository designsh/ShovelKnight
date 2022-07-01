#include "BrokenTileEffect.h"
#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>

#include "GlobalValue.h"

// Static Var
SoundPlayer BrokenTileEffect::m_BrokenTileSound;

// Static Func

// member Var
BrokenTileEffect::BrokenTileEffect()
	: m_WindowSize(FLOAT4::ZERO),
	m_AniBrokenTileEffect(nullptr), m_BrokenTileEffectFSM()
{

}

BrokenTileEffect::~BrokenTileEffect()
{

}

// member Func
void BrokenTileEffect::Start()
{
	// 현재 윈도우 크기를 가져온다.
	m_WindowSize = SGameEngineWindow::GetSize();

	// 애니메이션
	m_AniBrokenTileEffect = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniBrokenTileEffect->SetRenderScale({ 150, 150 });
	m_AniBrokenTileEffect->SetPivotPos({ 0.f, 10.f });
	m_AniBrokenTileEffect->CreateAnimation(L"EffectDeath", L"BrokenTile_Poof.bmp", 0, 6);

	// FSM 생성
	m_BrokenTileEffectFSM.CreateState(L"Effect_Death", this, &BrokenTileEffect::DeathStay, &BrokenTileEffect::DeathStart, &BrokenTileEffect::DeathEnd);
	m_BrokenTileEffectFSM.ChangeState(L"Effect_Death");
}

void BrokenTileEffect::Update()
{
	m_BrokenTileEffectFSM.Update();
}

void BrokenTileEffect::DebugRender()
{

}

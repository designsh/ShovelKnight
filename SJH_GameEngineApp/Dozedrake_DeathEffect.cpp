#include "Dozedrake_DeathEffect.h"
#include <SGameEngineWindow.h>

// Static Var

// Static Func

// member Var
Dozedrake_DeathEffect::Dozedrake_DeathEffect()
	: m_WindowSize(FLOAT4::ZERO), m_AniDeathEffect(nullptr), m_DeathEffectFSM()
{

}

Dozedrake_DeathEffect::~Dozedrake_DeathEffect()
{

}

// member Func
void Dozedrake_DeathEffect::Start()
{
	// 현재 윈도우 크기를 가져온다.
	m_WindowSize = SGameEngineWindow::GetSize();

	// 애니메이션 생성
	m_AniDeathEffect = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::MonsterEffect);
	m_AniDeathEffect->SetRenderScale({ 300, 300 });
	m_AniDeathEffect->CreateAnimation(L"DozeDeathEffectIdle", L"explosionSmall.bmp", 0, 4);

	// FSM 상태 생성
	m_DeathEffectFSM.CreateState(L"Dozedrake_Idle", this, &Dozedrake_DeathEffect::IdleStay, &Dozedrake_DeathEffect::IdleStart, &Dozedrake_DeathEffect::IdleEnd);
	m_DeathEffectFSM.ChangeState(L"Dozedrake_Idle");
}

void Dozedrake_DeathEffect::Update()
{
	m_DeathEffectFSM.Update();
}

void Dozedrake_DeathEffect::DebugRender()
{

}

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
	// ���� ������ ũ�⸦ �����´�.
	m_WindowSize = SGameEngineWindow::GetSize();

	// �ִϸ��̼�
	m_AniBrokenTileEffect = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniBrokenTileEffect->SetRenderScale({ 150, 150 });
	m_AniBrokenTileEffect->SetPivotPos({ 0.f, 10.f });
	m_AniBrokenTileEffect->CreateAnimation(L"EffectDeath", L"BrokenTile_Poof.bmp", 0, 6);

	// FSM ����
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

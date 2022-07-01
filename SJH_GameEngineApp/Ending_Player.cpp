#include "Ending_Player.h"
#include <SGameEngineWindow.h>

// Static Var

// Static Func

// member Var
Ending_Player::Ending_Player()
	: m_WindowSize(FLOAT4::ZERO),
	m_AniPlayer(nullptr), m_PlayerFSM()
{

}

Ending_Player::~Ending_Player()
{

}

// member Func
void Ending_Player::Start()
{
	// ������ũ�� ��������
	m_WindowSize = SGameEngineWindow::GetSize();

	// �ִϸ��̼� ����
	m_AniPlayer = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniPlayer->SetRenderScale({ 350, 350 });
	m_AniPlayer->CreateAnimation(L"State_Start", L"Ending_ShovelKnight.bmp", 0, 1);

	// FSM ����
	m_PlayerFSM.CreateState(L"Ending_StateStart", this, &Ending_Player::StateStay, &Ending_Player::StateStart, &Ending_Player::StateEnd);
	m_PlayerFSM.ChangeState(L"Ending_StateStart");
}

void Ending_Player::Update()
{
	m_PlayerFSM.Update();
}

void Ending_Player::DebugRender()
{

}

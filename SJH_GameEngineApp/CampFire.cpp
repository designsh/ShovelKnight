#include "CampFire.h"
#include <SGameEngineWindow.h>

// Static Var

// Static Func

// member Var
CampFire::CampFire()
	: m_WindowSize(FLOAT4::ZERO),
	m_AniCampFire(nullptr), m_CampFireFSM()
{

}

CampFire::~CampFire()
{

}

// member Func
void CampFire::Start()
{
	// ������ũ�� ��������
	m_WindowSize = SGameEngineWindow::GetSize();

	// �ִϸ��̼� ����
	m_AniCampFire = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniCampFire->SetRenderScale({ 200, 200 });
	m_AniCampFire->CreateAnimation(L"CampFire_Start", L"CampFire.bmp", 0, 2);

	// FSM ����
	m_CampFireFSM.CreateState(L"Ending_FireStart", this, &CampFire::FireStay, &CampFire::FireStart, &CampFire::FireEnd);
	m_CampFireFSM.ChangeState(L"Ending_FireStart");
}

void CampFire::Update()
{
	m_CampFireFSM.Update();
}

void CampFire::DebugRender()
{

}

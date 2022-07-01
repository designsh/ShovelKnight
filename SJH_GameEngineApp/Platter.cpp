#include "Platter.h"
#include <SGameEngineWindow.h>

// Static Var

// Static Func

// member Var
Platter::Platter()
    : m_WindowSize(FLOAT4::ZERO),
    m_PlatterRenderer(nullptr), m_PlatterCol(nullptr)
{

}

Platter::~Platter()
{

}

// member Func
void Platter::Start()
{
	// 현재 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 충돌체 생성
	m_PlatterCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::UI);
	m_PlatterCol->SetScale({ 70, 50 });
	m_PlatterCol->AddStartEvent(this, &Platter::CollisionStart);
	m_PlatterCol->AddStayEvent(this, &Platter::CollisionStay);
	m_PlatterCol->AddEndEvent(this, &Platter::CollisionEnd);
	m_PlatterCol->SetCheckData(1);

	// 이미지 설정
	m_PlatterRenderer = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::UI);
	m_PlatterRenderer->TransCenterSetting(L"platter1.bmp", { 29.f, 18.f });
	m_PlatterRenderer->SetCutData(0);
	m_PlatterRenderer->SetRenderScale({ 64, 40 });
}

void Platter::Update()
{
	
}

void Platter::DebugRender()
{
	Col2DData PlatterColData;
	PlatterColData.m_Pos = GetCamPosition() - m_PlatterCol->GetPivotPos();
	PlatterColData.m_Size = m_PlatterCol->GetScale();
	RECT PlatterColRect = { PlatterColData.iLeft(), PlatterColData.iTop(), PlatterColData.iRight(), PlatterColData.iBottom() };
	if (true == m_PlatterCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &PlatterColRect, SGameEngineWindow::GetGreenBrush());
	}
}

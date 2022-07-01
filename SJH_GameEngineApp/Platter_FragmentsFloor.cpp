#include "Platter_FragmentsFloor.h"
#include <SGameEngineWindow.h>

// Static Var

// Static Func

// member Var
Platter_FragmentsFloor::Platter_FragmentsFloor()
	: m_WindowSize(FLOAT4::ZERO),
	m_FragmentsFloorRenderer(nullptr),
	m_MoveDir(GlobalValue::BasicMoveType::Left), 
	m_MovePos(FLOAT4::ZERO), m_DirectPos(FLOAT4::ZERO), 
	m_AppearPos(FLOAT4::ZERO), m_AppearPower(FLOAT4::ZERO), m_AppearGravityPower(FLOAT4::ZERO)
{

}

Platter_FragmentsFloor::~Platter_FragmentsFloor()
{

}

// member Func
void Platter_FragmentsFloor::Start()
{
	// ���� ������ ũ�� ��������
	m_WindowSize = SGameEngineWindow::GetSize();

	// �̹��� ����
	m_FragmentsFloorRenderer = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::UI + 1);
	m_FragmentsFloorRenderer->TransCenterSetting(L"platter3.bmp", { 29.f, 18.f });
	m_FragmentsFloorRenderer->SetCutData(0);
	m_FragmentsFloorRenderer->SetRenderScale({ 64, 40 });

	// ���� �Ŀ� ����
	m_AppearPos = FLOAT4::ZERO;
	m_AppearPower = FLOAT4(0.f, -300.f);
	m_AppearGravityPower = FLOAT4(0.f, 1000.f);
}

void Platter_FragmentsFloor::Update()
{
	// �����ϸ� �ٴ����� ��������.
	FragmentsFloorAppear();
}

void Platter_FragmentsFloor::FragmentsFloorAppear()
{
	m_DirectPos = FLOAT4::ZERO;
	m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(150.f);

	// �߷�����
	m_AppearPower += m_AppearGravityPower * SGameEngineTimer::FDeltaTime();
	m_AppearPos = m_AppearPower * SGameEngineTimer::FDeltaTime();

	// ���⼭ ��� ������ ���� ���Ѵ�.
	m_MovePos = m_AppearPos + m_DirectPos;

	MovePosition(m_MovePos);

	// �̶� ī�޶� ���� �ۿ� ������ ���� �״´�.
	CamDistDel();
}

void Platter_FragmentsFloor::CamDistDel()
{
	FLOAT4 Dir = GetScene()->GetCamPos() - GetPosition();

	// ī�޶� ���������� ������ ���� �״´�.
	if (1000.0f <= FLOAT4::Len2D(Dir))
	{
		Death();
	}
}

void Platter_FragmentsFloor::DebugRender()
{

}

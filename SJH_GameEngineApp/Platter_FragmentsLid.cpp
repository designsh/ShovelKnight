#include "Platter_FragmentsLid.h"
#include <SGameEngineWindow.h>

// Static Var

// Static Func

// member Var
Platter_FragmentsLid::Platter_FragmentsLid()
	: m_WindowSize(FLOAT4::ZERO),
	m_FragmentsLidRenderer(nullptr),
	m_MoveDir(GlobalValue::BasicMoveType::Right),
	m_MovePos(FLOAT4::ZERO), m_DirectPos(FLOAT4::ZERO),
	m_AppearPos(FLOAT4::ZERO), m_AppearPower(FLOAT4::ZERO), m_AppearGravityPower(FLOAT4::ZERO)
{

}

Platter_FragmentsLid::~Platter_FragmentsLid()
{

}

// member Func
void Platter_FragmentsLid::Start()
{
	// ���� ������ ũ�� ��������
	m_WindowSize = SGameEngineWindow::GetSize();

	// �̹��� ����
	m_FragmentsLidRenderer = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::UI + 1);
	m_FragmentsLidRenderer->TransCenterSetting(L"platter2.bmp", { 29.f, 18.f });
	m_FragmentsLidRenderer->SetCutData(0);
	m_FragmentsLidRenderer->SetRenderScale({ 64, 40 });

	// ���� �Ŀ� ����
	m_AppearPos = FLOAT4::ZERO;
	m_AppearPower = FLOAT4(0.f, -300.f);
	m_AppearGravityPower = FLOAT4(0.f, 1000.f);
}

void Platter_FragmentsLid::Update()
{
	// �����ϸ� �ٴ����� ��������.
	FragmentsLidAppear();
}

void Platter_FragmentsLid::FragmentsLidAppear()
{
	m_DirectPos = FLOAT4::ZERO;
	m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(150.f);

	// �߷�����
	m_AppearPower += m_AppearGravityPower * SGameEngineTimer::FDeltaTime();
	m_AppearPos = m_AppearPower * SGameEngineTimer::FDeltaTime();

	// ���⼭ ��� ������ ���� ���Ѵ�.
	m_MovePos = m_AppearPos + m_DirectPos;

	MovePosition(m_MovePos);

	// �̶� ī�޶� ���� �ۿ� ������ ���� �״´�.
	CamDistDel();
}

void Platter_FragmentsLid::CamDistDel()
{
	FLOAT4 Dir = GetScene()->GetCamPos() - GetPosition();

	// ī�޶� ���������� ������ ���� �״´�.
	if (1000.0f <= FLOAT4::Len2D(Dir))
	{
		Death();
	}
}

void Platter_FragmentsLid::DebugRender()
{

}

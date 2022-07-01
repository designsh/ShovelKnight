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
	// 현재 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 이미지 설정
	m_FragmentsLidRenderer = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::UI + 1);
	m_FragmentsLidRenderer->TransCenterSetting(L"platter2.bmp", { 29.f, 18.f });
	m_FragmentsLidRenderer->SetCutData(0);
	m_FragmentsLidRenderer->SetRenderScale({ 64, 40 });

	// 등장 파워 설정
	m_AppearPos = FLOAT4::ZERO;
	m_AppearPower = FLOAT4(0.f, -300.f);
	m_AppearGravityPower = FLOAT4(0.f, 1000.f);
}

void Platter_FragmentsLid::Update()
{
	// 등장하며 바닥으로 떨어진다.
	FragmentsLidAppear();
}

void Platter_FragmentsLid::FragmentsLidAppear()
{
	m_DirectPos = FLOAT4::ZERO;
	m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(150.f);

	// 중력적용
	m_AppearPower += m_AppearGravityPower * SGameEngineTimer::FDeltaTime();
	m_AppearPos = m_AppearPower * SGameEngineTimer::FDeltaTime();

	// 여기서 모든 벡터의 값을 더한다.
	m_MovePos = m_AppearPos + m_DirectPos;

	MovePosition(m_MovePos);

	// 이때 카메라 범위 밖에 나가면 나는 죽는다.
	CamDistDel();
}

void Platter_FragmentsLid::CamDistDel()
{
	FLOAT4 Dir = GetScene()->GetCamPos() - GetPosition();

	// 카메라 범위밖으로 나가면 나는 죽는다.
	if (1000.0f <= FLOAT4::Len2D(Dir))
	{
		Death();
	}
}

void Platter_FragmentsLid::DebugRender()
{

}

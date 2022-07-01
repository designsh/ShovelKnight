#include "Chicken.h"
#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>

// Static Var

// Static Func

// member Var
Chicken::Chicken()
	: m_WindowSize(FLOAT4::ZERO),
	m_ChickenRenderer(nullptr), m_ChickenCol(nullptr),
	m_ChickenCheckPos(FLOAT4::ZERO), m_ChickenCheckDir(), m_iChickenCheckColor(),
	m_bAppearEnd(false)
{

}

Chicken::~Chicken()
{

}

// member Func
void Chicken::Start()
{
	// 현재 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 충돌체 생성
	m_ChickenCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::UI);
	m_ChickenCol->SetScale({ 70, 50 });
	m_ChickenCol->AddStartEvent(this, &Chicken::CollisionStart);
	m_ChickenCol->AddStayEvent(this, &Chicken::CollisionStay);
	m_ChickenCol->AddEndEvent(this, &Chicken::CollisionEnd);
	m_ChickenCol->SetCheckData(1);

	// 이미지 설정
	m_ChickenRenderer = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::UI);
	m_ChickenRenderer->TransCenterSetting(L"chicken.bmp", { 27.f, 18.f });
	m_ChickenRenderer->SetCutData(0);
	m_ChickenRenderer->SetRenderScale({ 64, 40 });

	// 등장 파워 설정
	m_AppearPos = FLOAT4::ZERO;
	m_AppearPower = FLOAT4(0.f, -300.f);
	m_AppearGravityPower = FLOAT4(0.f, 1000.f);
}

void Chicken::Update()
{
	if (false == m_bAppearEnd)
	{
		m_MovePos = FLOAT4::ZERO;

		ChickenAppear();

		MovePosition(m_MovePos);
	}
}

void Chicken::ChickenPixelCheck()
{
	// 등장하면서 바닥에 닿으면 이동을 멈추기 위해서
	m_ChickenCheckPos = GetPosition() + m_MovePos;
	m_ChickenCheckDir[(int)GlobalValue::PixelCheckDirect::Left] = { m_ChickenCheckPos.ix() - 20, m_ChickenCheckPos.iy() - 20 };
	m_ChickenCheckDir[(int)GlobalValue::PixelCheckDirect::Right] = { m_ChickenCheckPos.ix() + 20, m_ChickenCheckPos.iy() - 20 };
	m_ChickenCheckDir[(int)GlobalValue::PixelCheckDirect::Top] = { m_ChickenCheckPos.ix(), m_ChickenCheckPos.iy() - 30 };
	m_ChickenCheckDir[(int)GlobalValue::PixelCheckDirect::Bottom] = { m_ChickenCheckPos.ix(), m_ChickenCheckPos.iy() + 20 };

	SGameEngineWinImage* FindImage = SGameEngineResMgr::Inst().FindImage(L"Plains.bmp");
	if (nullptr != FindImage)
	{
		for (int i = 0; i < 4; i++)
		{
			m_iChickenCheckColor[i] = FindImage->GetPixelColor(m_ChickenCheckDir[i].ix(), m_ChickenCheckDir[i].iy());
		}
	}

	if (RGB(0, 0, 0) == m_iChickenCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_bAppearEnd = true;
		m_MovePos.y = 0.0f;
	}
}

void Chicken::ChickenAppear()
{
	// 중력적용
	m_AppearPower += m_AppearGravityPower * SGameEngineTimer::FDeltaTime();
	m_AppearPos = m_AppearPower * SGameEngineTimer::FDeltaTime();

	// 여기서 모든 벡터의 값을 더한다.
	m_MovePos = m_AppearPos;

	ChickenPixelCheck();
}

void Chicken::DebugRender()
{
	FLOAT4 ChickenPixelLeft = m_ChickenCheckDir[0] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), ChickenPixelLeft.ix() - 2, ChickenPixelLeft.iy() - 2, ChickenPixelLeft.ix() + 2, ChickenPixelLeft.iy() + 2);

	FLOAT4 ChickenPixelRight = m_ChickenCheckDir[1] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), ChickenPixelRight.ix() - 2, ChickenPixelRight.iy() - 2, ChickenPixelRight.ix() + 2, ChickenPixelRight.iy() + 2);

	FLOAT4 ChickenPixelTop = m_ChickenCheckDir[2] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), ChickenPixelTop.ix() - 2, ChickenPixelTop.iy() - 2, ChickenPixelTop.ix() + 2, ChickenPixelTop.iy() + 2);

	FLOAT4 ChickenPixelBot = m_ChickenCheckDir[3] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), ChickenPixelBot.ix() - 2, ChickenPixelBot.iy() - 2, ChickenPixelBot.ix() + 2, ChickenPixelBot.iy() + 2);

	Col2DData PlatterColData;
	PlatterColData.m_Pos = GetCamPosition() - m_ChickenCol->GetPivotPos();
	PlatterColData.m_Size = m_ChickenCol->GetScale();
	RECT PlatterColRect = { PlatterColData.iLeft(), PlatterColData.iTop(), PlatterColData.iRight(), PlatterColData.iBottom() };
	if (true == m_ChickenCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &PlatterColRect, SGameEngineWindow::GetGreenBrush());
	}
}

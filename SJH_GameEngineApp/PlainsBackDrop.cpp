#include "PlainsBackDrop.h"
#include <SGameEngineResMgr.h>
#include <SGameEngineWindow.h>
#include <SGameEngineDebug.h>
#include <Windows.h>

#include "GlobalValue.h"

// Static Var

// Static Func

// member Var
PlainsBackDrop::PlainsBackDrop() : m_SkyBackGround(nullptr), m_WindowSize(), m_Frame(0), m_CastleBackGround(nullptr), m_LightTreeBackGround(nullptr), m_ThickTreeBackGround(nullptr)
{

}

PlainsBackDrop::~PlainsBackDrop()
{

}

// member Func
void PlainsBackDrop::Start()
{
	// 키생성
	SGameEngineInput::CreateKey(L"BackDropOff", 'C');
	SGameEngineInput::CreateKey(L"BackDropOn", 'V');

	// 윈도우 크기가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	m_SkyBackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::SkyBackGround);
	m_SkyBackGround->TransCenterSetting(L"SkyBackDrop.bmp", { 1280.f, 720.f });
	 m_SkyBackGround->SetPivotPos({ m_WindowSize.x * 0.5f , m_WindowSize.y * 0.5f });
	 m_SkyBackGround->CamEffectOff();

	m_CastleBackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::CastleBackGround);
	m_CastleBackGround->TransCenterSetting(L"CastleBackDrop.bmp", { 1280.f, 720.f });
	m_CastleBackGround->SetPivotPos({ m_WindowSize.x * 0.5f , m_WindowSize.y * 0.5f });
	m_CastleBackGround->CamEffectOff();

	// 아래 두개만 카메라 스케일을 설정해야함
	// 단, 위치를 다 잡아놔야할듯
	// 현재는 카메라이펙트를 꺼서 이미지한개로만 대체
	m_LightTreeBackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::LightTreeBackGround);
	m_LightTreeBackGround->TransCenterSetting(L"Tree_BackDrop.bmp", { 1280.f, 720.f });
	m_LightTreeBackGround->SetPivotPos({ m_WindowSize.x * 0.5f , m_WindowSize.y * 0.5f });
	m_LightTreeBackGround->CamEffectOff();
	//m_LightTreeBackGround->SetCamEffectScale(0.8f);

	m_ThickTreeBackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::ThickTreeBackGound);
	m_ThickTreeBackGround->TransCenterSetting(L"Tree2_BackDrop.bmp", { 1280.f, 720.f });
	m_ThickTreeBackGround->SetPivotPos({ m_WindowSize.x * 0.5f , m_WindowSize.y * 0.5f });
	m_ThickTreeBackGround->CamEffectOff();
	//m_ThickTreeBackGround->SetCamEffectScale(0.6f);

	// 충돌맵과 동일하게하여 배경을 깐다
	// 초기위치 ( 0, 2160)
	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 0.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 0.f) + (m_WindowSize.y * 0.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 1.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 0.f) + (m_WindowSize.y * 0.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 2.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 0.f) + (m_WindowSize.y * 0.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 3.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 0.f) + (m_WindowSize.y * 0.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 4.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 0.f) + (m_WindowSize.y * 0.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 5.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 0.f) + (m_WindowSize.y * 0.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 5.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 1.f) + (m_WindowSize.y * 0.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 6.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 1.f) + (m_WindowSize.y * 0.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 7.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 1.f) + (m_WindowSize.y * 0.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 7.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 1.f) + (m_WindowSize.y * 1.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 7.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 1.f) + (m_WindowSize.y * 2.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 7.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 1.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 7.f) - (m_WindowSize.x * 1.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 1.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 8.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 1.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 9.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 1.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 10.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 1.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 10.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 2.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 11.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 2.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 12.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 2.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 10.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 3.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 10.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 4.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 11.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 4.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 12.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 4.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 13.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 4.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 14.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 4.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 14.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 5.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 14.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 6.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 14.f) - (m_WindowSize.x * 1.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 6.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 14.f) - (m_WindowSize.x * 2.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 6.f) + (m_WindowSize.y * 3.f) });

	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 15.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 6.f) + (m_WindowSize.y * 3.f) });

	//// 최종 보스방
	//m_BackGround = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::BackGround);
	//m_BackGround->TransCenterSetting(L"Plains_BackDrop.bmp", { 1280.f, 720.f });
	//m_BackGround->SetPivotPos({ m_WindowSize.x * 0.5f + (m_WindowSize.x * 16.f) - (m_WindowSize.x * 0.f), m_WindowSize.y * 0.5f + 2160.f - (m_WindowSize.y * 6.f) + (m_WindowSize.y * 3.f) });
}

void PlainsBackDrop::Update()
{
	if (true == SGameEngineInput::IsPress(L"BackDropOff"))
	{
		m_SkyBackGround->Off();
		m_CastleBackGround->Off();
		m_LightTreeBackGround->Off();
		m_ThickTreeBackGround->Off();
	}

	if (true == SGameEngineInput::IsPress(L"BackDropOn"))
	{
		m_SkyBackGround->On();
		m_CastleBackGround->On();
		m_LightTreeBackGround->On();
		m_ThickTreeBackGround->On();
	}
}

void PlainsBackDrop::DebugRender()
{

}

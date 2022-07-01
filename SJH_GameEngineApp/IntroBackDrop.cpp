#include "IntroBackDrop.h"
#include "SGameCore.h"

#include <SGameEngineResMgr.h>
#include <SGameEngineWindow.h>
#include <SGameEngineDebug.h>
#include <Windows.h>

// Static Var

// Static Func

// member Var
IntroBackDrop::IntroBackDrop()
	: m_WindowSize(), m_IntroTimer(), m_IntroImage1(nullptr), m_IntroImage2(nullptr),
	m_IntroImage3(nullptr), m_IntroImage4(nullptr), m_IntroImage5(nullptr), m_IntroImage6(nullptr),
	m_IntroImage7(nullptr), m_Alpha(0.0f), m_CastAlpha(0), m_FadeStop(false), m_FadeOutTimer(), m_FadeImage(nullptr)
{

}

IntroBackDrop::~IntroBackDrop()
{

}

// member Func
void IntroBackDrop::Start()
{
	// 현재 윈도우의 크기를 가져온다.
	m_WindowSize = SGameEngineWindow::GetSize();

	// 각 인트로 이미지를 생성하고 랜더링 Off한다.
	m_IntroImage1 = CreateRenderer<SGameEngineRendererBasic>(6);
	m_IntroImage1->TransSetting(L"Intro1.bmp", { m_WindowSize.x, m_WindowSize.y });
	m_IntroImage1->Off();

	m_IntroImage2 = CreateRenderer<SGameEngineRendererBasic>(5);
	m_IntroImage2->TransSetting(L"Intro2.bmp", { m_WindowSize.x, m_WindowSize.y });
	m_IntroImage2->Off();

	m_IntroImage3 = CreateRenderer<SGameEngineRendererBasic>(4);
	m_IntroImage3->TransSetting(L"Intro3.bmp", { m_WindowSize.x, m_WindowSize.y });
	m_IntroImage3->Off();

	m_IntroImage4 = CreateRenderer<SGameEngineRendererBasic>(3);
	m_IntroImage4->TransSetting(L"Intro4.bmp", { m_WindowSize.x, m_WindowSize.y });
	m_IntroImage4->Off();

	m_IntroImage5 = CreateRenderer<SGameEngineRendererBasic>(2);
	m_IntroImage5->TransSetting(L"Intro5.bmp", { m_WindowSize.x, m_WindowSize.y });
	m_IntroImage5->Off();

	m_IntroImage6 = CreateRenderer<SGameEngineRendererBasic>(1);
	m_IntroImage6->TransSetting(L"Intro6.bmp", { m_WindowSize.x, m_WindowSize.y });
	m_IntroImage6->Off();

	m_IntroImage7 = CreateRenderer<SGameEngineRendererBasic>(0);
	m_IntroImage7->TransSetting(L"Intro7.bmp", { m_WindowSize.x, m_WindowSize.y });
	m_IntroImage7->Off();

	m_FadeImage = CreateRenderer<SGameEngineRendererBasic>(100);
	m_FadeImage->TransCenterSetting(L"FadeInOut.bmp", { m_WindowSize.x, m_WindowSize.y }, { m_WindowSize.x * 0.5f, m_WindowSize.y * 0.5f });

	//m_IntroTimer.CreateTimeEvent(3.0f, this, &IntroBackDrop::IntroCut1End);
	m_IntroTimer.CreateTimeEvent(3.0f, this, nullptr, &IntroBackDrop::IntroCut1Start, &IntroBackDrop::IntroCut1Stay, &IntroBackDrop::IntroCut1Stop);
	m_IntroTimer.CreateTimeEvent(3.0f, this, nullptr, &IntroBackDrop::IntroCut2Start, &IntroBackDrop::IntroCut2Stay, &IntroBackDrop::IntroCut2Stop);
	m_IntroTimer.CreateTimeEvent(3.0f, this, nullptr, &IntroBackDrop::IntroCut3Start, &IntroBackDrop::IntroCut3Stay, &IntroBackDrop::IntroCut3Stop);
	m_IntroTimer.CreateTimeEvent(3.0f, this, nullptr, &IntroBackDrop::IntroCut4Start, &IntroBackDrop::IntroCut4Stay, &IntroBackDrop::IntroCut4Stop);
	m_IntroTimer.CreateTimeEvent(3.0f, this, nullptr, &IntroBackDrop::IntroCut5Start, &IntroBackDrop::IntroCut5Stay, &IntroBackDrop::IntroCut5Stop);
	m_IntroTimer.CreateTimeEvent(3.0f, this, nullptr, &IntroBackDrop::IntroCut6Start, &IntroBackDrop::IntroCut6Stay, &IntroBackDrop::IntroCut6Stop);
	m_IntroTimer.CreateTimeEvent(3.0f, this, nullptr, &IntroBackDrop::IntroCut7Start, &IntroBackDrop::IntroCut7Stay, &IntroBackDrop::IntroCut7Stop);

	// Scene Change
	m_IntroTimer.CreateTimeEvent(2.0f, this, &IntroBackDrop::SceneChange);
}

void IntroBackDrop::Update()
{
	// 함수포인터를 이용하여 리스트에서 해당하는 함수를 실행한다.
	m_IntroTimer.Update();
}

//---------------------------- Intro Func ----------------------------//
void IntroBackDrop::IntroCut1Start()
{
	m_IntroImage1->On();
	m_FadeImage->On();

	m_Alpha = 2.55f;
	m_CastAlpha = 255;
	m_FadeStop = false;
}

void IntroBackDrop::IntroCut1Stay()
{
	m_Alpha -= SGameEngineTimer::MainTimer.FDeltaTime();

	if (0.0f >= m_Alpha)
	{
		m_Alpha = 0.0f;
		m_CastAlpha = 0;
		m_FadeStop = true;
		m_IntroImage1->Off();
		m_FadeImage->Off();
	}
	else
	{
		m_CastAlpha = static_cast<unsigned char>(m_Alpha * 100.f);
	}

	m_FadeImage->SetAlpha(m_CastAlpha);
}

bool IntroBackDrop::IntroCut1Stop()
{
	return m_FadeStop;
}

void IntroBackDrop::IntroCut2Start()
{
	m_IntroImage1->Off();
	m_IntroImage2->On();
	m_FadeImage->On();

	m_Alpha = 2.55f;
	m_CastAlpha = 255;
	m_FadeStop = false;
}

void IntroBackDrop::IntroCut2Stay()
{
	m_Alpha -= SGameEngineTimer::MainTimer.FDeltaTime();

	if (0.0f >= m_Alpha)
	{
		m_Alpha = 0.0f;
		m_CastAlpha = 0;
		m_FadeStop = true;
		m_IntroImage2->Off();
		m_FadeImage->Off();
	}
	else
	{
		m_CastAlpha = static_cast<unsigned char>(m_Alpha * 100.f);
	}

	m_FadeImage->SetAlpha(m_CastAlpha);
}

bool IntroBackDrop::IntroCut2Stop()
{
	return m_FadeStop;
}

void IntroBackDrop::IntroCut3Start()
{
	m_IntroImage3->On();
	m_FadeImage->On();

	m_Alpha = 2.55f;
	m_CastAlpha = 255;
	m_FadeStop = false;
}

void IntroBackDrop::IntroCut3Stay()
{
	m_Alpha -= SGameEngineTimer::MainTimer.FDeltaTime();

	if (0.0f >= m_Alpha)
	{
		m_Alpha = 0.0f;
		m_CastAlpha = 0;
		m_FadeStop = true;
		m_IntroImage3->Off();
		m_FadeImage->Off();
	}
	else
	{
		m_CastAlpha = static_cast<unsigned char>(m_Alpha * 100.f);
	}

	m_FadeImage->SetAlpha(m_CastAlpha);
}

bool IntroBackDrop::IntroCut3Stop()
{
	return m_FadeStop;
}

void IntroBackDrop::IntroCut4Start()
{
	m_IntroImage4->On();
	m_FadeImage->On();

	m_Alpha = 2.55f;
	m_CastAlpha = 255;
	m_FadeStop = false;
}

void IntroBackDrop::IntroCut4Stay()
{
	m_Alpha -= SGameEngineTimer::MainTimer.FDeltaTime();

	if (0.0f >= m_Alpha)
	{
		m_Alpha = 0.0f;
		m_CastAlpha = 0;
		m_FadeStop = true;
		m_IntroImage4->Off();
		m_FadeImage->Off();
	}
	else
	{
		m_CastAlpha = static_cast<unsigned char>(m_Alpha * 100.f);
	}

	m_FadeImage->SetAlpha(m_CastAlpha);
}

bool IntroBackDrop::IntroCut4Stop()
{
	return m_FadeStop;
}

void IntroBackDrop::IntroCut5Start()
{
	m_IntroImage5->On();
	m_FadeImage->On();

	m_Alpha = 2.55f;
	m_CastAlpha = 255;
	m_FadeStop = false;
}

void IntroBackDrop::IntroCut5Stay()
{
	m_Alpha -= SGameEngineTimer::MainTimer.FDeltaTime();

	if (0.0f >= m_Alpha)
	{
		m_Alpha = 0.0f;
		m_CastAlpha = 0;
		m_FadeStop = true;
		m_IntroImage5->Off();
		m_FadeImage->Off();
	}
	else
	{
		m_CastAlpha = static_cast<unsigned char>(m_Alpha * 100.f);
	}

	m_FadeImage->SetAlpha(m_CastAlpha);
}

bool IntroBackDrop::IntroCut5Stop()
{
	return m_FadeStop;
}

void IntroBackDrop::IntroCut6Start()
{
	m_IntroImage6->On();
	m_FadeImage->On();

	m_Alpha = 2.55f;
	m_CastAlpha = 255;
	m_FadeStop = false;
}

void IntroBackDrop::IntroCut6Stay()
{
	m_Alpha -= SGameEngineTimer::MainTimer.FDeltaTime();

	if (0.0f >= m_Alpha)
	{
		m_Alpha = 0.0f;
		m_CastAlpha = 0;
		m_FadeStop = true;
		m_IntroImage6->Off();
		m_FadeImage->Off();
	}
	else
	{
		m_CastAlpha = static_cast<unsigned char>(m_Alpha * 100.f);
	}

	m_FadeImage->SetAlpha(m_CastAlpha);
}

bool IntroBackDrop::IntroCut6Stop()
{
	return m_FadeStop;
}

void IntroBackDrop::IntroCut7Start()
{
	m_IntroImage7->On();
	m_FadeImage->On();

	m_Alpha = 2.55f;
	m_CastAlpha = 255;
	m_FadeStop = false;
}

void IntroBackDrop::IntroCut7Stay()
{
	m_Alpha -= SGameEngineTimer::MainTimer.FDeltaTime();

	if (0.0f >= m_Alpha)
	{
		m_Alpha = 0.0f;
		m_CastAlpha = 0;
		m_FadeStop = true;
		m_IntroImage7->Off();
		m_FadeImage->Off();
	}
	else
	{
		m_CastAlpha = static_cast<unsigned char>(m_Alpha * 100.f);
	}

	m_FadeImage->SetAlpha(m_CastAlpha);
}

bool IntroBackDrop::IntroCut7Stop()
{
	return m_FadeStop;
}

//---------------------------- Scene Change Func ----------------------------//
void IntroBackDrop::SceneChange()
{
	SGameCore::SceneManager.ChangeScene(L"Plains");
}

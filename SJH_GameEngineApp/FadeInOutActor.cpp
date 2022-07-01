#include "FadeInOutActor.h"
#include <SGameEngineTimer.h>

// Static Var
bool FadeInOutActor::m_FadeInOutStart = false;
bool FadeInOutActor::m_FadeEnd = false;

// Static Func
void FadeInOutActor::FadeStartFlagOn()
{
	m_FadeInOutStart = true;
}

bool FadeInOutActor::GetFadeEnd()
{
	return m_FadeEnd;
}

// member Var
FadeInOutActor::FadeInOutActor()
	: m_Renderer(nullptr), m_FadeInTimer(), m_FadeOutTimer(), m_Alpha(0.0f), m_CastAlpha(),
	m_FadeType(FADE_TYPE::NONE), m_FadeStop(false)
{

}

FadeInOutActor::~FadeInOutActor()
{

}

// member Func
void FadeInOutActor::Start()
{
	// 인트로 장면 전환 시 페이드인 페이드아웃 효과 적용
	m_Renderer = CreateRenderer<SGameEngineRendererBasic>(1000000);
	m_Renderer->CamEffectOff();
	m_Renderer->TransCenterSetting(L"Enchantress_FadeInOut.bmp", { 1280.f, 720.f });
	m_Renderer->SetPivotPos({ 1280.f * 0.5f, 720.f * 0.5f });
	m_Renderer->Off();

	//m_FadeInTimer.CreateTimeEvent(3.0f, this, nullptr, &FadeInOutActor::FadeInStart, &FadeInOutActor::FadeIn, &FadeInOutActor::FadeStop);
	m_FadeInTimer.CreateTimeEvent(5.0f, this, &FadeInOutActor::FadeInEnd, &FadeInOutActor::FadeInStart, &FadeInOutActor::FadeIn);
	m_FadeOutTimer.CreateTimeEvent(10.0f, this, nullptr, &FadeInOutActor::FadeOutStart, &FadeInOutActor::FadeOut, &FadeInOutActor::FadeStop);
}

void FadeInOutActor::Update()
{
	if (true == m_FadeInOutStart)
	{
		switch (m_FadeType)
		{
			case FADE_TYPE::FADEIN:
			{
				m_FadeInTimer.Update();
				break;
			}
			case FADE_TYPE::FADEOUT:
			{
				m_FadeOutTimer.Update();
				break;
			}
			case FADE_TYPE::FADEINOUT:
			{
				m_FadeInTimer.Update();
				m_FadeOutTimer.Update();
				break;
			}
			case FADE_TYPE::NONE:
			{
				SGameEngineDebug::AssertMsg(L"case FADE_TYPE::NONE:");
				break;
			}
		}
	}
}

void FadeInOutActor::FadeInStart()
{
	m_Renderer->On();
	m_Alpha = 0.f;
	m_CastAlpha = 0;
}

void FadeInOutActor::FadeIn()
{
	m_Alpha += SGameEngineTimer::MainTimer.FDeltaTime();

	if (2.55f <= m_Alpha)
	{
		m_Alpha = 2.55f;
		m_CastAlpha = 255;
		m_FadeStop = true;
	}
	else
	{
		m_CastAlpha = static_cast<unsigned char>(m_Alpha * 100.f);
	}

	m_Renderer->SetAlpha(m_CastAlpha);
}

void FadeInOutActor::FadeOutStart()
{
	m_Alpha = 2.55f;
	m_CastAlpha = 255;
}

void FadeInOutActor::FadeOut()
{
	m_Alpha -= SGameEngineTimer::MainTimer.FDeltaTime();

	if (0.0f >= m_Alpha)
	{
		m_Alpha = 0.0f;
		m_CastAlpha = 0;
		m_FadeStop = true;
	}
	else
	{
		m_CastAlpha = static_cast<unsigned char>(m_Alpha * 100.f);
	}

	m_Renderer->SetAlpha(m_CastAlpha);
}

bool FadeInOutActor::FadeStop()
{
	m_FadeInOutStart = false;
	m_FadeEnd = true;
	m_Renderer->Off();

	return m_FadeStop;
}

void FadeInOutActor::FadeInEnd()
{
	m_FadeInOutStart = false;
	m_FadeEnd = true;
	m_Renderer->Off();
}

void FadeInOutActor::SetFadeType(const FADE_TYPE& _FadeType)
{
	m_FadeType = _FadeType;
}



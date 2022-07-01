#include "TitleEffect.h"
#include <SGameEngineResMgr.h>
#include <SGameEngineDebug.h>
#include <SGameEngineWindow.h>
#include <Windows.h>

#include "TitleBackDrop.h"


// Static Var

// Static Func

// member Var
TitleEffect::TitleEffect() : m_AniRenderer(), m_UpdateTime(0.45f), WindowSize(), m_RandomX(0.0f), m_RandomY(0.0f)
{

}

TitleEffect::~TitleEffect()
{

}

// member Func
void TitleEffect::Start()
{
	m_AniRenderer = CreateRenderer<SGameEngineRendererAnimation>(4);
	m_AniRenderer->SetRenderScale({ 50, 50 });
	m_AniRenderer->SetPivotPos({ 680.f, 320.f });
	m_AniRenderer->CreateAnimation(L"Effect", L"Game Title Effect.bmp", 0, 4, 0.08f, false);
	m_AniRenderer->ChangeAnimation(L"Effect");
}

void TitleEffect::Update()
{
	m_UpdateTime -= SGameEngineTimer::MainTimer.GetFDeltaTime();
	if (0.0f >= m_UpdateTime)
	{
		// 랜덤으로 화면에 뿌린다.
		// 타이틀이름에서 표시되어야하기때문에
		// 위치계산이 필요함
		if (m_RandomX > 600.f)
		{
			m_RandomX = static_cast<float>(rand() % (WindowSize.ix() - TitleBackDrop::GetImageChSize().ix())) + 300;
		}
		else
		{
			m_RandomX = static_cast<float>(rand() % (WindowSize.ix() - TitleBackDrop::GetImageChSize().ix())) + 600;
		}
		m_RandomY = static_cast<float>(rand() % (WindowSize.iy() - TitleBackDrop::GetImageChSize().iy()));

		m_AniRenderer->SetRenderScale({ 50, 50 });
		m_AniRenderer->SetPivotPos({ m_RandomX, m_RandomY });
		m_AniRenderer->ChangeAnimation(L"Effect");

		m_UpdateTime = 0.45f;
	}
}
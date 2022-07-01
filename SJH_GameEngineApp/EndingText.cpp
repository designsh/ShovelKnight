#include "EndingText.h"
#include <SGameEngineWindow.h>

#include "GlobalValue.h"

// Static Var

// Static Func

// member Var
EndingText::EndingText()
	: m_WindowSize(FLOAT4::ZERO),
	m_AniEndingText(nullptr), m_EndingTextFSM()
{

}

EndingText::~EndingText()
{

}

// member Func
void EndingText::Start()
{
	// 윈도우크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 애니메이션 생성
	m_AniEndingText = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniEndingText->SetRenderScale({ 800, 800 });
	m_AniEndingText->CreateAnimation(L"TheEndText_Start", L"TheEnd_TextImage.bmp", 0, 99, 0.1f, false);

	// FSM 생성
	m_EndingTextFSM.CreateState(L"Ending_SceneStart", this, &EndingText::SceneStay, &EndingText::SceneStart, &EndingText::SceneEnd);
	m_EndingTextFSM.ChangeState(L"Ending_SceneStart");
}

void EndingText::Update()
{
	m_EndingTextFSM.Update();
}

void EndingText::DebugRender()
{

}

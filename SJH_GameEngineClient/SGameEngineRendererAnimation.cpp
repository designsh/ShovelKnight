#include "SGameEngineRendererAnimation.h"
#include "SGameEngineResMgr.h"
#include <SGameEngineWinImage.h>
#include <SGameEngineDebug.h>
#include <SGameEngineWindow.h>

// Inner Class
SGameEngineRendererAnimation::Animation::Animation()
	: m_Image(nullptr),
	m_FrameTime(0.1f),
	m_CurTime(0.0f),
	m_StartFrame(-1),
	m_EndFrame(-1),
	m_CurFrame(-1),
	m_IsLoop(true),
	m_TransColor()
{
	
}

SGameEngineRendererAnimation::Animation::~Animation()
{

}

void SGameEngineRendererAnimation::Animation::Update()
{
	m_CurTime -= SGameEngineTimer::FDeltaTime();
	if (0.0f >= m_CurTime)
	{
		m_CurTime = m_FrameTime;
		++m_CurFrame;
		if (m_CurFrame > m_EndFrame)
		{
			if (true == m_IsLoop)
			{
				m_CurFrame = m_StartFrame;
			}
			else
			{
				--m_CurFrame;
			}
		}
	}
}

void SGameEngineRendererAnimation::Animation::Reset()
{
	m_CurTime = m_FrameTime;
	m_CurFrame = m_StartFrame;
}

bool SGameEngineRendererAnimation::Animation::IsEnd()
{
	return m_CurFrame == m_EndFrame;
}

// Static Var

// Static Func

// member Var
SGameEngineRendererAnimation::SGameEngineRendererAnimation()
	: m_Animation(), m_CurAnimation(nullptr), m_ChangeAnim(nullptr)
{
	m_RenderType = RENDERINGMODE::TRANSCENTER;
}

SGameEngineRendererAnimation::~SGameEngineRendererAnimation()
{

}

// member Func
SGameEngineRendererAnimation::Animation* SGameEngineRendererAnimation::FindAnimation(const SGameEngineString& _Name)
{
	if (m_Animation.end() == m_Animation.find(_Name))
	{
		return nullptr;
	}

	// map을 m_Animation[_Name]이런 형식으로사용하게 되면
	// insert와 find를 동시에 수행한다.
	return &m_Animation[_Name];
}

void SGameEngineRendererAnimation::CreateAnimation(const SGameEngineString& _AniName, const SGameEngineString& _ImageName, int _Start, int _End, float _FrameTime /*= 0.1f*/, bool _Loop /*= true*/)
{
	// 해당 이미지가 없으면 터뜨리고
	SGameEngineWinImage* FindImage = SGameEngineResMgr::Inst().FindImage(_ImageName);
	if (nullptr == FindImage)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == FindImage)");
		return;
	}

	// 자르려는 이미지크기가 0보다 작거나같으면 터뜨리고
	if (0 >= FindImage->GetCutSize())
	{
		SGameEngineDebug::AssertMsg(L"if (0 >= FindImage->GetCutSize())");
		return;
	}

	// 
	if (0 > _Start || 0 > _End ||
		_Start >= FindImage->GetCutSize() || _End >= FindImage->GetCutSize() ||
		_End < _Start)
	{
		SGameEngineDebug::AssertMsg(L"_Start And _End Error");
		return;
	}

	// 해당 애니메이션이 존재하므로 터뜨린다.
	if (nullptr != FindAnimation(_AniName))
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr != FindAnimation(_AniName))");
		return;
	}

	// 위의 조건이 모두 만족하다면
	// 애니메이션을 만들어낸다.
	Animation& NewAnimation = m_Animation[_AniName];
	NewAnimation.m_Image = FindImage;
	NewAnimation.m_EndFrame = _End;
	NewAnimation.m_StartFrame = _Start;
	NewAnimation.m_FrameTime = _FrameTime;
	NewAnimation.m_IsLoop = _Loop;
	NewAnimation.Reset();
}

void SGameEngineRendererAnimation::ChangeAnimationContinue(const SGameEngineString& _AniName)
{
	// 이동일때 이것으로 체크해서 한다.
	m_ChangeAnim = FindAnimation(_AniName);
	if (nullptr == m_ChangeAnim)
	{
		SGameEngineDebug::AssertMsg("if (nullptr == m_ChangeAnim)");
	}

	if (m_CurAnimation == m_ChangeAnim)
	{
		return;
	}
	m_CurAnimation = m_ChangeAnim;
	m_CurAnimation->Reset();
}

void SGameEngineRendererAnimation::ChangeAnimation(const SGameEngineString& _AniName)
{
	// 기본적인 애니메이션은 이것으로 처리한다.
	m_CurAnimation = FindAnimation(_AniName);
	m_CurAnimation->Reset();
	if (nullptr == m_CurAnimation)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_CurAnimation)");
		return;
	}
}

void SGameEngineRendererAnimation::Render()
{
	// 현재 애니메이션이 없으면 터뜨린다.
	if (nullptr == m_CurAnimation)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_CurAnimation)");
		return;
	}

	m_CurAnimation->Update();

	const CutData& Data = m_CurAnimation->m_Image->GetCutData(m_CurAnimation->m_CurFrame);
	m_CutPos = Data.m_Pos;
	m_CutSize = Data.m_Size;
	RennderImage(m_CurAnimation->m_Image);
}

bool SGameEngineRendererAnimation::IsEnd()
{
	return m_CurAnimation->IsEnd();
}

int SGameEngineRendererAnimation::GetEndFrame()
{
	// 현재 애니메이션이 없으면 터뜨린다.
	if (nullptr == m_CurAnimation)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_CurAnimation)");
		return 0;
	}

	return m_CurAnimation->m_EndFrame;
}

int SGameEngineRendererAnimation::GetCurFrame()
{
	// 현재 애니메이션이 없으면 터뜨린다.
	if (nullptr == m_CurAnimation)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_CurAnimation)");
		return 0;
	}

	return m_CurAnimation->m_CurFrame;
}

int SGameEngineRendererAnimation::GetStartFrame()
{
	// 현재 애니메이션이 없으면 터뜨린다.
	if (nullptr == m_CurAnimation)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_CurAnimation)");
		return 0;
	}

	return m_CurAnimation->m_StartFrame;
}

SGameEngineWinImage* SGameEngineRendererAnimation::GetImage()
{
	// 현재 애니메이션이 없으면 터뜨린다.
	if (nullptr == m_CurAnimation)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_CurAnimation)");
		return 0;
	}

	return m_CurAnimation->m_Image;
}

void SGameEngineRendererAnimation::SetLoop(bool _Loop)
{
	// 현재 애니메이션이 없으면 터뜨린다.
	if (nullptr == m_CurAnimation)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_CurAnimation)");
		return;
	}

	m_CurAnimation->m_IsLoop = _Loop;
}

void SGameEngineRendererAnimation::SetCurFrame(int _Frame)
{
	// 현재 애니메이션이 없으면 터뜨린다.
	if (nullptr == m_CurAnimation)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_CurAnimation)");
		return;
	}

	if (m_CurAnimation->m_EndFrame < _Frame)
	{
		SGameEngineDebug::AssertMsg(L"if (m_CurAnimation->m_EndFrame < _Frame)");
		return;
	}

	m_CurAnimation->m_CurFrame = _Frame;
}





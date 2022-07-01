#include "SGameEngineRendererBasic.h"
#include "SGameEngineResMgr.h"
#include <SGameEngineDebug.h>
#include <SGameEngineWindow.h>
#include <SGameEngineTimer.h>

// Static Var

// Static Func

// member Var
SGameEngineRendererBasic::SGameEngineRendererBasic() : m_Image(nullptr)
{

}

SGameEngineRendererBasic::~SGameEngineRendererBasic()
{

}

// member Func
void SGameEngineRendererBasic::SetCutData(int _Index)
{
    if (nullptr == m_Image)
    {
        SGameEngineDebug::AssertMsg(L"if (nullptr == m_Image)");
    }

    const CutData& Data = m_Image->GetCutData(_Index);

    m_CutPos = Data.m_Pos;
    m_CutSize = Data.m_Size;
}

void SGameEngineRendererBasic::SetCutPosAndSize(const FLOAT4& _Pos, const FLOAT4& _Size)
{
    m_CutPos = _Pos;
    m_CutSize = _Size;
}

FLOAT4 SGameEngineRendererBasic::GetCutPos()
{
    return m_CutPos;
}

void SGameEngineRendererBasic::SetCutPos(FLOAT4 _CutPos)
{
    m_CutPos = _CutPos;
}

FLOAT4 SGameEngineRendererBasic::GetCutSize()
{
    return m_CutSize;
}

void SGameEngineRendererBasic::SetCutSize(FLOAT4 _CutSize)
{
    m_CutSize = _CutSize;
}

void SGameEngineRendererBasic::NoneSetting(const SGameEngineString& _Image, int _TransRgb)
{
    m_Image = SGameEngineResMgr::Inst().FindImage(_Image);
    if (nullptr == m_Image)
    {
        SGameEngineDebug::AssertMsg(L"f (nullptr == m_Image)");
        return;
    }

    m_Image->SetTransColor(_TransRgb);
    m_RenderType = RENDERINGMODE::NONE;
}

void SGameEngineRendererBasic::TransSetting(const SGameEngineString& _Image, FLOAT4 _Scale, FLOAT4 __PivotPos)
{
    m_Image = SGameEngineResMgr::Inst().FindImage(_Image);
    if (nullptr == m_Image)
    {
        SGameEngineDebug::AssertMsg(L"f (nullptr == m_Image)");
        return;
    }
    
    m_RenderScale = _Scale;
    m_RenderType = RENDERINGMODE::TRANS;
}

void SGameEngineRendererBasic::TransCenterSetting(const SGameEngineString& _Image, FLOAT4 _Scale, FLOAT4 _PivotPos)
{
    m_Image = SGameEngineResMgr::Inst().FindImage(_Image);
    if (nullptr == m_Image)
    {
        SGameEngineDebug::AssertMsg(L"f (nullptr == m_Image)");
        return;
    }

    m_RenderScale = _Scale;
    m_PivotPos = _PivotPos;
    m_RenderType = RENDERINGMODE::TRANSCENTER;
}

void SGameEngineRendererBasic::RotImageSetting(const SGameEngineString& _Image, const SGameEngineString& _MaskImage, FLOAT4 _Scale, FLOAT4 _PivotPos)
{
    TransSetting(_Image, _Scale, _PivotPos);
    SetMaskImage(_MaskImage);
}

void SGameEngineRendererBasic::Render()
{
    RennderImage(m_Image);
}




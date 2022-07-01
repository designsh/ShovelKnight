#include "SGameEngineRenderer.h"
#include <SGameEngineWindow.h>
#include "SGameEngineResMgr.h"

// Static Var

// Static Func

// member Var
SGameEngineRenderer::SGameEngineRenderer() 
	: m_Actor(), m_iOrder(), m_IsCamEffect(true), m_RenderType(RENDERINGMODE::MAX),
	m_Alpha(255), m_CutPos(), m_CutSize(-1, -1), m_fCamEffectScale(1.0f), m_Angle(0.0f), m_MaskImage()
{

}

SGameEngineRenderer::~SGameEngineRenderer()
{

}

// member Func
void SGameEngineRenderer::SetCamEffectScale(float _Scale)
{
    m_fCamEffectScale = _Scale;
}

 // Order ���� �� ��������
void SGameEngineRenderer::SetOrder(int _Order)
{
	m_iOrder = _Order;
}

int SGameEngineRenderer::GetOrder()
{
	return m_iOrder;
}

// Actor ���� �� ��������
void SGameEngineRenderer::SetActor(SGameEngineActor* _Actor)
{
	m_Actor = _Actor;
}

SGameEngineActor* SGameEngineRenderer::GetActor()
{
	return m_Actor;
}

FLOAT4 SGameEngineRenderer::GetPivotPos()
{
	return m_PivotPos;
}

void SGameEngineRenderer::SetPivotPos(FLOAT4 _PivotPos)
{
	m_PivotPos = _PivotPos;
}

FLOAT4 SGameEngineRenderer::GetRenderScale()
{
	return m_RenderScale;
}

void SGameEngineRenderer::SetRenderScale(FLOAT4 _RenderScale)
{
	m_RenderScale = _RenderScale;
}

FLOAT4 SGameEngineRenderer::CamRenderPos()
{
	// True�̸� �ش� �������� ķ�� ������ �޴´�.
	if (true == m_IsCamEffect)
	{
        // m_fCamEffectScale�� ���� ī�޶� ���ߴ� ũ�Ⱑ �޶�����
        // �̸� ���� ���ٰ��� ǥ���� �� �ִ�.
		return GetActor()->GetPosition() + m_PivotPos - (GetActor()->GetScene()->GetCamPos() * m_fCamEffectScale);
	}

	// ���� ������ �ƴ϶�� ķ�� ������ ���� �ʴ´�.
	return GetActor()->GetPosition() + m_PivotPos;
}

void SGameEngineRenderer::CamEffectOff()
{
	m_IsCamEffect = false;
}

void SGameEngineRenderer::CamEffectOn()
{
	m_IsCamEffect = true;
}

bool SGameEngineRenderer::GetCamEffect()
{
	return m_IsCamEffect;
}

void SGameEngineRenderer::SetAlpha(unsigned char _Alpha)
{
	m_Alpha = _Alpha;

	if (255 > _Alpha)
	{
		m_RenderType = RENDERINGMODE::ALPHA;
	}
}

void SGameEngineRenderer::SetMaskImage(const SGameEngineString& _Image)
{
    m_MaskImage = SGameEngineResMgr::Inst().FindImage(_Image);

    if (nullptr == m_MaskImage)
    {
        SGameEngineDebug::AssertMsg(L"if (nullptr == m_Image)");
    }
}

void SGameEngineRenderer::SetAngle(float _Angle)
{
    m_Angle = _Angle;

    if (0 != m_Angle)
    {
        m_RenderType = RENDERINGMODE::ROT;
    }
}

void SGameEngineRenderer::RennderImage(SGameEngineWinImage* _Image)
{
    switch (m_RenderType)
    {
        case RENDERINGMODE::NONE:
        {
            break;
        }
        case RENDERINGMODE::BIT:
        {
            break;
        }
        case RENDERINGMODE::TRANS:
        {
            // m_PivotPos�� �������� ������ġ�� �����ϰ� ������
            // m_PivotPos�� ���� �������ְ�
            // �ش��Լ��� ó���ϸ��
            SGameEngineWindow::GetBackBufferImage().TransparentBlt(CamRenderPos(), m_RenderScale, *_Image, m_CutPos, m_CutSize);
            break;
        }
        case RENDERINGMODE::TRANSCENTER:
        {
            // m_PivotPos�� �������� ������ġ�� �����ϰ� ������
            // m_PivotPos�� ���� �������ְ�
            // �ش��Լ��� ó���ϸ��
            SGameEngineWindow::GetBackBufferImage().TransparentBltCenter(CamRenderPos(), m_RenderScale, *_Image, m_CutPos, m_CutSize);
            break;
        }
        case RENDERINGMODE::ROT:
        {
            SGameEngineWindow::GetBackBufferImage().PlgBltCenter(CamRenderPos(), m_RenderScale, m_Angle, *_Image, *m_MaskImage);
            break;
        }
        case RENDERINGMODE::ALPHA:
        {
            SGameEngineWindow::GetBackBufferImage().AlphaBlend(CamRenderPos(), m_RenderScale, *_Image, m_CutPos, m_CutSize, m_Alpha);
            break;
        }
        case RENDERINGMODE::MAX:
        {
            SGameEngineDebug::AssertMsg(L"case RENDERINGMODE::MAX:");
            break;
        }
    }
}

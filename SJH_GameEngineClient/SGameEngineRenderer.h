#pragma once
#include "SGameEngineActor.h"
#include <SGameEngineWinImage.h>
#include <SGameEngineObjectBase.h>


enum class RENDERINGMODE
{
    NONE,       // ��������
    BIT,
    TRANS,
    TRANSCENTER,
    ROT,          // ȸ��
    MAX,
    ALPHA,      // ���İ� ���� ���
};

// �з� :
// �뵵 : 
// ���� : 
class SGameEngineWinImage;
class SGameEngineRenderer : public SGameEngineObjectBase
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        // ���� ����Ʈ�� ������ �����Ѵ�.
        int m_iOrder;
        
        // �ڽ��� Render�Ϸ��� Actor�� �˰��ִ´�.
        SGameEngineActor* m_Actor;

        // �������� ī�޶� ũ�⸦ �˰��ִ´�.
        float m_fCamEffectScale;

    protected:
        // Rendering Type�� ������.
        RENDERINGMODE m_RenderType;

    protected:
        SGameEngineWinImage* m_MaskImage;

    protected:
        FLOAT4 m_PivotPos;        // ���� ��ǥ
        FLOAT4 m_RenderScale;  // Render ũ��
        FLOAT4 m_CutPos;          // �����̹��� ���Ϸ��� ������ǥ
        FLOAT4 m_CutSize;          // �����̹��� ���Ϸ��� ũ��

    // CamPos ��뿩�� Member Value
    // (true : On, false : Off)
    private:
        bool m_IsCamEffect;

    // Alpha Mode ��� Member Value
    protected:
        unsigned char m_Alpha;
        float m_Angle;

    public: // constructer destructer
        SGameEngineRenderer();

        // �ڽ� �Ҹ��� ȣ���� ���� ����Ҹ��ڷ� �����Ѵ�.
        virtual ~SGameEngineRenderer();

    public: // delete constructer 
        SGameEngineRenderer(const SGameEngineRenderer& _Other) = delete;
        SGameEngineRenderer(const SGameEngineRenderer&& _Other) = delete;

    public: // delete operator
        SGameEngineRenderer& operator=(const SGameEngineRenderer& _Other) = delete;
        SGameEngineRenderer& operator=(const SGameEngineRenderer&& _Other) = delete;

    public: // member Func
        // Order ���� �� ��������
        void SetOrder(int _Order);
        int GetOrder();

        // ī�޶� ���ߴ� ũ�⸦ �����Ѵ�.
        void SetCamEffectScale(float _Scale);

        // Actor ���� �� ��������
        void SetActor(SGameEngineActor* _Actor);
        SGameEngineActor* GetActor();

    public:
        // ���������Լ�
        // �Ϲ����� �����Լ��� ��üȭ(����)�� �����ϳ�,
        // ���������Լ��� ��üȭ(����)�� �Ұ����ϰ�
        // �̸� ������ Ŭ������ �߻�Ŭ������ Ī�Ѵ�.
        // �߻�Ŭ������ ��ӹ޴� �ڽ��� �ݵ�� �θ��� ���������Լ���
        // �����ؾ��Ѵ�.
        virtual void Render() = 0;
        void RennderImage(SGameEngineWinImage* _Image);

    public:
        // ���� ��ǥ ���� �� ��������
        FLOAT4 GetPivotPos();
        void SetPivotPos(FLOAT4 _PivotPos);

        // Render ũ�� ���� �� ��������
        FLOAT4 GetRenderScale();
        void SetRenderScale(FLOAT4 _RenderSize);

    public:
        FLOAT4 CamRenderPos();

    // CamPos ���� Member Function
    // �ش� �̹���(������)�� ķ�� ������ �޴��� �ȹ޴���
    public:
        void CamEffectOff();
        void CamEffectOn();
        bool GetCamEffect();

    // Alpha Mode ����
    public:
        void SetAlpha(unsigned char _Alpha);

    // ����ũ�̹��� ����
    public:
        void SetMaskImage(const SGameEngineString& _Image);
        void SetAngle(float _Angle);

};


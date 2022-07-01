#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineRendererBasic.h>

// �з� :
// �뵵 : 
// ���� : Title Game Text�� ǥ�õǴ� ����� ����Ʈ(������ǥ)�� �����ϴ� Ŭ����
class TitleEffect : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        SGameEngineRendererAnimation* m_AniRenderer;
        FLOAT4 WindowSize;

        float m_UpdateTime;
        float m_RandomX;
        float m_RandomY;

    public: // constructer destructer
        TitleEffect();
        ~TitleEffect();

    public: // delete constructer 
        TitleEffect(const TitleEffect& _Other) = delete;
        TitleEffect(const TitleEffect&& _Other) = delete;

    public: // delete operator
        TitleEffect& operator=(const TitleEffect& _Other) = delete;
        TitleEffect& operator=(const TitleEffect&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;

};


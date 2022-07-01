#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineTimeEventer.h>

// 분류 :
// 용도 : 
// 설명 : 
class IntroBackDrop : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;

    private:
        float m_Alpha;
        unsigned char m_CastAlpha;
        bool m_FadeStop;

    private:
        SGameEngineTimeEventer<IntroBackDrop> m_IntroTimer;
        SGameEngineTimeEventer<IntroBackDrop> m_FadeOutTimer;

    private:
        SGameEngineRendererBasic* m_IntroImage1;
        SGameEngineRendererBasic* m_IntroImage2;
        SGameEngineRendererBasic* m_IntroImage3;
        SGameEngineRendererBasic* m_IntroImage4;
        SGameEngineRendererBasic* m_IntroImage5;
        SGameEngineRendererBasic* m_IntroImage6;
        SGameEngineRendererBasic* m_IntroImage7;

        SGameEngineRendererBasic* m_FadeImage;

    public: // constructer destructer
        IntroBackDrop();
        ~IntroBackDrop();

    public: // delete constructer 
        IntroBackDrop(const IntroBackDrop& _Other) = delete;
        IntroBackDrop(const IntroBackDrop&& _Other) = delete;

    public: // delete operator
        IntroBackDrop& operator=(const IntroBackDrop& _Other) = delete;
        IntroBackDrop& operator=(const IntroBackDrop&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;

    // Intro Image Render On/Off
    public:
        // Intro 1 Function
        void IntroCut1Start();
        void IntroCut1Stay();
        bool IntroCut1Stop();

        // Intro 2 Function
        void IntroCut2Start();
        void IntroCut2Stay();
        bool IntroCut2Stop();

        // Intro 3 Function
        void IntroCut3Start();
        void IntroCut3Stay();
        bool IntroCut3Stop();

        // Intro 4 Function
        void IntroCut4Start();
        void IntroCut4Stay();
        bool IntroCut4Stop();

        // Intro 5 Function
        void IntroCut5Start();
        void IntroCut5Stay();
        bool IntroCut5Stop();

        // Intro 6 Function
        void IntroCut6Start();
        void IntroCut6Stay();
        bool IntroCut6Stop();

        // Intro 7 Function
        void IntroCut7Start();
        void IntroCut7Stay();
        bool IntroCut7Stop();

    // Intro Final Image -> Stage1 Scene Change
    public:
        void SceneChange();
};


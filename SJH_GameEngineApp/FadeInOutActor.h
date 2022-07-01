#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineTimeEventer.h>

enum class FADE_TYPE
{
    NONE,
    FADEIN,
    FADEOUT,
    FADEINOUT,
};

// 분류 :
// 용도 : 
// 설명 : 
class FadeInOutActor : public SGameEngineActor
{
    private: // Static Var
        static bool m_FadeInOutStart;
        static bool m_FadeEnd;

    public: // Static Func
        static void FadeStartFlagOn();
        static bool GetFadeEnd();

    private: // member Var
        SGameEngineRendererBasic* m_Renderer;
        float m_Alpha;
        unsigned char m_CastAlpha;
        bool m_FadeStop;

        SGameEngineTimeEventer<FadeInOutActor> m_FadeInTimer;
        SGameEngineTimeEventer<FadeInOutActor> m_FadeOutTimer;

        FADE_TYPE	m_FadeType;

    public: // constructer destructer
        FadeInOutActor();
        virtual ~FadeInOutActor();

    public: // delete constructer 
        FadeInOutActor(const FadeInOutActor& _Other) = delete;
        FadeInOutActor(const FadeInOutActor&& _Other) = delete;

    public: // delete operator
        FadeInOutActor& operator=(const FadeInOutActor& _Other) = delete;
        FadeInOutActor& operator=(const FadeInOutActor&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;

    public:
        void FadeInStart();
        void FadeIn();

        void FadeOutStart();
        void FadeOut();

        bool FadeStop();
        void FadeInEnd();

    public:
        void SetFadeType(const FADE_TYPE& _FadeType);

};


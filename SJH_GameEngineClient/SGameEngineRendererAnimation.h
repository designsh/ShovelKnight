#pragma once
#include "SGameEngineRenderer.h"
#include <SGameEngineWinImage.h>
#include <SGameEngineString.h>

// 분류 :
// 용도 : 
// 설명 : 
class SGameEngineRendererAnimation : public SGameEngineRenderer
{
    // Inner Class
    private:
        class Animation
        {
            public:
                SGameEngineWinImage* m_Image;
                float m_FrameTime; // 이미지 한장이 바뀌는 시간
                float m_CurTime;     // 현재 애니메이션 시간
                int m_StartFrame;    // 시작 프레임
                int m_EndFrame;     // 종료 프레임
                int m_CurFrame;     // 현재 프레임
                bool m_IsLoop;       // 루프상태(default : true)
                int m_TransColor;   // 특정색제거를 위한 특정색선정

            public:
                void Update();
                void Reset();

            public:
                bool IsEnd();

            public:
                Animation();
                ~Animation();
        };

    private: // Static Var

    public: // Static Func

    private: // member Var
        std::map<SGameEngineString, Animation> m_Animation;
        SGameEngineRendererAnimation::Animation* m_ChangeAnim;
        Animation* m_CurAnimation;

    public: // constructer destructer
        SGameEngineRendererAnimation();
        ~SGameEngineRendererAnimation();

    public: // delete constructer 
        SGameEngineRendererAnimation(const SGameEngineRendererAnimation& _Other) = delete;
        SGameEngineRendererAnimation(const SGameEngineRendererAnimation&& _Other) = delete;

    public: // delete operator
        SGameEngineRendererAnimation& operator=(const SGameEngineRendererAnimation& _Other) = delete;
        SGameEngineRendererAnimation& operator=(const SGameEngineRendererAnimation&& _Other) = delete;

    public: // member Func
        Animation* FindAnimation(const SGameEngineString& _Name);

    public:
        void CreateAnimation(const SGameEngineString& _AniName, const SGameEngineString& _ImageName, int _Start, int _End, float _FrameTime = 0.1f, bool _Loop = true);
        void ChangeAnimation(const SGameEngineString& _AniName);
        void ChangeAnimationContinue(const SGameEngineString& _AniName);

    public:
        int GetCurFrame();
        int GetStartFrame();
        int GetEndFrame();
        void SetLoop(bool _Loop);
        void SetCurFrame(int _Frame);
        SGameEngineWinImage* GetImage();

        bool IsEnd();

    public:
        void Render() override;
};


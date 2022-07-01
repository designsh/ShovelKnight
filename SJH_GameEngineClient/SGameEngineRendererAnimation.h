#pragma once
#include "SGameEngineRenderer.h"
#include <SGameEngineWinImage.h>
#include <SGameEngineString.h>

// �з� :
// �뵵 : 
// ���� : 
class SGameEngineRendererAnimation : public SGameEngineRenderer
{
    // Inner Class
    private:
        class Animation
        {
            public:
                SGameEngineWinImage* m_Image;
                float m_FrameTime; // �̹��� ������ �ٲ�� �ð�
                float m_CurTime;     // ���� �ִϸ��̼� �ð�
                int m_StartFrame;    // ���� ������
                int m_EndFrame;     // ���� ������
                int m_CurFrame;     // ���� ������
                bool m_IsLoop;       // ��������(default : true)
                int m_TransColor;   // Ư�������Ÿ� ���� Ư��������

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


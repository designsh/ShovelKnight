#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class EndingText : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererAnimation* m_AniEndingText;
        SGameEngineFSM<EndingText> m_EndingTextFSM;

    public: // constructer destructer
        EndingText();
        virtual ~EndingText();

    public: // delete constructer 
        EndingText(const EndingText& _Other) = delete;
        EndingText(const EndingText&& _Other) = delete;

    public: // delete operator
        EndingText& operator=(const EndingText& _Other) = delete;
        EndingText& operator=(const EndingText&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void SceneStart();
        void SceneStay();
        void SceneEnd();

};


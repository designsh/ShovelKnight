#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class Plains_IconEffect : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;

        SGameEngineRendererAnimation* m_AniClearEffect;
        SGameEngineFSM<Plains_IconEffect> m_ClearEffectFSM;

    public: // constructer destructer
        Plains_IconEffect();
        ~Plains_IconEffect();

    public: // delete constructer 
        Plains_IconEffect(const Plains_IconEffect& _Other) = delete;
        Plains_IconEffect(const Plains_IconEffect&& _Other) = delete;

    public: // delete operator
        Plains_IconEffect& operator=(const Plains_IconEffect& _Other) = delete;
        Plains_IconEffect& operator=(const Plains_IconEffect&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

        // FSM 상태
    public:
        // Idle상태
        void IdleStart();
        void IdleStay();
        void IdleEnd();

};


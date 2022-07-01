#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : Dozedrake 사망시 생성되며 랜덤한 위치에 생성된다.
class Dozedrake_DeathEffect : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;

        SGameEngineRendererAnimation* m_AniDeathEffect;
        SGameEngineFSM<Dozedrake_DeathEffect> m_DeathEffectFSM;

    public: // constructer destructer
        Dozedrake_DeathEffect();
        virtual ~Dozedrake_DeathEffect();

    public: // delete constructer 
        Dozedrake_DeathEffect(const Dozedrake_DeathEffect& _Other) = delete;
        Dozedrake_DeathEffect(const Dozedrake_DeathEffect&& _Other) = delete;

    public: // delete operator
        Dozedrake_DeathEffect& operator=(const Dozedrake_DeathEffect& _Other) = delete;
        Dozedrake_DeathEffect& operator=(const Dozedrake_DeathEffect&& _Other) = delete;

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


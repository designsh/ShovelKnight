#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class Ending_Player : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererAnimation* m_AniPlayer;
        SGameEngineFSM<Ending_Player> m_PlayerFSM;

    public: // constructer destructer
        Ending_Player();
        virtual ~Ending_Player();

    public: // delete constructer 
        Ending_Player(const Ending_Player& _Other) = delete;
        Ending_Player(const Ending_Player&& _Other) = delete;

    public: // delete operator
        Ending_Player& operator=(const Ending_Player& _Other) = delete;
        Ending_Player& operator=(const Ending_Player&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void StateStart();
        void StateStay();
        void StateEnd();

};


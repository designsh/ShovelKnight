#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class CampFire : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererAnimation* m_AniCampFire;
        SGameEngineFSM<CampFire> m_CampFireFSM;

    public: // constructer destructer
        CampFire();
        virtual ~CampFire();

    public: // delete constructer 
        CampFire(const CampFire& _Other) = delete;
        CampFire(const CampFire&& _Other) = delete;

    public: // delete operator
        CampFire& operator=(const CampFire& _Other) = delete;
        CampFire& operator=(const CampFire&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void FireStart();
        void FireStay();
        void FireEnd();

};


#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineCollision.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class GoldObject : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_GoldObjectRenderer;
        SGameEngineCollision* m_GoldObjectCol;
        SGameEngineRendererAnimation* m_AniGoldObject;
        SGameEngineFSM<GoldObject> m_GoldObjectFSM;

    private:
        int m_iGold;
        SGameEngineString m_CurAniMationName;
        SGameEngineString m_AniMationName;

    public: // constructer destructer
        GoldObject();
        virtual ~GoldObject();

    public: // delete constructer 
        GoldObject(const GoldObject& _Other) = delete;
        GoldObject(const GoldObject&& _Other) = delete;

    public: // delete operator
        GoldObject& operator=(const GoldObject& _Other) = delete;
        GoldObject& operator=(const GoldObject&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void ChangeAniMation(const SGameEngineString& _ChangeAniName);

    public:
        void SetAmountOfGold(int _Gold);

    // 충돌체
    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    // FSM 상태
    public:
        // 카메라를 찾는 상태
        void FindStart();
        void FindStay();
        void FindEnd();

        void IdleStart();
        void IdleStay();
        void IdleEnd();

};


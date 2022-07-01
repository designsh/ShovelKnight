#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineCollision.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class Chicken : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_ChickenRenderer;
        SGameEngineCollision* m_ChickenCol;

    private:
        FLOAT4 m_MovePos;
        FLOAT4 m_AppearPos;
        FLOAT4 m_AppearPower;
        FLOAT4 m_AppearGravityPower;

    private:
        bool m_bAppearEnd;

    private:
        FLOAT4 m_ChickenCheckPos;
        FLOAT4 m_ChickenCheckDir[4];
        int m_iChickenCheckColor[4];

    public: // constructer destructer
        Chicken();
        virtual ~Chicken();

    public: // delete constructer 
        Chicken(const Chicken& _Other) = delete;
        Chicken(const Chicken&& _Other) = delete;

    public: // delete operator
        Chicken& operator=(const Chicken& _Other) = delete;
        Chicken& operator=(const Chicken&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void ChickenPixelCheck();
        void ChickenAppear();

    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

};


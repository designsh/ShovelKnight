#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineCollision.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class Platter : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_PlatterRenderer;
        SGameEngineCollision* m_PlatterCol;

    public: // constructer destructer
        Platter();
        virtual ~Platter();

    public: // delete constructer 
        Platter(const Platter& _Other) = delete;
        Platter(const Platter&& _Other) = delete;

    public: // delete operator
        Platter& operator=(const Platter& _Other) = delete;
        Platter& operator=(const Platter&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);
};


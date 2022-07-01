#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class Platter_FragmentsFloor : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_FragmentsFloorRenderer;

    private:
        GlobalValue::BasicMoveType m_MoveDir;
        FLOAT4 m_MovePos;
        FLOAT4 m_DirectPos;
        FLOAT4 m_AppearPos;
        FLOAT4 m_AppearPower;
        FLOAT4 m_AppearGravityPower;

    public: // constructer destructer
        Platter_FragmentsFloor();
        virtual ~Platter_FragmentsFloor();

    public: // delete constructer 
        Platter_FragmentsFloor(const Platter_FragmentsFloor& _Other) = delete;
        Platter_FragmentsFloor(const Platter_FragmentsFloor&& _Other) = delete;

    public: // delete operator
        Platter_FragmentsFloor& operator=(const Platter_FragmentsFloor& _Other) = delete;
        Platter_FragmentsFloor& operator=(const Platter_FragmentsFloor&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void FragmentsFloorAppear();
        void CamDistDel();

};


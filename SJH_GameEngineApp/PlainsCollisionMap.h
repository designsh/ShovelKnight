#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>

// 분류 :
// 용도 : 
// 설명 : 
class PlainsCollisionMap : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        SGameEngineRendererBasic* m_CollistionMap;

    private:
        FLOAT4 m_WindowSize;

    public: // constructer destructer
        PlainsCollisionMap();
        virtual ~PlainsCollisionMap();

    public: // delete constructer 
        PlainsCollisionMap(const PlainsCollisionMap& _Other) = delete;
        PlainsCollisionMap(const PlainsCollisionMap&& _Other) = delete;

    public: // delete operator
        PlainsCollisionMap& operator=(const PlainsCollisionMap& _Other) = delete;
        PlainsCollisionMap& operator=(const PlainsCollisionMap&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

};


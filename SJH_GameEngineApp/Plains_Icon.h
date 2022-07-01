#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>

// 분류 :
// 용도 : 
// 설명 : 
class Plains_Icon : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_PlainsIcon;
        bool m_bFistEffect;

    public: // constructer destructer
        Plains_Icon();
        ~Plains_Icon();

    public: // delete constructer 
        Plains_Icon(const Plains_Icon& _Other) = delete;
        Plains_Icon(const Plains_Icon&& _Other) = delete;

    public: // delete operator
        Plains_Icon& operator=(const Plains_Icon& _Other) = delete;
        Plains_Icon& operator=(const Plains_Icon&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

};


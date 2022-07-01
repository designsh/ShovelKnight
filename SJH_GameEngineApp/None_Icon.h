#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>

// 분류 :
// 용도 : 
// 설명 : 
class None_Icon : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_NoneIcon;

    public: // constructer destructer
        None_Icon();
        ~None_Icon();

    public: // delete constructer 
        None_Icon(const None_Icon& _Other) = delete;
        None_Icon(const None_Icon&& _Other) = delete;

    public: // delete operator
        None_Icon& operator=(const None_Icon& _Other) = delete;
        None_Icon& operator=(const None_Icon&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

};


#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>

// 분류 :
// 용도 : 
// 설명 : 
class EndingBackDrop : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_BackGround;

    public: // constructer destructer
        EndingBackDrop();
        virtual ~EndingBackDrop();

    public: // delete constructer 
        EndingBackDrop(const EndingBackDrop& _Other) = delete;
        EndingBackDrop(const EndingBackDrop&& _Other) = delete;

    public: // delete operator
        EndingBackDrop& operator=(const EndingBackDrop& _Other) = delete;
        EndingBackDrop& operator=(const EndingBackDrop&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

};


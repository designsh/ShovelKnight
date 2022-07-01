#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>

// 분류 :
// 용도 : 
// 설명 : 
class LevelMapBackDrop : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_BackDrop;

    public: // constructer destructer
        LevelMapBackDrop();
        ~LevelMapBackDrop();

    public: // delete constructer 
        LevelMapBackDrop(const LevelMapBackDrop& _Other) = delete;
        LevelMapBackDrop(const LevelMapBackDrop&& _Other) = delete;

    public: // delete operator
        LevelMapBackDrop& operator=(const LevelMapBackDrop& _Other) = delete;
        LevelMapBackDrop& operator=(const LevelMapBackDrop&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

};


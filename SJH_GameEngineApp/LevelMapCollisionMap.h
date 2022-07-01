#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>

// 분류 :
// 용도 : 
// 설명 : 
class LevelMapCollisionMap : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_CollistionMap;

    public: // constructer destructer
        LevelMapCollisionMap();
        ~LevelMapCollisionMap();

    public: // delete constructer 
        LevelMapCollisionMap(const LevelMapCollisionMap& _Other) = delete;
        LevelMapCollisionMap(const LevelMapCollisionMap&& _Other) = delete;

    public: // delete operator
        LevelMapCollisionMap& operator=(const LevelMapCollisionMap& _Other) = delete;
        LevelMapCollisionMap& operator=(const LevelMapCollisionMap&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

};


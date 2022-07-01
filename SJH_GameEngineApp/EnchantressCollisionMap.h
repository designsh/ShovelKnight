#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>

// 분류 :
// 용도 : 
// 설명 : 
class EnchantressCollisionMap : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_CollistionMap;

    public: // constructer destructer
        EnchantressCollisionMap();
        virtual ~EnchantressCollisionMap();

    public: // delete constructer 
        EnchantressCollisionMap(const EnchantressCollisionMap& _Other) = delete;
        EnchantressCollisionMap(const EnchantressCollisionMap&& _Other) = delete;

    public: // delete operator
        EnchantressCollisionMap& operator=(const EnchantressCollisionMap& _Other) = delete;
        EnchantressCollisionMap& operator=(const EnchantressCollisionMap&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

};


#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>

// 분류 :
// 용도 : 
// 설명 : 
class EnchantressBackDrop : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_BackGround;

    public: // constructer destructer
        EnchantressBackDrop();
        virtual ~EnchantressBackDrop();

    public: // delete constructer 
        EnchantressBackDrop(const EnchantressBackDrop& _Other) = delete;
        EnchantressBackDrop(const EnchantressBackDrop&& _Other) = delete;

    public: // delete operator
        EnchantressBackDrop& operator=(const EnchantressBackDrop& _Other) = delete;
        EnchantressBackDrop& operator=(const EnchantressBackDrop&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

};


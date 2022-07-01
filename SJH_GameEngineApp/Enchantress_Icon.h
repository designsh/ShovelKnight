#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>

// �з� :
// �뵵 : 
// ���� : 
class Enchantress_Icon : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_EnchantressIcon;

    public: // constructer destructer
        Enchantress_Icon();
        ~Enchantress_Icon();

    public: // delete constructer 
        Enchantress_Icon(const Enchantress_Icon& _Other) = delete;
        Enchantress_Icon(const Enchantress_Icon&& _Other) = delete;

    public: // delete operator
        Enchantress_Icon& operator=(const Enchantress_Icon& _Other) = delete;
        Enchantress_Icon& operator=(const Enchantress_Icon&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

};


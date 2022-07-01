#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineTimeEventer.h>

#include "ShovelKnightInfo.h"

// 분류 :
// 용도 : 
// 설명 : 
class Enchantress_StateBar : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_TopBar;
        SGameEngineRendererBasic* m_PlayerHP;
        SGameEngineRendererBasic* m_FinalBossHP;

    private:
        std::list<SGameEngineRendererBasic*> m_ListPlayerHP;
        std::list<SGameEngineRendererBasic*> m_ListPlayerMP;
        std::list<SGameEngineRendererBasic*> m_ListPlayerHoldingGold;
        std::list<SGameEngineRendererBasic*> m_ListFinalBossHP;

    private:
        int m_iPlayerHP;
        int m_iPlayerMaxHP;
        int m_iPlayerMP;
        int m_iPlayerMaxMP;
        int m_iPlayerHoldingGold;
        int m_iPlayerMaxHoldingGold;

        int m_iFinalBossHP;
        int m_iFinalBossMaxHP;

    private:
        int m_iPrevGold;

    public: // constructer destructer
        Enchantress_StateBar();
        virtual ~Enchantress_StateBar();

    public: // delete constructer 
        Enchantress_StateBar(const Enchantress_StateBar& _Other) = delete;
        Enchantress_StateBar(const Enchantress_StateBar&& _Other) = delete;

    public: // delete operator
        Enchantress_StateBar& operator=(const Enchantress_StateBar& _Other) = delete;
        Enchantress_StateBar& operator=(const Enchantress_StateBar&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

};


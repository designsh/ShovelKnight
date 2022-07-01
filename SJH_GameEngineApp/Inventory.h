#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class Inventory : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_Inventory;
        SGameEngineRendererBasic* m_RelicsText;
        SGameEngineRendererBasic* m_EquipmentText;

        SGameEngineRendererBasic* m_InventoryCursor;
        SGameEngineRendererBasic* m_InventoryItem1;
        SGameEngineRendererBasic* m_InventoryItem2;

    public: // constructer destructer
        Inventory();
        virtual ~Inventory();

    public: // delete constructer 
        Inventory(const Inventory& _Other) = delete;
        Inventory(const Inventory&& _Other) = delete;

    public: // delete operator
        Inventory& operator=(const Inventory& _Other) = delete;
        Inventory& operator=(const Inventory&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

};


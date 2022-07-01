#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererTile.h>
#include <SGameEngineRendererBasic.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class EnchantressTileMap : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;

    public:
        SGameEngineRendererTile* m_TileMap;

    public: // constructer destructer
        EnchantressTileMap();
        virtual ~EnchantressTileMap();

    public: // delete constructer 
        EnchantressTileMap(const EnchantressTileMap& _Other) = delete;
        EnchantressTileMap(const EnchantressTileMap&& _Other) = delete;

    public: // delete operator
        EnchantressTileMap& operator=(const EnchantressTileMap& _Other) = delete;
        EnchantressTileMap& operator=(const EnchantressTileMap&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void LoadTileBlockImage(const SGameEngineString& _TileImageName, int _RenderGroup = (int)GlobalValue::RenderGroup::TileMap);

};


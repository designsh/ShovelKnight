#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererTile.h>
#include <SGameEngineRendererBasic.h>

#include "GlobalValue.h"

// �з� :
// �뵵 : 
// ���� : 
class PlainsTileMap : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var

    public:
        SGameEngineRendererTile* m_TileMap;

    private:
        FLOAT4 m_WindowSize;

    public: // constructer destructer
        PlainsTileMap();
        virtual ~PlainsTileMap();

    public: // delete constructer 
        PlainsTileMap(const PlainsTileMap& _Other) = delete;
        PlainsTileMap(const PlainsTileMap&& _Other) = delete;

    public: // delete operator
        PlainsTileMap& operator=(const PlainsTileMap& _Other) = delete;
        PlainsTileMap& operator=(const PlainsTileMap&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void LoadTileBlockImage(const SGameEngineString& _TileImageName, int _RenderGroup = (int)GlobalValue::RenderGroup::TileMap);

};


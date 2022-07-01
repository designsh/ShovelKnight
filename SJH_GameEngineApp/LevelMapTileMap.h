#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererTile.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class LevelMapTileMap : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;

    public:
        SGameEngineRendererTile* m_TileMap;

    public: // constructer destructer
        LevelMapTileMap();
        ~LevelMapTileMap();

    public: // delete constructer 
        LevelMapTileMap(const LevelMapTileMap& _Other) = delete;
        LevelMapTileMap(const LevelMapTileMap&& _Other) = delete;

    public: // delete operator
        LevelMapTileMap& operator=(const LevelMapTileMap& _Other) = delete;
        LevelMapTileMap& operator=(const LevelMapTileMap&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void LoadTileBlockImage(const SGameEngineString& _TileImageName, int _RenderGroup = (int)GlobalValue::RenderGroup::TileMap);

};


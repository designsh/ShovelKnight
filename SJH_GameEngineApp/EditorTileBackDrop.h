#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererTile.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineDirectory.h>

// 분류 :
// 용도 : 
// 설명 : 
class EditorTileBackDrop : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
    public:
        SGameEngineRendererTile* m_Tile;
        SGameEngineRendererTile* m_BrokenTile;
        SGameEngineRendererTile* m_LevelMapTile;
        SGameEngineRendererTile* m_LevelMapMoveTile;
        SGameEngineRendererTile* m_EnchantressTile;
        SGameEngineRendererTile* m_EnchantressBrokenTile;

    public: // constructer destructer
        EditorTileBackDrop();
        virtual ~EditorTileBackDrop();

    public: // delete constructer 
        EditorTileBackDrop(const EditorTileBackDrop& _Other) = delete;
        EditorTileBackDrop(const EditorTileBackDrop&& _Other) = delete;

    public: // delete operator
        EditorTileBackDrop& operator=(const EditorTileBackDrop& _Other) = delete;
        EditorTileBackDrop& operator=(const EditorTileBackDrop&& _Other) = delete;

    public: // member Func
        void Start()	override;
        void Update()	override;
        void DebugRender() override;

};


#pragma once
#include <SGameEngineScene.h>
#include <SGameEngineDirectory.h>
#include <SGameEngineString.h>
#include <SGameEngineWindow.h>

// 분류 :
// 용도 : 
// 설명 : 
class Tile;
class EditorBackDrop;
class SGameEngineFile;
class EditorTileBackDrop;
class TileMapEditor : public SGameEngineScene
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        SGameEngineDirectory m_ResPath;
        SGameEngineDirectory m_TileFilePath;
        EditorBackDrop* m_EditorDrop;
        EditorTileBackDrop* m_RenderTile;

        float m_Speed;

    private:
        FLOAT4 m_WindowSize;

    private:
        FLOAT4 m_CamPos;
        FLOAT4 m_Pos;

    private:
        bool m_DelSearch;

    // 타일저장용 변수
    private:
        int m_TileIndex;

    public: // constructer destructer
        TileMapEditor();
        ~TileMapEditor();

    public: // delete constructer 
        TileMapEditor(const TileMapEditor& _Other) = delete;
        TileMapEditor(const TileMapEditor&& _Other) = delete;

    public: // delete operator
        TileMapEditor& operator=(const TileMapEditor& _Other) = delete;
        TileMapEditor& operator=(const TileMapEditor&& _Other) = delete;

    public: // member Func
        void Start() override;
        void SceneUpdate() override;
        void SceneDebugRender() override;

};


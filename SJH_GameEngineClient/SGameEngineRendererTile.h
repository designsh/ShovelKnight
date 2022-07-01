#pragma once
#include "SGameEngineRenderer.h"
#include <SGameEngineWinImage.h>
#include <SGameEngineDebug.h>
#include <SGameEngineFile.h>
#include <vector>

// 분류 :
// 용도 : 
// 설명 : 
class SGameEngineActor;
class SGameEngineRendererTile : public SGameEngineRenderer
{
    private:
        class Tile
        {
            public:
                SGameEngineRendererTile* m_ParentTile;
                int m_ImageIndex;

            public:
                Tile() : m_ParentTile(nullptr), m_ImageIndex(-1)
                {

                }
        };

    private: // Static Var

    public: // Static Func

    private: // member Var
        SGameEngineWinImage* m_Image;
        std::vector<std::vector<Tile>> m_TilMap;

        FLOAT4 m_TileSize;
        FLOAT4 m_ImageScale;
        FLOAT4 m_PivotPos;
        int m_MaxIndex;
        int m_TileMaxX;
        int m_TileMaxY;

        // 랜더링 기준점
        SGameEngineActor* m_CullActor;

        // 랜더링 기준점으로부터 인덱스크기
        FLOAT4 m_RenderIndex;

    public: // constructer destructer
        SGameEngineRendererTile();
        virtual ~SGameEngineRendererTile();

    public: // delete constructer 
        SGameEngineRendererTile(const SGameEngineRendererTile& _Other) = delete;
        SGameEngineRendererTile(const SGameEngineRendererTile&& _Other) = delete;

    public: // delete operator
        SGameEngineRendererTile& operator=(const SGameEngineRendererTile& _Other) = delete;
        SGameEngineRendererTile& operator=(const SGameEngineRendererTile&& _Other) = delete;

    public: // member Func
        void Render() override;

    public:
        void SetCullActor(SGameEngineActor* _CullActor, FLOAT4 _Scale);

    public:
        void TileMapStart(const SGameEngineString& _TileMapImage, FLOAT4 _TileSize, FLOAT4 _ImageScale, int _SizeX, int _SizeY);
        void SetTile(const FLOAT4& _CheckPos, int _Index);
        void DelTile(const FLOAT4& _CheckPos);
        void DelTileIndex(const FLOAT4& _CheckPos);
        void SaveTile(const SGameEngineString& _pFilePath);
        void LoadTile(const SGameEngineString& _pFilePath);
        int GetTileImageIndex(const FLOAT4& _CheckPos);
        FLOAT4 GetTileMaxIndex();
        FLOAT4 GetCurIndexToPos(const FLOAT4& _CurIndex);

};


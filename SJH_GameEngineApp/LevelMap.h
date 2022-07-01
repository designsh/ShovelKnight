#pragma once
#include <SGameEngineScene.h>
#include <SGameEngineTimeEventer.h>
#include <SGameEngineDirectory.h>
#include <SGameEngineFile.h>
#include <SGameEngineSound.h>

// 분류 :
// 용도 : 
// 설명 : 
class LevelMapBackDrop;
class LevelMapCollisionMap;
class LevelMapTileMap;
class MapCloud;
class Plains_Icon;
class None_Icon;
class Enchantress_Icon;
class PlayerMaker;
class LevelMap : public SGameEngineScene
{
    private: // Static Var
        static SoundPlayer m_LevelMapStageBgm;
        static SoundPlayer m_CloudMoveStartSound;
        static SoundPlayer m_PlainsEffectSound;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineDirectory m_ResPath;
        SGameEngineDirectory m_TileFilePath;

    private:
        LevelMapBackDrop* m_BackDrop;
        LevelMapTileMap* m_TileMap;
        LevelMapCollisionMap* m_CollisionMap;

    private:
        Plains_Icon* m_PlainsIcon;
        None_Icon* m_NoneIcon;
        Enchantress_Icon* m_EnchantressIcon;
        MapCloud* m_MapCloud;

    private:
        PlayerMaker* m_Player;

    public: // constructer destructer
        LevelMap();
        ~LevelMap();

    public: // delete constructer 
        LevelMap(const LevelMap& _Other) = delete;
        LevelMap(const LevelMap&& _Other) = delete;

    public: // delete operator
        LevelMap& operator=(const LevelMap& _Other) = delete;
        LevelMap& operator=(const LevelMap&& _Other) = delete;

    public: // member Func
        void Start() override;
        void SceneUpdate() override;
        void SceneChangeStart() override;
        void SceneChangeEnd() override;
        void SceneDebugRender() override;

    public:
        // Level Map Image Cut
        void LevelMapImageCut();

        // Level Map Create CollisionGroup
        void LevelMapCreateCollisionGroup();

        // Level Map BackDrop Actor
        void LevelMapCreateBackDrop();

        // Level Map Object Actor
        void LevelMapCreateObject();

};


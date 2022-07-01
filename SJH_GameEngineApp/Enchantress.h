#pragma once
#include <SGameEngineScene.h>
#include <SGameEngineTimeEventer.h>
#include <SGameEngineDirectory.h>
#include <SGameEngineFile.h>
#include <SGameEngineSound.h>

// 분류 :
// 용도 : 
// 설명 : 
class EnchantressBackDrop;
class EnchantressCollisionMap;
class EnchantressTileMap;
class Enchantress_StateBar;
class Enchantress_ShovelKnight;
class Enchantress_FinalBoss;
class FadeInOutActor;
class Enchantress : public SGameEngineScene
{
    private: // Static Var
        static SoundPlayer m_EnchantressStageBgm;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineDirectory m_ResPath;
        SGameEngineDirectory m_TileFilePath;

    private: // 맵
        EnchantressBackDrop* m_BackDrop;
        EnchantressCollisionMap* m_ColMap;
        EnchantressTileMap* m_TileMap;

    private: // 상태창
        Enchantress_StateBar* m_StateBar;

    private: // 보스
        Enchantress_FinalBoss* m_FinalBoss;

    private: // 플레이어
        Enchantress_ShovelKnight* m_Player;

    private: // 씬체인지용 페이드인아웃효과
        FadeInOutActor* m_FadeInOut;

    public: // constructer destructer
        Enchantress();
        ~Enchantress();

    public: // delete constructer 
        Enchantress(const Enchantress& _Other) = delete;
        Enchantress(const Enchantress&& _Other) = delete;

    public: // delete operator
        Enchantress& operator=(const Enchantress& _Other) = delete;
        Enchantress& operator=(const Enchantress&& _Other) = delete;

    public: // member Func
        void Start() override;
        void SceneUpdate() override;
        void SceneChangeStart() override;
        void SceneChangeEnd() override;
        void SceneDebugRender() override;

    public:
        // Enchantress Image Cut
        void EnchantressImageCut();

        // Enchantress Create CollisionGroup
        void EnchantressCreateCollisionGroup();

        // Enchantress BackDrop Actor
        void EnchantressCreateBackDrop();

        // Enchantress Object Actor
        void EnchantressCreateObject();

        // Enchantress Monster Actor
        void EnchantressCreateMonster();

};


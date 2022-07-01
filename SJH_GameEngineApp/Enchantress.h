#pragma once
#include <SGameEngineScene.h>
#include <SGameEngineTimeEventer.h>
#include <SGameEngineDirectory.h>
#include <SGameEngineFile.h>
#include <SGameEngineSound.h>

// �з� :
// �뵵 : 
// ���� : 
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

    private: // ��
        EnchantressBackDrop* m_BackDrop;
        EnchantressCollisionMap* m_ColMap;
        EnchantressTileMap* m_TileMap;

    private: // ����â
        Enchantress_StateBar* m_StateBar;

    private: // ����
        Enchantress_FinalBoss* m_FinalBoss;

    private: // �÷��̾�
        Enchantress_ShovelKnight* m_Player;

    private: // ��ü������ ���̵��ξƿ�ȿ��
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


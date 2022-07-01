#pragma once
#include <SGameEngineScene.h>
#include <SGameEngineTimeEventer.h>
#include <SGameEngineDirectory.h>
#include <SGameEngineFile.h>

// 분류 :
// 용도 : 
// 설명 : 평원의 길(Stage 1) 씬이며 해당 씬에서 움직이거나 위치하고있는 모든 액터를 관리한다.
class PlainsBackDrop;
class PlainsCollisionMap;
class PlainsTileMap;
class SavePoint;
class MovingPlatform;
class DeathScreen;
class ShovelKnight;
class StateTopBar;
class Beeto;
class SkullSoldier;
class Slime;
class Dragon;
class Dozedrake;
class BlackKnight;
class StoneObject;
class DirtBlock;
class DirtBlock_Small;
class PileBubbles;
class GoldObject;
class Platter;
class Plains : public SGameEngineScene
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        SGameEngineDirectory m_ResPath;
        ShovelKnight* m_Player;

        //------------------------------------------- State Bar -------------------------------------------//
        StateTopBar* m_TopBar;

        //------------------------------------------- Death Screen -------------------------------------------//
        DeathScreen* m_DeathScreen;

        //------------------------------------------- Moving Platform -------------------------------------------//
        MovingPlatform* m_MovingPlatform1;
        MovingPlatform* m_MovingPlatform2;
        MovingPlatform* m_MovingPlatform3;
        MovingPlatform* m_MovingPlatform4;
        MovingPlatform* m_MovingPlatform5;

        //------------------------------------------- Monster -------------------------------------------//
        // Beeto
        Beeto* m_Beeto1;
        Beeto* m_Beeto2;
        Beeto* m_Beeto3;
        Beeto* m_Beeto4;
        Beeto* m_Beeto5;
        Beeto* m_Beeto6;
        Beeto* m_Beeto7;
        Beeto* m_Beeto8;
        Beeto* m_Beeto9;
        Beeto* m_Beeto10;
        Beeto* m_Beeto11;

        // SkullSoldier
        SkullSoldier* m_SkullSoldier1;
        SkullSoldier* m_SkullSoldier2;
        SkullSoldier* m_SkullSoldier3;
        SkullSoldier* m_SkullSoldier4;

        // Slime
        Slime* m_Slime1;
        Slime* m_Slime2;
        Slime* m_Slime3;
        Slime* m_Slime4;
        Slime* m_Slime5;
        Slime* m_Slime6;

        // Dragon
        Dragon* m_Dragon1;
        Dragon* m_Dragon2;
        Dragon* m_Dragon3;
        Dragon* m_Dragon4;
        Dragon* m_Dragon5;

        // Dozedrake
        Dozedrake* m_Dozedrake1;
        Dozedrake* m_Dozedrake2;

        // Black Knight
        BlackKnight* m_FinalBoss;

        //------------------------------------------- UI -------------------------------------------//
        StoneObject* m_Stone1;
        StoneObject* m_Stone2;
        StoneObject* m_Stone3;
        StoneObject* m_Stone4;
        StoneObject* m_Stone5;
        StoneObject* m_Stone6;
        StoneObject* m_Stone7;
        StoneObject* m_Stone8;
        StoneObject* m_Stone9;

        DirtBlock* m_DirtBlock1;
        DirtBlock* m_DirtBlock2;
        DirtBlock* m_DirtBlock3;
        DirtBlock* m_DirtBlock4;
        DirtBlock* m_DirtBlock5;
        DirtBlock* m_DirtBlock6;
        DirtBlock* m_DirtBlock7;
        DirtBlock* m_DirtBlock8;
        DirtBlock* m_DirtBlock9;
        DirtBlock* m_DirtBlock10;
        DirtBlock* m_DirtBlock11;
        DirtBlock* m_DirtBlock12;
        DirtBlock* m_DirtBlock13;
        DirtBlock* m_DirtBlock14;
        DirtBlock* m_DirtBlock15;
        DirtBlock* m_DirtBlock16;
        DirtBlock* m_DirtBlock17;
        DirtBlock* m_DirtBlock18;
        DirtBlock* m_DirtBlock19;
        DirtBlock* m_DirtBlock20;
        DirtBlock* m_DirtBlock21;
        DirtBlock* m_DirtBlock22;
        DirtBlock* m_DirtBlock23;
        DirtBlock* m_DirtBlock24;
        DirtBlock* m_DirtBlock25;
        DirtBlock* m_DirtBlock26;
        DirtBlock* m_DirtBlock27;
        DirtBlock* m_DirtBlock28;
        DirtBlock* m_DirtBlock29;
        DirtBlock* m_DirtBlock30;
        DirtBlock* m_DirtBlock31;
        DirtBlock* m_DirtBlock32;
        DirtBlock* m_DirtBlock33;
        DirtBlock* m_DirtBlock34;
        DirtBlock* m_DirtBlock35;
        DirtBlock* m_DirtBlock36;
        DirtBlock* m_DirtBlock37;
        DirtBlock* m_DirtBlock38;
        DirtBlock* m_DirtBlock39;
        DirtBlock* m_DirtBlock40;
        DirtBlock* m_DirtBlock41;
        DirtBlock* m_DirtBlock42;
        DirtBlock* m_DirtBlock43;
        DirtBlock* m_DirtBlock44;
        DirtBlock* m_DirtBlock45;
        DirtBlock* m_DirtBlock46;
        DirtBlock* m_DirtBlock47;
        DirtBlock* m_DirtBlock48;
        DirtBlock* m_DirtBlock49;
        DirtBlock* m_DirtBlock50;
        DirtBlock* m_DirtBlock51;
        DirtBlock* m_DirtBlock52;
        DirtBlock* m_DirtBlock53;
        DirtBlock* m_DirtBlock54;
        DirtBlock* m_DirtBlock55;
        DirtBlock* m_DirtBlock56;
        DirtBlock* m_DirtBlock57;
        DirtBlock* m_DirtBlock58;
        DirtBlock* m_DirtBlock59;
        DirtBlock* m_DirtBlock60;
        DirtBlock* m_DirtBlock61;
        DirtBlock* m_DirtBlock62;
        DirtBlock* m_DirtBlock63;
        DirtBlock* m_DirtBlock64;
        DirtBlock* m_DirtBlock65;
        DirtBlock* m_DirtBlock66;
        DirtBlock* m_DirtBlock67;
        DirtBlock* m_DirtBlock68;

        DirtBlock_Small* m_DirtSmall1;
        DirtBlock_Small* m_DirtSmall2;
        DirtBlock_Small* m_DirtSmall3;
        DirtBlock_Small* m_DirtSmall4;
        DirtBlock_Small* m_DirtSmall5;
        DirtBlock_Small* m_DirtSmall6;
        DirtBlock_Small* m_DirtSmall7;
        DirtBlock_Small* m_DirtSmall8;
        DirtBlock_Small* m_DirtSmall9;
        DirtBlock_Small* m_DirtSmall10;

        PileBubbles* m_PileBubbles1;
        PileBubbles* m_PileBubbles2;
        PileBubbles* m_PileBubbles3;
        PileBubbles* m_PileBubbles4;
        PileBubbles* m_PileBubbles5;
        PileBubbles* m_PileBubbles6;
        PileBubbles* m_PileBubbles7;

        SavePoint* m_SavePoint1;
        SavePoint* m_SavePoint2;
        SavePoint* m_SavePoint3;
        SavePoint* m_SavePoint4;

        GoldObject* m_GoldObject1;
        GoldObject* m_GoldObject2;
        GoldObject* m_GoldObject3;
        GoldObject* m_GoldObject4;
        GoldObject* m_GoldObject5;
        GoldObject* m_GoldObject6;
        GoldObject* m_GoldObject7;
        GoldObject* m_GoldObject8;
        GoldObject* m_GoldObject9;
        GoldObject* m_GoldObject10;
        GoldObject* m_GoldObject11;
        GoldObject* m_GoldObject12;
        GoldObject* m_GoldObject13;
        GoldObject* m_GoldObject14;
        GoldObject* m_GoldObject15;
        GoldObject* m_GoldObject16;


        GoldObject* m_GoldObject17;
        GoldObject* m_GoldObject18;
        GoldObject* m_GoldObject19;

        Platter* m_Platter1;

    private:
        PlainsBackDrop* m_BackDrop;
        PlainsCollisionMap* m_CollisionMap;
        PlainsTileMap* m_TileMap;

    private: // 타일맵관련
        SGameEngineDirectory m_TileFilePath;

    private:
        FLOAT4 m_WindowSize;

    private: // 각 오브젝트 재생성 관련
        SGameEngineTimeEventer<Plains> m_TimeEventer;

    public: // constructer destructer
        Plains();
        ~Plains();

    public: // delete constructer 
        Plains(const Plains& _Other) = delete;
        Plains(const Plains&& _Other) = delete;

    public: // delete operator
        Plains& operator=(const Plains& _Other) = delete;
        Plains& operator=(const Plains&& _Other) = delete;

    public: // member Func
        void Start() override;
        void SceneUpdate() override;
        void SceneChangeStart() override;
        void SceneChangeEnd() override;
        void SceneDebugRender() override;

    public: // 타임이벤터(오브젝트 재생성)
        void ResurrectObject();

    public:
        // Image Cut 
        void PlainsImageCut();

        // Current Scene BackDrop Actor
        void PlainsCreateBackDrop();

        // Current Scene Object Actor
        void PlainsCreateObject();

        // Current Scene Monster Actor
        void PlainsCreateMonster();

        // Current Scene Collision Group 생성
        void PlainsCreateCollisionGroup();
};


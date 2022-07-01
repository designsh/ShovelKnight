#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>
#include <SGameEngineCollision.h>
#include <SGameEngineTimeEventer.h>
#include <SGameEngineSound.h>

#include "MonsterInfo.h"
#include "GlobalValue.h"
#include "ShovelKnight.h"

// 분류 :
// 용도 : 
// 설명 : 
class Dragon : public SGameEngineActor
{
    private: // Static Var
        static SoundPlayer m_DragonActionSound;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        MonsterInfo m_DragonInfo;
        SGameEngineRendererAnimation* m_AniDragon;
        SGameEngineFSM<Dragon> m_DragonFSM;
        SGameEngineCollision* m_DragonCol;
        SGameEngineRendererBasic* m_BeShotLeftDragon;
        SGameEngineRendererBasic* m_BeShotRightDragon;

    private:
        SGameEngineString m_CurAniMationName;
        SGameEngineString m_AniMationName;

    private:
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;

        float m_Speed;

        FLOAT4 m_DirectPos;
        FLOAT4 m_MovePos;
        FLOAT4 m_MoveStartPos;
        FLOAT4 m_UpPos;
        FLOAT4 m_UpStartPos;
        FLOAT4 m_DownPos;
        FLOAT4 m_DownStartPos;
        FLOAT4 m_MaxDist;

    private: // BeShot Image Blink
        bool m_bBlinkImage;

        float m_fBlinkImageOnTime;
        float m_fBlinkImageOffTime;
        float m_fBlinkImageTotalTime;

    private:
        bool m_bDropCoin;

    public: // constructer destructer
        Dragon();
        virtual ~Dragon();

    public: // delete constructer 
        Dragon(const Dragon& _Other) = delete;
        Dragon(const Dragon&& _Other) = delete;

    public: // delete operator
        Dragon& operator=(const Dragon& _Other) = delete;
        Dragon& operator=(const Dragon&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        bool IsDropCoin();
        void DropCoinOn();
        void DropCoinOff();

    public:
        void ChangeAniMation(const SGameEngineString& _ChangeAniName);

    public:
        void SetStartMoveDirect(GlobalValue::BasicMoveType _Direct);
        void SetMaxMoveDist(FLOAT4 _MaxDist);

    public:
        void DirPosCheck();
        void UpPosCheck();
        void DownPosCheck();

    public: // KnockBack Blink Image Set
        void BeShotBlink();
        SGameEngineRendererBasic* DirectCheck();

    // 충돌체
    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public:
        // 플레이어 찾는 상태
        void FindStart();
        void FindStay();
        void FindEnd();

        // 이동상태
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // 하향이동상태
        void DownMoveStart();
        void DownMoveStay();
        void DownMoveEnd();

        // 상향이동상태
        void UpMoveStart();
        void UpMoveStay();
        void UpMoveEnd();

        // 사망상태
        void DeathStart();
        void DeathStay();
        void DeathEnd();

};


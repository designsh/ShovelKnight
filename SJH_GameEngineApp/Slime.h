#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineInput.h>
#include <SGameEngineFSM.h>
#include <SGameEngineCollision.h>
#include <SGameEngineTimeEventer.h>
#include <SGameEngineSound.h>

#include "MonsterInfo.h"
#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class Slime : public SGameEngineActor
{
    private: // Static Var
        static SoundPlayer m_SlimeActionSound;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        MonsterInfo m_SlimeInfo;
        SGameEngineRendererAnimation* m_AniSlime;
        SGameEngineFSM<Slime> m_SlimeFSM;
        SGameEngineCollision* m_SlimeCol;
        SGameEngineRendererBasic* m_BeShotSlime;

    private:
        FLOAT4 m_MovePos;
        FLOAT4 m_DirectPos;

        float m_Speed;
        float m_JumpTime;

    private:
        bool m_DirtBlockCol;
        bool m_DirtBlockSmallCol;

    private: // 피격 관련
        bool m_bBlinkImage;

        float m_fBlinkImageOnTime;
        float m_fBlinkImageOffTime;
        float m_fBlinkImageTotalTime;

    private: // 점프어택 관련
        FLOAT4 m_GravityPos;
        FLOAT4 m_GravityPower;
        FLOAT4 m_JumpPos;
        FLOAT4 m_JumpPower;

    private:
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;

    private:
        FLOAT4 m_SlimeCheckPos;
        FLOAT4 m_SlimeCheckDir[4];
        int m_iSlimeCheckColor[4];

    private:
        SGameEngineTimeEventer<Slime> m_JumpEventer;

    public: // constructer destructer
        Slime();
        virtual ~Slime();

    public: // delete constructer 
        Slime(const Slime& _Other) = delete;
        Slime(const Slime&& _Other) = delete;

    public: // delete operator
        Slime& operator=(const Slime& _Other) = delete;
        Slime& operator=(const Slime&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public: // Monster BeShot Blink
        void SetBlinkImage();

    public: // 타임이벤터
        void JumpAttackChange();

    public: // Actor Init Function
        void SetInitMove(GlobalValue::BasicMoveType _MoveDirect);

    public:
        void DirPosCheck();

    public:
        void SlimePixcelCol();
        void MoveCheck();
        void JumpAttackCheck();

    public:
        void SetJumpTime(float _JumpTime);

    // 충돌체
    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    // FSM 상태
    public:
        // 정지상태(대기상태)
        void FindStart();
        void FindStay();
        void FindEnd();

        // 이동상태
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // 점프 공격상태
        void JumpAttackStart();
        void JumpAttackStay();
        void JumpAttackEnd();

        // 사망상태
        void DieStart();
        void DieStay();
        void DieEnd();

};


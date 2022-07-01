#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineInput.h>
#include <SGameEngineFSM.h>
#include <SGameEngineCollision.h>
#include <SGameEngineSound.h>

#include "MonsterInfo.h"
#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class Beeto : public SGameEngineActor
{
    private: // Static Var
        static SoundPlayer m_BeetoActionSound;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        MonsterInfo m_BeetoBasicInfo;
        SGameEngineRendererAnimation* m_AniBeeto;
        SGameEngineFSM<Beeto> m_BeetoFSM;
        SGameEngineCollision* m_BeetoCol;

    private:
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;

        FLOAT4 m_MovePos;
        FLOAT4 m_DirectPos;
        FLOAT4 m_DeathPos;
        FLOAT4 m_DeathPower;
        FLOAT4 m_DeathGravityPower;

    private:
        SGameEngineString m_CurAniMationName;
        SGameEngineString m_AniMationName;

    private: // 픽셀체크관련
        FLOAT4 m_BeetoCheckPos;
        FLOAT4 m_BeetoCheckDir[4];
        int m_iBeetoCheckColor[4];

    public: // constructer destructer
        Beeto();
        virtual ~Beeto();

    public: // delete constructer 
        Beeto(const Beeto& _Other) = delete;
        Beeto(const Beeto&& _Other) = delete;

    public: // delete operator
        Beeto& operator=(const Beeto& _Other) = delete;
        Beeto& operator=(const Beeto&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void SetMoveDirect(GlobalValue::BasicMoveType _MoveDir);

    public: // Beeto Pixel Check
        void BeetoPixelCheck();
        void MoveStateCheck();
        void DieStateCheck();

    public:
        void ChangeAniMation(const SGameEngineString& _ChangeAniName);
        void DirCheck();

    // 충돌체
    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public:
        // 정지상태(대기상태)
        void FindStart();
        void FindStay();
        void FindEnd();

        // 이동상태
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // 사망상태
        void DieStart();
        void DieStay();
        void DieEnd();

        // 사망상태->몬스터 사라지는 모션
        void DieMotionStart();
        void DieMotionStay();
        void DieMotionEnd();

};


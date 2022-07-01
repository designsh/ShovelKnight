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
#include "Dozedrake_AttackBubble.h" // 공격 물방울
#include "Dozedrake_DeathEffect.h"   // 사망 이펙트

// 분류 :
// 용도 : 
// 설명 : Dozedrake Monster의 행동 및 드랍에 대해 관리하는 클래스
class Dozedrake : public SGameEngineActor
{
    private: // Static Var
        static SoundPlayer m_DozedrakeSound;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        MonsterInfo m_DozedrakeInfo;

        SGameEngineRendererAnimation* m_AniDozedrake;
        SGameEngineRendererBasic* m_BeShotDozedrake;       // 공격당한 이미지
        SGameEngineFSM<Dozedrake> m_DozedrakeFSM;
        SGameEngineCollision* m_DozedrakeHeadCol;              // 피격판정
        SGameEngineCollision* m_DozedrakeBodyCol;              // 몸체

    private: // 무브관련
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;
        FLOAT4 m_MovePos;
        FLOAT4 m_MaxBackPos;

        float m_Speed;
        float m_MaxDist;

        bool m_LimitBackMove;

    private: // 타임이벤터
        SGameEngineTimeEventer<Dozedrake> m_BubbleEvent;
        SGameEngineTimeEventer<Dozedrake> m_AttackEndEvent;
        SGameEngineTimeEventer<Dozedrake> m_DeathEvent;

    private: // 타격이미지 깜빡임 
        float m_fBlinkImageOnTime;
        float m_fBlinkImageOffTime;
        float m_fBlinkEndTime;
        bool m_bBlinkImage;

    private: // 사망 이펙트 생성 랜덤 좌표
        FLOAT4 m_RandomPos;

    public: // constructer destructer
        Dozedrake();
        virtual ~Dozedrake();

    public: // delete constructer 
        Dozedrake(const Dozedrake& _Other) = delete;
        Dozedrake(const Dozedrake&& _Other) = delete;

    public: // delete operator
        Dozedrake& operator=(const Dozedrake& _Other) = delete;
        Dozedrake& operator=(const Dozedrake&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void MoveCheck();

    public:
        void AttackBubbleCreate1();
        void AttackBubbleCreate2();
        void AttackBubbleCreate3();
        void AttackBubbleCreateEnd();

    public: // 사망이펙트 생성
        void DeathEffectStart();
        void DeathEffectStay();
        void DeathEffectEnd();

    public:
        void AttackComplete();

    public:
        void BeShotBlink();

    // 충돌체
    public:
        void HeadCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void HeadCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void HeadCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

        void BodyCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void BodyCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void BodyCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    // FSM 상태
    public:
        // 플레이어 찾는상태
        void FindStart();
        void FindStay();
        void FindEnd();

        // 대기상태
        void IdleStart();
        void IdleStay();
        void IdleEnd();

        // 앞으로 이동
        void FrontMoveStart();
        void FrontMoveStay();
        void FrontMoveEnd();

        // 공격모션 시작(물방울 생성)
        void AttackStartStart();
        void AttackStartStay();
        void AttackStartEnd();

        // 공격모션 종료(물방울과 일정거리멀어지면)
        void AttackComplateStart();
        void AttackComplateStay();
        void AttackComplateEnd();

        // 뒤로 이동(플레이어에 의해 머리 앞부분을 피격)
        void BackMoveStart();
        void BackMoveStay();
        void BackMoveEnd();

        // 사망상태
        void DeathStart();
        void DeathStay();
        void DeathEnd();

};


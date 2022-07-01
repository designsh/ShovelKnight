#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineInput.h>
#include <SGameEngineFSM.h>
#include <SGameEngineCollision.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class Dozedrake_AttackBubble : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;

        SGameEngineRendererAnimation* m_AniAttackBubble;
        SGameEngineFSM<Dozedrake_AttackBubble> m_AttackBubbleFSM;
        SGameEngineCollision* m_AttackBubbleCol;

    private: // 사정거리 러프
        FLOAT4 m_MoveStartPos;     // 생성위치
        FLOAT4 m_MoveEndPos;      // 목표지점
        FLOAT4 m_UpMoveEndPos; // 목표지점

        FLOAT4 m_MovePos;            // 버블의 러프포지션
        float m_fMoveLerpSpeed;    // 러프 이동속도
        float m_fUpLerpSpeed;         // 
        float m_fLerpTime;                // 러프 누적시간
        float m_fMoveDistMax;        // 공격최대사정거리
        float m_fUpDistMax;            // 하늘위로 올라가는 최대거리

        bool m_bFirstMoveGet;
        bool m_bFirstUpGet;

    public: // constructer destructer
        Dozedrake_AttackBubble();
        virtual ~Dozedrake_AttackBubble();

    public: // delete constructer 
        Dozedrake_AttackBubble(const Dozedrake_AttackBubble& _Other) = delete;
        Dozedrake_AttackBubble(const Dozedrake_AttackBubble&& _Other) = delete;

    public: // delete operator
        Dozedrake_AttackBubble& operator=(const Dozedrake_AttackBubble& _Other) = delete;
        Dozedrake_AttackBubble& operator=(const Dozedrake_AttackBubble&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public: // 러프관련
        FLOAT4 GetMoveEndPos();
        float GetMoveMax();
        void SetMoveDistMax(float _MaxDist);
        void SetUpDistMax(float _MaxDist);
        void SetMoveLerpSpeed(float _Speed);
        void SetUpLerpSpeed(float _Speed);

    // 충돌체
    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    // FSM 상태
    public:
        // 이동상태
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // 위로올라가는상태
        void UpMoveStart();
        void UpMoveStay();
        void UpMoveEnd();

        // 죽는 상태
        void DeathStart();
        void DeathStay();
        void DeathEnd();

};


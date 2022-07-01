#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineCollision.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class MovingPlatform : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_MovingPlatform;
        SGameEngineCollision* m_MovingPlatformCol;
        SGameEngineFSM<MovingPlatform> m_MovingPlatformFSM;
        SGameEngineRendererAnimation* m_AniMovingPlatform;

    private: // 러프 설정
        float m_fLerpSpeed;
        float m_LerpMoveTime;

        FLOAT4 m_MoveStartPos;
        FLOAT4 m_MoveTargetPos;
        FLOAT4 m_MovePos;

        GlobalValue::BasicMoveType m_CurDirect;

    private:
        FLOAT4 m_PlayerMovePos;

    public: // constructer destructer
        MovingPlatform();
        virtual ~MovingPlatform();

    public: // delete constructer 
        MovingPlatform(const MovingPlatform& _Other) = delete;
        MovingPlatform(const MovingPlatform&& _Other) = delete;

    public: // delete operator
        MovingPlatform& operator=(const MovingPlatform& _Other) = delete;
        MovingPlatform& operator=(const MovingPlatform&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public: // 러프관련
        // 러프 속도 설정
        float GetLerpSpeed();
        void SetLerpSpeed(float _Speed);

        // 러프 시작위치 설정
        FLOAT4 GetMoveStartPos();
        void SetMoveStartPos(FLOAT4 _StartPos);

        // 러프 목표위치 설정
        FLOAT4 GetMoveTargetPos();
        void SetMoveTargetPos(FLOAT4 _TargetPos);

        // 현재 러프 진행방향
        GlobalValue::BasicMoveType GetCurLerpDirect();
        void SetCurLerpDirect(FLOAT4 _StartPos, FLOAT4 _EndPos);

    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public:
        // Find 상태(플레이어와의 거리를 알아내는상태)
        void PlatformFindStart();
        void PlatformFindStay();
        void PlatformFindEnd();

        // Idle 상태(대기상태)
        void PlatformIdleStart();
        void PlatformIdleStay();
        void PlatformIdleEnd();

        // Move 상태(계속하여 러프하며 방향전환)
        void PlatformMoveStart();
        void PlatformMoveStay();
        void PlatformMoveEnd();

};


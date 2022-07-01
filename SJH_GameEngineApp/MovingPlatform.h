#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineCollision.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"

// �з� :
// �뵵 : 
// ���� : 
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

    private: // ���� ����
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

    public: // ��������
        // ���� �ӵ� ����
        float GetLerpSpeed();
        void SetLerpSpeed(float _Speed);

        // ���� ������ġ ����
        FLOAT4 GetMoveStartPos();
        void SetMoveStartPos(FLOAT4 _StartPos);

        // ���� ��ǥ��ġ ����
        FLOAT4 GetMoveTargetPos();
        void SetMoveTargetPos(FLOAT4 _TargetPos);

        // ���� ���� �������
        GlobalValue::BasicMoveType GetCurLerpDirect();
        void SetCurLerpDirect(FLOAT4 _StartPos, FLOAT4 _EndPos);

    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public:
        // Find ����(�÷��̾���� �Ÿ��� �˾Ƴ��»���)
        void PlatformFindStart();
        void PlatformFindStay();
        void PlatformFindEnd();

        // Idle ����(������)
        void PlatformIdleStart();
        void PlatformIdleStay();
        void PlatformIdleEnd();

        // Move ����(����Ͽ� �����ϸ� ������ȯ)
        void PlatformMoveStart();
        void PlatformMoveStay();
        void PlatformMoveEnd();

};


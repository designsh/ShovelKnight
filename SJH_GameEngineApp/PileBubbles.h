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
class PileBubbles : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_PileBubbles;
        SGameEngineCollision* m_PileBubblesCol;
        SGameEngineFSM<PileBubbles> m_PileBubblesFSM;
        SGameEngineRendererAnimation* m_AniPileBubbles;

    private: // ��纤���� ��
        FLOAT4 m_MovePos;

    private: // ���幫��
        FLOAT4 m_MoveTargetPos;
        FLOAT4 m_MoveStartPos;

        float m_LerpMoveTime;
        float m_LerpSpeed;

    public: // constructer destructer
        PileBubbles();
        virtual ~PileBubbles();

    public: // delete constructer 
        PileBubbles(const PileBubbles& _Other) = delete;
        PileBubbles(const PileBubbles&& _Other) = delete;

    public: // delete operator
        PileBubbles& operator=(const PileBubbles& _Other) = delete;
        PileBubbles& operator=(const PileBubbles&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public: // LerpMove Setting
        FLOAT4 GetMoveStartPos();
        FLOAT4 GetMoveTargetPos();
        void SetMoveStartPos(FLOAT4 _StartPos);
        void SetMoveTargetPos(FLOAT4 _TargetPos);

        float GetLerpSpeed();
        void SetLerpSpeed(float _Speed);

    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public:
        // �÷��̾� ã�� ����
        void FindStart();
        void FindStay();
        void FindEnd();

        // �������
        void AppearStart();
        void AppearStay();
        void AppearEnd();

        // ������
        void IDLEStart();
        void IDLEStay();
        void IDLEEnd();

        // �÷��̾ ���� ������ ����
        void BeShotStart();
        void BeShotStay();
        void BeShotEnd();
};


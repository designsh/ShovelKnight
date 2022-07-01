#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineInput.h>
#include <SGameEngineFSM.h>
#include <SGameEngineCollision.h>

#include "GlobalValue.h"

// �з� :
// �뵵 : 
// ���� : 
class Dozedrake_AttackBubble : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;

        SGameEngineRendererAnimation* m_AniAttackBubble;
        SGameEngineFSM<Dozedrake_AttackBubble> m_AttackBubbleFSM;
        SGameEngineCollision* m_AttackBubbleCol;

    private: // �����Ÿ� ����
        FLOAT4 m_MoveStartPos;     // ������ġ
        FLOAT4 m_MoveEndPos;      // ��ǥ����
        FLOAT4 m_UpMoveEndPos; // ��ǥ����

        FLOAT4 m_MovePos;            // ������ ����������
        float m_fMoveLerpSpeed;    // ���� �̵��ӵ�
        float m_fUpLerpSpeed;         // 
        float m_fLerpTime;                // ���� �����ð�
        float m_fMoveDistMax;        // �����ִ�����Ÿ�
        float m_fUpDistMax;            // �ϴ����� �ö󰡴� �ִ�Ÿ�

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

    public: // ��������
        FLOAT4 GetMoveEndPos();
        float GetMoveMax();
        void SetMoveDistMax(float _MaxDist);
        void SetUpDistMax(float _MaxDist);
        void SetMoveLerpSpeed(float _Speed);
        void SetUpLerpSpeed(float _Speed);

    // �浹ü
    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    // FSM ����
    public:
        // �̵�����
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // ���οö󰡴»���
        void UpMoveStart();
        void UpMoveStay();
        void UpMoveEnd();

        // �״� ����
        void DeathStart();
        void DeathStay();
        void DeathEnd();

};


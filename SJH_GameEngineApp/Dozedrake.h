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
#include "Dozedrake_AttackBubble.h" // ���� �����
#include "Dozedrake_DeathEffect.h"   // ��� ����Ʈ

// �з� :
// �뵵 : 
// ���� : Dozedrake Monster�� �ൿ �� ����� ���� �����ϴ� Ŭ����
class Dozedrake : public SGameEngineActor
{
    private: // Static Var
        static SoundPlayer m_DozedrakeSound;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        MonsterInfo m_DozedrakeInfo;

        SGameEngineRendererAnimation* m_AniDozedrake;
        SGameEngineRendererBasic* m_BeShotDozedrake;       // ���ݴ��� �̹���
        SGameEngineFSM<Dozedrake> m_DozedrakeFSM;
        SGameEngineCollision* m_DozedrakeHeadCol;              // �ǰ�����
        SGameEngineCollision* m_DozedrakeBodyCol;              // ��ü

    private: // �������
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;
        FLOAT4 m_MovePos;
        FLOAT4 m_MaxBackPos;

        float m_Speed;
        float m_MaxDist;

        bool m_LimitBackMove;

    private: // Ÿ���̺���
        SGameEngineTimeEventer<Dozedrake> m_BubbleEvent;
        SGameEngineTimeEventer<Dozedrake> m_AttackEndEvent;
        SGameEngineTimeEventer<Dozedrake> m_DeathEvent;

    private: // Ÿ���̹��� ������ 
        float m_fBlinkImageOnTime;
        float m_fBlinkImageOffTime;
        float m_fBlinkEndTime;
        bool m_bBlinkImage;

    private: // ��� ����Ʈ ���� ���� ��ǥ
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

    public: // �������Ʈ ����
        void DeathEffectStart();
        void DeathEffectStay();
        void DeathEffectEnd();

    public:
        void AttackComplete();

    public:
        void BeShotBlink();

    // �浹ü
    public:
        void HeadCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void HeadCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void HeadCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

        void BodyCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void BodyCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void BodyCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    // FSM ����
    public:
        // �÷��̾� ã�»���
        void FindStart();
        void FindStay();
        void FindEnd();

        // ������
        void IdleStart();
        void IdleStay();
        void IdleEnd();

        // ������ �̵�
        void FrontMoveStart();
        void FrontMoveStay();
        void FrontMoveEnd();

        // ���ݸ�� ����(����� ����)
        void AttackStartStart();
        void AttackStartStay();
        void AttackStartEnd();

        // ���ݸ�� ����(������ �����Ÿ��־�����)
        void AttackComplateStart();
        void AttackComplateStay();
        void AttackComplateEnd();

        // �ڷ� �̵�(�÷��̾ ���� �Ӹ� �պκ��� �ǰ�)
        void BackMoveStart();
        void BackMoveStay();
        void BackMoveEnd();

        // �������
        void DeathStart();
        void DeathStay();
        void DeathEnd();

};


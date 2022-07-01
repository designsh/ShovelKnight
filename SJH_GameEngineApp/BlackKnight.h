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

// �з� :
// �뵵 : 
// ���� : ���� ������ �̵�, �������� ���� ����
class BlackKnight : public SGameEngineActor
{
    private: // Static Var
        static SoundPlayer m_BlackKnightActionSound;

    public: // Static Func

    public:
        MonsterInfo m_BlackKnightInfo;

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererAnimation* m_AniBlackKnight;
        SGameEngineFSM<BlackKnight> m_BlackKnightFSM;

        // �浹ü 3��
        // (0 : ��ü, 1 : �Ϲݰ���, 2 : ��������)
        SGameEngineCollision* m_BlackKnightCol;
        SGameEngineCollision* m_BlackKnightNomalAttackCol;
        SGameEngineCollision* m_BlackKnightJumpAttackCol;

        // �ǰݽ� �̹���(���⺰)
        SGameEngineRendererBasic* m_BeShotLeftBlackKnight;
        SGameEngineRendererBasic* m_BeShotRightBlackKnight;

    private: // �̵����� ����
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;
        GlobalValue::BasicMoveType m_KnockBackMoveDir;
        GlobalValue::BasicMoveType m_BackJumpMoveDir;
        GlobalValue::BasicMoveType m_DeathMoveDir;

    private: // �̵� �� �ִϸ��̼� �������
        SGameEngineString m_CurAniMationName;
        SGameEngineString m_AniMationName;

        float m_Speed;
        int m_JumpAttackCnt;
        float m_HPChargeTime;
        bool m_bFirstAppear;

    private: // ���� �ȼ�üũ����
        FLOAT4 m_BossCheckPos;
        FLOAT4 m_BossCheckDir[4];
        int m_iBossCheckColor[4];

    private: // ��� ����(��)
        // ���� ����
        FLOAT4 m_MovePos;

        // �⺻ �̵�
        FLOAT4 m_DirectPos;

        // �˹�
        FLOAT4 m_KnockBackPos;
        FLOAT4 m_KnockBackPower;
        FLOAT4 m_KnockBackGravityPower;

        // ������
        FLOAT4 m_BackJumpPos;
        FLOAT4 m_BackJumpPower;
        FLOAT4 m_BackJumpGravityPower;

        // ��������
        FLOAT4 m_JumpAttackPos;
        FLOAT4 m_JumpAttackPower;
        FLOAT4 m_JumpAttackGravityPower;

        // ���
        FLOAT4 m_DeathPos;
        FLOAT4 m_DeathPower;
        FLOAT4 m_DeathGravityPower;

    private: // BeShot Image Blink����
        bool m_bBlinkImage;

        float m_fBlinkImageOnTime;
        float m_fBlinkImageOffTime;
        float m_fBlinkImageTotalTime;

    private: // �������� ����
        int m_RandomState;
        int m_PrevRandomState;

    private: // Ÿ���̺��� 
        SGameEngineTimeEventer<BlackKnight> m_LaughEventer;

    public: // constructer destructer
        BlackKnight();
        virtual ~BlackKnight();

    public: // delete constructer 
        BlackKnight(const BlackKnight& _Other) = delete;
        BlackKnight(const BlackKnight&& _Other) = delete;

    public: // delete operator
        BlackKnight& operator=(const BlackKnight& _Other) = delete;
        BlackKnight& operator=(const BlackKnight&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public: // �⺻ ������ �⺻��������
        void SetMoveDirect(GlobalValue::BasicMoveType _MoveDirect);

    public: // �ִϸ��̼� �������
        void ChangeAniMation(const SGameEngineString& _ChangeAniName);
        void DirCheck();

    public: // �̵� ����
        void MovePosCheck();
        void KnockBackPosCheck();
        void BackJumpPosCheck();
        void JumpAttackPosCheck();
        void JumpAttackHighPosCheck();
        void DeathPosCheck();

    public: // �ȼ�üũ
        void BlackKnightPixelCheck();

    public: // ��ġüũ(�÷��̾���س���ġ)
        void BasicDirectCheck();
        void KnockBackDirectCheck();
        void LaughDirectCheck();
        void BackJumpDirectCheck();
        void JumpAttackDirectCheck();
        void DeathDirectCheck();

    public: // ���º� üũ����
        void MoveStateCheck();
        void KnockBackStateCheck();
        void BackJumpStateCheck();
        void JumpAttackStateCheck();
        void JumpAttackEndCheck();
        void DeathStateCheck();

    public: // Ÿ���̺��� ����
        // Laugh Ÿ���̺���
        void LaughTimeEventerEnd();

    public: // �÷��̾����κ��� ���ݹ޾����� �̹��� Blink
        void BeShotImageBlink();
        SGameEngineRendererBasic* DirectCheckImage();

    public: // �÷��̾� ġƮ�� ���� ���� ���
        void PlayerCheetBossDeath();

    // �浹ü
    public:
        // ��ü �浹
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

        // �Ϲݰ��� �浹
        void AttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void AttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void AttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        
        // �������� �浹
        void JumpAttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void JumpAttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void JumpAttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    // FSM ����
    public:
        // ī�޶�ã�� ����(ī�޶� ������ ������)
        void FindStart();
        void FindStay();
        void FindEnd();

        // ������
        void IdleStart();
        void IdleStay();
        void IdleEnd();

        // �������
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // ������ ����
        void BackJumpStart();
        void BackJumpStay();
        void BackJumpEnd();

        // ����»���
        void LaughStart();
        void LaughStay();
        void LaughEnd();

        // �������ý��� ����
        void JumpAttackStart();
        void JumpAttackStay();
        void JumpAttackEnd();

        // �������� �ְ������� ������� ����
        void JumpAttackHighPointStart();
        void JumpAttackHighPointStay();
        void JumpAttackHighPointEnd();

        // �Ϲݰ��ݻ���
        void NomalAttackStart();
        void NomalAttackStay();
        void NomalAttackEnd();

        // ��ų������¡ ����
        void SkillChargingStart();
        void SkillChargingStay();
        void SkillChargingEnd();

        // ��ų������ ����
        void SkillAttackStart();
        void SkillAttackStay();
        void SkillAttackEnd();

        // �˹����(�÷��̾����κ��� �ǰݽ�)
        void KnockBackStart();
        void KnockBackStay();
        void KnockBackEnd();

        // ������� ����(�̶� �浹ü ���)
        void DeathStart();
        void DeathStay();
        void DeathEnd();

        // ������ ������ ����
        void DeathMotionStart();
        void DeathMotionStay();
        void DeathMotionEnd();
};


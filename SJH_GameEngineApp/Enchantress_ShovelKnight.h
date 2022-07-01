#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>
#include <SGameEngineTimeEventer.h>
#include <SGameEngineCollision.h>
#include <SGameEngineSound.h>

#include "ShovelKnightInfo.h"
#include "GlobalValue.h"

// �з� :
// �뵵 : 
// ���� : 
class Enchantress_ShovelKnight : public SGameEngineActor
{
    private: // Static Var
        static SoundPlayer m_EnchantressPlayerSound;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererAnimation* m_AniPlayer;
        SGameEngineFSM<Enchantress_ShovelKnight> m_ShovelKnightFSM;

    private: // �÷��̾� �浹ü
        // ���¿� 1��, �ϴ� 1���� ����
        SGameEngineCollision* m_PlayerCol;           // SetCheckData(0)
        SGameEngineCollision* m_PlayerBotCol;     // SetCheckData(1)

        // �÷��̾��� ���ݸ�� �浹ü
        SGameEngineCollision* m_AttackCol;

        // �÷��̾��� �������ݸ�� �浹ü
        SGameEngineCollision* m_JumpAttackCol;

    public: // �÷��̾� �⺻����
        ShovelKnightInfo m_PlayerInfo;

    private: // �÷��̾� �̵�����
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;
        
    private: // ī�޶� ���� ����
        GlobalValue::BasicMoveType m_CamMoveDir;
        GlobalValue::BasicMoveType m_PrevCamMoveDir;

    private: // �÷��̾� �̵����⿡ ���� �ִϸ��̼�
        SGameEngineString m_CurAniMationName;
        SGameEngineString m_AniMationName;

    private: // �÷��̾� ����
        FLOAT4 m_MovePos;
        FLOAT4 m_DirectPos;
        FLOAT4 m_JumpPos;
        FLOAT4 m_JumpPower;
        FLOAT4 m_JumpGravityPowerPos;
        FLOAT4 m_KnockBackPos;
        FLOAT4 m_KnockBackPower;
        FLOAT4 m_KnockBackGravityPowerPos;

    private: // Ÿ���̺���
        SGameEngineTimeEventer<Enchantress_ShovelKnight> m_JumpEventer;
        SGameEngineTimeEventer<Enchantress_ShovelKnight> m_KnockBackEventer;

    private: // ī�޶� ����
        bool m_bWallCollision;                                                         // �÷��̾� �̵��� Ư���� �浹
        bool m_LerpStartMove;                                                        // �浹�� ���⿡���� m_LerpCamPos���Ϸ� �� ķ �̵�

        FLOAT4 m_LerpCamPos;                                                      // Lerp Move Pos(�����̵� ��ġ)
        FLOAT4 m_LerpStartPos;                                                      // Lerp Start Pos(�������� ��ġ:����ī�޶���ġ)
        FLOAT4 m_LerpEndPos;                                                       // Lerp End Pos(�������� ��ġ:������ũ��(���⿡����))
        float  m_LerpTime;                                                               // Lerp Ratio Time(�����̵� ��������)

    private: // �÷��̾� �ȼ��浹
        FLOAT4 m_PlayerCheckPos;
        FLOAT4 m_PlayerCheckDir[5];
        int m_iPlayerCheckColor[5];

    private: // ī�޶� �ȼ��浹
        FLOAT4 m_CamCheckPos;
        FLOAT4 m_CamCheckDir[4];
        int m_iCamCheckColor[4];

    private: // �÷��̾� ���� �� ��������(ī�޶���)����
        FLOAT4 m_PlayerAppearPos;

    private: // �������� �浹üũ�� Flag
        bool m_bJumping;
        bool m_bKnockBack;

    public: // constructer destructer
        Enchantress_ShovelKnight();
        virtual ~Enchantress_ShovelKnight();

    public: // delete constructer 
        Enchantress_ShovelKnight(const Enchantress_ShovelKnight& _Other) = delete;
        Enchantress_ShovelKnight(const Enchantress_ShovelKnight&& _Other) = delete;

    public: // delete operator
        Enchantress_ShovelKnight& operator=(const Enchantress_ShovelKnight& _Other) = delete;
        Enchantress_ShovelKnight& operator=(const Enchantress_ShovelKnight&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public: // ġƮ��� ����
        void CheetCheck();

    public: // �� ���º� ��ġ�̵�
        void BossFindIDLE_MovePosCheck();
        void BossFindMOVE_MovePosCheck();
        void Idle_MovePosCheck();
        void Move_MovePosCheck();
        void Jump_MovePosCheck();
        void JumpAttack_MovePosCheck();
        void JumpAttackCol_MovePosCheck();
        void KnockBack_MovePosCheck();

    public: // �� ���º� �ȼ�üũ, Űüũ ��
        void BossFindIDLE_StateCheck();
        void BossFindMOVE_StateCheck();
        void Idle_StateCheck();
        void Move_StateCheck();
        void Jump_StateCheck();
        void JumpAttack_StateCheck();
        void JumpAttackCol_StateCheck();
        void KnockBack_StateCheck();

    public: // Alpha �����Լ�
        void HitAlphaInStart();
        void HitAlphaInStay();
        void HitAlphaInEnd();
        void HitAlphaOutStart();
        void HitAlphaOutStay();
        void HitAlphaOutEnd();

    public: // �÷��̾� �⺻���� �� ��������
        // �÷��̾� �⺻���� ����
        void SetPlayerInfomation();

        // �÷��̾� �׼��� ���� Ű ����
        void CreateActionKey();

        // �÷��̾� �浹ü ����
        void CreatePlayerCollision();

        // �÷��̾� �ִϸ��̼� ����
        void CreatePlayerAnimation();

        // �÷��̾� FSM ���� ����
        void CreatePlayerFSMState();

    public: // �̵��� ���� �ִϸ��̼� ����
        void ChangeAniMation(const SGameEngineString& _ChangeAniName);
        void DirCheck();

    public: // �ȼ�üũ ����
        void CamPixelCheck();
        void PlayerPixelCheck();

    public: // ī�޶� ����
        void LerpCamMove();

    public: // �÷��̾� ��������
        ShovelKnightInfo& GetPlayerInfo();

    public: // �浹ü
        // ����(0)
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

        // �ٴ�(1)
        void BottomCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void BottomCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void BottomCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

        // ���ݸ��
        void AttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void AttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void AttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

        // �������ݸ��
        void JumpAttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void JumpAttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void JumpAttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public: // FSM ����
        // ����ã�� ������
        void BossFindIdleStart();
        void BossFindIdleStay();
        void BossFindIdleEnd();

        // ���� ã�� �������((�����Ÿ� �̵��ϸ� ���º���)
        void BossFindMoveStart();
        void BossFindMoveStay();
        void BossFindMoveEnd();

        // ī�޶��� ������(ī�޶�� ���͸� ã�´�.)
        void CamLerpingIdleStart();
        void CamLerpingIdleStay();
        void CamLerpingIdleEnd();

        // ���(����) ����
        void IdleStart();
        void IdleStay();
        void IdleEnd();

        // �⺻�̵� ����(��, ��)
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // ���� ����
        void HighJumpCheckEvent();
        void LowJumpCheckEvent();
        void JumpStart();
        void JumpStay();
        void JumpEnd();

        // �������� ����
        void JumpAttackStart();
        void JumpAttackStay();
        void JumpAttackEnd();

        // ��������(Object �浹)
        void JumpAttackColStart();
        void JumpAttackColStay();
        void JumpAttackColEnd();

        // �⺻���� ����
        void AttackStart();
        void AttackStay();
        void AttackEnd();

        // �˹� ����
        void KnockBackStart();
        void KnockBackStay();
        void KnockBackEnd();

        // ���б�縦 �޾Ƴ��� ����
        void ShildKnightColStart();
        void ShildKnightColStay();
        void ShildKnightColEnd();

        // ��������ȯ ����
        void EndingSceneChangeStart();
        void EndingSceneChangeStay();
        void EndingSceneChangeEnd();

};


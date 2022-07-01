#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineInput.h>
#include <SGameEngineFSM.h>
#include <SGameEngineSound.h>
#include <SGameEngineTimeEventer.h>
#include <SGameEngineRendererTile.h>
#include <SGameEngineDirectory.h>
#include <SGameEngineCollision.h>

#include "ShovelKnightInfo.h"
#include "GlobalValue.h"

#include <vector>

// �з� :
// �뵵 : 
// ���� : 
class MovingPlatform;
class ShovelKnight : public SGameEngineActor
{
    public: // Static Var
        static SoundPlayer m_StageBgm;
        static SoundPlayer m_ActionSound;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererAnimation* m_AniPlayer;
        SGameEngineFSM<ShovelKnight> m_ShovelKnightFSM;

    private: // �÷��̾� �浹ü
        // ���¿� 1��, �ϴ� 1���� ����
        SGameEngineCollision* m_PlayerCol;           // SetCheckData(0)
        SGameEngineCollision* m_PlayerBotCol;     // SetCheckData(1)

        // �÷��̾��� ���ݸ�� �浹ü
        SGameEngineCollision* m_AttackCol;

        // �÷��̾��� �������ݸ�� �浹ü
        SGameEngineCollision* m_JumpAttackCol;

    private: // �÷��̾� ����
        FLOAT4 m_MovePos;
        FLOAT4 m_DirectPos;
        FLOAT4 m_GravityPos;
        FLOAT4 m_JumpPos;
        FLOAT4 m_JumpPower;
        FLOAT4 m_JumpGravityPowerPos;
        FLOAT4 m_KnockBackPos;
        FLOAT4 m_KnockBackPower;
        FLOAT4 m_KnockBackGravityPowerPos;

    private: // �÷��̾� �̵�����
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;
        GlobalValue::BasicMoveType m_LadderPrevMoveDir;

    private: // �÷��̾� �̵����⿡ ���� �ִϸ��̼�
        SGameEngineString m_CurAniMationName;
        SGameEngineString m_AniMationName;

    private: // Ÿ���̺���
        SGameEngineTimeEventer<ShovelKnight> m_JumpEventer;
        SGameEngineTimeEventer<ShovelKnight> m_KnockBackEventer;

    private: // �÷��̾� ����
        float m_fAngle;

    private: // Flag ����
        bool m_bJumping;
        bool m_bLadderCollision;
        bool m_bDirtBlockCollision;
        bool m_bFinalBossRoom;
        bool m_bFinalBossHPCharge;
        bool m_bEffectSound;
        bool m_bAppearIdle;

    private: // �÷��̾� �ȼ��浹
        FLOAT4 m_PlayerCheckPos;
        FLOAT4 m_PlayerCheckDir[5];
        int m_iPlayerCheckColor[5];

    private: // ī�޶� �ȼ��浹
        FLOAT4 m_CamCheckPos;
        FLOAT4 m_CamCheckDir[4];
        int m_iCamCheckColor[4];

    private: // ī�޶� ����
        bool m_bWallCollision;                                                         // �÷��̾� �̵��� Ư���� �浹
        bool m_LerpStartMove;                                                        // �浹�� ���⿡���� m_LerpCamPos���Ϸ� �� ķ �̵�

        FLOAT4 m_LerpCamPos;                                                      // Lerp Move Pos(�����̵� ��ġ)
        FLOAT4 m_LerpStartPos;                                                      // Lerp Start Pos(�������� ��ġ:����ī�޶���ġ)
        FLOAT4 m_LerpEndPos;                                                       // Lerp End Pos(�������� ��ġ:������ũ��(���⿡����))
        float  m_LerpTime;                                                               // Lerp Ratio Time(�����̵� ��������)

    private: // BrokenTile ��������
        SGameEngineDirectory m_BrokenTileFilePath;
        SGameEngineRendererTile* m_BrokenTile;
        FLOAT4 m_PlayerPosIndex;
        FLOAT4 m_PlayerAttackPosIndex;
        std::list<std::vector<FLOAT4>> m_BrokenAllTile;
        SGameEngineTimeEventer<ShovelKnight> m_BrokenEventer;

    public: // �÷��̾� �⺻����
        ShovelKnightInfo m_PlayerInfo;

    public: // �÷��̾� ġƮ Flag
        bool m_bInvincibility; // �������
        bool m_bTelePort;

        FLOAT4 m_PlayerTeleportStartPos;
        FLOAT4 m_CamTeleportStartPos;

    public:
        bool m_bFinalBossDeath;

    public: // constructer destructer
        ShovelKnight();
        virtual ~ShovelKnight();

    public: // delete constructer 
        ShovelKnight(const ShovelKnight& _Other) = delete;
        ShovelKnight(const ShovelKnight&& _Other) = delete;

    public: // delete operator
        ShovelKnight& operator=(const ShovelKnight& _Other) = delete;
        ShovelKnight& operator=(const ShovelKnight&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public: // �÷��̾� �⺻���� �� ��������
        // �÷��̾� �⺻���� ����
        void SetPlayerInfomation();

        // �÷��̾� �׼��� ���� Ű ����
        void CreateActionKey();

        // �÷��̾� ���ݿ� ���� �μ����� Ÿ�ϸ� �ε�
        void LoadBrokenTileMap();
        int GetBrokenTileImageIndex(const FLOAT4& _CheckPos);
        void SetPlayerPosIndex();
        void BrokenTileStay();
        void RightFind(FLOAT4 _StartIndex);
        void LeftFind(FLOAT4 _StartIndex);

        // �÷��̾� �浹ü ����
        void CreatePlayerCollision();

        // �÷��̾� �ִϸ��̼� ����
        void CreatePlayerAnimation();

        // �÷��̾� FSM ���� ����
        void CreatePlayerFSMState();

    public: // �÷��̾� ��������
        ShovelKnightInfo& GetPlayerInfo();

    public: // Alpha �����Լ�
        void HitAlphaInStart();
        void HitAlphaInStay();
        void HitAlphaInEnd();
        void HitAlphaOutStart();
        void HitAlphaOutStay();
        void HitAlphaOutEnd();

    public:
        void CheckFinalBossRoom();

    public: // �̵��� ���� �ִϸ��̼� ����
        void ChangeAniMation(const SGameEngineString& _ChangeAniName);
        void DirCheck();

    public: // �ȼ�üũ ����
        void CamPixelCheck();
        void PlayerPixelCheck();

    public: // ī�޶� ����
        void LerpCamMove();

    public: // ġƮüũ
        void CheetKeyDownCheck();

    public:
        void BossVictoryStateChagne();

    public: // ���Ͱ���(�̵�, �׼� ���)
        // �⺻����
        void IdlePos_Check();
        void FallingPos_Check();
        void MovePos_Check();
        void LadderMovePos_Check();
        void LadderJumpPos_Check();
        void JumpPos_Check();
        void JumpAttackPos_Check();
        void JumpAttackColPos_Check();
        void KnockBackPos_Check();

        // ������Ʈ �浹����
        void RideIdlePos_Check();
        void RideMovePos_Check();
        void RideAttackPos_Check();

    public: // FSM ���¿� ���� üũ
        // �⺻����
        void IdleState_Check();
        void FallingState_Check();
        void MoveState_Check();
        void LadderMoveState_Check();
        void LadderJumpState_Check();
        void JumpState_Check();
        void JumpAttackState_Check();
        void JumpAttackColState_Check();
        void KnockBackState_Check();

        // ������Ʈ �浹����
        void RideIdleState_Check();
        void RideMoveState_Check();
        
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

    public: // FSM ����(�⺻)
        // ���� ����
        void AppearStart();
        void AppearStay();
        void AppearEnd();

        // ���(����) ����
        void IdleStart();
        void IdleStay();
        void IdleEnd();

        // Falling ����
        void FallingStart();
        void FallingStay();
        void FallingEnd();

        // �⺻�̵� ����(��, ��)
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // ��ٸ��̵� ����(��, ��)
        void LadderMoveStart();
        void LadderMoveStay();
        void LadderMoveEnd();

        // ��ٸ� �̵��� ����
        void LadderJumpStart();
        void LadderJumpStay();
        void LadderJumpEnd();

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

        // ��������(Object or Monster �浹)
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

        // ����óġ(�¸�)
        void BossVictoryStart();
        void BossVictoryStay();
        void BossVictoryEnd();

    public: // FSM ����(������Ʈ�� �浹���� ����)
        // ������Ʈ ž�»��� IDLE
        void RideIdleStart();
        void RideIdleStay();
        void RideIdleEnd();

        // ������Ʈ ž�»��� Move
        void RideMoveStart();
        void RideMoveStay();
        void RideMoveEnd();

        // ������Ʈ ž�»��� Attack
        void RideAttackStart();
        void RideAttackStay();
        void RideAttackEnd();

    public: // ġƮ������(������� - ��� �繰�� �����ϰ� �̵��Ѵ�.)
        void CheetFreeStart();
        void CheetFreeStay();
        void CheetFreeEnd();

};


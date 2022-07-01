#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineInput.h>
#include <SGameEngineFSM.h>
#include <SGameEngineTimeEventer.h>
#include <SGameEngineRendererTile.h>
#include <SGameEngineDirectory.h>
#include <SGameEngineCollision.h>
#include <SGameEngineSound.h>

#include "MonsterInfo.h"
#include "GlobalValue.h"
#include "EnchantressBrokenTile.h"

#include <vector>

// �з� :
// �뵵 : 
// ���� : 
class Enchantress_FinalBoss : public SGameEngineActor
{
    private: // Static Var
        static SoundPlayer m_FinalBossSound;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererAnimation* m_AniEnchantress;
        SGameEngineRendererAnimation* m_AniShildKnight;
        SGameEngineFSM<Enchantress_FinalBoss> m_EnchantressFSM;
        SGameEngineCollision* m_EnchantressCol;

        SGameEngineRendererBasic* m_LeftBeShotImage;
        SGameEngineRendererBasic* m_RightBeShotImage;

    public:
        MonsterInfo m_EnchantressInfo;

    private: // �μ����� ������Ʈ ����(������ �ٴ�Ÿ��)
        // Load File & File Info Save
        SGameEngineRendererTile* m_BrokenTile;
        SGameEngineDirectory m_BrokenTileFilePath;

        // �ڷᱸ���� ����
        int m_iDataStructXSize;
        int m_iYSearchIndex;
        std::vector<std::vector<EnchantressBrokenTile*>> m_BrokenObject;

    private: // �̵����� �� �ִϸ��̼� ����
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;
        GlobalValue::BasicMoveType m_CamMoveDir;
        GlobalValue::BasicMoveType m_PrevCamMoveDir;

        SGameEngineString m_CurAniMationName;
        SGameEngineString m_AniMationName;

    private: // ����(��) ����
        FLOAT4 m_MovePos;
        FLOAT4 m_DirectPos;

    private: // ��Ÿ
        float m_fPatternStartTime;
        float m_fStateChangeDelay;
        float m_fCamShakeTime;
        bool m_bAppearMove;

        FLOAT4 m_MoveTargetPos;
        int m_iBossAttackSkillCnt;
        int m_iBossDownAttackSkillCnt;
        int m_iBossUpAttackSkillCnt;
        int m_iTileObjectCnt;

        FLOAT4 m_DownShotMove;
        FLOAT4 m_UpShotMove;

        bool m_bRegenSkilling;
        bool m_bBossFalling;

    private: // ����� ���� ����(ī�޶� �̵���Ų��)
        bool m_DeathLerpStart;
        float m_DeathLerpTime;
        FLOAT4 m_DeathMoveStartPos;
        FLOAT4 m_DeathMoveEndPos;
        FLOAT4 m_DeathLerpPos;

        FLOAT4 m_DeathCamMoveStartPos;
        FLOAT4 m_DeathCamMoveEndPos;
        FLOAT4 m_DeathCamLerpPos;

    private: // ��� ����Ʈ ����
        SGameEngineTimeEventer<Enchantress_FinalBoss> m_DeathImageChange;
        SGameEngineTimeEventer<Enchantress_FinalBoss> m_DeathImageChangeEnd;
        SGameEngineTimeEventer<Enchantress_FinalBoss> m_DeathCamShake;

        bool m_bDeathEffectMove;

    private: // BeShot Image Blink ����
        bool m_bBlinkImage;
        float m_fBlinkImageOnTime;
        float m_fBlinkImageOffTime;
        float m_fBlinkImageTotalTime;

    private: // ī�޶� �ȼ��浹
        FLOAT4 m_CamCheckPos;
        FLOAT4 m_CamCheckDir[4];
        int m_iCamCheckColor[4];

    private: // ���� ���� ����
        bool m_LerpStartMove;
        FLOAT4 m_LerpMovePos;
        FLOAT4 m_LerpStartPos;
        float  m_LerpTime;

    public: // constructer destructer
        Enchantress_FinalBoss();
        virtual ~Enchantress_FinalBoss();

    public: // delete constructer 
        Enchantress_FinalBoss(const Enchantress_FinalBoss& _Other) = delete;
        Enchantress_FinalBoss(const Enchantress_FinalBoss&& _Other) = delete;

    public: // delete operator
        Enchantress_FinalBoss& operator=(const Enchantress_FinalBoss& _Other) = delete;
        Enchantress_FinalBoss& operator=(const Enchantress_FinalBoss&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public: // BrokenObject �ش� ���� ���� �� ����
        void DelBrokenObject(int _IndexX, int _IndexY);
        bool RegenBrokenObject(FLOAT4 _BrokenTileIndex, FLOAT4 _MyIndex);

    public: // ���� ���� ����
        void Create_BossCollision();
        void Create_BossAnimation();
        void Create_BossFSMState();
        void Create_BossBeShotImage();

    public: // Broken Object ����
        void DataStructSetting();
        void BrokenObjectSetting();
        void LoadBrokenTile();
        void CreateBrokenObject();

        // Broken Object �������� ������ ���� ��� üũ
        void BrokenTileObjectCheck();
        void SetRegenSkillingFlagOff();

    public: // �̵����⿡ ���� �ִϸ��̼� ����
        void ChangeAniMation(const SGameEngineString& _ChangeAniName);
        void DirCheck();

    public: // ī�޶� �ȼ�üũ
        void AppearCamPixelCheck();

    public: // �ǰ� �̹��� Blink
        void BeShotImageBlink();
        SGameEngineRendererBasic* DirectCheckImage();

    public: // ������ �������� ������ �������� ������ On
        // �÷��̾ üũ�ؾ� �ϱ� ������ ���� ��ȯ�Ѵ�.
        bool GetBossFallingFlag();

    public: // �̵����� ���� Check
        // ������
        void IdleState_MovePosCheck();

        // �̵� ����
        void MoveState_MovePosCheck();

        // ���� ��ų ���� ����
        void AttackSkillChargingState_MovePosCheck();
        void DownAttackSkillChargingState_MovePosCheck();
        void UpAttackSkillChargingState_MovePosCheck();

        // ���� ��ų �߻� ����
        void AttackSkillShotState_MovePosCheck();
        void DownAttackSkillShotState_MovePosCheck();
        void UpAttackSkillShotState_MovePosCheck();

        // ���� ��ų �߻��� �̵� ����
        void DownAttackSkillShotMoveState_MovePosCheck();
        void UpAttackSkillShotMoveState_MovePosCheck();

        // ���� ��ų ���� ����
        void RegenSkillChargingState_MovePosCheck();

    public: // ���¿� ���� Check
        // ��� ����
        void IdleState_StateCheck();

        // �̵� ����
        void MoveState_StateCheck();

        // ���� ��ų ���� ����
        void AttackSkillChargingState_StateCheck();
        void DownAttackSkillChargingState_StateCheck();
        void UpAttackSkillChargingState_StateCheck();

        // ���� ��ų �߻� ����
        void AttackSkillShotState_StateCheck();
        void DownAttackSkillShotState_StateCheck();
        void UpAttackSkillShotState_StateCheck();

        // ���� ��ų �߻��� �̵� ����
        void DownAttackSkillShotMoveState_StateCheck();
        void UpAttackSkillShotMoveState_StateCheck();

        // ���� ��ų ���� ����
        void RegenSkillChargingState_StateCheck();

        // Death ȿ��
        void FinalBossImageStart();
        void FinalBossImageStay();
        void FinalBossImageEnd();
        void ShildKnightImageStart();
        void ShildKnightImageStay();
        void ShildKnightImageEnd();
        void ImageChangeEnd();

        // Camera Shake
        void CamShakeStart();
        void CamShakeStay();
        void CamShakeEnd();

    public: // ���ų ġƮ �ߵ�
        void FinalBoss_InstantKill();

    public: // �浹ü
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public: // FSM ����
        // ī�޶� ã�� �� ����
        void FindStart();
        void FindStay();
        void FindEnd();

        // ī�޶� ã�� ����
        void CamFoundStart();
        void CamFoundStay();
        void CamFoundEnd();

        // ���� ����
        void AppearStart();
        void AppearStay();
        void AppearEnd();

        // ���(����) ����
        void IdleStart();
        void IdleStay();
        void IdleEnd();

        // �̵� ����
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // ���ݽ�ų ���� ����(��,��)
        void AttackSkillChargingStart();
        void AttackSkillChargingStay();
        void AttackSkillChargingEnd();

        // ���ݽ�ų ���� ����(�Ʒ�)
        void DownAttackSkillChargingStart();
        void DownAttackSkillChargingStay();
        void DownAttackSkillChargingEnd();

        // ���ݽ�ų ���� ����(��)
        void UpAttackSkillChargingStart();
        void UpAttackSkillChargingStay();
        void UpAttackSkillChargingEnd();

        // ���� ��ų ��Ÿ���� ����(��, ��)
        void BasicAttackSkillShotStart();
        void BasicAttackSkillShotStay();
        void BasicAttackSkillShotEnd();

        // ���� ��ų �Ʒ��ΰ��� ����
        void DownAttackSkillShotStart();
        void DownAttackSkillShotStay();
        void DownAttackSkillShotEnd();

        // ���� ��ų �Ʒ��� ���� �� �̵�����
        void DownAttackSkillShotMoveStart();
        void DownAttackSkillShotMoveStay();
        void DownAttackSkillShotMoveEnd();

        // ���� ��ų ���ΰ��� ����
        void UpAttackSkillShotStart();
        void UpAttackSkillShotStay();
        void UpAttackSkillShotEnd();

        // ���� ��ų ���� ���� �� �̵�����
        void UpAttackSkillShotMoveStart();
        void UpAttackSkillShotMoveStay();
        void UpAttackSkillShotMoveEnd();

        // ���� ��ų ���� ����
        void BlockRegenSkillChargingStart();
        void BlockRegenSkillChargingStay();
        void BlockRegenSkillChargingEnd();

        // ���� ��ų �ߵ��� ������
        void BlockRegenSkillIdleStart();
        void BlockRegenSkillIdleStay();
        void BlockRegenSkillIdleEnd();

        // ��� ����
        void DeathStart();
        void DeathStay();
        void DeathEnd();

        // ��� ���� ~ ��ǥ�����̵�
        void DeathMoveStart();
        void DeathMoveStay();
        void DeathMoveEnd();

        // ī�޶� ����ũ ȿ�� ����
        void DeathCamShakeEffectStart();
        void DeathCamShakeEffectStay();
        void DeathCamShakeEffectEnd();

        // ī�޶� ����ũ ȿ�� ������ �̹��� ������
        void DeathEffectStart();
        void DeathEffectStay();
        void DeathEffectEnd();

        // ȿ�� ���� �� �̵�
        void DeathEffectMoveStart();
        void DeathEffectMoveStay();
        void DeathEffectMoveEnd();


};


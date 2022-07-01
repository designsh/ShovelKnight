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

// 분류 :
// 용도 : 
// 설명 : 
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

    private: // 부서지는 오브젝트 관리(전투씬 바닥타일)
        // Load File & File Info Save
        SGameEngineRendererTile* m_BrokenTile;
        SGameEngineDirectory m_BrokenTileFilePath;

        // 자료구조로 관리
        int m_iDataStructXSize;
        int m_iYSearchIndex;
        std::vector<std::vector<EnchantressBrokenTile*>> m_BrokenObject;

    private: // 이동방향 및 애니메이션 관련
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;
        GlobalValue::BasicMoveType m_CamMoveDir;
        GlobalValue::BasicMoveType m_PrevCamMoveDir;

        SGameEngineString m_CurAniMationName;
        SGameEngineString m_AniMationName;

    private: // 벡터(힘) 관련
        FLOAT4 m_MovePos;
        FLOAT4 m_DirectPos;

    private: // 기타
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

    private: // 사망시 무브 관련(카메라도 이동시킨다)
        bool m_DeathLerpStart;
        float m_DeathLerpTime;
        FLOAT4 m_DeathMoveStartPos;
        FLOAT4 m_DeathMoveEndPos;
        FLOAT4 m_DeathLerpPos;

        FLOAT4 m_DeathCamMoveStartPos;
        FLOAT4 m_DeathCamMoveEndPos;
        FLOAT4 m_DeathCamLerpPos;

    private: // 사망 이펙트 관련
        SGameEngineTimeEventer<Enchantress_FinalBoss> m_DeathImageChange;
        SGameEngineTimeEventer<Enchantress_FinalBoss> m_DeathImageChangeEnd;
        SGameEngineTimeEventer<Enchantress_FinalBoss> m_DeathCamShake;

        bool m_bDeathEffectMove;

    private: // BeShot Image Blink 관련
        bool m_bBlinkImage;
        float m_fBlinkImageOnTime;
        float m_fBlinkImageOffTime;
        float m_fBlinkImageTotalTime;

    private: // 카메라 픽셀충돌
        FLOAT4 m_CamCheckPos;
        FLOAT4 m_CamCheckDir[4];
        int m_iCamCheckColor[4];

    private: // 무브 러프 관련
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

    public: // BrokenObject 해당 액터 삭제 및 생성
        void DelBrokenObject(int _IndexX, int _IndexY);
        bool RegenBrokenObject(FLOAT4 _BrokenTileIndex, FLOAT4 _MyIndex);

    public: // 보스 생성 관련
        void Create_BossCollision();
        void Create_BossAnimation();
        void Create_BossFSMState();
        void Create_BossBeShotImage();

    public: // Broken Object 관련
        void DataStructSetting();
        void BrokenObjectSetting();
        void LoadBrokenTile();
        void CreateBrokenObject();

        // Broken Object 일정개수 유지를 위해 계속 체크
        void BrokenTileObjectCheck();
        void SetRegenSkillingFlagOff();

    public: // 이동방향에 따른 애니메이션 변경
        void ChangeAniMation(const SGameEngineString& _ChangeAniName);
        void DirCheck();

    public: // 카메라 픽셀체크
        void AppearCamPixelCheck();

    public: // 피격 이미지 Blink
        void BeShotImageBlink();
        SGameEngineRendererBasic* DirectCheckImage();

    public: // 보스가 사망모션을 끝내고 떨어지고 있을때 On
        // 플레이어가 체크해야 하기 때문에 값을 반환한다.
        bool GetBossFallingFlag();

    public: // 이동량에 대한 Check
        // 대기상태
        void IdleState_MovePosCheck();

        // 이동 상태
        void MoveState_MovePosCheck();

        // 공격 스킬 장전 상태
        void AttackSkillChargingState_MovePosCheck();
        void DownAttackSkillChargingState_MovePosCheck();
        void UpAttackSkillChargingState_MovePosCheck();

        // 공격 스킬 발사 상태
        void AttackSkillShotState_MovePosCheck();
        void DownAttackSkillShotState_MovePosCheck();
        void UpAttackSkillShotState_MovePosCheck();

        // 공격 스킬 발사중 이동 상태
        void DownAttackSkillShotMoveState_MovePosCheck();
        void UpAttackSkillShotMoveState_MovePosCheck();

        // 리젠 스킬 장전 상태
        void RegenSkillChargingState_MovePosCheck();

    public: // 상태에 대한 Check
        // 대기 상태
        void IdleState_StateCheck();

        // 이동 상태
        void MoveState_StateCheck();

        // 공격 스킬 장전 상태
        void AttackSkillChargingState_StateCheck();
        void DownAttackSkillChargingState_StateCheck();
        void UpAttackSkillChargingState_StateCheck();

        // 공격 스킬 발사 상태
        void AttackSkillShotState_StateCheck();
        void DownAttackSkillShotState_StateCheck();
        void UpAttackSkillShotState_StateCheck();

        // 공격 스킬 발사중 이동 상태
        void DownAttackSkillShotMoveState_StateCheck();
        void UpAttackSkillShotMoveState_StateCheck();

        // 리젠 스킬 장전 상태
        void RegenSkillChargingState_StateCheck();

        // Death 효과
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

    public: // 즉시킬 치트 발동
        void FinalBoss_InstantKill();

    public: // 충돌체
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public: // FSM 상태
        // 카메라 찾는 중 상태
        void FindStart();
        void FindStay();
        void FindEnd();

        // 카메라 찾음 상태
        void CamFoundStart();
        void CamFoundStay();
        void CamFoundEnd();

        // 등장 상태
        void AppearStart();
        void AppearStay();
        void AppearEnd();

        // 대기(정지) 상태
        void IdleStart();
        void IdleStay();
        void IdleEnd();

        // 이동 상태
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // 공격스킬 장전 상태(왼,우)
        void AttackSkillChargingStart();
        void AttackSkillChargingStay();
        void AttackSkillChargingEnd();

        // 공격스킬 장전 상태(아래)
        void DownAttackSkillChargingStart();
        void DownAttackSkillChargingStay();
        void DownAttackSkillChargingEnd();

        // 공격스킬 장전 상태(위)
        void UpAttackSkillChargingStart();
        void UpAttackSkillChargingStay();
        void UpAttackSkillChargingEnd();

        // 공격 스킬 평타공격 상태(왼, 우)
        void BasicAttackSkillShotStart();
        void BasicAttackSkillShotStay();
        void BasicAttackSkillShotEnd();

        // 공격 스킬 아래로공격 상태
        void DownAttackSkillShotStart();
        void DownAttackSkillShotStay();
        void DownAttackSkillShotEnd();

        // 공격 스킬 아래로 공격 중 이동상태
        void DownAttackSkillShotMoveStart();
        void DownAttackSkillShotMoveStay();
        void DownAttackSkillShotMoveEnd();

        // 공격 스킬 위로공격 상태
        void UpAttackSkillShotStart();
        void UpAttackSkillShotStay();
        void UpAttackSkillShotEnd();

        // 공격 스킬 위로 공격 중 이동상태
        void UpAttackSkillShotMoveStart();
        void UpAttackSkillShotMoveStay();
        void UpAttackSkillShotMoveEnd();

        // 리젠 스킬 장전 상태
        void BlockRegenSkillChargingStart();
        void BlockRegenSkillChargingStay();
        void BlockRegenSkillChargingEnd();

        // 리젠 스킬 발동중 대기상태
        void BlockRegenSkillIdleStart();
        void BlockRegenSkillIdleStay();
        void BlockRegenSkillIdleEnd();

        // 사망 상태
        void DeathStart();
        void DeathStay();
        void DeathEnd();

        // 사망 상태 ~ 목표지점이동
        void DeathMoveStart();
        void DeathMoveStay();
        void DeathMoveEnd();

        // 카메라 쉐이크 효과 상태
        void DeathCamShakeEffectStart();
        void DeathCamShakeEffectStay();
        void DeathCamShakeEffectEnd();

        // 카메라 쉐이크 효과 종료후 이미지 깜빡임
        void DeathEffectStart();
        void DeathEffectStay();
        void DeathEffectEnd();

        // 효과 종료 후 이동
        void DeathEffectMoveStart();
        void DeathEffectMoveStay();
        void DeathEffectMoveEnd();


};


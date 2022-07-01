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

// 분류 :
// 용도 : 
// 설명 : 최종 보스의 이동, 공격패턴 등을 관리
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

        // 충돌체 3개
        // (0 : 몸체, 1 : 일반공격, 2 : 점프공격)
        SGameEngineCollision* m_BlackKnightCol;
        SGameEngineCollision* m_BlackKnightNomalAttackCol;
        SGameEngineCollision* m_BlackKnightJumpAttackCol;

        // 피격시 이미지(방향별)
        SGameEngineRendererBasic* m_BeShotLeftBlackKnight;
        SGameEngineRendererBasic* m_BeShotRightBlackKnight;

    private: // 이동방향 관련
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;
        GlobalValue::BasicMoveType m_KnockBackMoveDir;
        GlobalValue::BasicMoveType m_BackJumpMoveDir;
        GlobalValue::BasicMoveType m_DeathMoveDir;

    private: // 이동 및 애니메이션 변경관련
        SGameEngineString m_CurAniMationName;
        SGameEngineString m_AniMationName;

        float m_Speed;
        int m_JumpAttackCnt;
        float m_HPChargeTime;
        bool m_bFirstAppear;

    private: // 보스 픽셀체크관련
        FLOAT4 m_BossCheckPos;
        FLOAT4 m_BossCheckDir[4];
        int m_iBossCheckColor[4];

    private: // 모든 벡터(힘)
        // 벡터 총합
        FLOAT4 m_MovePos;

        // 기본 이동
        FLOAT4 m_DirectPos;

        // 넉백
        FLOAT4 m_KnockBackPos;
        FLOAT4 m_KnockBackPower;
        FLOAT4 m_KnockBackGravityPower;

        // 백점프
        FLOAT4 m_BackJumpPos;
        FLOAT4 m_BackJumpPower;
        FLOAT4 m_BackJumpGravityPower;

        // 점프공격
        FLOAT4 m_JumpAttackPos;
        FLOAT4 m_JumpAttackPower;
        FLOAT4 m_JumpAttackGravityPower;

        // 사망
        FLOAT4 m_DeathPos;
        FLOAT4 m_DeathPower;
        FLOAT4 m_DeathGravityPower;

    private: // BeShot Image Blink관련
        bool m_bBlinkImage;

        float m_fBlinkImageOnTime;
        float m_fBlinkImageOffTime;
        float m_fBlinkImageTotalTime;

    private: // 랜덤패턴 관련
        int m_RandomState;
        int m_PrevRandomState;

    private: // 타임이벤터 
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

    public: // 기본 생성시 기본설정사항
        void SetMoveDirect(GlobalValue::BasicMoveType _MoveDirect);

    public: // 애니메이션 변경관련
        void ChangeAniMation(const SGameEngineString& _ChangeAniName);
        void DirCheck();

    public: // 이동 관련
        void MovePosCheck();
        void KnockBackPosCheck();
        void BackJumpPosCheck();
        void JumpAttackPosCheck();
        void JumpAttackHighPosCheck();
        void DeathPosCheck();

    public: // 픽셀체크
        void BlackKnightPixelCheck();

    public: // 위치체크(플레이어기준내위치)
        void BasicDirectCheck();
        void KnockBackDirectCheck();
        void LaughDirectCheck();
        void BackJumpDirectCheck();
        void JumpAttackDirectCheck();
        void DeathDirectCheck();

    public: // 상태별 체크사항
        void MoveStateCheck();
        void KnockBackStateCheck();
        void BackJumpStateCheck();
        void JumpAttackStateCheck();
        void JumpAttackEndCheck();
        void DeathStateCheck();

    public: // 타임이벤터 관련
        // Laugh 타임이벤터
        void LaughTimeEventerEnd();

    public: // 플레이어으로부터 공격받았을때 이미지 Blink
        void BeShotImageBlink();
        SGameEngineRendererBasic* DirectCheckImage();

    public: // 플레이어 치트에 의해 보스 즉사
        void PlayerCheetBossDeath();

    // 충돌체
    public:
        // 몸체 충돌
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

        // 일반공격 충돌
        void AttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void AttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void AttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        
        // 점프공격 충돌
        void JumpAttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void JumpAttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void JumpAttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    // FSM 상태
    public:
        // 카메라찾는 상태(카메라가 범위에 들어오면)
        void FindStart();
        void FindStay();
        void FindEnd();

        // 대기상태
        void IdleStart();
        void IdleStay();
        void IdleEnd();

        // 무브상태
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // 백점프 상태
        void BackJumpStart();
        void BackJumpStay();
        void BackJumpEnd();

        // 비웃는상태
        void LaughStart();
        void LaughStay();
        void LaughEnd();

        // 점프어택시작 상태
        void JumpAttackStart();
        void JumpAttackStay();
        void JumpAttackEnd();

        // 점프어택 최고점에서 내려찍는 상태
        void JumpAttackHighPointStart();
        void JumpAttackHighPointStay();
        void JumpAttackHighPointEnd();

        // 일반공격상태
        void NomalAttackStart();
        void NomalAttackStay();
        void NomalAttackEnd();

        // 스킬공격차징 상태
        void SkillChargingStart();
        void SkillChargingStay();
        void SkillChargingEnd();

        // 스킬공격중 상태
        void SkillAttackStart();
        void SkillAttackStay();
        void SkillAttackEnd();

        // 넉백상태(플레이어으로부터 피격시)
        void KnockBackStart();
        void KnockBackStay();
        void KnockBackEnd();

        // 사망시작 상태(이때 충돌체 사망)
        void DeathStart();
        void DeathStay();
        void DeathEnd();

        // 사망모션 진행중 상태
        void DeathMotionStart();
        void DeathMotionStay();
        void DeathMotionEnd();
};


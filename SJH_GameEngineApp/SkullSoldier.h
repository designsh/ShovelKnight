#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineInput.h>
#include <SGameEngineFSM.h>
#include <SGameEngineCollision.h>
#include <SGameEngineSound.h>

#include "MonsterInfo.h"
#include "GlobalValue.h"
#include "ShovelKnight.h"

// 분류 :
// 용도 : 
// 설명 : 
class SkullSoldier : public SGameEngineActor
{
    private: // Static Var
        static SoundPlayer m_SkullSoldierActionSound;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        MonsterInfo m_SkullSoldierInfo;
        SGameEngineRendererAnimation* m_AniSkullSoldier;
        SGameEngineFSM<SkullSoldier> m_SkullSoldierFSM;
        SGameEngineCollision* m_SkullSoldierCol;
        SGameEngineCollision* m_SkullSoldierAttackCol;

        SGameEngineRendererBasic* m_BeShotLeftSkullSoldier;
        SGameEngineRendererBasic* m_BeShotRightSkullSoldier;

    private: // Knock Back Image Blink
        bool m_bBlinkImage;
        float m_fBlinkImageOnTime;
        float m_fBlinkImageOffTime;
        float m_fBlinkImageTotalTime;

    private: // 충돌 Flag
        bool m_bDirtBlockCol;
        bool m_bDirtBlockSmallCol;

    private: // 이동 위치 관련
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;
        GlobalValue::BasicMoveType m_BackMoveDir;
        GlobalValue::BasicMoveType m_KnockBackMoveDir;

        // 총괄 벡터
        FLOAT4 m_MovePos;

        // 이동 벡터
        FLOAT4 m_DirectPos;

        // 백무브 시작위치 및 최대이동거리
        FLOAT4 m_BackMoveStartPos;
        float m_BackMoveMaxDistance;

        // 넉백 시작위치 및 최대이동거리
        FLOAT4 m_KnockBackStartPos;
        float m_KnockBackMaxDistance;

        // 플레이어기준 나의 위치
        // 이전 위치와 현재 위치가 달라지면 상태변환을 위해
        GlobalValue::BasicMoveType m_PlayerBaseMyPos;
        GlobalValue::BasicMoveType m_PrevPlayerBaseMyPos;

    private: // Direct Change Animation
        SGameEngineString m_AniMationName;
        SGameEngineString m_CurAniMationName;

    private: // 픽셀체크관련
        FLOAT4 m_SkullCheckPos;
        FLOAT4 m_SkullCheckDir[4];
        int m_iSkullCheckColor[4];

    public: // constructer destructer
        SkullSoldier();
        virtual ~SkullSoldier();

    public: // delete constructer 
        SkullSoldier(const SkullSoldier& _Other) = delete;
        SkullSoldier(const SkullSoldier&& _Other) = delete;

    public: // delete operator
        SkullSoldier& operator=(const SkullSoldier& _Other) = delete;
        SkullSoldier& operator=(const SkullSoldier&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public: // 생성 기본 설정
        void SetMoveDiect(GlobalValue::BasicMoveType _MoveDir);

    public: // BeShot ImageBlink
        void SetBlinkImage();
        SGameEngineRendererBasic* BlinkImageDirCheck();

    public: // Direct Change Animation
        void ChangeAniMation(const SGameEngineString& _ChangeAniName);
        void DirCheck();
        void MyPosOnBasePlayer();

    public: // Skull Soldier Pixel Check
        void BlackKnightPixelCheck();
        void MoveStateCheck();
        void BackMoveStateCheck();
        void KnockBackStateCheck();
        
    // 충돌체
    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

        void CollisionAttackStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionAttackStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionAttackEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public:
        // 플레이어 찾는 상태(플레이어와 일정거리가되면 Move)
        void FindStart();
        void FindStay();
        void FindEnd();

        // 이동상태(이동중 플레이어와 일정거리가 되면 Back Move)
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // 백무브상태(이동중 플레이어와 일정거리가 되면 Attack)
        void BackMoveStart();
        void BackMoveStay();
        void BackMoveEnd();

        // 공격준비상태
        void AttackIdleStart();
        void AttackIdleStay();
        void AttackIdleEnd();

        // 공격상태(공격모션 끝나면 Move)
        void AttackStart();
        void AttackStay();
        void AttackEnd();

        // 넉백상태(공격받으면 넉백 및 이미지 Blink)
        void KnockBackStart();
        void KnockBackStay();
        void KnockBackEnd();

        // 몬스터 사라지는 모션(죽으면서 골드 드랍)
        void DieMotionStart();
        void DieMotionStay();
        void DieMotionEnd();

};


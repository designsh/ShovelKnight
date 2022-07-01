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

// 분류 :
// 용도 : 
// 설명 : 
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

    private: // 플레이어 충돌체
        // 상좌우 1개, 하단 1개로 변경
        SGameEngineCollision* m_PlayerCol;           // SetCheckData(0)
        SGameEngineCollision* m_PlayerBotCol;     // SetCheckData(1)

        // 플레이어의 공격모션 충돌체
        SGameEngineCollision* m_AttackCol;

        // 플레이어의 점프공격모션 충돌체
        SGameEngineCollision* m_JumpAttackCol;

    private: // 플레이어 벡터
        FLOAT4 m_MovePos;
        FLOAT4 m_DirectPos;
        FLOAT4 m_GravityPos;
        FLOAT4 m_JumpPos;
        FLOAT4 m_JumpPower;
        FLOAT4 m_JumpGravityPowerPos;
        FLOAT4 m_KnockBackPos;
        FLOAT4 m_KnockBackPower;
        FLOAT4 m_KnockBackGravityPowerPos;

    private: // 플레이어 이동방향
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;
        GlobalValue::BasicMoveType m_LadderPrevMoveDir;

    private: // 플레이어 이동방향에 따른 애니메이션
        SGameEngineString m_CurAniMationName;
        SGameEngineString m_AniMationName;

    private: // 타임이벤터
        SGameEngineTimeEventer<ShovelKnight> m_JumpEventer;
        SGameEngineTimeEventer<ShovelKnight> m_KnockBackEventer;

    private: // 플레이어 등장
        float m_fAngle;

    private: // Flag 관련
        bool m_bJumping;
        bool m_bLadderCollision;
        bool m_bDirtBlockCollision;
        bool m_bFinalBossRoom;
        bool m_bFinalBossHPCharge;
        bool m_bEffectSound;
        bool m_bAppearIdle;

    private: // 플레이어 픽셀충돌
        FLOAT4 m_PlayerCheckPos;
        FLOAT4 m_PlayerCheckDir[5];
        int m_iPlayerCheckColor[5];

    private: // 카메라 픽셀충돌
        FLOAT4 m_CamCheckPos;
        FLOAT4 m_CamCheckDir[4];
        int m_iCamCheckColor[4];

    private: // 카메라 러프
        bool m_bWallCollision;                                                         // 플레이어 이동중 특정색 충돌
        bool m_LerpStartMove;                                                        // 충돌후 방향에따른 m_LerpCamPos계산완료 후 캠 이동

        FLOAT4 m_LerpCamPos;                                                      // Lerp Move Pos(러프이동 위치)
        FLOAT4 m_LerpStartPos;                                                      // Lerp Start Pos(러프시작 위치:현재카메라위치)
        FLOAT4 m_LerpEndPos;                                                       // Lerp End Pos(러프종료 위치:윈도우크기(방향에따른))
        float  m_LerpTime;                                                               // Lerp Ratio Time(러프이동 단위비율)

    private: // BrokenTile 정보관련
        SGameEngineDirectory m_BrokenTileFilePath;
        SGameEngineRendererTile* m_BrokenTile;
        FLOAT4 m_PlayerPosIndex;
        FLOAT4 m_PlayerAttackPosIndex;
        std::list<std::vector<FLOAT4>> m_BrokenAllTile;
        SGameEngineTimeEventer<ShovelKnight> m_BrokenEventer;

    public: // 플레이어 기본정보
        ShovelKnightInfo m_PlayerInfo;

    public: // 플레이어 치트 Flag
        bool m_bInvincibility; // 무적모드
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

    public: // 플레이어 기본정보 및 생성관련
        // 플레이어 기본정보 설정
        void SetPlayerInfomation();

        // 플레이어 액션을 위한 키 생성
        void CreateActionKey();

        // 플레이어 공격에 의해 부서지는 타일맵 로드
        void LoadBrokenTileMap();
        int GetBrokenTileImageIndex(const FLOAT4& _CheckPos);
        void SetPlayerPosIndex();
        void BrokenTileStay();
        void RightFind(FLOAT4 _StartIndex);
        void LeftFind(FLOAT4 _StartIndex);

        // 플레이어 충돌체 생성
        void CreatePlayerCollision();

        // 플레이어 애니메이션 생성
        void CreatePlayerAnimation();

        // 플레이어 FSM 상태 생성
        void CreatePlayerFSMState();

    public: // 플레이어 정보관련
        ShovelKnightInfo& GetPlayerInfo();

    public: // Alpha 조절함수
        void HitAlphaInStart();
        void HitAlphaInStay();
        void HitAlphaInEnd();
        void HitAlphaOutStart();
        void HitAlphaOutStay();
        void HitAlphaOutEnd();

    public:
        void CheckFinalBossRoom();

    public: // 이동에 대한 애니메이션 관련
        void ChangeAniMation(const SGameEngineString& _ChangeAniName);
        void DirCheck();

    public: // 픽셀체크 관련
        void CamPixelCheck();
        void PlayerPixelCheck();

    public: // 카메라 러프
        void LerpCamMove();

    public: // 치트체크
        void CheetKeyDownCheck();

    public:
        void BossVictoryStateChagne();

    public: // 벡터관련(이동, 액션 등등)
        // 기본상태
        void IdlePos_Check();
        void FallingPos_Check();
        void MovePos_Check();
        void LadderMovePos_Check();
        void LadderJumpPos_Check();
        void JumpPos_Check();
        void JumpAttackPos_Check();
        void JumpAttackColPos_Check();
        void KnockBackPos_Check();

        // 오브젝트 충돌상태
        void RideIdlePos_Check();
        void RideMovePos_Check();
        void RideAttackPos_Check();

    public: // FSM 상태에 대한 체크
        // 기본상태
        void IdleState_Check();
        void FallingState_Check();
        void MoveState_Check();
        void LadderMoveState_Check();
        void LadderJumpState_Check();
        void JumpState_Check();
        void JumpAttackState_Check();
        void JumpAttackColState_Check();
        void KnockBackState_Check();

        // 오브젝트 충돌상태
        void RideIdleState_Check();
        void RideMoveState_Check();
        
    public: // 충돌체
        // 몸통(0)
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

        // 바닥(1)
        void BottomCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void BottomCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void BottomCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

        // 공격모션
        void AttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void AttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void AttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

        // 점프공격모션
        void JumpAttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void JumpAttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void JumpAttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public: // FSM 상태(기본)
        // 등장 상태
        void AppearStart();
        void AppearStay();
        void AppearEnd();

        // 대기(정지) 상태
        void IdleStart();
        void IdleStay();
        void IdleEnd();

        // Falling 상태
        void FallingStart();
        void FallingStay();
        void FallingEnd();

        // 기본이동 상태(왼, 우)
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // 사다리이동 상태(상, 하)
        void LadderMoveStart();
        void LadderMoveStay();
        void LadderMoveEnd();

        // 사다리 이동중 점프
        void LadderJumpStart();
        void LadderJumpStay();
        void LadderJumpEnd();

        // 점프 상태
        void HighJumpCheckEvent();
        void LowJumpCheckEvent();
        void JumpStart();
        void JumpStay();
        void JumpEnd();

        // 점프공격 상태
        void JumpAttackStart();
        void JumpAttackStay();
        void JumpAttackEnd();

        // 점프공격(Object or Monster 충돌)
        void JumpAttackColStart();
        void JumpAttackColStay();
        void JumpAttackColEnd();

        // 기본공격 상태
        void AttackStart();
        void AttackStay();
        void AttackEnd();

        // 넉백 상태
        void KnockBackStart();
        void KnockBackStay();
        void KnockBackEnd();

        // 보스처치(승리)
        void BossVictoryStart();
        void BossVictoryStay();
        void BossVictoryEnd();

    public: // FSM 상태(오브젝트와 충돌중인 상태)
        // 오브젝트 탑승상태 IDLE
        void RideIdleStart();
        void RideIdleStay();
        void RideIdleEnd();

        // 오브젝트 탑승상태 Move
        void RideMoveStart();
        void RideMoveStay();
        void RideMoveEnd();

        // 오브젝트 탑승상태 Attack
        void RideAttackStart();
        void RideAttackStay();
        void RideAttackEnd();

    public: // 치트모드상태(프리모드 - 모든 사물을 무시하고 이동한다.)
        void CheetFreeStart();
        void CheetFreeStay();
        void CheetFreeEnd();

};


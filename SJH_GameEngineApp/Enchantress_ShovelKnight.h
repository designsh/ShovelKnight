#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>
#include <SGameEngineTimeEventer.h>
#include <SGameEngineCollision.h>
#include <SGameEngineSound.h>

#include "ShovelKnightInfo.h"
#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class Enchantress_ShovelKnight : public SGameEngineActor
{
    private: // Static Var
        static SoundPlayer m_EnchantressPlayerSound;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererAnimation* m_AniPlayer;
        SGameEngineFSM<Enchantress_ShovelKnight> m_ShovelKnightFSM;

    private: // 플레이어 충돌체
        // 상좌우 1개, 하단 1개로 변경
        SGameEngineCollision* m_PlayerCol;           // SetCheckData(0)
        SGameEngineCollision* m_PlayerBotCol;     // SetCheckData(1)

        // 플레이어의 공격모션 충돌체
        SGameEngineCollision* m_AttackCol;

        // 플레이어의 점프공격모션 충돌체
        SGameEngineCollision* m_JumpAttackCol;

    public: // 플레이어 기본정보
        ShovelKnightInfo m_PlayerInfo;

    private: // 플레이어 이동방향
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;
        
    private: // 카메라 러프 방향
        GlobalValue::BasicMoveType m_CamMoveDir;
        GlobalValue::BasicMoveType m_PrevCamMoveDir;

    private: // 플레이어 이동방향에 따른 애니메이션
        SGameEngineString m_CurAniMationName;
        SGameEngineString m_AniMationName;

    private: // 플레이어 벡터
        FLOAT4 m_MovePos;
        FLOAT4 m_DirectPos;
        FLOAT4 m_JumpPos;
        FLOAT4 m_JumpPower;
        FLOAT4 m_JumpGravityPowerPos;
        FLOAT4 m_KnockBackPos;
        FLOAT4 m_KnockBackPower;
        FLOAT4 m_KnockBackGravityPowerPos;

    private: // 타임이벤터
        SGameEngineTimeEventer<Enchantress_ShovelKnight> m_JumpEventer;
        SGameEngineTimeEventer<Enchantress_ShovelKnight> m_KnockBackEventer;

    private: // 카메라 러프
        bool m_bWallCollision;                                                         // 플레이어 이동중 특정색 충돌
        bool m_LerpStartMove;                                                        // 충돌후 방향에따른 m_LerpCamPos계산완료 후 캠 이동

        FLOAT4 m_LerpCamPos;                                                      // Lerp Move Pos(러프이동 위치)
        FLOAT4 m_LerpStartPos;                                                      // Lerp Start Pos(러프시작 위치:현재카메라위치)
        FLOAT4 m_LerpEndPos;                                                       // Lerp End Pos(러프종료 위치:윈도우크기(방향에따른))
        float  m_LerpTime;                                                               // Lerp Ratio Time(러프이동 단위비율)

    private: // 플레이어 픽셀충돌
        FLOAT4 m_PlayerCheckPos;
        FLOAT4 m_PlayerCheckDir[5];
        int m_iPlayerCheckColor[5];

    private: // 카메라 픽셀충돌
        FLOAT4 m_CamCheckPos;
        FLOAT4 m_CamCheckDir[4];
        int m_iCamCheckColor[4];

    private: // 플레이어 등장 및 보스등장(카메라러프)관련
        FLOAT4 m_PlayerAppearPos;

    private: // 점프관련 충돌체크용 Flag
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

    public: // 치트모드 감지
        void CheetCheck();

    public: // 각 상태별 위치이동
        void BossFindIDLE_MovePosCheck();
        void BossFindMOVE_MovePosCheck();
        void Idle_MovePosCheck();
        void Move_MovePosCheck();
        void Jump_MovePosCheck();
        void JumpAttack_MovePosCheck();
        void JumpAttackCol_MovePosCheck();
        void KnockBack_MovePosCheck();

    public: // 각 상태별 픽셀체크, 키체크 등
        void BossFindIDLE_StateCheck();
        void BossFindMOVE_StateCheck();
        void Idle_StateCheck();
        void Move_StateCheck();
        void Jump_StateCheck();
        void JumpAttack_StateCheck();
        void JumpAttackCol_StateCheck();
        void KnockBack_StateCheck();

    public: // Alpha 조절함수
        void HitAlphaInStart();
        void HitAlphaInStay();
        void HitAlphaInEnd();
        void HitAlphaOutStart();
        void HitAlphaOutStay();
        void HitAlphaOutEnd();

    public: // 플레이어 기본정보 및 생성관련
        // 플레이어 기본정보 설정
        void SetPlayerInfomation();

        // 플레이어 액션을 위한 키 생성
        void CreateActionKey();

        // 플레이어 충돌체 생성
        void CreatePlayerCollision();

        // 플레이어 애니메이션 생성
        void CreatePlayerAnimation();

        // 플레이어 FSM 상태 생성
        void CreatePlayerFSMState();

    public: // 이동에 대한 애니메이션 관련
        void ChangeAniMation(const SGameEngineString& _ChangeAniName);
        void DirCheck();

    public: // 픽셀체크 관련
        void CamPixelCheck();
        void PlayerPixelCheck();

    public: // 카메라 러프
        void LerpCamMove();

    public: // 플레이어 정보관련
        ShovelKnightInfo& GetPlayerInfo();

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

    public: // FSM 상태
        // 보스찾는 대기상태
        void BossFindIdleStart();
        void BossFindIdleStay();
        void BossFindIdleEnd();

        // 보스 찾는 무브상태((일정거리 이동하면 상태변경)
        void BossFindMoveStart();
        void BossFindMoveStay();
        void BossFindMoveEnd();

        // 카메라러프 대기상태(카메라는 몬스터를 찾는다.)
        void CamLerpingIdleStart();
        void CamLerpingIdleStay();
        void CamLerpingIdleEnd();

        // 대기(정지) 상태
        void IdleStart();
        void IdleStay();
        void IdleEnd();

        // 기본이동 상태(왼, 우)
        void MoveStart();
        void MoveStay();
        void MoveEnd();

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

        // 점프공격(Object 충돌)
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

        // 방패기사를 받아내는 상태
        void ShildKnightColStart();
        void ShildKnightColStay();
        void ShildKnightColEnd();

        // 엔딩씬전환 상태
        void EndingSceneChangeStart();
        void EndingSceneChangeStay();
        void EndingSceneChangeEnd();

};


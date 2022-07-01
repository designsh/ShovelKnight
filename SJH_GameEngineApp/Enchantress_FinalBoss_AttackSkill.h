#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineCollision.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class Enchantress_FinalBoss_AttackSkill : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererAnimation* m_AniAttackSkill;
        SGameEngineFSM<Enchantress_FinalBoss_AttackSkill> m_AttackSkillFSM;
        SGameEngineCollision* m_AttackSkillCol;

    private:
        GlobalValue::BasicMoveType m_FiringDir;
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;

        SGameEngineString m_CurAniMationName;
        SGameEngineString m_AniMationName;

    private:
        FLOAT4 m_MovePos;
        FLOAT4 m_DirectPos;
        FLOAT4 m_FirePos;

    private:
        FLOAT4 m_AttackSkillCheckPos;
        FLOAT4 m_AttackSkillCheckDir[4];
        int m_iAttackSkillCheckColor[4];

    public: // constructer destructer
        Enchantress_FinalBoss_AttackSkill();
        virtual ~Enchantress_FinalBoss_AttackSkill();

    public: // delete constructer 
        Enchantress_FinalBoss_AttackSkill(const Enchantress_FinalBoss_AttackSkill& _Other) = delete;
        Enchantress_FinalBoss_AttackSkill(const Enchantress_FinalBoss_AttackSkill&& _Other) = delete;

    public: // delete operator
        Enchantress_FinalBoss_AttackSkill& operator=(const Enchantress_FinalBoss_AttackSkill& _Other) = delete;
        Enchantress_FinalBoss_AttackSkill& operator=(const Enchantress_FinalBoss_AttackSkill&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void SetFirstMoveDirect(GlobalValue::BasicMoveType _Direct);
        void SetFirstFireDirect(GlobalValue::BasicMoveType _Direct);

    public: // 이동방향에 따른 애니메이션 변경
        void ChangeAniMation(const SGameEngineString& _ChangeAniName);
        void DirCheck();

    public:
        void AttackSkillPixelCheck();

    public:
        void MovePos_Check();
        void MoveState_Check();

    public: // 충돌체
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public: // FSM 생성
        // 타겟을 찾는 상태
        void FindStart();
        void FindStay();
        void FindEnd();

        // 이동 상태
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // 사망 상태
        void DeathStart();
        void DeathStay();
        void DeathEnd();

};


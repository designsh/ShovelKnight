#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineCollision.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"

// �з� :
// �뵵 : 
// ���� : 
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

    public: // �̵����⿡ ���� �ִϸ��̼� ����
        void ChangeAniMation(const SGameEngineString& _ChangeAniName);
        void DirCheck();

    public:
        void AttackSkillPixelCheck();

    public:
        void MovePos_Check();
        void MoveState_Check();

    public: // �浹ü
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public: // FSM ����
        // Ÿ���� ã�� ����
        void FindStart();
        void FindStay();
        void FindEnd();

        // �̵� ����
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // ��� ����
        void DeathStart();
        void DeathStay();
        void DeathEnd();

};


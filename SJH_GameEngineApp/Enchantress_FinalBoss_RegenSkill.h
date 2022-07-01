#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineCollision.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"

// �з� :
// �뵵 : 
// ���� : 
class Enchantress_FinalBoss_RegenSkill : public SGameEngineActor
{
    private: // Static Var
        //static int RegenTileCount;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererAnimation* m_AniRegenSkillStone;
        SGameEngineRendererAnimation* m_AniRegenSkillFlame;
        SGameEngineFSM<Enchantress_FinalBoss_RegenSkill> m_RegenSkillFSM;
        SGameEngineCollision* m_RegenSkillCol;

    private:
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;

        SGameEngineString m_CurAniMationName;
        SGameEngineString m_AniMationName;

    private:
        FLOAT4 m_MovePos;
        FLOAT4 m_DirectPos;

    private:
        float m_fMoveDelay;
        float m_fDeathDelay;

    private: // BrokenTile Object ����� �� ���� �̵��� ���� ����
        FLOAT4 m_TargetPos;
        FLOAT4 m_MyIndex;

    private: // ������
        FLOAT4 m_LerpPos;
        FLOAT4 m_LerpStartPos;
        FLOAT4 m_LerpEndPos;
        bool m_LerpStartMove;
        float m_LerpTime;

    public: // constructer destructer
        Enchantress_FinalBoss_RegenSkill();
        virtual ~Enchantress_FinalBoss_RegenSkill();

    public: // delete constructer 
        Enchantress_FinalBoss_RegenSkill(const Enchantress_FinalBoss_RegenSkill& _Other) = delete;
        Enchantress_FinalBoss_RegenSkill(const Enchantress_FinalBoss_RegenSkill&& _Other) = delete;

    public: // delete operator
        Enchantress_FinalBoss_RegenSkill& operator=(const Enchantress_FinalBoss_RegenSkill& _Other) = delete;
        Enchantress_FinalBoss_RegenSkill& operator=(const Enchantress_FinalBoss_RegenSkill&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public: // Ÿ�� ��ġ�� �ε����� ����
        void SetTargeIndex(FLOAT4 _Index);

    public: // �浹ü
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public: // FSM ����
        // Ÿ�� ���� ����
        void StoneCreateStart();
        void StoneCreateStay();
        void StoneCreateEnd();

        // �Ҳ� ���� ����
        void FlameCreateStart();
        void FlameCreateStay();
        void FlameCreateEnd();

        // ���� ��ų ��� ����
        void RegenSkillIdleStart();
        void RegenSkillIdleStay();
        void RegenSkillIdleEnd();

        // �����Ϸ� �� ���� ����
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // �ش� ��ġ ���� �� Ÿ�ϸ��� ����
        void TileObjectRegenStart();
        void TileObjectRegenStay();
        void TileObjectRegenEnd();

        // ���� �Ϸ� �� ���
        void DeathStart();
        void DeathStay();
        void DeathEnd();

};


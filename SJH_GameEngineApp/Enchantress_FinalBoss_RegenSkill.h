#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineCollision.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
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

    private: // BrokenTile Object 재생성 및 나의 이동을 위한 변수
        FLOAT4 m_TargetPos;
        FLOAT4 m_MyIndex;

    private: // 러프용
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

    public: // 타겟 위치와 인덱스를 저장
        void SetTargeIndex(FLOAT4 _Index);

    public: // 충돌체
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public: // FSM 생성
        // 타일 생성 시작
        void StoneCreateStart();
        void StoneCreateStay();
        void StoneCreateEnd();

        // 불꽃 생성 시작
        void FlameCreateStart();
        void FlameCreateStay();
        void FlameCreateEnd();

        // 리젠 스킬 대기 상태
        void RegenSkillIdleStart();
        void RegenSkillIdleStay();
        void RegenSkillIdleEnd();

        // 생성완료 후 무브 시작
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // 해당 위치 도착 후 타일리젠 시작
        void TileObjectRegenStart();
        void TileObjectRegenStay();
        void TileObjectRegenEnd();

        // 리젠 완료 후 사망
        void DeathStart();
        void DeathStay();
        void DeathEnd();

};


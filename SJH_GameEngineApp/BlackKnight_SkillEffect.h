#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>
#include <SGameEngineCollision.h>
#include <SGameEngineTimeEventer.h>

#include "GlobalValue.h"

// �з� :
// �뵵 : 
// ���� : BlackKnight�� ��ų ���ݽ� �߻�Ǵ� �߻�ü
class BlackKnight_SkillEffect : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;

        SGameEngineRendererAnimation* m_AniSkillEffect;
        SGameEngineFSM<BlackKnight_SkillEffect> m_SkillEffectFSM;
        SGameEngineCollision* m_SkillEffectCol;

    private:
        SGameEngineString m_CurAniMationName;
        SGameEngineString m_AniMationName;
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;

        float m_Speed;
        float m_MaximumRange;

        FLOAT4 m_StartPos;
        FLOAT4 m_MovePos;

    public: // constructer destructer
        BlackKnight_SkillEffect();
        ~BlackKnight_SkillEffect();

    public: // delete constructer 
        BlackKnight_SkillEffect(const BlackKnight_SkillEffect& _Other) = delete;
        BlackKnight_SkillEffect(const BlackKnight_SkillEffect&& _Other) = delete;

    public: // delete operator
        BlackKnight_SkillEffect& operator=(const BlackKnight_SkillEffect& _Other) = delete;
        BlackKnight_SkillEffect& operator=(const BlackKnight_SkillEffect&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void ChangeAniMation(const SGameEngineString& _ChangeAniName);
        void DirCheck();
        void MovePosCheck();
        void MaximumRangeCheck();

    public: // ���� �� �����Ǿ���ϴ� ����
        void SetSkillEffectDirect(GlobalValue::BasicMoveType _Direct);

    // �浹ü
    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    // FSM ����
    public:
        // ������ �����̴� ����
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // �״»���
        void DeathStart();
        void DeathStay();
        void DeathEnd();

};


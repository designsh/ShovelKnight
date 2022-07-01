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

// �з� :
// �뵵 : 
// ���� : 
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

    private: // �浹 Flag
        bool m_bDirtBlockCol;
        bool m_bDirtBlockSmallCol;

    private: // �̵� ��ġ ����
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;
        GlobalValue::BasicMoveType m_BackMoveDir;
        GlobalValue::BasicMoveType m_KnockBackMoveDir;

        // �Ѱ� ����
        FLOAT4 m_MovePos;

        // �̵� ����
        FLOAT4 m_DirectPos;

        // �鹫�� ������ġ �� �ִ��̵��Ÿ�
        FLOAT4 m_BackMoveStartPos;
        float m_BackMoveMaxDistance;

        // �˹� ������ġ �� �ִ��̵��Ÿ�
        FLOAT4 m_KnockBackStartPos;
        float m_KnockBackMaxDistance;

        // �÷��̾���� ���� ��ġ
        // ���� ��ġ�� ���� ��ġ�� �޶����� ���º�ȯ�� ����
        GlobalValue::BasicMoveType m_PlayerBaseMyPos;
        GlobalValue::BasicMoveType m_PrevPlayerBaseMyPos;

    private: // Direct Change Animation
        SGameEngineString m_AniMationName;
        SGameEngineString m_CurAniMationName;

    private: // �ȼ�üũ����
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

    public: // ���� �⺻ ����
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
        
    // �浹ü
    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

        void CollisionAttackStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionAttackStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionAttackEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public:
        // �÷��̾� ã�� ����(�÷��̾�� �����Ÿ����Ǹ� Move)
        void FindStart();
        void FindStay();
        void FindEnd();

        // �̵�����(�̵��� �÷��̾�� �����Ÿ��� �Ǹ� Back Move)
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // �鹫�����(�̵��� �÷��̾�� �����Ÿ��� �Ǹ� Attack)
        void BackMoveStart();
        void BackMoveStay();
        void BackMoveEnd();

        // �����غ����
        void AttackIdleStart();
        void AttackIdleStay();
        void AttackIdleEnd();

        // ���ݻ���(���ݸ�� ������ Move)
        void AttackStart();
        void AttackStay();
        void AttackEnd();

        // �˹����(���ݹ����� �˹� �� �̹��� Blink)
        void KnockBackStart();
        void KnockBackStay();
        void KnockBackEnd();

        // ���� ������� ���(�����鼭 ��� ���)
        void DieMotionStart();
        void DieMotionStay();
        void DieMotionEnd();

};


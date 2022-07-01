#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineInput.h>
#include <SGameEngineFSM.h>
#include <SGameEngineCollision.h>
#include <SGameEngineTimeEventer.h>
#include <SGameEngineSound.h>

#include "MonsterInfo.h"
#include "GlobalValue.h"

// �з� :
// �뵵 : 
// ���� : 
class Slime : public SGameEngineActor
{
    private: // Static Var
        static SoundPlayer m_SlimeActionSound;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        MonsterInfo m_SlimeInfo;
        SGameEngineRendererAnimation* m_AniSlime;
        SGameEngineFSM<Slime> m_SlimeFSM;
        SGameEngineCollision* m_SlimeCol;
        SGameEngineRendererBasic* m_BeShotSlime;

    private:
        FLOAT4 m_MovePos;
        FLOAT4 m_DirectPos;

        float m_Speed;
        float m_JumpTime;

    private:
        bool m_DirtBlockCol;
        bool m_DirtBlockSmallCol;

    private: // �ǰ� ����
        bool m_bBlinkImage;

        float m_fBlinkImageOnTime;
        float m_fBlinkImageOffTime;
        float m_fBlinkImageTotalTime;

    private: // �������� ����
        FLOAT4 m_GravityPos;
        FLOAT4 m_GravityPower;
        FLOAT4 m_JumpPos;
        FLOAT4 m_JumpPower;

    private:
        GlobalValue::BasicMoveType m_MoveDir;
        GlobalValue::BasicMoveType m_PrevMoveDir;

    private:
        FLOAT4 m_SlimeCheckPos;
        FLOAT4 m_SlimeCheckDir[4];
        int m_iSlimeCheckColor[4];

    private:
        SGameEngineTimeEventer<Slime> m_JumpEventer;

    public: // constructer destructer
        Slime();
        virtual ~Slime();

    public: // delete constructer 
        Slime(const Slime& _Other) = delete;
        Slime(const Slime&& _Other) = delete;

    public: // delete operator
        Slime& operator=(const Slime& _Other) = delete;
        Slime& operator=(const Slime&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public: // Monster BeShot Blink
        void SetBlinkImage();

    public: // Ÿ���̺���
        void JumpAttackChange();

    public: // Actor Init Function
        void SetInitMove(GlobalValue::BasicMoveType _MoveDirect);

    public:
        void DirPosCheck();

    public:
        void SlimePixcelCol();
        void MoveCheck();
        void JumpAttackCheck();

    public:
        void SetJumpTime(float _JumpTime);

    // �浹ü
    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    // FSM ����
    public:
        // ��������(������)
        void FindStart();
        void FindStay();
        void FindEnd();

        // �̵�����
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // ���� ���ݻ���
        void JumpAttackStart();
        void JumpAttackStay();
        void JumpAttackEnd();

        // �������
        void DieStart();
        void DieStay();
        void DieEnd();

};


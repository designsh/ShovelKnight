#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineCollision.h>
#include <SGameEngineFSM.h>
#include <SGameEngineTimeEventer.h>

#include "GlobalValue.h"

// �з� :
// �뵵 : 
// ���� : 
class DropGold : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_DropGoldRender;
        SGameEngineCollision* m_DropGoldCol;
        SGameEngineFSM<DropGold> m_DropGoldFSM;
        SGameEngineRendererAnimation* m_AniDropGold;

    private: // �⺻����
        int m_DropGold;
        GlobalValue::BasicMoveType m_MoveDir;
        float m_Speed;
        float m_DelayTime;
        float m_DeathTime;

        FLOAT4 m_MovePos;
        FLOAT4 m_DirectPos;
        FLOAT4 m_DropPos;
        FLOAT4 m_DropPower;
        FLOAT4 m_DropGravityPower;

    private:
        FLOAT4 m_DropGoldCheckPos;
        FLOAT4 m_DropGoldCheckDir[4];
        int m_iDropGoldCheckColor[4];

    private:
        SGameEngineTimeEventer<DropGold> m_EvaporationEventer;
        SGameEngineTimeEventer<DropGold> m_AlphaEventer;

    public: // constructer destructer
        DropGold();
        virtual ~DropGold();

    public: // delete constructer 
        DropGold(const DropGold& _Other) = delete;
        DropGold(const DropGold&& _Other) = delete;

    public: // delete operator
        DropGold& operator=(const DropGold& _Other) = delete;
        DropGold& operator=(const DropGold&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void SetDropGold(int _DropGold);
        int GetDropGold();
        void SetDropGoldImage(int _DropGold);
        void SetMoveDirect();
        void SetMoveSpeed(float _MoveSpeed);

    public:
        void MovePosCheck();
        void MoveStateCheck();

    public:
        void GoldPixelCheck();

    public:
        void TimeAlphaInStart();
        void TimeAlphaInStay();
        void TimeAlphaInEnd();

        void TimeAlphaOutStart();
        void TimeAlphaOutStay();
        void TimeAlphaOutEnd();

    // �浹ü
    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    // FSM ����
    public:
        // ������(��尡 ����Ǵ� ���⼳������)
        void IDLEStart();
        void IDLEStay();
        void IDLEEnd();

        // ��� ������� ����
        void MoveStart();
        void MoveStay();
        void MoveEnd();

        // ��� Blink ������ Delay
        void TimeDelayStart();
        void TimeDelayStay();
        void TimeDelayEnd();

        // ��� Blink �� �Ҹ� ����
        void GoldEvaporationStart();
        void GoldEvaporationStay();
        void GoldEvaporationEnd();
};


#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineCollision.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class EnchantressBrokenTile : public SGameEngineActor
{
    private: // Static Var

    public:
        static int m_BrokenTileTotalCount;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererAnimation* m_AniBrokenObject;
        SGameEngineCollision* m_BrokenObjectCol;
        SGameEngineFSM<EnchantressBrokenTile> m_BrokenObjectColFSM;

    private: // 나의 저장 인덱스를 알고있는다.
        int m_iMyIndexX;
        int m_iMyIndexY;

    public: // constructer destructer
        EnchantressBrokenTile();
        virtual ~EnchantressBrokenTile();

    public: // delete constructer 
        EnchantressBrokenTile(const EnchantressBrokenTile& _Other) = delete;
        EnchantressBrokenTile(const EnchantressBrokenTile&& _Other) = delete;

    public: // delete operator
        EnchantressBrokenTile& operator=(const EnchantressBrokenTile& _Other) = delete;
        EnchantressBrokenTile& operator=(const EnchantressBrokenTile&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void SetMyIndex(int _x, int _y);
        FLOAT4 GetMyIndex();

    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public:
        // 생성상태
        void IdleStart();
        void IdleStay();
        void IdleEnd();

        // 사망상태
        void DieStart();
        void DieStay();
        void DieEnd();

};


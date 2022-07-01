#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineCollision.h>
#include <SGameEngineFSM.h>
#include <SGameEngineSound.h>

#include "GlobalValue.h"

// 분류 :
// 용도 : 
// 설명 : 
class DirtBlock_Small : public SGameEngineActor
{
    private: // Static Var
        static SoundPlayer m_DritBlockSmallSound;

    public: // Static Func

    private:	// member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_DirtBlock;
        SGameEngineCollision* m_DirtBlockCol;
        SGameEngineFSM<DirtBlock_Small> m_DirtBlockFSM;
        SGameEngineRendererAnimation* m_AniDirtBlock;

    private:
        bool m_bDropCoin;

    public: // constructer destructer
        DirtBlock_Small();
        virtual ~DirtBlock_Small();

    public: // delete constructer 
        DirtBlock_Small(const DirtBlock_Small& _Other) = delete;
        DirtBlock_Small(const DirtBlock_Small&& _Other) = delete;

    public: // delete operator
        DirtBlock_Small& operator=(const DirtBlock_Small& _Other) = delete;
        DirtBlock_Small& operator=(const DirtBlock_Small&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        bool IsDropCoin();
        void DropCoinOn();
        void DropCoinOff();

    public:
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public:
        // 대기상태
        void IDLEStart();
        void IDLEStay();
        void IDLEEnd();

        // 플레이어가 나를 공격한 상태
        void BeShotStart();
        void BeShotStay();
        void BeShotEnd();

};


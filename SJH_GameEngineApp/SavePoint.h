#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineCollision.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"

#define BESHOTMAX 4
#define SAVEPOINTMAX 4

// 분류 :
// 용도 : 
// 설명 : 

// 세이브 포인터는 마지막 활성화된 세이브포인터의 정보를 가지고있다.
class SavePointInfo
{
public:
    // 가질만한 정보
    // 1. 카메라위치(플레이를 다시 따라가야하므로)
    // 2. 각 세이브포인트의 위치(추후 플레이어 부활위치)
    // 3. 마지막으로 활성화된 세이브포인트 Index(초기값 0)
    FLOAT4 m_CamPos;
    FLOAT4 m_SavePointPos;
    int m_iActiveSavePoint;

public:
    // 초기 위치는 플레이어의 처음 생성위치와 동일하다
    SavePointInfo() : m_CamPos(FLOAT4(0.f, 2160.f)), m_SavePointPos({ 100.f, (720.f - 132.f) + 2160.f }), m_iActiveSavePoint(0)
    {

    }
};

class SavePoint : public SGameEngineActor
{
    private: // Static Var
        // 마지막으로 활성화된 세이브포인터의 정보를 가진다.
        static SavePointInfo m_LastSaveData;

    public: // Static Func
        static SavePointInfo GetLastSaveData();

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_SavePoint;
        SGameEngineCollision* m_SavePointCol;
        SGameEngineFSM<SavePoint> m_SavePointFSM;
        SGameEngineRendererAnimation* m_AniSavePoint;

    private:
        int m_iPlayerAttack; // 플레이어가 나를 공격한 횟수

    private:
        bool m_bFirstCollision;

    private:
        // 현재 플레이어와 충돌한 세이브 포인터의 정보를 가지고있다.
        SavePointInfo m_MySaveData;

    public: // constructer destructer
        SavePoint();
        virtual ~SavePoint();

    public: // delete constructer 
        SavePoint(const SavePoint& _Other) = delete;
        SavePoint(const SavePoint&& _Other) = delete;

    public: // delete operator
        SavePoint& operator=(const SavePoint& _Other) = delete;
        SavePoint& operator=(const SavePoint&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        // 플레이어가 나를 치는 횟수에 따라 애니메이션 변경
        void ChangeAnimation();

    public: // 충돌관련
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public: // 상태관련
        // 대기상태
        void IDLEStart();
        void IDLEStay();
        void IDLEEnd();

        // 충돌상태
        void ColStart();
        void ColStay();
        void ColEnd();

        // 활성화상태
        void ActiveStart();
        void ActiveStay();
        void ActiveEnd();

};


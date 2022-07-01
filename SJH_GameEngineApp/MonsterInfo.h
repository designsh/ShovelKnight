#pragma once
#include <SGameEngineMath.h>

// 분류 :
// 용도 : 
// 설명 : 기본적으로 몬스터가 가지는 정보
class MonsterInfo
{
    private: // Static Var

    public: // Static Func

    public: // member Var
        float m_MoveSpeed;              // 이동속도
        int m_DropCoin;                     // 드랍골드
        int m_HP;                                // 1개가 체력 1
        int m_MaxHP;                        // 최대체력
        FLOAT4 m_MaxDistance;            // 최대이동거리
        FLOAT4 m_MaximumRange;       // 최대 사거리
        
    public: // constructer destructer
        MonsterInfo();
        virtual ~MonsterInfo();

    public: // delete constructer 
        MonsterInfo(const MonsterInfo& _Other) = delete;
        MonsterInfo(const MonsterInfo&& _Other) = delete;

    public: // delete operator
        MonsterInfo& operator=(const MonsterInfo& _Other) = delete;
        MonsterInfo& operator=(const MonsterInfo&& _Other) = delete;

    public: // member Func
        void SetMoveSpeed(float _MoveSpeed);
        float GetMoveSpeed();

        void SetDropCoin(int _Coin);
        int GetDropCoin();

        void SetHP(int _HP);
        void AddHP(int _HP);
        void SubtractHP(int _SubtractHP);
        void SubtractHPAll();
        int GetHP();

        void SetMaxHP(int _MaxHP);
        int GetMaxHP();

        void SetMaxDistance(FLOAT4 _MaxDist);
        FLOAT4 GetMaxDistance();

        void SetMaximumRange(FLOAT4 _MaxRange);
        FLOAT4 GetMaximumRange();

};


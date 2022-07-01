#pragma once
#include <SGameEngineMath.h>

// �з� :
// �뵵 : 
// ���� : �⺻������ ���Ͱ� ������ ����
class MonsterInfo
{
    private: // Static Var

    public: // Static Func

    public: // member Var
        float m_MoveSpeed;              // �̵��ӵ�
        int m_DropCoin;                     // ������
        int m_HP;                                // 1���� ü�� 1
        int m_MaxHP;                        // �ִ�ü��
        FLOAT4 m_MaxDistance;            // �ִ��̵��Ÿ�
        FLOAT4 m_MaximumRange;       // �ִ� ��Ÿ�
        
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


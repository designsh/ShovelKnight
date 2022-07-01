#pragma once

// 분류 :
// 용도 : 
// 설명 : 기본적으로 플레이어가 가지는 정보
class ShovelKnightInfo
{
    private: // Static Var

    public: // Static Func

    private: // member Var

    public:
        float m_MoveSpeed; // 이동속도

        int m_HP;               // 체력
        int m_MaxHP;        // 최대체력

        int m_MP;              // 마력
        int m_MaxMP;       // 최대마력

        int m_LostGold;        // Death로인해 드랍한 골드
        int m_HoldingGold;  // 현재 보유골드
        int m_MaxHoldingGold;
        int m_RecoveryGold; // 회복한 골드

    public: // constructer destructer
        ShovelKnightInfo();
        virtual ~ShovelKnightInfo();

    public: // delete constructer 
        ShovelKnightInfo(const ShovelKnightInfo& _Other) = delete;
        ShovelKnightInfo(const ShovelKnightInfo&& _Other) = delete;

    public: // delete operator
        ShovelKnightInfo& operator=(const ShovelKnightInfo& _Other) = delete;
        ShovelKnightInfo& operator=(const ShovelKnightInfo&& _Other) = delete;

    public: // member Func
        // 이동 속도 관련
        float GetMoveSpeed();
        void SetMoveSpeed(float _Speed);

        // 골드 관련
        int GetHoldingGold();
        void SetHoldingGold(int _HoldingGold);
        int GetMaxHoldingGold();
        void SetMaxHoldingGold(int _MaxHoldingGold);
        void AddHoldingGold(int _AddGold);
        int GetLostGold();
        void SetLostGold(int _LostGold);
        int GetRecoveryGold();
        void SetRecoveryGold(int _RecoveryGold);

        // 체력 및 마력 관련
        int GetCurHP();
        void SetCurHP(int _HP);
        void SubtractCurHP(int _BeShotCount);
        void AddCurHP(int _AddHP);

        int GetMaxHP();
        void SetMaxHP(int _MaxHP);

        int GetCurMP();
        void SetCurMP(int _MP);
        void ConsumptionCurMP(int _ConsumptionMP);
        void AddCurMP(int _AddMP);

        int GetMaxMP();
        void SetMaxMP(int _MaxMP);

    public:
        void ResetPlayerInfo();

};


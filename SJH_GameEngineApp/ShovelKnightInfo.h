#pragma once

// �з� :
// �뵵 : 
// ���� : �⺻������ �÷��̾ ������ ����
class ShovelKnightInfo
{
    private: // Static Var

    public: // Static Func

    private: // member Var

    public:
        float m_MoveSpeed; // �̵��ӵ�

        int m_HP;               // ü��
        int m_MaxHP;        // �ִ�ü��

        int m_MP;              // ����
        int m_MaxMP;       // �ִ븶��

        int m_LostGold;        // Death������ ����� ���
        int m_HoldingGold;  // ���� �������
        int m_MaxHoldingGold;
        int m_RecoveryGold; // ȸ���� ���

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
        // �̵� �ӵ� ����
        float GetMoveSpeed();
        void SetMoveSpeed(float _Speed);

        // ��� ����
        int GetHoldingGold();
        void SetHoldingGold(int _HoldingGold);
        int GetMaxHoldingGold();
        void SetMaxHoldingGold(int _MaxHoldingGold);
        void AddHoldingGold(int _AddGold);
        int GetLostGold();
        void SetLostGold(int _LostGold);
        int GetRecoveryGold();
        void SetRecoveryGold(int _RecoveryGold);

        // ü�� �� ���� ����
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


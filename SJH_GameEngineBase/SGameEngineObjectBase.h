#pragma once

// 분류 :
// 용도 : 
// 설명 : 생명주기가 있거나 업데이트가 있는 클래스들의 기본적인 기능을 제공한다.
class SGameEngineObjectBase
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        bool m_IsOn;
        bool m_IsDeadth;
        bool m_IsDebug;
        bool m_IsOnTask;
        bool m_IsOffTask;

        SGameEngineObjectBase* m_Parent;


    public: // constructer destructer
        SGameEngineObjectBase();
        virtual ~SGameEngineObjectBase();

    public: // delete constructer 
        SGameEngineObjectBase(const SGameEngineObjectBase& _Other) = delete;
        SGameEngineObjectBase(const SGameEngineObjectBase&& _Other) = delete;

    public: // delete operator
        SGameEngineObjectBase& operator=(const SGameEngineObjectBase& _Other) = delete;
        SGameEngineObjectBase& operator=(const SGameEngineObjectBase&& _Other) = delete;

    public: // member Func
        SGameEngineObjectBase* GetPaentBase();
        void SetParentBase(SGameEngineObjectBase* _Parent);

    public:
        void IsDebugOn();
        bool IsOn();
        void On();
        void Off();

        void DebugCheck();
        
    public:
        bool IsDeath();
        void Death();

    public:
        void CallOffTask();
        bool IsOffTask();
        void CallOnTask();
        bool IsOnTask();

    public:
        virtual void OnTask();
        virtual void OffTask();
        virtual void DeathTask();

};


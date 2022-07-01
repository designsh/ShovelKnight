#pragma once
#include <Windows.h>

// 분류 :
// 용도 : 
// 설명 : 
class SGameEngineTimer
{
    private: // Static Var

    public: // Static Var
        static SGameEngineTimer MainTimer;

    public: // Static Func
        static float FDeltaTime(float _Speed = 1.0f);

    private: // member Var

    public:
        LARGE_INTEGER m_CountTime;
        LARGE_INTEGER m_CurTime;
        LARGE_INTEGER m_PrevTime;
        double m_DDeltaTime;
        float m_FDeltaTime;

    public: // constructer destructer
        SGameEngineTimer();

    public: // member Func
        double GetDDeltaTime();
        float GetFDeltaTime();
        void Reset();
        void CalTime();

};


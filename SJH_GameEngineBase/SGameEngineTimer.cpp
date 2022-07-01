#include "SGameEngineTimer.h"

SGameEngineTimer SGameEngineTimer::MainTimer = SGameEngineTimer();

// Static Var

// Static Func
float SGameEngineTimer::FDeltaTime(float _Speed)
{
    return MainTimer.GetFDeltaTime() * _Speed;
}

// member Var
SGameEngineTimer::SGameEngineTimer() : m_CountTime(), m_CurTime(), m_PrevTime()
{
	QueryPerformanceFrequency(&m_CountTime);
	Reset();
}

// member Func
double SGameEngineTimer::GetDDeltaTime()
{
    return m_DDeltaTime;
}

float SGameEngineTimer::GetFDeltaTime()
{
    return m_FDeltaTime;
}

void SGameEngineTimer::Reset()
{
    QueryPerformanceCounter(&m_CurTime);
    QueryPerformanceCounter(&m_PrevTime);
}

void SGameEngineTimer::CalTime()
{
    QueryPerformanceCounter(&m_CurTime);
    __int64 InterCount = m_CurTime.QuadPart - m_PrevTime.QuadPart;
    m_DDeltaTime = (double)InterCount / (double)m_CountTime.QuadPart;
    m_FDeltaTime = (float)m_DDeltaTime;
    m_PrevTime.QuadPart = m_CurTime.QuadPart;
}

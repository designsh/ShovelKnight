#include "DropGold.h"

// 대기상태(골드가 드랍되는 방향설정상태)
void DropGold::IDLEStart()
{
	// 플레이어 위치에 따른 무브 방향설정
	SetMoveDirect();
}

void DropGold::IDLEStay()
{
	m_DropGoldFSM.ChangeState(L"DropGold_Move");
}

void DropGold::IDLEEnd()
{

}

// 골드 드랍중인상태
void DropGold::MoveStart()
{
	SetDropGoldImage(m_DropGold);

	// 드랍중에 충돌체 Off
	m_DropGoldCol->Off();

	// 드랍 파워설정
	m_DropPos = FLOAT4::ZERO;
	m_DropPower = FLOAT4(0.f, -300.f);
	m_DropGravityPower = FLOAT4(0.f, 1000.f);

	// 플레이어 위치에 따른 무브 방향설정
	SetMoveDirect();
}

void DropGold::MoveStay()
{
	MovePosCheck();

	MoveStateCheck();
}

void DropGold::MoveEnd()
{

}

// 골드 Blink 상태전 Delay
void DropGold::TimeDelayStart()
{

}

void DropGold::TimeDelayStay()
{
	// 골드 증발 딜레이타임
	m_DelayTime -= SGameEngineTimer::FDeltaTime();
	if (0.0f >= m_DelayTime)
	{
		m_DelayTime = 2.f;

		m_DropGoldFSM.ChangeState(L"DropGold_Death");
	}
}

void DropGold::TimeDelayEnd()
{

}

// 골드 Blink 및 증발 상태
void DropGold::GoldEvaporationStart()
{
	if (0 == m_AlphaEventer.IsEventSize())
	{
		m_AlphaEventer.CreateTimeEvent(0.1f, this, &DropGold::TimeAlphaInEnd, &DropGold::TimeAlphaInStart, &DropGold::TimeAlphaInStay);
		m_AlphaEventer.CreateTimeEvent(0.1f, this, &DropGold::TimeAlphaOutEnd, &DropGold::TimeAlphaOutStart, &DropGold::TimeAlphaOutStay);
		m_AlphaEventer.LoopOn();
	}
}

void DropGold::GoldEvaporationStay()
{
	m_AlphaEventer.Update();

	// 죽는 타이밍 시간 계산
	m_DeathTime -= SGameEngineTimer::FDeltaTime();
	if (0.0f >= m_DeathTime)
	{
		m_DeathTime = 3.f;

		Death();
	}
}

void DropGold::GoldEvaporationEnd()
{

}

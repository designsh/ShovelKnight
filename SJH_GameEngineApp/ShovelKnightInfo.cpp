#include "ShovelKnightInfo.h"

// Static Var

// Static Func

// member Var
ShovelKnightInfo::ShovelKnightInfo() 
	: m_MoveSpeed(1.f),
	m_HP(4), m_MaxHP(4),
	m_MP(30), m_MaxMP(30),
	m_HoldingGold(0), m_MaxHoldingGold(0), m_LostGold(0), m_RecoveryGold(0)
{

}

ShovelKnightInfo::~ShovelKnightInfo()
{

}

// member Func
void ShovelKnightInfo::ResetPlayerInfo()
{
	// 플레이어가 사망했을때 호출되는 함수이며
	// 플레이어의 기본 정보를 리셋한다.
	m_HP = 8;
	m_MP = 30;
}

// 이동 속도 관련
float ShovelKnightInfo::GetMoveSpeed()
{
	return m_MoveSpeed;
}

void ShovelKnightInfo::SetMoveSpeed(float _Speed)
{
	m_MoveSpeed = _Speed;
}

// 골드 관련
int ShovelKnightInfo::GetHoldingGold()
{
	return m_HoldingGold;
}

void ShovelKnightInfo::SetHoldingGold(int _HoldingGold)
{
	m_HoldingGold = _HoldingGold;
}

int ShovelKnightInfo::GetMaxHoldingGold()
{
	return m_MaxHoldingGold;
}

void ShovelKnightInfo::SetMaxHoldingGold(int _MaxHoldingGold)
{
	m_MaxHoldingGold = _MaxHoldingGold;
}

void ShovelKnightInfo::AddHoldingGold(int _AddGold)
{
	m_HoldingGold += _AddGold;
}

int ShovelKnightInfo::GetLostGold()
{
	return m_LostGold;
}

void ShovelKnightInfo::SetLostGold(int _LostGold)
{
	m_LostGold = _LostGold;
}

int ShovelKnightInfo::GetRecoveryGold()
{
	return m_RecoveryGold;
}

void ShovelKnightInfo::SetRecoveryGold(int _RecoveryGold)
{
	m_RecoveryGold = _RecoveryGold;
}

// 체력 및 마력 관련
int ShovelKnightInfo::GetCurHP()
{
	return m_HP;
}

void ShovelKnightInfo::SetCurHP(int _HP)
{
	m_HP = _HP;
}

void ShovelKnightInfo::SubtractCurHP(int _BeShotCount)
{
	m_HP -= _BeShotCount;
}

void ShovelKnightInfo::AddCurHP(int _AddHP)
{
	m_HP += _AddHP;
}

int ShovelKnightInfo::GetMaxHP()
{
	return m_MaxHP;
}

void ShovelKnightInfo::SetMaxHP(int _MaxHP)
{
	m_MaxHP = _MaxHP;
}

int ShovelKnightInfo::GetCurMP()
{
	return m_MP;
}

void ShovelKnightInfo::SetCurMP(int _MP)
{
	m_MP = _MP;
}

void ShovelKnightInfo::ConsumptionCurMP(int _ConsumptionMP)
{
	m_MP -= _ConsumptionMP;
}

void ShovelKnightInfo::AddCurMP(int _AddMP)
{
	m_MP += _AddMP;
}

int ShovelKnightInfo::GetMaxMP()
{
	return m_MaxMP;
}

void ShovelKnightInfo::SetMaxMP(int _MaxMP)
{
	m_MaxMP = _MaxMP;
}

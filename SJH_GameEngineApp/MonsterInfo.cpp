#include "MonsterInfo.h"

// Static Var

// Static Func

// member Var
MonsterInfo::MonsterInfo()
	: m_MoveSpeed(0.0f),
      m_DropCoin(0), 
      m_HP(0), 
      m_MaxHP(0),
      m_MaxDistance(FLOAT4::ZERO),
      m_MaximumRange(FLOAT4::ZERO)
{

}

MonsterInfo::~MonsterInfo()
{

}

// member Func
void MonsterInfo::SetMoveSpeed(float _MoveSpeed)
{
    m_MoveSpeed = _MoveSpeed;
}

float MonsterInfo::GetMoveSpeed()
{
    return m_MoveSpeed;
}

void MonsterInfo::SetDropCoin(int _Coin)
{
    m_DropCoin = _Coin;
}

int MonsterInfo::GetDropCoin()
{
    return m_DropCoin;
}

void MonsterInfo::SetHP(int _HP)
{
    m_HP = _HP;
}

void MonsterInfo::AddHP(int _HP)
{
    m_HP += _HP;
}

void MonsterInfo::SubtractHP(int _SubtractHP)
{
    m_HP -= _SubtractHP;
}

void MonsterInfo::SubtractHPAll()
{
    m_HP = 0;
}

int MonsterInfo::GetHP()
{
    return m_HP;
}

void MonsterInfo::SetMaxHP(int _MaxHP)
{
    m_MaxHP = _MaxHP;
}

int MonsterInfo::GetMaxHP()
{
    return m_MaxHP;
}

void MonsterInfo::SetMaxDistance(FLOAT4 _MaxDist)
{
    m_MaxDistance = _MaxDist;
}

FLOAT4 MonsterInfo::GetMaxDistance()
{
    return m_MaxDistance;
}

void MonsterInfo::SetMaximumRange(FLOAT4 _MaxRange)
{
    m_MaximumRange = _MaxRange;
}

FLOAT4 MonsterInfo::GetMaximumRange()
{
    return m_MaximumRange;
}
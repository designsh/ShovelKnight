#include "SGameEngineObjectBase.h"

// Static Var

// Static Func

// member Var
SGameEngineObjectBase::SGameEngineObjectBase()
	: m_IsOn(true), m_IsDeadth(false), m_Parent(nullptr), m_IsDebug(false), m_IsOnTask(false), m_IsOffTask(false)
{

}

SGameEngineObjectBase::~SGameEngineObjectBase()
{
	// 해당 객체의 소멸자 호출시에 메모리상의 해당 객체의
	// 영역을 파괴하기때문에 
	// DeathTask()를 호출하여 파괴직전에 할 수 있는 일을 실행한다.
	DeathTask();
}

void SGameEngineObjectBase::IsDebugOn() 
{
	m_IsDebug = true;
}

// member Func
void SGameEngineObjectBase::CallOffTask()
{
	if (true == m_IsOffTask)
	{
		OffTask();
		m_IsOffTask = false;
	}
}

bool SGameEngineObjectBase::IsOffTask()
{
	return m_IsOffTask;
}

void SGameEngineObjectBase::CallOnTask()
{
	if (true == m_IsOnTask)
	{
		OnTask();
		m_IsOnTask = false;
	}
}

bool SGameEngineObjectBase::IsOnTask()
{
	return m_IsOnTask;
}

// Object On/Off Function
bool SGameEngineObjectBase::IsOn()
{
	if (nullptr == m_Parent)
	{
		return m_IsOn && (false == m_IsDeadth);
	}

	return (m_IsOn && (false == m_IsDeadth)) && m_Parent->IsOn();
}

void SGameEngineObjectBase::On()
{
	if (false == m_IsOn)
	{
		m_IsOnTask = true;
	}

	m_IsOn = true;
}

void SGameEngineObjectBase::Off()
{
	if (true == m_IsOn)
	{
		m_IsOffTask = true;
	}

	m_IsOn = false;
}

void SGameEngineObjectBase::DebugCheck() 
{
	if (true == m_IsDebug)
	{
		// 디버그
	}
}

// Object Death Function
bool SGameEngineObjectBase::IsDeath()
{
	if (nullptr == m_Parent)
	{
		return m_IsDeadth;
	}

	return m_IsDeadth || m_Parent->IsDeath();
}

void SGameEngineObjectBase::Death()
{
	m_IsDeadth = true;
}

// 해당 Object의 부모 Object 가져오기 및 설정 Function
SGameEngineObjectBase* SGameEngineObjectBase::GetPaentBase()
{
	return m_Parent;
}

void SGameEngineObjectBase::SetParentBase(SGameEngineObjectBase* _Parent)
{
	m_Parent = _Parent;
}

// Object가 꺼졌다가 다시 켜질때 일어날 수 있는 일
void SGameEngineObjectBase::OnTask()
{

}

// Object가 켜져있다가 꺼졌을때 일어날 수 있는 일
void SGameEngineObjectBase::OffTask()
{

}

// Object가 완전히 메모리상에서 파괴되기 직전에 일어날 수 있는 일
void SGameEngineObjectBase::DeathTask()
{

}
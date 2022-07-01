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
	// �ش� ��ü�� �Ҹ��� ȣ��ÿ� �޸𸮻��� �ش� ��ü��
	// ������ �ı��ϱ⶧���� 
	// DeathTask()�� ȣ���Ͽ� �ı������� �� �� �ִ� ���� �����Ѵ�.
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
		// �����
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

// �ش� Object�� �θ� Object �������� �� ���� Function
SGameEngineObjectBase* SGameEngineObjectBase::GetPaentBase()
{
	return m_Parent;
}

void SGameEngineObjectBase::SetParentBase(SGameEngineObjectBase* _Parent)
{
	m_Parent = _Parent;
}

// Object�� �����ٰ� �ٽ� ������ �Ͼ �� �ִ� ��
void SGameEngineObjectBase::OnTask()
{

}

// Object�� �����ִٰ� �������� �Ͼ �� �ִ� ��
void SGameEngineObjectBase::OffTask()
{

}

// Object�� ������ �޸𸮻󿡼� �ı��Ǳ� ������ �Ͼ �� �ִ� ��
void SGameEngineObjectBase::DeathTask()
{

}
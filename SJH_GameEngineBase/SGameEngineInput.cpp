#include "SGameEngineInput.h"
#include <Windows.h>

// Static Var
std::map<SGameEngineString, SGameEngineInput::SGameEngineKey> SGameEngineInput::m_KeyMap;

// Static Func
bool SGameEngineInput::IsFree(const SGameEngineString& _Name)
{
	return FindKey(_Name).m_KeyFree;
}
bool SGameEngineInput::IsUp(const SGameEngineString& _Name)
{
	return FindKey(_Name).m_KeyUp;
}
bool SGameEngineInput::IsPress(const SGameEngineString& _Name)
{
	return FindKey(_Name).m_KeyPress;
}
bool SGameEngineInput::IsDown(const SGameEngineString& _Name)
{
	return FindKey(_Name).m_KeyDown;
}

// member Var

SGameEngineInput::SGameEngineInput()
{

}

SGameEngineInput::~SGameEngineInput()
{

}

// Inner Class ������ �Ҹ���
SGameEngineInput::SGameEngineKey::SGameEngineKey() : m_KeyDown(false), m_KeyPress(false), m_KeyUp(false), m_KeyFree(true)
{

}

SGameEngineInput::SGameEngineKey::~SGameEngineKey()
{

}

// Inner Class Member Func
bool SGameEngineInput::SGameEngineKey::KeyCheck()
{
	for (size_t i = 0; i < m_Key.size(); i++)
	{
		// ����Ű�ΰ�� : �ϳ��� Ű�� ������ �ʾҴٸ�
		if (0 == GetAsyncKeyState(m_Key[i]))
		{
			return false;
		}
	}

	// ����Ű���� Ű�� ��� �������ٸ�
	return true;
}

void SGameEngineInput::SGameEngineKey::KeyStateUpdate()
{
	// Ű�� ���ȴ�
	if (true == KeyCheck())
	{
		if (true == m_KeyFree) // ��ó�� ��������
		{
			m_KeyDown = true;
			m_KeyPress = true;
			m_KeyUp = false;
			m_KeyFree = false;
		}
		else // ���� �����ӿ� ���ȴ������־�����
		{
			m_KeyDown = false;
			m_KeyPress = true;
			m_KeyUp = false;
			m_KeyFree = false;
		}
	}
	else // Ű�� �������� �ʾҴ�.
	{
		// ���������� �ٷ� ���� �����ӱ����� Ű�� �������־��ٸ�
		if (true == m_KeyPress)
		{
			m_KeyDown = false;
			m_KeyPress = false;
			m_KeyUp = true;
			m_KeyFree = true;
		}
		else // ���������� �ٷ� ���� �����ӱ����� ���������ʾҴ�.
		{
			m_KeyDown = false;
			m_KeyPress = false;
			m_KeyUp = false;
			m_KeyFree = true;
		}
	}
}

// member Func
SGameEngineInput::SGameEngineKey& SGameEngineInput::FindKey(const SGameEngineString& _KeyName)
{
	if (m_KeyMap.end() == m_KeyMap.find(_KeyName))
	{
		SGameEngineDebug::AssertMsg(L"if (m_KeyMap.end() == m_KeyMap.find(_KeyName))");
		return m_KeyMap[_KeyName];
	}

	return m_KeyMap[_KeyName];
}

void SGameEngineInput::Update()
{
	std::map<SGameEngineString, SGameEngineKey>::iterator Start = m_KeyMap.begin();
	std::map<SGameEngineString, SGameEngineKey>::iterator End = m_KeyMap.end();

	for (; Start != End; ++Start)
	{
		Start->second.KeyStateUpdate();
	}
}



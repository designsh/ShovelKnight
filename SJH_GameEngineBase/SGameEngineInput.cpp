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

// Inner Class 생성자 소멸자
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
		// 복합키인경우 : 하나라도 키를 누르지 않았다면
		if (0 == GetAsyncKeyState(m_Key[i]))
		{
			return false;
		}
	}

	// 복합키에서 키가 모두 눌려졌다면
	return true;
}

void SGameEngineInput::SGameEngineKey::KeyStateUpdate()
{
	// 키를 눌렸다
	if (true == KeyCheck())
	{
		if (true == m_KeyFree) // 맨처음 눌렸을때
		{
			m_KeyDown = true;
			m_KeyPress = true;
			m_KeyUp = false;
			m_KeyFree = false;
		}
		else // 이전 프레임에 눌렸던적이있었을때
		{
			m_KeyDown = false;
			m_KeyPress = true;
			m_KeyUp = false;
			m_KeyFree = false;
		}
	}
	else // 키를 누르지는 않았다.
	{
		// 현재프레임 바로 이전 프레임까지도 키를 누르고있었다면
		if (true == m_KeyPress)
		{
			m_KeyDown = false;
			m_KeyPress = false;
			m_KeyUp = true;
			m_KeyFree = true;
		}
		else // 현재프레임 바로 이전 프레임까지도 눌려있지않았다.
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



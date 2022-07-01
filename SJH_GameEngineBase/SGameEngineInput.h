#pragma once
#include <vector>
#include <map>
#include "SGameEngineString.h"
#include "SGameEngineDebug.h"

// 분류 :
// 용도 : 
// 설명 : 모든 키(키보드 or 마우스)를 관리하고 키의 기능을 구현한 클래스이다.
class SGameEngineInput
{
    public:
        class SGameEngineKey
        {
            public:
                std::vector<int> m_Key;

            public:
                bool m_KeyDown;
                bool m_KeyPress;
                bool m_KeyUp;
                bool m_KeyFree;

            public:
                template<typename ... REST>
                void PushKey(int _Key, REST ... _Arg)
                {
                    // 소문자 -> 대문자
                    if ('a' <= _Key && 'z' >= _Key)
                    {
                        _Key = toupper(_Key);
                    }

                    m_Key.push_back(_Key);
                    PushKey(_Arg ...);
                }

                void PushKey(int _Key)
                {
                    // 소문자 -> 대문자
                    if ('a' <= _Key && 'z' >= _Key)
                    {
                        _Key = toupper(_Key);
                    }
                    m_Key.push_back(_Key);
                }

            public:
                bool KeyCheck();
                void KeyStateUpdate();

            public:
                SGameEngineKey();
                ~SGameEngineKey();
        };

    private: // Static Var
        static std::map<SGameEngineString, SGameEngineKey> m_KeyMap;

    public: // Static Func
        static void Update();

        static bool IsFree(const SGameEngineString& _KeyName);
        static bool IsUp(const SGameEngineString& _KeyName);
        static bool IsPress(const SGameEngineString& _KeyName);
        static bool IsDown(const SGameEngineString& _KeyName);

    private:
        static SGameEngineKey& FindKey(const SGameEngineString& _KeyName);

    private: // member Var

    public: // constructer destructer
        SGameEngineInput();
        ~SGameEngineInput();

    public: // delete constructer 
        SGameEngineInput(const SGameEngineInput& _Other) = delete;
        SGameEngineInput(const SGameEngineInput&& _Other) = delete;

    public: // delete operator
        SGameEngineInput& operator=(const SGameEngineInput& _Other) = delete;
        SGameEngineInput& operator=(const SGameEngineInput&& _Other) = delete;

    public: // member Func
        template<typename ... REST>
        static void CreateKey(const SGameEngineString& _KeyName, REST ... _Arg)
        {
            // 현재 KeyMap에 생성하려는 키가 없으면
            if (m_KeyMap.end() == m_KeyMap.find(_KeyName))
            {
                m_KeyMap.insert(std::map<SGameEngineString, SGameEngineKey>::value_type(_KeyName, SGameEngineKey()));
            }
            else // 현재 KeyMap에 생성하려는 키가 존재한다면 프로그램을 터뜨린다.
            {
                SGameEngineDebug::AssertMsg(L"if (m_KeyMap.end() != m_KeyMap.find(_KeyName))");
            }

            m_KeyMap[_KeyName].m_Key.reserve(sizeof...(_Arg));
            m_KeyMap[_KeyName].PushKey(_Arg...);
        }

};


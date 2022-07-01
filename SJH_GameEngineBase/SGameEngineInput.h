#pragma once
#include <vector>
#include <map>
#include "SGameEngineString.h"
#include "SGameEngineDebug.h"

// �з� :
// �뵵 : 
// ���� : ��� Ű(Ű���� or ���콺)�� �����ϰ� Ű�� ����� ������ Ŭ�����̴�.
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
                    // �ҹ��� -> �빮��
                    if ('a' <= _Key && 'z' >= _Key)
                    {
                        _Key = toupper(_Key);
                    }

                    m_Key.push_back(_Key);
                    PushKey(_Arg ...);
                }

                void PushKey(int _Key)
                {
                    // �ҹ��� -> �빮��
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
            // ���� KeyMap�� �����Ϸ��� Ű�� ������
            if (m_KeyMap.end() == m_KeyMap.find(_KeyName))
            {
                m_KeyMap.insert(std::map<SGameEngineString, SGameEngineKey>::value_type(_KeyName, SGameEngineKey()));
            }
            else // ���� KeyMap�� �����Ϸ��� Ű�� �����Ѵٸ� ���α׷��� �Ͷ߸���.
            {
                SGameEngineDebug::AssertMsg(L"if (m_KeyMap.end() != m_KeyMap.find(_KeyName))");
            }

            m_KeyMap[_KeyName].m_Key.reserve(sizeof...(_Arg));
            m_KeyMap[_KeyName].PushKey(_Arg...);
        }

};


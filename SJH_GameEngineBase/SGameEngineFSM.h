#pragma once
#include "SGameEngineTimer.h"
#include "SGameEngineString.h"
#include "SGameEngineDebug.h"

#include <map>

// 분류 :
// 용도 : 
// 설명 : 사용자의 입력이나 의도에 의하여 상태를 변화 시키는 클래스
//           한개의 개념에 하나의 기능을하는 클래스이다.
template <typename StateTarget>
class SGameEngineFSM
{
    // Inner Class
    public:
        class SGameEngineState
        {
            public:
                StateTarget* m_Obj;
                void(StateTarget::* m_StartFunc)();
                void(StateTarget::* m_EndFunc)();
                void(StateTarget::* m_StayFunc)();

            public:
                SGameEngineState() : m_Obj(nullptr), m_StartFunc(nullptr), m_EndFunc(nullptr), m_StayFunc(nullptr)
                {

                }

                ~SGameEngineState()
                {

                }

            public:
                void Start()
                {
                    if (nullptr == m_StartFunc)
                    {
                        return;
                    }

                    (m_Obj->*m_StartFunc)();
                }

                void End()
                {
                    if (nullptr == m_EndFunc)
                    {
                        return;
                    }

                    (m_Obj->*m_EndFunc)();
                }

                void Update()
                {
                    if (nullptr == m_StayFunc)
                    {
                        SGameEngineDebug::AssertMsg(L"if (nullptr == m_StayFunc)");
                    }

                    (m_Obj->*m_StayFunc)();
                }
        };

    private: // Static Var

    public: // Static Func
    
    private: // member Var
        std::map<SGameEngineString, SGameEngineState> m_State;
        SGameEngineState* m_CurState;

    public: // constructer destructer
        SGameEngineFSM() : m_CurState(nullptr)
        {

        }

        ~SGameEngineFSM()
        {
            m_State.clear();
        }

    public: // delete constructer 
        SGameEngineFSM(const SGameEngineFSM& _Other) = delete;
        SGameEngineFSM(const SGameEngineFSM&& _Other) = delete;

    public: // delete operator
        SGameEngineFSM& operator=(const SGameEngineFSM& _Other) = delete;
        SGameEngineFSM& operator=(const SGameEngineFSM&& _Other) = delete;

    public: // member Func
        void CreateState(SGameEngineString _StartName, StateTarget* _Obj, void(StateTarget::*_StayFunc)(), void(StateTarget::*_StartFunc)() = nullptr, void(StateTarget::*_EndFunc)() = nullptr)
        {
            if (m_State.end() != m_State.find(_StartName))
            {
                SGameEngineDebug::AssertMsg(L"if (m_State.end() != m_State.fine(_StartName))");
            }

            m_State[_StartName].m_Obj = _Obj;
            m_State[_StartName].m_StayFunc = _StayFunc;
            m_State[_StartName].m_StartFunc = _StartFunc;
            m_State[_StartName].m_EndFunc = _EndFunc;
        }

        void ChangeState(SGameEngineString _StartName)
        {
            if (m_State.end() == m_State.find(_StartName))
            {
                SGameEngineDebug::AssertMsg(L"if (m_State.end() == m_State.find(_StartName))");
            }

            if (nullptr != m_CurState)
            {
                m_CurState->End();
            }

            m_CurState = &m_State[_StartName];
            m_CurState->Start();
        }

        void Update()
        {
            if (nullptr == m_CurState)
            {
                SGameEngineDebug::AssertMsg(L"if (nullptr == m_CurState)");
            }

            m_CurState->Update();
        }

};


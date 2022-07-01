#pragma once
#include "SGameEngineTimer.h"
#include "SGameEngineDebug.h"
#include <vector>

// 분류 :
// 용도 : 
// 설명 : n초 후에 m함수를 실행하는 클래스
template<typename EventTarget>
class SGameEngineTimeEventer
{
    // Inner Class
	public:
		class STimeEvent
		{
			public:
				float m_Time;
				float m_MaxTime;
				EventTarget* m_Object;
				void(EventTarget::* m_StartFunc)();
				void(EventTarget::* m_EndFunc)();
				void(EventTarget::* m_StayFunc)();
				bool(EventTarget::* m_StopFunc)();

			public:
				void Reset() 
				{
					m_Time = m_MaxTime;
				}

			public:
				STimeEvent() : m_Time(0.0f), m_MaxTime(0.0f), m_Object(), m_StartFunc(), m_EndFunc(), m_StayFunc(), m_StopFunc()
				{

				}

				~STimeEvent()
				{

				}

			public:
				bool Update()
				{
					// m_Time과 m_MaxTime가 같다는 것은
					// 처음 시작 프레임이다.
					if (m_Time >= m_MaxTime)
					{
						// 시간을 계산해준다.
						m_Time -= SGameEngineTimer::FDeltaTime();

						// 이때 m_StartFunc 이 없다면 false를 리턴
						if (nullptr == m_StartFunc)
						{
							return false;
						}

						// 위의 조건이 아니라면 
						// 해당 함수를 실행한다.
						(m_Object->*m_StartFunc)();

						return false;
					}

					m_Time -= SGameEngineTimer::FDeltaTime();
					if (0.0 <= m_Time)
					{
						if (nullptr == m_StayFunc)
						{
							return false;
						}

						if (nullptr != m_StopFunc)
						{
							if (true == (m_Object->*m_StopFunc)())
							{
								return false;
							}
						}

						(m_Object->*m_StayFunc)();

						return false;
					}

					m_Time = m_MaxTime;
					if (nullptr == m_EndFunc)
					{
						return true;
					}

					(m_Object->*m_EndFunc)();
					return true;
				}
		};

    private: // Static Var

    public: // Static Var

    public: // Static Func

    private: // member Var
		int m_CurEvent;
		bool m_Loop;
		std::vector<STimeEvent> m_Events;

	public:
		size_t IsEventSize() 
		{
			return m_Events.size();
		}


    public: // constructer destructer
		SGameEngineTimeEventer() : m_CurEvent(0), m_Loop(false), m_Events()
		{

		}

		~SGameEngineTimeEventer()
		{

		}

    public: // member Func
		void LoopOn()
		{
			m_Loop = true;
		}

		void LoopOff()
		{
			m_Loop = false;
		}

		bool IsEnd()
		{
			return m_CurEvent >= m_Events.size();
		}

		bool IsLoop()
		{
			return m_Loop;
		}

		void CreateTimeEventEnd(float _Time, EventTarget* _Obj, void(EventTarget::* _EndFunc)(), void(EventTarget::* _StartFunc)() = nullptr, void(EventTarget::* _StayFunc)() = nullptr, bool(EventTarget::* m_StopFunc)() = nullptr)
		{
			m_Events.resize(m_Events.size() + 1);
			m_Events[m_Events.size() - 1].m_Time = _Time;
			m_Events[m_Events.size() - 1].m_MaxTime = _Time;
			m_Events[m_Events.size() - 1].m_Object = _Obj;
			m_Events[m_Events.size() - 1].m_StartFunc = _StartFunc;
			m_Events[m_Events.size() - 1].m_StayFunc = _StayFunc;
			m_Events[m_Events.size() - 1].m_EndFunc = _EndFunc;
			m_Events[m_Events.size() - 1].m_StopFunc = m_StopFunc;
		}

		void CreateTimeEventStay(float _Time, EventTarget* _Obj, void(EventTarget::* _StayFunc)(), void(EventTarget::* _StartFunc)() = nullptr,  void(EventTarget::* _EndFunc)() = nullptr, bool(EventTarget::* m_StopFunc)() = nullptr)
		{
			m_Events.resize(m_Events.size() + 1);
			m_Events[m_Events.size() - 1].m_Time = _Time;
			m_Events[m_Events.size() - 1].m_MaxTime = _Time;
			m_Events[m_Events.size() - 1].m_Object = _Obj;
			m_Events[m_Events.size() - 1].m_StartFunc = _StartFunc;
			m_Events[m_Events.size() - 1].m_StayFunc = _StayFunc;
			m_Events[m_Events.size() - 1].m_EndFunc = _EndFunc;
			m_Events[m_Events.size() - 1].m_StopFunc = m_StopFunc;
		}

		void CreateTimeEventStart(float _Time, EventTarget* _Obj, void(EventTarget::* _StartFunc)(), void(EventTarget::* _StayFunc)() = nullptr, void(EventTarget::* _EndFunc)() = nullptr, bool(EventTarget::* m_StopFunc)() = nullptr)
		{
			m_Events.resize(m_Events.size() + 1);
			m_Events[m_Events.size() - 1].m_Time = _Time;
			m_Events[m_Events.size() - 1].m_MaxTime = _Time;
			m_Events[m_Events.size() - 1].m_Object = _Obj;
			m_Events[m_Events.size() - 1].m_StartFunc = _StartFunc;
			m_Events[m_Events.size() - 1].m_StayFunc = _StayFunc;
			m_Events[m_Events.size() - 1].m_EndFunc = _EndFunc;
			m_Events[m_Events.size() - 1].m_StopFunc = m_StopFunc;
		}

		void CreateTimeEvent(float _Time, EventTarget* _Obj, void(EventTarget::* _EndFunc)(), void(EventTarget::* _StartFunc)() = nullptr, void(EventTarget::*_StayFunc)() = nullptr, bool(EventTarget::* m_StopFunc)() = nullptr)
		{
			m_Events.resize(m_Events.size() + 1);
			m_Events[m_Events.size() - 1].m_Time = _Time;
			m_Events[m_Events.size() - 1].m_MaxTime = _Time;
			m_Events[m_Events.size() - 1].m_Object = _Obj;
			m_Events[m_Events.size() - 1].m_StartFunc = _StartFunc;
			m_Events[m_Events.size() - 1].m_StayFunc = _StayFunc;
			m_Events[m_Events.size() - 1].m_EndFunc = _EndFunc;
			m_Events[m_Events.size() - 1].m_StopFunc = m_StopFunc;
		}

		void Reset() 
		{
			m_CurEvent = 0;

			for (size_t i = 0; i < m_Events.size(); i++)
			{
				m_Events[i].Reset();
			}
		}


		void Update()
		{
			if (0 == m_Events.size())
			{
				SGameEngineDebug::AssertMsg(L"if (0 == m_Events.size())");
			}

			if (m_Events.size() <= m_CurEvent)
			{
				if (false == m_Loop)
				{
					return;
				}

				m_CurEvent = 0;
			}

			if (true == m_Events[m_CurEvent].Update())
			{
				++m_CurEvent;
			}
		}

};


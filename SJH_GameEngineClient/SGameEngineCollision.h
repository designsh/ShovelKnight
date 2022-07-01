#pragma once
#include <SGameEngineObjectBase.h>
#include <SGameEngineMath.h>
#include <set>
#include <vector>

// 분류 :
// 용도 : 
// 설명 : 
class SGameEngineActor;
class SGameEngineCollision : public SGameEngineObjectBase
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        int m_Order;
        SGameEngineActor* m_Actor;
        FLOAT4 m_PivotPos;
        FLOAT4 m_ColScale;

        COLTYPE m_Type;
        Col2DData m_Data;

        // 충돌체는 자신이 충돌한 객체를 들고있는다
        std::set<SGameEngineCollision*> m_ColSet;

        // 충돌체는 자신의 충돌체액터의 종류를 알고있는다.
        int m_iCheckData;

    public: // constructer destructer
        SGameEngineCollision();
        virtual ~SGameEngineCollision();

    public: // delete constructer 
        SGameEngineCollision(const SGameEngineCollision& _Other) = delete;
        SGameEngineCollision(const SGameEngineCollision&& _Other) = delete;

    public: // delete operator
        SGameEngineCollision& operator=(const SGameEngineCollision& _Other) = delete;
        SGameEngineCollision& operator=(const SGameEngineCollision&& _Other) = delete;

    public: // member Func
        void DeathTask() override;
        void OffTask() override;

    public:
        void ReleaseUpdate();

    public:
        void SetCheckData(int _iCheckData);
        int GetCheckData();
        FLOAT4 GetPivotPos();
        void SetPivotPos(FLOAT4 _PivotPos);
        FLOAT4 GetPos();
        void SetPos(FLOAT4 _Pos);
        void SetScale(FLOAT4 _Scale);
        FLOAT4 GetScale();
        void SetOrder(int _Order);
        int GetOrder();
        void SetActor(SGameEngineActor* _Actor);
        SGameEngineActor* GetActor();
        void SetCollisionType(COLTYPE _Type);

    public:
        void CollisionDataUpdate();
        void CollisionCheck(SGameEngineCollision* _Other);

    public:
        void DebugRender();

    // Inner Class
    // 충돌시작, 충돌중, 충돌종료시 호출할 함수(각 객체가 할일)를
    // 생성하고 각 함수를 실행한다.
    private:
        class EventBase
        {
            public:
                virtual void CallBack(SGameEngineCollision* _This, SGameEngineCollision* _Other) { }
        };

        template<typename EventType>
        class EventBaseTemplate : public EventBase
        {
            public:
                EventType* m_Object;
                void(EventType::* m_StartFunc)(SGameEngineCollision* _This, SGameEngineCollision* _Other);

            public:
                void CallBack(SGameEngineCollision* _This, SGameEngineCollision* _Other) override
                {
                    (m_Object->*m_StartFunc)(_This, _Other);
                }

            public:
                EventBaseTemplate(EventType* _Obj, void(EventType::* _StartFunc)(SGameEngineCollision* _This, SGameEngineCollision* _Other))
                    : m_Object(_Obj), m_StartFunc(_StartFunc)
                {

                }
        };

    // 충돌체는 다른 충돌체와 충돌(시작, 중, 끝)일때
    // 실행하려는 함수를 벡터를 통해 저장해놓는다.
    private:
        std::vector<EventBase*> m_StartEvent;
        std::vector<EventBase*> m_StayEvent;
        std::vector<EventBase*> m_EndEvent;

    // 충돌시작 시 처리할 이벤트(함수)를 벡터에 저장 후
    // 해당 이벤트들을 실행한다.
    public:
        template<typename Target>
        void AddStartEvent(Target* _Obj, void(Target::* _StartFunc)(SGameEngineCollision* _This, SGameEngineCollision* _Other))
        {
            m_StartEvent.push_back(new EventBaseTemplate<Target>(_Obj, _StartFunc));
        }

        void UpdateStartEvent(SGameEngineCollision* _This, SGameEngineCollision* _Other)
        {
            m_ColSet.insert(_Other);

            for (size_t i = 0; i < m_StartEvent.size(); i++)
            {
                m_StartEvent[i]->CallBack(_This, _Other);
            }
        }

    // 충돌중 처리할 이벤트(함수)를 벡터에 저장 후
    // 해당 이벤트들을 실행한다.
    public:
        template<typename Target>
        void AddStayEvent(Target* _Obj, void(Target::* _StayFunc)(SGameEngineCollision* _This, SGameEngineCollision* _Other))
        {
            m_StayEvent.push_back(new EventBaseTemplate<Target>(_Obj, _StayFunc));
        }

        void UpdateStayEvent(SGameEngineCollision* _This, SGameEngineCollision* _Other)
        {
            for (size_t i = 0; i < m_StayEvent.size(); i++)
            {
                m_StayEvent[i]->CallBack(_This, _Other);
            }
        }

    // 충돌종료 시 처리할 이벤트(함수)를 벡터에 저장 후
    // 해당 이벤트들을 실행한다.
    public:
        template<typename Target>
        void AddEndEvent(Target* _Obj, void(Target::* _EndFunc)(SGameEngineCollision* _This, SGameEngineCollision* _Other))
        {
            m_EndEvent.push_back(new EventBaseTemplate<Target>(_Obj, _EndFunc));
        }

        void UpdateEndEvent(SGameEngineCollision* _This, SGameEngineCollision* _Other)
        {
            for (size_t i = 0; i < m_EndEvent.size(); i++)
            {
                m_EndEvent[i]->CallBack(_This, _Other);
            }

            m_ColSet.erase(_Other);
        }



};


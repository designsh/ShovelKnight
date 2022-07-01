#pragma once
#include <SGameEngineObjectBase.h>
#include <SGameEngineMath.h>
#include <set>
#include <vector>

// �з� :
// �뵵 : 
// ���� : 
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

        // �浹ü�� �ڽ��� �浹�� ��ü�� ����ִ´�
        std::set<SGameEngineCollision*> m_ColSet;

        // �浹ü�� �ڽ��� �浹ü������ ������ �˰��ִ´�.
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
    // �浹����, �浹��, �浹����� ȣ���� �Լ�(�� ��ü�� ����)��
    // �����ϰ� �� �Լ��� �����Ѵ�.
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

    // �浹ü�� �ٸ� �浹ü�� �浹(����, ��, ��)�϶�
    // �����Ϸ��� �Լ��� ���͸� ���� �����س��´�.
    private:
        std::vector<EventBase*> m_StartEvent;
        std::vector<EventBase*> m_StayEvent;
        std::vector<EventBase*> m_EndEvent;

    // �浹���� �� ó���� �̺�Ʈ(�Լ�)�� ���Ϳ� ���� ��
    // �ش� �̺�Ʈ���� �����Ѵ�.
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

    // �浹�� ó���� �̺�Ʈ(�Լ�)�� ���Ϳ� ���� ��
    // �ش� �̺�Ʈ���� �����Ѵ�.
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

    // �浹���� �� ó���� �̺�Ʈ(�Լ�)�� ���Ϳ� ���� ��
    // �ش� �̺�Ʈ���� �����Ѵ�.
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


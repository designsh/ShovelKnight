#pragma once
#include <SGameEngineBasePublic.h>
#include <SGameEnginePlatformPublic.h>
#include <list>
#include <map>
#include <set>

// �з� : ������Ʈ
// �뵵 : �������� & �Ŵ���
// ���� : ������ ���͵��� �����ϴ� Ŭ����
//           �������� : ���Ϳ� �ڱ��ڽ��� ������ �ִ� �Լ����� ����
//           �Ŵ��� : �ڱ��ڽ� ���� ����(������Ʈ)���� ����
class SGameEngineCollision;
class SGameEngineRenderer;
class SGameEngineActor;
class SGameEngineScene
{
    private: // Static Var
        static bool m_bIsDebugRender;

    public: // Static Func
        static void IsDebugRenderOn();
        static void IsDebugRenderOff();

    private: // member Var
        // GameEngineScene�� Actor���� �����ϹǷ� Actor List�� ������.
        std::list<SGameEngineActor*> m_Actors;

    private:
        // ������ �������ϴ� ������ �����ϹǷ�
        std::map<int, std::list<SGameEngineRenderer*>> m_RendererList;

        // ������ �浹�ϴ� ������ ����
        std::map<int, std::list<SGameEngineCollision*>> m_CollisionList;
        std::map<int, std::set<int>> m_LinkCollisionGroup;

        // ������ ī�޶� ��ġ�� �������ִ�.
        FLOAT4 m_CamPos;

    public: // constructer destructer
        SGameEngineScene();
        virtual ~SGameEngineScene();

    public: // delete constructer 
        SGameEngineScene(const SGameEngineScene& _Other) = delete;
        SGameEngineScene(const SGameEngineScene&& _Other) = delete;

    public: // delete operator
        SGameEngineScene& operator=(const SGameEngineScene& _Other) = delete;
        SGameEngineScene& operator=(const SGameEngineScene&& _Other) = delete;

    public: // member Func

        // ���ο� ���͸� �����ϴ� �Լ�
        template<typename ActorType>
        ActorType* CreateActor()
        {
            ActorType* NewActor = new ActorType();

            // ���� �ڱ��ڽ��� �������ش�.
            NewActor->SetScene(this);

            NewActor->Start();

            m_Actors.push_back(NewActor);

            return NewActor;
        }

        // �������� �̿��Ͽ� �ش� ������Ʈ���� �ϴ� ���� ���ϵ��� �����Լ����
        // �θ�� ���͸� ���������� ������ ��� �� Ư���� �ڽĸ� �˰� ������ �Ǳ� ������
        virtual void Start();
        virtual void SceneUpdate();
        virtual void SceneChangeStart();
        virtual void SceneChangeEnd();
        virtual void SceneDebugRender();
        void Progress();

    public: // ����
        void PushRenderer(SGameEngineRenderer* _Renderer);
        void Render();

    public:
        FLOAT4 GetCamPos();
        void SetCamPos(const FLOAT4& _CamPos);
        void SetCamMove(const FLOAT4& _CamPos);

    public: // �浹
        void CollisionGroupLink(int _Left, int _Right);
        void PushCollision(SGameEngineCollision* _Collision);
        void CollisionProcess();
        void CollisionGroupOtherCheck(int _Left, int _Right);
        void CollisionGroupThisCheck(int _Value);
        void CollisionPosSet();

    public: // Death
        void Release();
        void OnOffCheck();
};


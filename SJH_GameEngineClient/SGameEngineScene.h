#pragma once
#include <SGameEngineBasePublic.h>
#include <SGameEnginePlatformPublic.h>
#include <list>
#include <map>
#include <set>

// 분류 : 오브젝트
// 용도 : 업데이터 & 매니저
// 설명 : 씬내의 액터들을 관리하는 클래스
//           업데이터 : 액터와 자기자신이 가지고 있는 함수들을 실행
//           매니저 : 자기자신 내의 액터(오브젝트)들을 관리
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
        // GameEngineScene은 Actor들을 관리하므로 Actor List를 가진다.
        std::list<SGameEngineActor*> m_Actors;

    private:
        // 씬에서 랜더링하는 역할을 수행하므로
        std::map<int, std::list<SGameEngineRenderer*>> m_RendererList;

        // 씬에서 충돌하는 역할을 수행
        std::map<int, std::list<SGameEngineCollision*>> m_CollisionList;
        std::map<int, std::set<int>> m_LinkCollisionGroup;

        // 씬에서 카메라 위치를 가지고있다.
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

        // 새로운 액터를 생성하는 함수
        template<typename ActorType>
        ActorType* CreateActor()
        {
            ActorType* NewActor = new ActorType();

            // 씬이 자기자신을 세팅해준다.
            NewActor->SetScene(this);

            NewActor->Start();

            m_Actors.push_back(NewActor);

            return NewActor;
        }

        // 다형성을 이용하여 해당 오브젝트들이 하는 일을 정하도록 가상함수사용
        // 부모는 액터를 관리하지만 각각의 기능 및 특성은 자식만 알고 있으면 되기 때문에
        virtual void Start();
        virtual void SceneUpdate();
        virtual void SceneChangeStart();
        virtual void SceneChangeEnd();
        virtual void SceneDebugRender();
        void Progress();

    public: // 랜더
        void PushRenderer(SGameEngineRenderer* _Renderer);
        void Render();

    public:
        FLOAT4 GetCamPos();
        void SetCamPos(const FLOAT4& _CamPos);
        void SetCamMove(const FLOAT4& _CamPos);

    public: // 충돌
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


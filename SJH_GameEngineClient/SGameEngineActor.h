#pragma once
#include "SGameEngineScene.h"
#include <SGameEngineObjectBase.h>
#include <SGameEngineMath.h>
#include <list>

// 분류 : 오브젝트
// 용도 : 
// 설명 : 씬에 존재하는 모든 오브젝트를 관리하는 클래스
class SGameEngineRenderer;
class SGameEngineCollision;
class SGameEngineScene;
class SGameEngineActor : public SGameEngineObjectBase
{
    friend SGameEngineScene;

    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_Position;
        FLOAT4 m_OldPosition;

        // Actor는 스스로가 속한 씬을 알고있다.
        SGameEngineScene* m_Scene;

    public:
        std::list<SGameEngineRenderer*> m_Renderer;
        std::list<SGameEngineCollision*> m_Collision;

    public: // constructer destructer
        SGameEngineActor();
        virtual ~SGameEngineActor();

    public: // delete constructer 
        SGameEngineActor(const SGameEngineActor& _Other) = delete;
        SGameEngineActor(const SGameEngineActor&& _Other) = delete;

    public: // delete operator
        SGameEngineActor& operator=(const SGameEngineActor& _Other) = delete;
        SGameEngineActor& operator=(const SGameEngineActor&& _Other) = delete;

    public: // member Func
        // 엔진 시점함수
        // 구간이 필요하면 추가
        virtual void Start();
        virtual void Update();
        virtual void DebugRender();

    // 해당 함수는 내부에서 모든 처리를 끝내기 때문에
    // 다른곳에서 호출하면 안됨
    private:
        void Release();

    public:
        void DeathTask() override;

    public:
        // 위치 설정 및 가져오기
        FLOAT4 GetPosition();
        void SetPosition(const FLOAT4& _Other);

        // 이전 위치 설정 및 가져오기
        FLOAT4 GetOldPosition();
        void SetOldPosition(const FLOAT4& _Other);

        // 캠의 위치 가져오기
        FLOAT4 GetCamPosition();

        // 씬 설정 및 가져오기
        SGameEngineScene* GetScene();
        void SetScene(SGameEngineScene* _Scene);

        // 액터의 위치를 움직인다.
        void MovePosition(const FLOAT4& _Other);

    public:
        // 액터의 순서를 설정하고 해당 랜더러를 리스트로 만들어낸다.
        template<typename T>
        T* CreateRenderer(int _Order)
        {
            T* NewRenderer = new T();

            // 오더 설정
            NewRenderer->SetOrder(_Order);

            // 액터 설정
            NewRenderer->SetActor(this);
            NewRenderer->SetParentBase(this); // 액터는 자기의 부모가 누군지 알고있다.
            m_Renderer.push_back(NewRenderer);
            m_Scene->PushRenderer(NewRenderer);
            return NewRenderer;
        }

        // 액터의 순서를 설정하고 해당 충돌을 리스트로 만들어낸다.
        template<typename T>
        T* CreateCollision(int _Order)
        {
            T* NewCol = new T();

            // 오더 설정
            NewCol->SetOrder(_Order);

            // 액터 설정
            NewCol->SetActor(this);
            NewCol->SetParentBase(this); // 액터는 자기의 부모가 누군지 알고있다.
            m_Collision.push_back(NewCol);
            m_Scene->PushCollision(NewCol);
            return NewCol;
        }
};


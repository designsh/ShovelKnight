#pragma once
#include "SGameEngineScene.h"
#include <SGameEngineObjectBase.h>
#include <SGameEngineMath.h>
#include <list>

// �з� : ������Ʈ
// �뵵 : 
// ���� : ���� �����ϴ� ��� ������Ʈ�� �����ϴ� Ŭ����
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

        // Actor�� �����ΰ� ���� ���� �˰��ִ�.
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
        // ���� �����Լ�
        // ������ �ʿ��ϸ� �߰�
        virtual void Start();
        virtual void Update();
        virtual void DebugRender();

    // �ش� �Լ��� ���ο��� ��� ó���� ������ ������
    // �ٸ������� ȣ���ϸ� �ȵ�
    private:
        void Release();

    public:
        void DeathTask() override;

    public:
        // ��ġ ���� �� ��������
        FLOAT4 GetPosition();
        void SetPosition(const FLOAT4& _Other);

        // ���� ��ġ ���� �� ��������
        FLOAT4 GetOldPosition();
        void SetOldPosition(const FLOAT4& _Other);

        // ķ�� ��ġ ��������
        FLOAT4 GetCamPosition();

        // �� ���� �� ��������
        SGameEngineScene* GetScene();
        void SetScene(SGameEngineScene* _Scene);

        // ������ ��ġ�� �����δ�.
        void MovePosition(const FLOAT4& _Other);

    public:
        // ������ ������ �����ϰ� �ش� �������� ����Ʈ�� ������.
        template<typename T>
        T* CreateRenderer(int _Order)
        {
            T* NewRenderer = new T();

            // ���� ����
            NewRenderer->SetOrder(_Order);

            // ���� ����
            NewRenderer->SetActor(this);
            NewRenderer->SetParentBase(this); // ���ʹ� �ڱ��� �θ� ������ �˰��ִ�.
            m_Renderer.push_back(NewRenderer);
            m_Scene->PushRenderer(NewRenderer);
            return NewRenderer;
        }

        // ������ ������ �����ϰ� �ش� �浹�� ����Ʈ�� ������.
        template<typename T>
        T* CreateCollision(int _Order)
        {
            T* NewCol = new T();

            // ���� ����
            NewCol->SetOrder(_Order);

            // ���� ����
            NewCol->SetActor(this);
            NewCol->SetParentBase(this); // ���ʹ� �ڱ��� �θ� ������ �˰��ִ�.
            m_Collision.push_back(NewCol);
            m_Scene->PushCollision(NewCol);
            return NewCol;
        }
};


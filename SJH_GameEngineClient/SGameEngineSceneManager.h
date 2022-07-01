#pragma once
#include <map>
#include <SGameEngineString.h>
#include "SGameEngineScene.h"

// �з� :
// �뵵 : 
// ���� : 
class SGameEngineSceneManager
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        std::map<SGameEngineString, SGameEngineScene*> m_AllScene;

        // ���� �������� scene
        SGameEngineScene* m_CurScene;

        // ���� ������ scene
        SGameEngineScene* m_NextScene;

    public: // constructer destructer
        SGameEngineSceneManager();
        ~SGameEngineSceneManager();

    public: // delete constructer 
        SGameEngineSceneManager(const SGameEngineSceneManager& _Other) = delete;
        SGameEngineSceneManager(const SGameEngineSceneManager&& _Other) = delete;

    public: // delete operator
        SGameEngineSceneManager& operator=(const SGameEngineSceneManager& _Other) = delete;
        SGameEngineSceneManager& operator=(const SGameEngineSceneManager&& _Other) = delete;

    public: // member Func
        SGameEngineScene* GetCurScene()
        {
            return m_CurScene;
        }

    public:
        // Scene�� �����ϴ� �Լ�
        template<typename SceneType>
        SGameEngineScene* CreateScene(const SGameEngineString& _SceneName)
        {
            // �����س��� m_AllScene�� Map���� _SceneName�� ã�Ƴ���.
            std::map<SGameEngineString, SGameEngineScene*>::iterator FindIter = m_AllScene.find(_SceneName);

            // �ش� ���� ã���� ���
            if (m_AllScene.end() != FindIter)
            {
                return m_AllScene[_SceneName];
            }

            // ã�� ���Ѱ�� ���ο� Scene ����
            SceneType* NewScene = new SceneType();

            // ������ Scene ����
            NewScene->Start();

            // ������ Scene�� �ʿ� �߰�
            m_AllScene.insert(std::map<SGameEngineString, SGameEngineScene*>::value_type(_SceneName, NewScene));

            // ���ο� ���� ��ȯ�Ѵ�.
            return NewScene;
        }

        // Ư�� Scene�� ã�� �Լ�
        SGameEngineScene* FindScene(const SGameEngineString& _SceneName);

        // ���� Scene�� �����ϴ� �Լ�
        void ChangeScene(const SGameEngineString& _SceneName);

        // ���� �������� Scene�� Ȯ���ϴ� �Լ�
        void ChangeCheck();



};


#pragma once
#include <map>
#include <SGameEngineString.h>
#include "SGameEngineScene.h"

// 분류 :
// 용도 : 
// 설명 : 
class SGameEngineSceneManager
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        std::map<SGameEngineString, SGameEngineScene*> m_AllScene;

        // 현재 실행중인 scene
        SGameEngineScene* m_CurScene;

        // 변경 예정인 scene
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
        // Scene을 생성하는 함수
        template<typename SceneType>
        SGameEngineScene* CreateScene(const SGameEngineString& _SceneName)
        {
            // 저장해놓은 m_AllScene의 Map에서 _SceneName을 찾아낸다.
            std::map<SGameEngineString, SGameEngineScene*>::iterator FindIter = m_AllScene.find(_SceneName);

            // 해당 맵을 찾았을 경우
            if (m_AllScene.end() != FindIter)
            {
                return m_AllScene[_SceneName];
            }

            // 찾지 못한경우 새로운 Scene 생성
            SceneType* NewScene = new SceneType();

            // 생성된 Scene 시작
            NewScene->Start();

            // 생성된 Scene을 맵에 추가
            m_AllScene.insert(std::map<SGameEngineString, SGameEngineScene*>::value_type(_SceneName, NewScene));

            // 새로운 씬을 반환한다.
            return NewScene;
        }

        // 특정 Scene을 찾는 함수
        SGameEngineScene* FindScene(const SGameEngineString& _SceneName);

        // 현재 Scene을 설정하는 함수
        void ChangeScene(const SGameEngineString& _SceneName);

        // 현재 실행중인 Scene을 확인하는 함수
        void ChangeCheck();



};


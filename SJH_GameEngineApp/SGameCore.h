#pragma once
#include <SGameEngineScene.h>
#include <SGameEngineString.h>
#include <SGameEngineSceneManager.h>
#include <SGameEngineSound.h>

// 분류 : 컨텐츠
// 용도 : 업데이터 & 매니저
// 설명 : 게임의 시작을 관리하고 게임의 전반적인 내용을 관리하는 클래스
//           업데이터 : 현재 장면을 돌려주는 역할
//           매니저 : 씬을 관리
class SGameCore
{
    private: // Static Var

    public:
        static SGameEngineSceneManager SceneManager;

    public: // Static Func
        static void GameStart();
        static void GameUpdate();
        static void GameEnd();

    private: // member Var

    private: // constructer destructer
        SGameCore();
        ~SGameCore();

    public: // delete constructer 
        SGameCore(const SGameCore& _Other) = delete;
        SGameCore(const SGameCore&& _Other) = delete;

    public: // delete operator
        SGameCore& operator=(const SGameCore& _Other) = delete;
        SGameCore& operator=(const SGameCore&& _Other) = delete;

    public: // member Func

};


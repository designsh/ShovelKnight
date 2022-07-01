#pragma once
#include <SGameEngineScene.h>
#include <SGameEngineString.h>
#include <SGameEngineSceneManager.h>
#include <SGameEngineSound.h>

// �з� : ������
// �뵵 : �������� & �Ŵ���
// ���� : ������ ������ �����ϰ� ������ �������� ������ �����ϴ� Ŭ����
//           �������� : ���� ����� �����ִ� ����
//           �Ŵ��� : ���� ����
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


#pragma once
#include "SGameEngineString.h"


// �з� : �����
// �뵵 : ����
// ���� : �� Ŭ������ ������ �������� �Լ��� ���ڸ��� �̿��� ���̸�
//           ���� ��üȭ �ؼ� ����Ҽ� ���� �����ڸ� Private���� �����Ѵ�.
class SGameEngineDebug
{
    private: // Static Var

    public: // Static Func
        static void AssertMsg(const SGameEngineString& _ErrorMsg);
        static void AssertMsg(const std::string& _ErrorMsg);
        static void OutPutMsg(const SGameEngineString& _ErrorMsg);
        static void LeakCheck();

    private: // member Var

    private: // constructer destructer
        SGameEngineDebug();
        ~SGameEngineDebug();

    private: // delete constructer 
        SGameEngineDebug(const SGameEngineDebug& _Other) = delete;
        SGameEngineDebug(const SGameEngineDebug&& _Other) = delete;

    private: // delete operator
        SGameEngineDebug& operator=(const SGameEngineDebug& _Other) = delete;
        SGameEngineDebug& operator=(const SGameEngineDebug&& _Other) = delete;

    public: // member Func

};


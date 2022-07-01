#pragma once
#include "SGameEngineString.h"


// 분류 : 디버깅
// 용도 : 헬퍼
// 설명 : 이 클래스는 오로지 전역적인 함수와 인자만을 이용할 것이며
//           절대 객체화 해서 사용할수 없게 생성자를 Private으로 설정한다.
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


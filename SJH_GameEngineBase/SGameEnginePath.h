#pragma once
#include "SGameEngineString.h"

// 분류 : 
// 용도 : 
// 설명 : 
class SGameEnginePath : public SGameEngineString
{
private: // Static Var

public: // Static Func
    static bool IsExist(const SGameEngineString& _Path);
    static SGameEngineString IOName(const SGameEngineString& _Path);

private: // member Var

public: // constructer destructer
    SGameEnginePath();
    SGameEnginePath(const SGameEngineString& _Path);
    ~SGameEnginePath();

public: // member Func
    SGameEngineString IOName();
    bool IsExist();

    SGameEngineString GetPath();

};


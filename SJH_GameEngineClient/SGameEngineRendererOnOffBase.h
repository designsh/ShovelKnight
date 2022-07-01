#pragma once

// 분류 :
// 용도 : 
// 설명 : 
class SGameEngineRendererOnOffBase
{
private: // Static Var

public: // Static Func

private: // member Var
    bool OnOff;

public: // constructer destructer
    SGameEngineRendererOnOffBase();
    ~SGameEngineRendererOnOffBase();

public: // delete constructer 
    SGameEngineRendererOnOffBase(const SGameEngineRendererOnOffBase& _Other) = delete;
    SGameEngineRendererOnOffBase(const SGameEngineRendererOnOffBase&& _Other) = delete;

public: // delete operator
    SGameEngineRendererOnOffBase& operator=(const SGameEngineRendererOnOffBase& _Other) = delete;
    SGameEngineRendererOnOffBase& operator=(const SGameEngineRendererOnOffBase&& _Other) = delete;

public: // member Func
	void On();
    void Off();
    bool IsOn();

};

#include "SGameEngineRendererOnOffBase.h"

// Static Var

// Static Func

// member Var
SGameEngineRendererOnOffBase::SGameEngineRendererOnOffBase() : OnOff(true)
{

}

SGameEngineRendererOnOffBase::~SGameEngineRendererOnOffBase()
{

}

// member Func
void SGameEngineRendererOnOffBase::On()
{
	OnOff = true;
}

void SGameEngineRendererOnOffBase::Off()
{
	OnOff = false;
}

bool SGameEngineRendererOnOffBase::IsOn()
{
	return OnOff;
}

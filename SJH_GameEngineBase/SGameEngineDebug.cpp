#include "SGameEngineDebug.h"
#include <assert.h>
#include <crtdbg.h>
#include <Windows.h>

// Static Var

// Static Func
void SGameEngineDebug::AssertMsg(const SGameEngineString& _ErrorMsg)
{
#ifdef DEBUG
	//OutputDebugStringW(_ErrorMsg.c_str());
	//_wassert(_ErrorMsg.c_str(), __FILEW__, __LINE__);
	assert(!_ErrorMsg.c_str());
#endif // DEBUG
}

void SGameEngineDebug::AssertMsg(const std::string& _ErrorMsg)
{
#ifdef DEBUG
	//OutputDebugStringW(_ErrorMsg.c_str());
	//_wassert(_ErrorMsg.c_str(), __FILEW__, __LINE__);
	assert(!_ErrorMsg.c_str());
#endif // DEBUG
}

void SGameEngineDebug::OutPutMsg(const SGameEngineString& _ErrorMsg)
{
	OutputDebugStringW(_ErrorMsg.c_str());
}

void SGameEngineDebug::LeakCheck()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

// member Var
SGameEngineDebug::SGameEngineDebug()
{

}

SGameEngineDebug::~SGameEngineDebug()
{

}

// member Func
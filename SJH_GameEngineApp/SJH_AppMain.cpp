// 참조 헤더(SJH_GameEngineBase 관련 헤더)
#include <SGameEngineMemory.h>
#include <SGameEngineDirectory.h>
#include <SGameEnginePath.h>
#include <SGameEngineFile.h>
#include <SGameEngineString.h>
#include <SGameEngineTimer.h>

// 참조 헤더(SJH_GameEnginePlatform 관련 헤더)
#include <SGameEngineWindow.h>

// 라이브러리 참조 헤더
#include <SGameEngineBasePublic.h>
#include <SGameEnginePlatformPublic.h>
#include <SGameEngineClientPublic.h>

// STL 관련 헤더
#include <list>
#include <vector>
#include <map>

// 윈도우 API를 사용하기 위해 선언
#include <Windows.h>

// GameEngineApp 참조
#include "SGameCore.h"

// C++ 기본 헤더
#include <iostream>

// warning 방지를 위해 WinMain 원형 사용
// winapi는 진입점이 WinMain() 함수로 설정되어있으며 이는 원형이 존재한다. 
int __stdcall wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	SGameEngineDebug::LeakCheck();
	SGameEngineWindow::CreateGameEngineWindow(hInstance, L"GameWindow", { 100, 100 }, { 1280, 720 });
	SGameEngineWindow::GameLoop<SGameCore>();

	return 0;
}

// ���� ���(SJH_GameEngineBase ���� ���)
#include <SGameEngineMemory.h>
#include <SGameEngineDirectory.h>
#include <SGameEnginePath.h>
#include <SGameEngineFile.h>
#include <SGameEngineString.h>
#include <SGameEngineTimer.h>

// ���� ���(SJH_GameEnginePlatform ���� ���)
#include <SGameEngineWindow.h>

// ���̺귯�� ���� ���
#include <SGameEngineBasePublic.h>
#include <SGameEnginePlatformPublic.h>
#include <SGameEngineClientPublic.h>

// STL ���� ���
#include <list>
#include <vector>
#include <map>

// ������ API�� ����ϱ� ���� ����
#include <Windows.h>

// GameEngineApp ����
#include "SGameCore.h"

// C++ �⺻ ���
#include <iostream>

// warning ������ ���� WinMain ���� ���
// winapi�� �������� WinMain() �Լ��� �����Ǿ������� �̴� ������ �����Ѵ�. 
int __stdcall wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	SGameEngineDebug::LeakCheck();
	SGameEngineWindow::CreateGameEngineWindow(hInstance, L"GameWindow", { 100, 100 }, { 1280, 720 });
	SGameEngineWindow::GameLoop<SGameCore>();

	return 0;
}

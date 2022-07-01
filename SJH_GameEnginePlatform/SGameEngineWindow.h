#pragma once
#include "SGameEngineWinImage.h"
#include <SGameEngineInput.h>
#include <SGameEngineTimer.h>
#include <SGameEngineBasePublic.h>
#include <SGameEngineString.h>
#include <SGameEngineSound.h>
#include <Windows.h>

// 분류 : 
// 용도 : 
// 설명 : 윈도우를 생성하고 메세지를 감시하여 윈도우내의 모든 객체 핸들을 관리하고 사용하는 클래스
class SGameEngineWindow
{
    private: // Static Var
        // 생성된 윈도우에 대한 권한(핸들)
        static HWND m_WindowHWnd;

        // 생성된 윈도우의 DC에 대한 권한(핸들)
        static HDC m_WindowHDC;

        static FLOAT4 m_Size;
        static FLOAT4 m_Pos;
        static bool m_bWindowProgress;

        // 생성된 윈도우의 이미지
        static SGameEngineWinImage m_WindowMainImage;

        // 생성된 윈도우의 더블버퍼링 이미지
        static SGameEngineWinImage m_DoubleBufferImage;

        // 브러쉬 생성
        static HBRUSH m_GreenBrush;
        static HBRUSH m_RedBrush;

    public: // Static Func
        static FLOAT4 SettingWindowSize(FLOAT4 _Size);
        static void SetSize(FLOAT4 _Size);
        static void SetPos(FLOAT4 _Pos);
        static void SetPosAndSize(FLOAT4 _Pos, FLOAT4 _Size);

        static FLOAT4 GetSize();
        static FLOAT4 GetPos();
        static FLOAT4 MousePos();

        static HBRUSH GetGreenBrush();
        static HBRUSH GetRedBrush();

    public: // Static Func
        static __int64 WindowEvent(HWND _hWnd, unsigned int _EventType, unsigned __int64 _LValue, __int64 _SubValue);
        static void CreateGameEngineWindow(HINSTANCE _ProcessHandle, const SGameEngineString& _Name, FLOAT4 _Pos, FLOAT4 _Size);

        template<typename Updater>
        static void GameLoop()
        {
            Updater::GameStart();

            MSG MsgData;

            while (m_bWindowProgress)
            {
                // Main Timer 계산
                SGameEngineTimer::MainTimer.CalTime();
                SGameEngineInput::Update();
                SGameEngineSound::Update();

                if (0 != PeekMessage(&MsgData, m_WindowHWnd, 0, 0, PM_REMOVE))
                {
                    TranslateMessage(&MsgData);
                    DispatchMessage(&MsgData);
                    Updater::GameUpdate();
                }
                else
                {
                    // 윈도우 데드타임(메세지가 없는 시간)을 이용하여 게임을 업데이트(갱신)한다.
                    Updater::GameUpdate();
                }
            }

            Updater::GameEnd();

            // Window Handle 해제
            if (nullptr != m_WindowHWnd)
            {
                DestroyWindow(m_WindowHWnd);
                m_WindowHWnd = nullptr;
            }
        }

    public: // Static Func
        static HDC GetWindowDC();
        static HDC GetBackBufferDC();
        static SGameEngineWinImage& GetWindowImage();
        static SGameEngineWinImage& GetBackBufferImage();
        static void WindowEnd(bool _EndFlag);
        static void BackBufferCopy();

    private: // member Var

    public: // constructer destructer
        SGameEngineWindow();
        ~SGameEngineWindow();

    public: // delete constructer 
        SGameEngineWindow(const SGameEngineWindow& _Other) = delete;
        SGameEngineWindow(const SGameEngineWindow&& _Other) = delete;

    public: // delete operator
        SGameEngineWindow& operator=(const SGameEngineWindow& _Other) = delete;
        SGameEngineWindow& operator=(const SGameEngineWindow&& _Other) = delete;

    public: // member Func

};


#pragma once
#include "SGameEngineWinImage.h"
#include <SGameEngineInput.h>
#include <SGameEngineTimer.h>
#include <SGameEngineBasePublic.h>
#include <SGameEngineString.h>
#include <SGameEngineSound.h>
#include <Windows.h>

// �з� : 
// �뵵 : 
// ���� : �����츦 �����ϰ� �޼����� �����Ͽ� �����쳻�� ��� ��ü �ڵ��� �����ϰ� ����ϴ� Ŭ����
class SGameEngineWindow
{
    private: // Static Var
        // ������ �����쿡 ���� ����(�ڵ�)
        static HWND m_WindowHWnd;

        // ������ �������� DC�� ���� ����(�ڵ�)
        static HDC m_WindowHDC;

        static FLOAT4 m_Size;
        static FLOAT4 m_Pos;
        static bool m_bWindowProgress;

        // ������ �������� �̹���
        static SGameEngineWinImage m_WindowMainImage;

        // ������ �������� ������۸� �̹���
        static SGameEngineWinImage m_DoubleBufferImage;

        // �귯�� ����
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
                // Main Timer ���
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
                    // ������ ����Ÿ��(�޼����� ���� �ð�)�� �̿��Ͽ� ������ ������Ʈ(����)�Ѵ�.
                    Updater::GameUpdate();
                }
            }

            Updater::GameEnd();

            // Window Handle ����
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


#include "SGameEngineWindow.h"
#include <SGameEngineDebug.h>

#include <Windows.h>

// Static Var
FLOAT4 SGameEngineWindow::m_Size;
FLOAT4 SGameEngineWindow::m_Pos;
HWND SGameEngineWindow::m_WindowHWnd = nullptr;
HDC SGameEngineWindow::m_WindowHDC = nullptr;
bool SGameEngineWindow::m_bWindowProgress = true;
SGameEngineWinImage SGameEngineWindow::m_WindowMainImage;
SGameEngineWinImage SGameEngineWindow::m_DoubleBufferImage;
HBRUSH SGameEngineWindow::m_GreenBrush = CreateSolidBrush(RGB(0,255,0));
HBRUSH SGameEngineWindow::m_RedBrush = CreateSolidBrush(RGB(255, 0, 0));

// Static Func
HBRUSH SGameEngineWindow::GetGreenBrush()
{
	return m_GreenBrush;
}

HBRUSH SGameEngineWindow::GetRedBrush()
{
	return m_RedBrush;
}

// 마우스 좌표를 얻어오는 함수
FLOAT4 SGameEngineWindow::MousePos()
{
	POINT P;
	
	// 모니터에서의 마우스 위치
	GetCursorPos(&P);

	// m_WindowHWnd 윈도우 기준으로
	ScreenToClient(m_WindowHWnd, &P);

	return { (float)P.x, (float)P.y };
}

// 현재 윈도우의 Size를 가져오는 함수
FLOAT4 SGameEngineWindow::GetSize()
{
	return m_Size;
}

// 현재 윈도우의 Pos를 가져오는 함수
FLOAT4 SGameEngineWindow::GetPos()
{
	return m_Pos;
}

// 현재 윈도우의 DC를 가져오는 함수
HDC SGameEngineWindow::GetWindowDC()
{
	return m_WindowMainImage.GetImageDC();
}

// 현재 윈도우의 BackBuffer의 DC를 가져오는 함수
HDC SGameEngineWindow::GetBackBufferDC()
{
	return m_DoubleBufferImage.GetImageDC();
}

SGameEngineWinImage& SGameEngineWindow::GetWindowImage()
{
	return m_WindowMainImage;
}

SGameEngineWinImage& SGameEngineWindow::GetBackBufferImage()
{
	return m_DoubleBufferImage;
}

void SGameEngineWindow::WindowEnd(bool _EndFlag)
{
	m_bWindowProgress = false;
}

// 현재 윈도우 이미지를 BackBuffer의 이미지에 복사하는 함수
void SGameEngineWindow::BackBufferCopy()
{
	m_WindowMainImage.BitBlt(m_DoubleBufferImage);
}

// 현재 윈도우의 위치와 크기를 변경하는 함수
void SGameEngineWindow::SetPosAndSize(FLOAT4 _Pos, FLOAT4 _Size)
{
	m_Size = _Size;
	m_Pos = _Pos;

	RECT Rect = { 0,0, m_Size.ix(), m_Size.iy() };

	AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(m_WindowHWnd, HWND_BOTTOM, _Pos.ix(), _Pos.iy(), Rect.right - Rect.left, Rect.bottom - Rect.top, SWP_NOZORDER);
}

// 메인 윈도우 생성시 클라이언트 영역을 사용자가 정의한 크기로 설정하는 함수
FLOAT4 SGameEngineWindow::SettingWindowSize(FLOAT4 _Size)
{
	// 멤버 변수저장
	m_Size = _Size;

	// 윈도우의 높이와 넓이는 
	// 타이틀바 높이와 경계선(얇은프레임)의 크기를 포함한 크기가 지정 되므로
	// 	임시 사각형을 사용자가 입력한 크기로 만들어낸 후
	// 	이를 클라이언트(작업) 영역으로 설정하고
	// 타이틀바 높이, 경계선의 크기를 포함한 실제 윈도우창 크기를 저장하여 이를 리턴

	// Return Size 선언
	FLOAT4 SetSize = { 0, };

	// 클라이언트(작업) 영역 크기 설정
	//LONG    left;            // 왼쪽
	//LONG    top;            // 상단
	//LONG    right;          // 오른쪽
	//LONG    bottom;     // 하단
	RECT rcClient = { 0, 0, _Size.ix(), _Size.iy() };

	// 클라이언트(작업) 영역을 현재 설정한 크기로 Setting
	AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

	// 위에서 설정한 클라이언트 영역의 크기를 저장
	// Width = 오른쪽 - 왼쪽
	// Height = 하단 - 상단
	SetSize.x = (float)(rcClient.right - rcClient.left);
	SetSize.y = (float)(rcClient.bottom - rcClient.top);

	// 원래의 값을 저장하여 리턴
	SetSize.z = _Size.z;
	SetSize.w = _Size.w;

	// 메인 윈도우 생성 전에 설정하기 위하여
	// SetSize를 반환하여 메인 윈도우 생성에 사용하도록 함
	return SetSize;
}

// 생성이 완료된 윈도우의 크기를 클라이언트영역 기준으로 변경하는 함수(오더, 윈도우위치 변경안됨)
void SGameEngineWindow::SetSize(FLOAT4 _Size)
{
	// 멤버 변수저장
	m_Size = _Size;

	// 클라이언트 영역 크기를 받아올 변수
	FLOAT4 ChangeSize = { 0, };

	// 임의의 사각형을 만든다.
	RECT rcClient = { 0, 0, _Size.ix(), _Size.iy() };

	// 클라이언트(작업) 영역을 현재 설정한 크기로 Setting
	AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

	// 위에서 설정한 클라이언트 영역의 크기를 저장
	ChangeSize.x = (float)(rcClient.right - rcClient.left);
	ChangeSize.y = (float)(rcClient.bottom - rcClient.top);
	ChangeSize.z = _Size.z;
	ChangeSize.w = _Size.w;

	// 현재 윈도우의 크기를 변경(마지막인자 옵션으로 Order와 위치는 바뀌지 않도록 설정)
	SetWindowPos(m_WindowHWnd, HWND_NOTOPMOST, 0, 0, ChangeSize.ix(), ChangeSize.iy(), SWP_NOZORDER | SWP_NOMOVE);
}

// 생성이 완료된 윈도우의 위치를 변경하는 함수(오더, 윈도우크기 변경안됨)
void SGameEngineWindow::SetPos(FLOAT4 _Pos)
{
	// 멤버 변수저장
	m_Pos = _Pos;

	// 첫번째    인자 : Handle
	// 	두번째    인자 : Z Order(pWndInsertAfter : 현재 Windows 시스템이 관리하고 있는 Z Order를 기준으로 어떤 윈도우 뒤에 이 함수를 호출한 윈도우가 위치할 것인지를 지정)
	// 세번째    인자 : 이동할 위치 X
	// 네번째    인자 : 이동할 위치 Y
	// 다섯번째 인자 : Window Width(윈도우의 시작점을 변경한 후 윈도우의 폭을 지정)
	// 여섯번째 인자 : Window Height(윈도우의 시작점을 변경한 후 윈도우의 높이를 지정)
	// 일곱번째 인자 : 옵션(아래와 같음)
	// SWP_DRAWFRAME : 윈도우가 생성되었을 때 정의된 형식으로 주변의 Frame을 다시 그린다.
	// SWP_FRAMECHANGED : 윈도우의 크기 변경여부에 상관없이 해당 윈도우에게 WM_NCCALCSIZE 메시지를 전달
	// SWP_HIDEWINDOW : 현재 윈도우를 감춘다
	// SWP_NOACTIVATE : 윈도우를 활성화 시키지 않는다
	// SWP_NOCOPYBITS : Client 영역의 모든 정보를 취소
	// SWP_NOMOVE :윈도우의 현재 시작점 위치를 그대로 유지(세번째 인자, 네번째 인자 무시)
	// SWP_NOOWNERZORDER : 현재 윈도우의 Z-Order를 변경하지 않는다
	// SWP_NOREDRAW : 변경된 내용을 다시 그리지 않는다
	// SWP_NOREPOSITION : SWP_NOOWNERZORDER와 동일
	// SWP_SENDCHANGING : WM_WINDOWPOSCHANGING 메시지를 무시
	// SWP_NOSIZE : 현재 윈도우 크기를 유지(다섯번째 인자, 여섯번째 인자 무시)
	// SWP_NOZORDER : 현재의 Z-Order를 유지(두번째 인자 무시)
	// SWP_SHOWWINDOW : 윈도우를 화면에 보여준다
	SetWindowPos(m_WindowHWnd, HWND_NOTOPMOST, _Pos.ix(), _Pos.iy(), 0, 0, SWP_NOZORDER|SWP_NOSIZE);
}

__int64 SGameEngineWindow::WindowEvent(HWND _hWnd, unsigned int _EventType, unsigned __int64 _LValue, __int64 _SubValue)
{
	switch (_EventType)
	{
		// 사용자가 시스템메뉴에서 종료하거나 [ALT+F4]로 종료시 발생
		case WM_DESTROY:
		{
			m_bWindowProgress = false;
			break;
		}
		// 사용자가 현재 창의 포커스를 해제했을때
		case WM_KILLFOCUS:
		{
			// 추후하기 지금은 타일맵이 급함
			break;
		}

		default:
		{
			return DefWindowProcW(_hWnd, _EventType, _LValue, _SubValue);
		}
	}

	return 0;
}

void SGameEngineWindow::CreateGameEngineWindow(HINSTANCE _ProcessHandle, const SGameEngineString& _Name, FLOAT4 _Pos, FLOAT4 _Size)
{
	WNDCLASSEXW WCEX = { 0, };

	WCEX.cbSize = sizeof(WNDCLASSEXW);
	WCEX.style = CS_HREDRAW | CS_VREDRAW;                              // 윈도우 크기가 바뀌면 화면을 갱신
	WCEX.lpfnWndProc = &SGameEngineWindow::WindowEvent; // 윈도우 메세지 감시
	WCEX.cbClsExtra = 0;                                                                     // 윈도우의 예약영역(사용안할 시 0으로 설정)
	WCEX.cbWndExtra = 0;                                                                  // 윈도우의 예약영역(사용안할 시 0으로 설정)
	WCEX.hInstance = _ProcessHandle;                                               // 윈도우를 띄우고자하는 프로그램
	WCEX.hIcon = nullptr;                                                                     // 윈도우 아이콘
	WCEX.hIconSm = nullptr;                                                               // 윈도우 타이틀바의 아이콘
	WCEX.hCursor = nullptr;                                                                // 윈도우 창에서의 커서
	WCEX.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);      // 윈도우 창의 기본 배경색
	WCEX.lpszMenuName = nullptr;                                                   // 윈도우 창의 메뉴
	WCEX.lpszClassName = L"MYWINDOW";                                    // 현재 윈도우 형태의 명칭

	// 현재 설정한 윈도우 형태를 등록하는 함수
	// 실패시 0 반환
	if (0 == RegisterClassExW(&WCEX))
	{
		SGameEngineDebug::AssertMsg(L"if (0 == RegisterClassExW(&WCEX))");
	}

	// 메인 윈도우의 클라이언트영역을 사용자가 설정한 사이즈로 설정
	FLOAT4 ClientSize;
	ClientSize = SettingWindowSize(_Size);

	// WS_CAPTION 제목이 존재하고
	// WS_SYSMENU 메뉴가 존재하고
	// WS_THICKFRAME 얇은 외각선이 있고
	// WS_MINIMIZEBOX 최소화 버튼이 있고
	// WS_MAXIMIZEBOX 최대화 버튼이 있는
	// WS_OVERLAPPED 다른 윈도우위에오거나 아래에 올수 있는
	// 등록된 윈도우 형태로 윈도우 생성
	m_WindowHWnd = CreateWindowW(L"MYWINDOW", _Name.c_str(), WS_OVERLAPPEDWINDOW, (int)_Pos.x, (int)_Pos.y, (int)ClientSize.x, (int)ClientSize.y, nullptr, nullptr, _ProcessHandle, 0);
	if (nullptr == m_WindowHWnd) // 생성된 윈도우가 정상인지 체크
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_WindowHWnd)");
		return;
	}

	// 윈도우를 화면에 표시하는 함수
	ShowWindow(m_WindowHWnd, SW_SHOW);

	// 윈도우를 한번 갱신하는 함수
	UpdateWindow(m_WindowHWnd);

	// 생성된 윈도우의 DC를 가져온다.
	m_WindowHDC = GetDC(m_WindowHWnd);

	// GetDC()로 가져온 HDC를 이용하여 현재 윈도우의 DC를
	// 저장한다.
	m_WindowMainImage.Create(m_WindowHDC);

	// 생성된 윈도우의 _Size 정보를 이용하여 새로운 DC를 생성한다.
	m_DoubleBufferImage.Create(_Size);
}

// member Var
SGameEngineWindow::SGameEngineWindow()
{

}

SGameEngineWindow::~SGameEngineWindow()
{
	// 브러쉬 반납
	DeleteObject(m_GreenBrush);
	DeleteObject(m_RedBrush);
}

// member Func


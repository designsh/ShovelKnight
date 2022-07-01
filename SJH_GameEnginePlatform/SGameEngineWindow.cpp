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

// ���콺 ��ǥ�� ������ �Լ�
FLOAT4 SGameEngineWindow::MousePos()
{
	POINT P;
	
	// ����Ϳ����� ���콺 ��ġ
	GetCursorPos(&P);

	// m_WindowHWnd ������ ��������
	ScreenToClient(m_WindowHWnd, &P);

	return { (float)P.x, (float)P.y };
}

// ���� �������� Size�� �������� �Լ�
FLOAT4 SGameEngineWindow::GetSize()
{
	return m_Size;
}

// ���� �������� Pos�� �������� �Լ�
FLOAT4 SGameEngineWindow::GetPos()
{
	return m_Pos;
}

// ���� �������� DC�� �������� �Լ�
HDC SGameEngineWindow::GetWindowDC()
{
	return m_WindowMainImage.GetImageDC();
}

// ���� �������� BackBuffer�� DC�� �������� �Լ�
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

// ���� ������ �̹����� BackBuffer�� �̹����� �����ϴ� �Լ�
void SGameEngineWindow::BackBufferCopy()
{
	m_WindowMainImage.BitBlt(m_DoubleBufferImage);
}

// ���� �������� ��ġ�� ũ�⸦ �����ϴ� �Լ�
void SGameEngineWindow::SetPosAndSize(FLOAT4 _Pos, FLOAT4 _Size)
{
	m_Size = _Size;
	m_Pos = _Pos;

	RECT Rect = { 0,0, m_Size.ix(), m_Size.iy() };

	AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, false);

	SetWindowPos(m_WindowHWnd, HWND_BOTTOM, _Pos.ix(), _Pos.iy(), Rect.right - Rect.left, Rect.bottom - Rect.top, SWP_NOZORDER);
}

// ���� ������ ������ Ŭ���̾�Ʈ ������ ����ڰ� ������ ũ��� �����ϴ� �Լ�
FLOAT4 SGameEngineWindow::SettingWindowSize(FLOAT4 _Size)
{
	// ��� ��������
	m_Size = _Size;

	// �������� ���̿� ���̴� 
	// Ÿ��Ʋ�� ���̿� ��輱(����������)�� ũ�⸦ ������ ũ�Ⱑ ���� �ǹǷ�
	// 	�ӽ� �簢���� ����ڰ� �Է��� ũ��� ���� ��
	// 	�̸� Ŭ���̾�Ʈ(�۾�) �������� �����ϰ�
	// Ÿ��Ʋ�� ����, ��輱�� ũ�⸦ ������ ���� ������â ũ�⸦ �����Ͽ� �̸� ����

	// Return Size ����
	FLOAT4 SetSize = { 0, };

	// Ŭ���̾�Ʈ(�۾�) ���� ũ�� ����
	//LONG    left;            // ����
	//LONG    top;            // ���
	//LONG    right;          // ������
	//LONG    bottom;     // �ϴ�
	RECT rcClient = { 0, 0, _Size.ix(), _Size.iy() };

	// Ŭ���̾�Ʈ(�۾�) ������ ���� ������ ũ��� Setting
	AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

	// ������ ������ Ŭ���̾�Ʈ ������ ũ�⸦ ����
	// Width = ������ - ����
	// Height = �ϴ� - ���
	SetSize.x = (float)(rcClient.right - rcClient.left);
	SetSize.y = (float)(rcClient.bottom - rcClient.top);

	// ������ ���� �����Ͽ� ����
	SetSize.z = _Size.z;
	SetSize.w = _Size.w;

	// ���� ������ ���� ���� �����ϱ� ���Ͽ�
	// SetSize�� ��ȯ�Ͽ� ���� ������ ������ ����ϵ��� ��
	return SetSize;
}

// ������ �Ϸ�� �������� ũ�⸦ Ŭ���̾�Ʈ���� �������� �����ϴ� �Լ�(����, ��������ġ ����ȵ�)
void SGameEngineWindow::SetSize(FLOAT4 _Size)
{
	// ��� ��������
	m_Size = _Size;

	// Ŭ���̾�Ʈ ���� ũ�⸦ �޾ƿ� ����
	FLOAT4 ChangeSize = { 0, };

	// ������ �簢���� �����.
	RECT rcClient = { 0, 0, _Size.ix(), _Size.iy() };

	// Ŭ���̾�Ʈ(�۾�) ������ ���� ������ ũ��� Setting
	AdjustWindowRect(&rcClient, WS_OVERLAPPEDWINDOW, FALSE);

	// ������ ������ Ŭ���̾�Ʈ ������ ũ�⸦ ����
	ChangeSize.x = (float)(rcClient.right - rcClient.left);
	ChangeSize.y = (float)(rcClient.bottom - rcClient.top);
	ChangeSize.z = _Size.z;
	ChangeSize.w = _Size.w;

	// ���� �������� ũ�⸦ ����(���������� �ɼ����� Order�� ��ġ�� �ٲ��� �ʵ��� ����)
	SetWindowPos(m_WindowHWnd, HWND_NOTOPMOST, 0, 0, ChangeSize.ix(), ChangeSize.iy(), SWP_NOZORDER | SWP_NOMOVE);
}

// ������ �Ϸ�� �������� ��ġ�� �����ϴ� �Լ�(����, ������ũ�� ����ȵ�)
void SGameEngineWindow::SetPos(FLOAT4 _Pos)
{
	// ��� ��������
	m_Pos = _Pos;

	// ù��°    ���� : Handle
	// 	�ι�°    ���� : Z Order(pWndInsertAfter : ���� Windows �ý����� �����ϰ� �ִ� Z Order�� �������� � ������ �ڿ� �� �Լ��� ȣ���� �����찡 ��ġ�� �������� ����)
	// ����°    ���� : �̵��� ��ġ X
	// �׹�°    ���� : �̵��� ��ġ Y
	// �ټ���° ���� : Window Width(�������� �������� ������ �� �������� ���� ����)
	// ������° ���� : Window Height(�������� �������� ������ �� �������� ���̸� ����)
	// �ϰ���° ���� : �ɼ�(�Ʒ��� ����)
	// SWP_DRAWFRAME : �����찡 �����Ǿ��� �� ���ǵ� �������� �ֺ��� Frame�� �ٽ� �׸���.
	// SWP_FRAMECHANGED : �������� ũ�� ���濩�ο� ������� �ش� �����쿡�� WM_NCCALCSIZE �޽����� ����
	// SWP_HIDEWINDOW : ���� �����츦 �����
	// SWP_NOACTIVATE : �����츦 Ȱ��ȭ ��Ű�� �ʴ´�
	// SWP_NOCOPYBITS : Client ������ ��� ������ ���
	// SWP_NOMOVE :�������� ���� ������ ��ġ�� �״�� ����(����° ����, �׹�° ���� ����)
	// SWP_NOOWNERZORDER : ���� �������� Z-Order�� �������� �ʴ´�
	// SWP_NOREDRAW : ����� ������ �ٽ� �׸��� �ʴ´�
	// SWP_NOREPOSITION : SWP_NOOWNERZORDER�� ����
	// SWP_SENDCHANGING : WM_WINDOWPOSCHANGING �޽����� ����
	// SWP_NOSIZE : ���� ������ ũ�⸦ ����(�ټ���° ����, ������° ���� ����)
	// SWP_NOZORDER : ������ Z-Order�� ����(�ι�° ���� ����)
	// SWP_SHOWWINDOW : �����츦 ȭ�鿡 �����ش�
	SetWindowPos(m_WindowHWnd, HWND_NOTOPMOST, _Pos.ix(), _Pos.iy(), 0, 0, SWP_NOZORDER|SWP_NOSIZE);
}

__int64 SGameEngineWindow::WindowEvent(HWND _hWnd, unsigned int _EventType, unsigned __int64 _LValue, __int64 _SubValue)
{
	switch (_EventType)
	{
		// ����ڰ� �ý��۸޴����� �����ϰų� [ALT+F4]�� ����� �߻�
		case WM_DESTROY:
		{
			m_bWindowProgress = false;
			break;
		}
		// ����ڰ� ���� â�� ��Ŀ���� ����������
		case WM_KILLFOCUS:
		{
			// �����ϱ� ������ Ÿ�ϸ��� ����
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
	WCEX.style = CS_HREDRAW | CS_VREDRAW;                              // ������ ũ�Ⱑ �ٲ�� ȭ���� ����
	WCEX.lpfnWndProc = &SGameEngineWindow::WindowEvent; // ������ �޼��� ����
	WCEX.cbClsExtra = 0;                                                                     // �������� ���࿵��(������ �� 0���� ����)
	WCEX.cbWndExtra = 0;                                                                  // �������� ���࿵��(������ �� 0���� ����)
	WCEX.hInstance = _ProcessHandle;                                               // �����츦 �������ϴ� ���α׷�
	WCEX.hIcon = nullptr;                                                                     // ������ ������
	WCEX.hIconSm = nullptr;                                                               // ������ Ÿ��Ʋ���� ������
	WCEX.hCursor = nullptr;                                                                // ������ â������ Ŀ��
	WCEX.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);      // ������ â�� �⺻ ����
	WCEX.lpszMenuName = nullptr;                                                   // ������ â�� �޴�
	WCEX.lpszClassName = L"MYWINDOW";                                    // ���� ������ ������ ��Ī

	// ���� ������ ������ ���¸� ����ϴ� �Լ�
	// ���н� 0 ��ȯ
	if (0 == RegisterClassExW(&WCEX))
	{
		SGameEngineDebug::AssertMsg(L"if (0 == RegisterClassExW(&WCEX))");
	}

	// ���� �������� Ŭ���̾�Ʈ������ ����ڰ� ������ ������� ����
	FLOAT4 ClientSize;
	ClientSize = SettingWindowSize(_Size);

	// WS_CAPTION ������ �����ϰ�
	// WS_SYSMENU �޴��� �����ϰ�
	// WS_THICKFRAME ���� �ܰ����� �ְ�
	// WS_MINIMIZEBOX �ּ�ȭ ��ư�� �ְ�
	// WS_MAXIMIZEBOX �ִ�ȭ ��ư�� �ִ�
	// WS_OVERLAPPED �ٸ� �������������ų� �Ʒ��� �ü� �ִ�
	// ��ϵ� ������ ���·� ������ ����
	m_WindowHWnd = CreateWindowW(L"MYWINDOW", _Name.c_str(), WS_OVERLAPPEDWINDOW, (int)_Pos.x, (int)_Pos.y, (int)ClientSize.x, (int)ClientSize.y, nullptr, nullptr, _ProcessHandle, 0);
	if (nullptr == m_WindowHWnd) // ������ �����찡 �������� üũ
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_WindowHWnd)");
		return;
	}

	// �����츦 ȭ�鿡 ǥ���ϴ� �Լ�
	ShowWindow(m_WindowHWnd, SW_SHOW);

	// �����츦 �ѹ� �����ϴ� �Լ�
	UpdateWindow(m_WindowHWnd);

	// ������ �������� DC�� �����´�.
	m_WindowHDC = GetDC(m_WindowHWnd);

	// GetDC()�� ������ HDC�� �̿��Ͽ� ���� �������� DC��
	// �����Ѵ�.
	m_WindowMainImage.Create(m_WindowHDC);

	// ������ �������� _Size ������ �̿��Ͽ� ���ο� DC�� �����Ѵ�.
	m_DoubleBufferImage.Create(_Size);
}

// member Var
SGameEngineWindow::SGameEngineWindow()
{

}

SGameEngineWindow::~SGameEngineWindow()
{
	// �귯�� �ݳ�
	DeleteObject(m_GreenBrush);
	DeleteObject(m_RedBrush);
}

// member Func


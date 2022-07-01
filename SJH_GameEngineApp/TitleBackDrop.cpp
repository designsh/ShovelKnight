#include "TitleBackDrop.h"
#include <SGameEngineResMgr.h>
#include <SGameEngineWindow.h>
#include <SGameEngineDebug.h>
#include <Windows.h>

// Static Var
FLOAT4 TitleBackDrop::m_ImageChSize = { 900, 400 };

// Static Func
FLOAT4 TitleBackDrop::GetImageChSize()
{
	return m_ImageChSize;
}

// member Var
TitleBackDrop::TitleBackDrop() : m_ImageCnt(1), m_Cnt(0), m_RandomX(0), m_RandomY(0), m_WindowSize(), m_WindowCenterWidth(0.f), m_Title(), m_BackGround()
{

}

TitleBackDrop::~TitleBackDrop()
{

}

// member Func
void TitleBackDrop::Start()
{
	// Window X��(�ʺ�)�� �߾ӿ� ��ġ�ؾ��ϹǷ�
	// WindowSize ���� ��ǥ���� �׸������ϴ� �̹��� �ʺ��� ���� ��
	// ���� : �ʺ� 900�� �̹����� DC�� �ʺ��� �߾ӿ� ǥ���ϱ� ���ؼ�
	m_WindowSize = SGameEngineWindow::GetSize();
	m_WindowCenterWidth = m_WindowSize.HarfX() - (m_ImageChSize.x / 2.f);

	// BackGround�� ȭ�鿡 ����.
	m_BackGround = CreateRenderer<SGameEngineRendererBasic>(1);
	m_BackGround->TransSetting(L"BackGround.bmp", { m_WindowSize.x, m_WindowSize.y }, { 0, 0 });

	// TitleGameName�� ȭ�鿡 ����.
	m_Title = CreateRenderer<SGameEngineRendererBasic>(2);
	m_Title->TransSetting(L"Title Text.bmp", { m_ImageChSize.x, m_ImageChSize.y }, { 0, 0 });
	m_Title->SetPivotPos({ m_WindowCenterWidth, 3.f });
}

void TitleBackDrop::Update()
{

}
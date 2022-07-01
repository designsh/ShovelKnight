#include "SGameEngineWinImage.h"
#include "SGameEngineWindow.h"
#include <SGameEngineDebug.h>

// ������ ���� ���̺귯��(TransparentBlt()�Լ��� ����ϱ� ����)
#pragma comment(lib, "msimg32.lib")

// Static Var

// Static Func

// member Var
SGameEngineWinImage::SGameEngineWinImage() : m_BitMapInfo(), m_BitMap(0), m_OldBitMap(0), m_hDC(0), m_Size(0), m_TransColor(RGB(255, 0, 255))
{
	m_Bland.BlendOp = AC_SRC_OVER;
	m_Bland.BlendFlags = 0;
	m_Bland.AlphaFormat = AC_SRC_ALPHA;
	m_Bland.SourceConstantAlpha = 255;
}

SGameEngineWinImage::~SGameEngineWinImage()
{
	// ��� ���� �ڵ� & ������Ʈ �ݳ�
	if (nullptr != m_hDC)
	{
		DeleteObject(m_BitMap);
		DeleteObject(m_OldBitMap);
		DeleteDC(m_hDC);
	}
}

// member Func
HDC SGameEngineWinImage::GetImageDC()
{
	return m_hDC;
}

BITMAP SGameEngineWinImage::GetBitMapInfo()
{
	return m_BitMapInfo;
}

void SGameEngineWinImage::SetTransColor(int _Color)
{
	m_TransColor = _Color;
}

int SGameEngineWinImage::GetCutSize()
{
	return static_cast<int>(m_CutData.size());
}

FLOAT4 SGameEngineWinImage::GetImageSize()
{
	return m_Size;
}

// ���ο� ���� �迭(�̹��� DC)�� ������ �Լ�
void SGameEngineWinImage::Create(const Scale& _ImageScale)
{
	// ���ǹ迭(�̹���DC)�� �����Ϸ��� �ϴµ� �޾ƿ� ������ ���� �ϳ��� 0�̶��
	// ���α׷��� �Ͷ߸���.
	// ����: �������� DC�� ���� �迭�� ���ϰ� �迭�� ũ��� 0�� ������ ���� �����̴�.
	if (true == _ImageScale.IsZero2D())
	{
		SGameEngineDebug::AssertMsg(L"if (true == _ImageScale.IsZero2D())");
	}

	// ���� ������ �ƴ϶��
	// GetWindowDC()�� DC�� ��Ʈ�� ����(���ο�����)�� ���´�.
	m_BitMap = CreateCompatibleBitmap(SGameEngineWindow::GetWindowDC(), _ImageScale.ix(), _ImageScale.iy());

	// �׸��� ���ο� dc�� �����Ѵ�.
	m_hDC = CreateCompatibleDC(nullptr);
	// DC ������ �����ߴٸ� ���α׷��� �Ͷ߸���.
	if (nullptr == m_hDC)
	{
		SGameEngineDebug::AssertMsg(L"	if (nullptr == m_hDC)");
	}
	// ������ �����ߴٸ� ������ dc�� ��ü(m_BitMap)�� �����Ѵ�.
	else
	{
		// ������ �Ϸ�� dc�� m_OldBitMap�� �����Ѵ�.
		m_OldBitMap = (HBITMAP)SelectObject(m_hDC, m_BitMap);

		// ���� ������ DC�� ������ m_OldBitMap�� ���������Ƿ�
		// ���� DC�� ��Ʈ�� ������ �ٽ� �������ش�.
		SetImageInfo();
	}
}

// �̹� �����ϰ� �ִ� HDC(DC ���� ����)�� �̿��Ͽ� SGameEngineWinImage�� DC�� ����� �Լ�
void SGameEngineWinImage::Create(HDC _hDC)
{
	// �̹� �����ϰ� �ִ� DC �ڵ��� �ƴ� �˼����� ���� ���´ٸ�
	// ���� ���α׷��� �Ͷ߸���.
	if (nullptr == _hDC)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == _hDC)");
	}
	// ���� ������ �ƴ϶�� �޾ƿ� ����(_hDC)�� m_hDC�� ������ ��
	// m_hDC�� ��Ʈ�� ������ ���´�.
	else
	{
		m_hDC = _hDC;
		SetImageInfo();
	}
}

// �̹����� �ε�� ���� �̹��� ũ�� �״�� �ε��ϴ� �Լ�
void SGameEngineWinImage::ImageLoad(const SGameEngineString& _LoadPath)
{
	m_BitMap = (HBITMAP)LoadImage(NULL, _LoadPath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	if (nullptr == m_BitMap)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_BitMap)");
		return;
	}

	m_hDC = CreateCompatibleDC(nullptr);
	if (nullptr == m_hDC)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_hDC)");
		return;
	}

	m_OldBitMap = (HBITMAP)SelectObject(m_hDC, m_BitMap);
	SetImageInfo();
}

// �̹��� �ε�� ����ڰ� �̹���ũ�⸦ �����Ͽ� �ε��ϴ� �Լ�
void SGameEngineWinImage::ImageLoadSetSize(const SGameEngineString& _LoadPath, FLOAT4 _Size)
{
	m_BitMap = (HBITMAP)LoadImage(NULL, _LoadPath.c_str(), IMAGE_BITMAP, _Size.ix(), _Size.iy(), LR_LOADFROMFILE);
	if (nullptr == m_BitMap)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_BitMap)");
		return;
	}

	m_hDC = CreateCompatibleDC(nullptr);
	if (nullptr == m_hDC)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_hDC)");
		return;
	}

	m_OldBitMap = (HBITMAP)SelectObject(m_hDC, m_BitMap);
	SetImageInfo();
}

// SGameEngineWinImage�� �����ϴ� �̹����� ���� ��ü�̹�����
// ������(�״��)�����ϴ� �Լ�
// => SGameEngineWinImage�� �̹����� ���� SGameEngineWinImage�� �׸��� �Լ�
void SGameEngineWinImage::BitBlt(SGameEngineWinImage& _OtherImage)
{
	// ù��°    ���� : �̹����� ����� ��ġ�� �ڵ�
	// �ι�°    ���� : ȭ���� ��ġ(X ��ǥ)
	// ����°    ���� : ȭ���� ��ġ(Y ��ǥ)
	// �׹�°    ���� : ���� �̹����� �ʺ�
	// �ټ���° ���� : ���� �̹����� ����
	// ������° ���� : �̹����� �ڵ�
	// �ϰ���° ���� : ������ �̹����� ������(X ��ǥ)
	// ������° ���� : ������ �̹����� ������(Y ��ǥ)
	// ������     ���� : �̹��� ��¹��(SRCCOPY �����̹����� ���)
	::BitBlt(m_hDC, 0, 0, _OtherImage.m_BitMapInfo.bmWidth, _OtherImage.m_BitMapInfo.bmHeight, _OtherImage.m_hDC, 0, 0, SRCCOPY);
}

void SGameEngineWinImage::BitBlt(FLOAT4 _Pos, SGameEngineWinImage& _OtherImage)
{
	::BitBlt(m_hDC, _Pos.ix(), _Pos.iy(), _OtherImage.m_BitMapInfo.bmWidth, _OtherImage.m_BitMapInfo.bmHeight, _OtherImage.m_hDC, 0, 0, SRCCOPY);
}

void SGameEngineWinImage::BitBltCenter(FLOAT4 _Pos, SGameEngineWinImage& _OtherImage)
{
	::BitBlt(m_hDC, _Pos.ix() - _OtherImage.m_Size.HarfX(), _Pos.iy() - _OtherImage.m_Size.HarfY(), _OtherImage.m_BitMapInfo.bmWidth, _OtherImage.m_BitMapInfo.bmHeight, _OtherImage.m_hDC, 0, 0, SRCCOPY);
}

// �����̹����� ���ϴ� ũ��, ���ϴ� ����(Ư�� �� ����)�� �����ϴ� ������
void SGameEngineWinImage::TransparentBlt(const FLOAT4& _Pos, const FLOAT4& _Size, SGameEngineWinImage& _OtherImage, const FLOAT4& _CutPos, const FLOAT4& _CutSize)
{
	FLOAT4 CutSize = _CutSize;

	if (-1 == CutSize.ix())
	{
		CutSize.x = _OtherImage.m_Size.x;
	}

	if (-1 == CutSize.iy())
	{
		CutSize.y = _OtherImage.m_Size.y;
	}

	// �����̹��� ũ�⸦ �����ϰ� �ٽ� �����ؾ��ϹǷ� TransparentBlt()�Լ��� ���
	// ù��° ����     : �׸��� ���� ���� X��ǥ
	// �ι�° ����     : �׸��� ���� ���� Y��ǥ
	// ����° ����     : �׸������ϴ� �̹����� �ʺ�
	// �׹�° ����     : �׸������ϴ� �̹����� ����
	// �ټ���° ����  : ���� �̹��� DC
	// ������° ����  : ���� �̹����� ���� X��ǥ
	// �ϰ���° ����  : ���� �̹����� ���� Y��ǥ
	// ������° ����  : ���� �̹����� �ʺ�
	// ��ȩ��° ����  : ���� �̹����� ����
	// ������ ����     : ���������(�������� ������ �� ����) - Default : 0
	::TransparentBlt(m_hDC, _Pos.ix(), _Pos.iy(), _Size.ix(), _Size.iy(), _OtherImage.m_hDC, _CutPos.ix(), _CutPos.iy(), CutSize.ix(), CutSize.iy(), _OtherImage.m_TransColor);
}

// ���� �Լ��� ������ �̹����� ��ġ�� ���� DC�� ���߾ӿ� ��ġ�ϵ��� �����ϴ� ������
void SGameEngineWinImage::TransparentBltCenter(const FLOAT4& _Pos, const FLOAT4& _Size, SGameEngineWinImage& _OtherImage, const FLOAT4& _CutPos, const FLOAT4& _CutSize)
{
	FLOAT4 CutSize = _CutSize;

	if (-1 == CutSize.ix())
	{
		CutSize.x = _OtherImage.m_Size.x;
	}

	if (-1 == CutSize.iy())
	{
		CutSize.y = _OtherImage.m_Size.y;
	}

	::TransparentBlt(m_hDC, _Pos.ix() - _Size.HarfX(), _Pos.iy() - _Size.HarfY(), _Size.ix(), _Size.iy(), _OtherImage.m_hDC, _CutPos.ix(), _CutPos.iy(), CutSize.ix(), CutSize.iy(), _OtherImage.m_TransColor);
}

// �����̹����� ���İ��� �����ϴ� �Լ�
void SGameEngineWinImage::AlphaBlend(const FLOAT4& _Pos, const FLOAT4& _Size, SGameEngineWinImage& _OtherImage, const FLOAT4& _CutPos, const FLOAT4& _CutSize, BYTE _Alpha)
{
	m_Bland.SourceConstantAlpha = _Alpha;

	FLOAT4 CutSize = _CutSize;

	if (-1 == CutSize.ix())
	{
		CutSize.x = _OtherImage.m_Size.x;
	}

	if (-1 == CutSize.iy())
	{
		CutSize.y = _OtherImage.m_Size.y;
	}

	::AlphaBlend(m_hDC, _Pos.ix() - _Size.HarfX(), _Pos.iy() - _Size.HarfY(), _Size.ix(), _Size.iy(), _OtherImage.m_hDC, _CutPos.ix(), _CutPos.iy(), CutSize.ix(), CutSize.iy(), m_Bland);
}

void SGameEngineWinImage::PlgBltCenter(const FLOAT4& _Pos, const FLOAT4& _Size, float _Angle, SGameEngineWinImage& _OtherImage, SGameEngineWinImage& _MaskImage)
{
	// ���� �׸��� ���� ��ġ
	FLOAT4 CenterPos = _Pos;

	FLOAT4 ArrRotPivot[3] = { {-_Size.fHarfX(), -_Size.fHarfY()}, {_Size.fHarfX(), -_Size.fHarfY()}, {-_Size.fHarfX(), _Size.fHarfY()} };

	for (size_t i = 0; i < 3; i++)
	{
		ArrRotPivot[i] = FLOAT4::AngleTo2DDeg(ArrRotPivot[i], _Angle);
	}

	// �� ������ ȸ�� ���Ѿ� �մϴ�.
	POINT ArrPos[3] = {0, };

	for (size_t i = 0; i < 3; i++)
	{
		FLOAT4 Pos = ArrRotPivot[i] + CenterPos;

		ArrPos[i] = { Pos.ix(), Pos.iy() };
	}

	::PlgBlt(m_hDC, ArrPos, _OtherImage.m_hDC, 0, 0, _OtherImage.GetImageSize().ix(), _OtherImage.GetImageSize().iy(), _MaskImage.m_BitMap, 0, 0);
}

// m_hDC�� �̹��� ����(��Ʈ�� ����)�� ���ͼ� m_BitMapInfo ����ü�� ä���ִ� �Լ�
void SGameEngineWinImage::SetImageInfo()
{
	// ���� ������Ʈ(�ڵ�)�� ������ �Լ�
	HBITMAP CurrentHDC = (HBITMAP)GetCurrentObject(m_hDC, OBJ_BITMAP);

	// ������ ���� �ڵ��� ��Ʈ�� ������ m_BitMapInfo�� �����ϴ� �Լ�
	GetObjectW(CurrentHDC, sizeof(m_BitMapInfo), &m_BitMapInfo);

	// ��� ���� ����
	m_Size.x = static_cast<float>(m_BitMapInfo.bmWidth);
	m_Size.y = static_cast<float>(m_BitMapInfo.bmHeight);
}

// �̹����� _x ������ŭ _y ������ŭ �߶󳻶�
const CutData& SGameEngineWinImage::GetCutData(int _Index)
{
	// �ڸ����� �̹����� ������ ����� ���α׷��� �Ͷ߸���.
	if (0 > _Index || m_CutData.size() <= _Index)
	{
		SGameEngineDebug::AssertMsg(L"if (0 > _Index || m_CutData.size() <= _Index)");
	}

	return m_CutData[_Index];
}

void SGameEngineWinImage::ImageCut(int _x, int _y)
{
	if (_x == 0 || _y == 0)
	{
		SGameEngineDebug::AssertMsg(L"	if (_x == 0 || _y == 0)");
		return;
	}

	// 1���� �ִϸ��̼� �̹���ũ��� ���� �̹����� _x , _y ũ��
	FLOAT4 ImageSize = FLOAT4{ m_Size.x / _x, m_Size.y / _y };

	// ó�� �������� x = 0, y = 0
	FLOAT4 CurPos = FLOAT4{ 0, 0 };

	for (int y = 0; y < _y; y++)
	{
		for (int x = 0; x < _x; x++)
		{
			m_CutData.push_back({ CurPos, ImageSize });
			CurPos.x += ImageSize.x;
		}

		CurPos.x = 0;
		CurPos.y += ImageSize.y;
	}
}

unsigned long SGameEngineWinImage::GetPixelColor(int _x, int _y)
{
	return GetPixel(m_hDC, _x, _y);
}

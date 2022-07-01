#include "SGameEngineWinImage.h"
#include "SGameEngineWindow.h"
#include <SGameEngineDebug.h>

// 윈도우 제공 라이브러리(TransparentBlt()함수를 사용하기 위해)
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
	// 사용 끝난 핸들 & 오브젝트 반납
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

// 새로운 색의 배열(이미지 DC)를 만들어내는 함수
void SGameEngineWinImage::Create(const Scale& _ImageScale)
{
	// 색의배열(이미지DC)를 생성하려고 하는데 받아온 인자의 값이 하나라도 0이라면
	// 프로그램을 터뜨린다.
	// 이유: 윈도우의 DC란 색의 배열을 뜻하고 배열의 크기는 0을 가질수 없기 때문이다.
	if (true == _ImageScale.IsZero2D())
	{
		SGameEngineDebug::AssertMsg(L"if (true == _ImageScale.IsZero2D())");
	}

	// 위의 조건이 아니라면
	// GetWindowDC()의 DC의 비트맵 정보(새로운정보)를 얻어온다.
	m_BitMap = CreateCompatibleBitmap(SGameEngineWindow::GetWindowDC(), _ImageScale.ix(), _ImageScale.iy());

	// 그리고 새로운 dc를 생성한다.
	m_hDC = CreateCompatibleDC(nullptr);
	// DC 생성에 실패했다면 프로그램을 터뜨린다.
	if (nullptr == m_hDC)
	{
		SGameEngineDebug::AssertMsg(L"	if (nullptr == m_hDC)");
	}
	// 생성에 성공했다면 생성된 dc의 개체(m_BitMap)를 설정한다.
	else
	{
		// 설정이 완료된 dc는 m_OldBitMap에 저장한다.
		m_OldBitMap = (HBITMAP)SelectObject(m_hDC, m_BitMap);

		// 새로 생성된 DC의 정보를 m_OldBitMap에 저장했으므로
		// 기존 DC의 비트맵 정보를 다시 저장해준다.
		SetImageInfo();
	}
}

// 이미 존재하고 있는 HDC(DC 접근 권한)을 이용하여 SGameEngineWinImage의 DC로 만드는 함수
void SGameEngineWinImage::Create(HDC _hDC)
{
	// 이미 존재하고 있는 DC 핸들이 아닌 알수없는 값이 들어온다면
	// 현재 프로그램을 터뜨린다.
	if (nullptr == _hDC)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == _hDC)");
	}
	// 위의 조건이 아니라면 받아온 인자(_hDC)를 m_hDC에 저장한 뒤
	// m_hDC의 비트맵 정보를 얻어온다.
	else
	{
		m_hDC = _hDC;
		SetImageInfo();
	}
}

// 이미지를 로드시 원본 이미지 크기 그대로 로드하는 함수
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

// 이미지 로드시 사용자가 이미지크기를 설정하여 로드하는 함수
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

// SGameEngineWinImage에 존재하는 이미지를 현재 객체이미지에
// 빠르게(그대로)복사하는 함수
// => SGameEngineWinImage의 이미지를 현재 SGameEngineWinImage에 그리는 함수
void SGameEngineWinImage::BitBlt(SGameEngineWinImage& _OtherImage)
{
	// 첫번째    인자 : 이미지를 출력할 위치의 핸들
	// 두번째    인자 : 화면의 위치(X 좌표)
	// 세번째    인자 : 화면의 위치(Y 좌표)
	// 네번째    인자 : 원본 이미지의 너비
	// 다섯번째 인자 : 원본 이미지의 높이
	// 여섯번째 인자 : 이미지의 핸들
	// 일곱번째 인자 : 가져올 이미지의 시작점(X 좌표)
	// 여덟번째 인자 : 가져올 이미지의 시작점(Y 좌표)
	// 마지막     인자 : 이미지 출력방법(SRCCOPY 원본이미지를 출력)
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

// 원본이미지를 원하는 크기, 원하는 투명(특정 색 제거)를 지원하는 랜더링
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

	// 원본이미지 크기를 사용못하고 다시 설정해야하므로 TransparentBlt()함수를 사용
	// 첫번째 인자     : 그리는 곳의 시작 X좌표
	// 두번째 인자     : 그리는 곳의 시작 Y좌표
	// 세번째 인자     : 그리려고하는 이미지의 너비
	// 네번째 인자     : 그리려고하는 이미지의 높이
	// 다섯번째 인자  : 원본 이미지 DC
	// 여섯번째 인자  : 원본 이미지의 시작 X좌표
	// 일곱번째 인자  : 원본 이미지의 시작 Y좌표
	// 여덟번째 인자  : 원본 이미지의 너비
	// 아홉번째 인자  : 원본 이미지의 높이
	// 마지막 인자     : 투명색설정(랜더링시 제거할 색 지정) - Default : 0
	::TransparentBlt(m_hDC, _Pos.ix(), _Pos.iy(), _Size.ix(), _Size.iy(), _OtherImage.m_hDC, _CutPos.ix(), _CutPos.iy(), CutSize.ix(), CutSize.iy(), _OtherImage.m_TransColor);
}

// 위의 함수와 같으며 이미지의 위치를 현재 DC의 정중앙에 위치하도록 설정하는 랜더링
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

// 원본이미지의 알파값을 조절하는 함수
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
	// 내가 그리고 싶은 위치
	FLOAT4 CenterPos = _Pos;

	FLOAT4 ArrRotPivot[3] = { {-_Size.fHarfX(), -_Size.fHarfY()}, {_Size.fHarfX(), -_Size.fHarfY()}, {-_Size.fHarfX(), _Size.fHarfY()} };

	for (size_t i = 0; i < 3; i++)
	{
		ArrRotPivot[i] = FLOAT4::AngleTo2DDeg(ArrRotPivot[i], _Angle);
	}

	// 이 점들을 회전 시켜야 합니다.
	POINT ArrPos[3] = {0, };

	for (size_t i = 0; i < 3; i++)
	{
		FLOAT4 Pos = ArrRotPivot[i] + CenterPos;

		ArrPos[i] = { Pos.ix(), Pos.iy() };
	}

	::PlgBlt(m_hDC, ArrPos, _OtherImage.m_hDC, 0, 0, _OtherImage.GetImageSize().ix(), _OtherImage.GetImageSize().iy(), _MaskImage.m_BitMap, 0, 0);
}

// m_hDC의 이미지 정보(비트맵 정보)를 얻어와서 m_BitMapInfo 구조체에 채워넣는 함수
void SGameEngineWinImage::SetImageInfo()
{
	// 현재 오브젝트(핸들)을 얻어오는 함수
	HBITMAP CurrentHDC = (HBITMAP)GetCurrentObject(m_hDC, OBJ_BITMAP);

	// 위에서 얻어온 핸들의 비트맵 정보를 m_BitMapInfo에 저장하는 함수
	GetObjectW(CurrentHDC, sizeof(m_BitMapInfo), &m_BitMapInfo);

	// 멤버 변수 저장
	m_Size.x = static_cast<float>(m_BitMapInfo.bmWidth);
	m_Size.y = static_cast<float>(m_BitMapInfo.bmHeight);
}

// 이미지를 _x 개수만큼 _y 개수만큼 잘라내라
const CutData& SGameEngineWinImage::GetCutData(int _Index)
{
	// 자르려는 이미지의 범위에 벗어나면 프로그램을 터뜨린다.
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

	// 1개의 애니메이션 이미지크기는 현재 이미지의 _x , _y 크기
	FLOAT4 ImageSize = FLOAT4{ m_Size.x / _x, m_Size.y / _y };

	// 처음 포지션은 x = 0, y = 0
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

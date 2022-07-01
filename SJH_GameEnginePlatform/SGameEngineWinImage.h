#pragma once
#include <Windows.h>
#include <SGameEngineMath.h>
#include <SGameEngineString.h>

class CutData
{
    public:
        FLOAT4 m_Pos;
        FLOAT4 m_Size;
};

// 분류 :
// 용도 : 
// 설명 : 
class SGameEngineWinImage
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        // DC = 윈도우에서 IMAGE 1개
        HDC m_hDC;

        // 비트맵 정보를 가지고 있는 struct
        // HDC를 얻어와서 현재 정보를 저장하기 위해 선언
        BITMAP m_BitMapInfo;

        // BITMAP 정보에 접근 할 수 있는 권한(핸들)
        // 현재 BitMap 권한
        HBITMAP m_BitMap;

        // BITMAP 정보에 접근 할 수 있는 권한(핸들)
        // 이전 BitMap 권한
        HBITMAP m_OldBitMap;

        // 이미지 Size 정보를 담아놓는 변수
        FLOAT4 m_Size;

        // 이미지는 특정색제거의 색을 가진다.
        int m_TransColor;

        // 이미지는 
        BLENDFUNCTION m_Bland;

    private:
        std::vector<CutData> m_CutData;

    public: // constructer destructer
        SGameEngineWinImage();
        ~SGameEngineWinImage();

    public: // delete constructer 
        SGameEngineWinImage(const SGameEngineWinImage& _Other) = delete;
        SGameEngineWinImage(const SGameEngineWinImage&& _Other) = delete;

    public: // delete operator
        SGameEngineWinImage& operator=(const SGameEngineWinImage& _Other) = delete;
        SGameEngineWinImage& operator=(const SGameEngineWinImage&& _Other) = delete;

    public: // member Func
        HDC GetImageDC();
        BITMAP GetBitMapInfo();

    public:
        // 새로운 색의 배열(이미지)를 만들어내는 함수
        void Create(const Scale& _ImageScale);
        // 이미 존재하고 있는 HDC(DC 접근 권한)을 이용하여 SGameEngineWinImage로 만드는 함수
        void Create(HDC _hDC);

    public:
        void ImageLoad(const SGameEngineString& _LoadPath);
        void ImageLoadSetSize(const SGameEngineString& _LoadPath, FLOAT4 _Size);

    public:
        // SGameEngineWinImage에 존재하는 이미지를 현재 객체이미지에
        // 빠르게(그대로)복사하는 함수
        void BitBlt(SGameEngineWinImage& _OtherImage);
        void BitBlt(FLOAT4 _Pos, SGameEngineWinImage& _OtherImage);
        void BitBltCenter(FLOAT4 _Pos, SGameEngineWinImage& _OtherImage);

    public:
        // 원본이미지를 원하는 크기, 원하는 투명(특정 색 제거)를 지원하는 랜더링
        void TransparentBlt(const FLOAT4& _Pos, const FLOAT4& _Size, SGameEngineWinImage& _OtherImage, const FLOAT4& _CutPos, const FLOAT4& _CutSize);
        void TransparentBltCenter(const FLOAT4& _Pos, const FLOAT4& _Size, SGameEngineWinImage& _OtherImage, const FLOAT4& _CutPos, const FLOAT4& _CutSize);

    public:
        // 원본이미지의 알파값을 조정하여 랜더링한다.
        // 알파값 조절 : 투명화작업
        void AlphaBlend(const FLOAT4& _Pos, const FLOAT4& _Size, SGameEngineWinImage& _OtherImage, const FLOAT4& _CutPos, const FLOAT4& _CutSize, BYTE _Alpha);

    public:
        // 회전
        void PlgBltCenter(const FLOAT4& _Pos, const FLOAT4& _Size, float _Angle, SGameEngineWinImage& _OtherImage, SGameEngineWinImage& _MaskImage);

    private:
        // m_hDC의 이미지 정보(비트맵 정보)를 얻어와서 
        // m_BitMapInfo 구조체에 채워넣는 함수
        void SetImageInfo();

    public:
        void SetTransColor(int _Color);

    public:
        int GetCutSize();
        FLOAT4 GetImageSize();

        // 이미지를 _x 개수만큼 _y 개수만큼 잘라내라
        const CutData& GetCutData(int _Index);
        void ImageCut(int _x, int _y);

    public:
        unsigned long GetPixelColor(int _x, int _y);

};


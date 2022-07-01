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

// �з� :
// �뵵 : 
// ���� : 
class SGameEngineWinImage
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        // DC = �����쿡�� IMAGE 1��
        HDC m_hDC;

        // ��Ʈ�� ������ ������ �ִ� struct
        // HDC�� ���ͼ� ���� ������ �����ϱ� ���� ����
        BITMAP m_BitMapInfo;

        // BITMAP ������ ���� �� �� �ִ� ����(�ڵ�)
        // ���� BitMap ����
        HBITMAP m_BitMap;

        // BITMAP ������ ���� �� �� �ִ� ����(�ڵ�)
        // ���� BitMap ����
        HBITMAP m_OldBitMap;

        // �̹��� Size ������ ��Ƴ��� ����
        FLOAT4 m_Size;

        // �̹����� Ư���������� ���� ������.
        int m_TransColor;

        // �̹����� 
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
        // ���ο� ���� �迭(�̹���)�� ������ �Լ�
        void Create(const Scale& _ImageScale);
        // �̹� �����ϰ� �ִ� HDC(DC ���� ����)�� �̿��Ͽ� SGameEngineWinImage�� ����� �Լ�
        void Create(HDC _hDC);

    public:
        void ImageLoad(const SGameEngineString& _LoadPath);
        void ImageLoadSetSize(const SGameEngineString& _LoadPath, FLOAT4 _Size);

    public:
        // SGameEngineWinImage�� �����ϴ� �̹����� ���� ��ü�̹�����
        // ������(�״��)�����ϴ� �Լ�
        void BitBlt(SGameEngineWinImage& _OtherImage);
        void BitBlt(FLOAT4 _Pos, SGameEngineWinImage& _OtherImage);
        void BitBltCenter(FLOAT4 _Pos, SGameEngineWinImage& _OtherImage);

    public:
        // �����̹����� ���ϴ� ũ��, ���ϴ� ����(Ư�� �� ����)�� �����ϴ� ������
        void TransparentBlt(const FLOAT4& _Pos, const FLOAT4& _Size, SGameEngineWinImage& _OtherImage, const FLOAT4& _CutPos, const FLOAT4& _CutSize);
        void TransparentBltCenter(const FLOAT4& _Pos, const FLOAT4& _Size, SGameEngineWinImage& _OtherImage, const FLOAT4& _CutPos, const FLOAT4& _CutSize);

    public:
        // �����̹����� ���İ��� �����Ͽ� �������Ѵ�.
        // ���İ� ���� : ����ȭ�۾�
        void AlphaBlend(const FLOAT4& _Pos, const FLOAT4& _Size, SGameEngineWinImage& _OtherImage, const FLOAT4& _CutPos, const FLOAT4& _CutSize, BYTE _Alpha);

    public:
        // ȸ��
        void PlgBltCenter(const FLOAT4& _Pos, const FLOAT4& _Size, float _Angle, SGameEngineWinImage& _OtherImage, SGameEngineWinImage& _MaskImage);

    private:
        // m_hDC�� �̹��� ����(��Ʈ�� ����)�� ���ͼ� 
        // m_BitMapInfo ����ü�� ä���ִ� �Լ�
        void SetImageInfo();

    public:
        void SetTransColor(int _Color);

    public:
        int GetCutSize();
        FLOAT4 GetImageSize();

        // �̹����� _x ������ŭ _y ������ŭ �߶󳻶�
        const CutData& GetCutData(int _Index);
        void ImageCut(int _x, int _y);

    public:
        unsigned long GetPixelColor(int _x, int _y);

};


#pragma once
#include "SGameEngineRenderer.h"
#include <SGameEngineWinImage.h>

// �з� :
// �뵵 : 
// ���� : 
class SGameEngineWinImage;
class SGameEngineRendererBasic : public SGameEngineRenderer
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        SGameEngineWinImage* m_Image;

    public: // constructer destructer
        SGameEngineRendererBasic();
        ~SGameEngineRendererBasic();

    public: // delete constructer 
        SGameEngineRendererBasic(const SGameEngineRendererBasic& _Other) = delete;
        SGameEngineRendererBasic(const SGameEngineRendererBasic&& _Other) = delete;

    public: // delete operator
        SGameEngineRendererBasic& operator=(const SGameEngineRendererBasic& _Other) = delete;
        SGameEngineRendererBasic& operator=(const SGameEngineRendererBasic&& _Other) = delete;

    public: // member Func
        // 
        void SetCutData(int _Index);
        void SetCutPosAndSize(const FLOAT4& _Pos, const FLOAT4& _Size);

        // �����̹��� ���Ϸ��� ������ǥ ���� �� ��������
        FLOAT4 GetCutPos();
        void SetCutPos(FLOAT4 _CutPos);

        // �����̹��� ���Ϸ��� ũ�� ���� �� ��������
        FLOAT4 GetCutSize();
        void SetCutSize(FLOAT4 _CutSize);

    // Trans
    public:
        void TransSetting(const SGameEngineString& _Image, FLOAT4 _Scale, FLOAT4 _PivotPos = FLOAT4{ 0,0 });
        void TransCenterSetting(const SGameEngineString& _Image, FLOAT4 _Scale, FLOAT4 _PivotPos = FLOAT4{ 0,0 });

    // None
    public:
        void NoneSetting(const SGameEngineString& _Image, int _TransRgb = RGB(0, 0, 0));

    // Rot
    public:
        void RotImageSetting(const SGameEngineString& _Image, const SGameEngineString& _MaskImage, FLOAT4 _Scale, FLOAT4 _PivotPos = FLOAT4{ 0,0 });

    public:
        // SGameEngineRenderer�� ���������Լ��� ����
        void Render() override;

};


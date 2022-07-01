#pragma once
#include "SGameEngineRenderer.h"
#include <SGameEngineWinImage.h>

// 분류 :
// 용도 : 
// 설명 : 
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

        // 원본이미지 컷하려는 시작좌표 설정 및 가져오기
        FLOAT4 GetCutPos();
        void SetCutPos(FLOAT4 _CutPos);

        // 원본이미지 컷하려는 크기 설정 및 가져오기
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
        // SGameEngineRenderer의 순수가상함수를 구현
        void Render() override;

};


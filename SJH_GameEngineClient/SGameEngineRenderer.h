#pragma once
#include "SGameEngineActor.h"
#include <SGameEngineWinImage.h>
#include <SGameEngineObjectBase.h>


enum class RENDERINGMODE
{
    NONE,       // 생성만함
    BIT,
    TRANS,
    TRANSCENTER,
    ROT,          // 회전
    MAX,
    ALPHA,      // 알파값 조정 모드
};

// 분류 :
// 용도 : 
// 설명 : 
class SGameEngineWinImage;
class SGameEngineRenderer : public SGameEngineObjectBase
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        // 액터 리스트의 순서를 관리한다.
        int m_iOrder;
        
        // 자신이 Render하려는 Actor를 알고있는다.
        SGameEngineActor* m_Actor;

        // 랜더러는 카메라 크기를 알고있는다.
        float m_fCamEffectScale;

    protected:
        // Rendering Type을 가진다.
        RENDERINGMODE m_RenderType;

    protected:
        SGameEngineWinImage* m_MaskImage;

    protected:
        FLOAT4 m_PivotPos;        // 기준 좌표
        FLOAT4 m_RenderScale;  // Render 크기
        FLOAT4 m_CutPos;          // 원본이미지 컷하려는 시작좌표
        FLOAT4 m_CutSize;          // 원본이미지 컷하려는 크기

    // CamPos 사용여부 Member Value
    // (true : On, false : Off)
    private:
        bool m_IsCamEffect;

    // Alpha Mode 사용 Member Value
    protected:
        unsigned char m_Alpha;
        float m_Angle;

    public: // constructer destructer
        SGameEngineRenderer();

        // 자식 소멸자 호출을 위해 가상소멸자로 설정한다.
        virtual ~SGameEngineRenderer();

    public: // delete constructer 
        SGameEngineRenderer(const SGameEngineRenderer& _Other) = delete;
        SGameEngineRenderer(const SGameEngineRenderer&& _Other) = delete;

    public: // delete operator
        SGameEngineRenderer& operator=(const SGameEngineRenderer& _Other) = delete;
        SGameEngineRenderer& operator=(const SGameEngineRenderer&& _Other) = delete;

    public: // member Func
        // Order 설정 및 가져오기
        void SetOrder(int _Order);
        int GetOrder();

        // 카메라가 비추는 크기를 변경한다.
        void SetCamEffectScale(float _Scale);

        // Actor 설정 및 가져오기
        void SetActor(SGameEngineActor* _Actor);
        SGameEngineActor* GetActor();

    public:
        // 순수가상함수
        // 일반적인 가상함수는 객체화(생성)이 가능하나,
        // 순수가상함수는 객체화(생성)이 불가능하고
        // 이를 포함한 클래스를 추상클래스라 칭한다.
        // 추상클래스를 상속받는 자식은 반드시 부모의 순수가상함수를
        // 구현해야한다.
        virtual void Render() = 0;
        void RennderImage(SGameEngineWinImage* _Image);

    public:
        // 기준 좌표 설정 및 가져오기
        FLOAT4 GetPivotPos();
        void SetPivotPos(FLOAT4 _PivotPos);

        // Render 크기 설정 및 가져오기
        FLOAT4 GetRenderScale();
        void SetRenderScale(FLOAT4 _RenderSize);

    public:
        FLOAT4 CamRenderPos();

    // CamPos 관련 Member Function
    // 해당 이미지(랜더러)의 캠의 영향을 받는지 안받는지
    public:
        void CamEffectOff();
        void CamEffectOn();
        bool GetCamEffect();

    // Alpha Mode 관련
    public:
        void SetAlpha(unsigned char _Alpha);

    // 마스크이미지 관련
    public:
        void SetMaskImage(const SGameEngineString& _Image);
        void SetAngle(float _Angle);

};


#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>

// 분류 :
// 용도 : 
// 설명 : 
class TitleBackDrop : public SGameEngineActor
{
    private: // Static Var
        static FLOAT4 m_ImageChSize;

    public: // Static Func
        static FLOAT4 GetImageChSize();

    private: // member Var
        // Effect 전용 멤버변수
        float m_RandomX;
        float m_RandomY;
        int    m_ImageCnt;
        int    m_Cnt;

    private:
        SGameEngineRendererBasic* m_Title;
        SGameEngineRendererBasic* m_BackGround;

    private:
        FLOAT4 m_WindowSize;
        float m_WindowCenterWidth;

    public: // constructer destructer
        TitleBackDrop();
        ~TitleBackDrop();

    public: // delete constructer 
        TitleBackDrop(const TitleBackDrop& _Other) = delete;
        TitleBackDrop(const TitleBackDrop&& _Other) = delete;

    public: // delete operator
        TitleBackDrop& operator=(const TitleBackDrop& _Other) = delete;
        TitleBackDrop& operator=(const TitleBackDrop&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;

};


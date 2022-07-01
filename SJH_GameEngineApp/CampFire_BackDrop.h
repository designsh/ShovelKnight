#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineTimeEventer.h>

// 분류 :
// 용도 : 
// 설명 : 
class CampFire_BackDrop : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_CampFire1;
        SGameEngineRendererBasic* m_CampFire2;
        SGameEngineTimeEventer<CampFire_BackDrop> m_CampChangeEventer;

    public: // constructer destructer
        CampFire_BackDrop();
        virtual ~CampFire_BackDrop();

    public: // delete constructer 
        CampFire_BackDrop(const CampFire_BackDrop& _Other) = delete;
        CampFire_BackDrop(const CampFire_BackDrop&& _Other) = delete;

    public: // delete operator
        CampFire_BackDrop& operator=(const CampFire_BackDrop& _Other) = delete;
        CampFire_BackDrop& operator=(const CampFire_BackDrop&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        void ImageChangeEnd();

};


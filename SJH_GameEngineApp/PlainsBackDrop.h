#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>

// 분류 :
// 용도 : 
// 설명 : 
class PlainsBackDrop : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        SGameEngineRendererBasic* m_Frame;
        SGameEngineRendererBasic* m_SkyBackGround;
        SGameEngineRendererBasic* m_CastleBackGround;
        SGameEngineRendererBasic* m_LightTreeBackGround;
        SGameEngineRendererBasic* m_ThickTreeBackGround;

    private:
        FLOAT4 m_WindowSize;

    public: // constructer destructer
        PlainsBackDrop();
        virtual ~PlainsBackDrop();

    public: // delete constructer 
        PlainsBackDrop(const PlainsBackDrop& _Other) = delete;
        PlainsBackDrop(const PlainsBackDrop&& _Other) = delete;

    public: // delete operator
        PlainsBackDrop& operator=(const PlainsBackDrop& _Other) = delete;
        PlainsBackDrop& operator=(const PlainsBackDrop&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

};


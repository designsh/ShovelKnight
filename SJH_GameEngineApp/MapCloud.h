#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>

// 분류 :
// 용도 : 
// 설명 : 
class MapCloud : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_Cloud;

    private:
        FLOAT4 m_LerpStartPos;
        FLOAT4 m_LerpEndPos;
        FLOAT4 m_LerpMyPos;

        float m_LerpTime;

        bool m_LerpStartMove;
        bool m_SceneStart;

    public: // constructer destructer
        MapCloud();
        ~MapCloud();

    public: // delete constructer 
        MapCloud(const MapCloud& _Other) = delete;
        MapCloud(const MapCloud&& _Other) = delete;

    public: // delete operator
        MapCloud& operator=(const MapCloud& _Other) = delete;
        MapCloud& operator=(const MapCloud&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

};


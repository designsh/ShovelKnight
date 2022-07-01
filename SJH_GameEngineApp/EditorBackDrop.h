#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererTile.h>
#include <SGameEngineRendererBasic.h>

// 분류 :
// 용도 : 
// 설명 : 
class EditorBackDrop : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;

    private:
        SGameEngineRendererBasic* m_CollBackGround;
        SGameEngineRendererBasic* m_RefBackGround;
        SGameEngineRendererBasic* m_TileUI;
        SGameEngineRendererBasic* m_LevelMapBackGound;
        SGameEngineRendererBasic* m_EnchantressBackGound;
        SGameEngineRendererBasic* m_EnchantressCollBackGround;

    public:

    public: // constructer destructer
        EditorBackDrop();
        ~EditorBackDrop();

    public: // delete constructer 
        EditorBackDrop(const EditorBackDrop& _Other) = delete;
        EditorBackDrop(const EditorBackDrop&& _Other) = delete;

    public: // delete operator
        EditorBackDrop& operator=(const EditorBackDrop& _Other) = delete;
        EditorBackDrop& operator=(const EditorBackDrop&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;

};


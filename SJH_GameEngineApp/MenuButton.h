#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineInput.h>
#include <SGameEngineTimeEventer.h>

// 분류 :
// 용도 : 
// 설명 : 
class MenuButton : public SGameEngineActor
{
    private: // Static Var

    public: // Static Func

    private: // member Var

    private:
        SGameEngineRendererBasic* m_SelStart;
        SGameEngineRendererBasic* m_SelEditor;
        SGameEngineRendererBasic* m_SelExit;
        SGameEngineRendererBasic* m_MenuCover;

    private:
        SGameEngineTimeEventer<MenuButton> m_MenuBlinkEventer;

    public: // constructer destructer
        MenuButton();
        virtual ~MenuButton();

    public: // delete constructer 
        MenuButton(const MenuButton& _Other) = delete;
        MenuButton(const MenuButton&& _Other) = delete;

    public: // delete operator
        MenuButton& operator=(const MenuButton& _Other) = delete;
        MenuButton& operator=(const MenuButton&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;

    public:
        void SelectMenuBlinkStart();
        void SelectMenuBlinkStay();
        void SelectMenuBlinkEnd();
};


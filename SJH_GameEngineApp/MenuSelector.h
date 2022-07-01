#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineWindow.h>
#include <SGameEngineSound.h>

enum class SelectMenu
{
    MN_START = 1,
    MN_EDITOR,
    MN_EXIT
};

// �з� :
// �뵵 : 
// ���� : 
class MenuSelector : public SGameEngineActor
{
    private: // Static Var
        static SoundPlayer m_ActionSound;

    public:
        static bool m_bMenuSelect;
        static int m_iSelectMenu; // �ʱⰪ : MN_START

    public: // Static Func
        static int GetSelectMenu();

    private: // member Var
        float m_Speed;
        float m_MoveTime;
        bool m_Move;

    // Menu Selector Lerp Move Member Value
    private:
        bool m_bLerpFlag;                  // Space Key Down�� On, Lerp End�� Off
        bool m_bLerpMoveStart;        // Lerp Start�� On, Lerp End�� Off
        bool m_bLerpMoveEnd;         // Lerp End�� On, Scene Change�� Off

        FLOAT4 m_LerpPos;               // Lerp Move Pos
        FLOAT4 m_LerpStartPos;       // Lerp Start Pos
        FLOAT4 m_LerpEndPos;         // Lerp End Pos
        float  m_LerpTime;                 // Lerp Ratio Time

    private:
        SGameEngineRendererBasic* m_Selector;
        FLOAT4 m_WindowSize;

    public: // constructer destructer
        MenuSelector();
        virtual ~MenuSelector();

    public: // delete constructer 
        MenuSelector(const MenuSelector& _Other) = delete;
        MenuSelector(const MenuSelector&& _Other) = delete;

    public: // delete operator
        MenuSelector& operator=(const MenuSelector& _Other) = delete;
        MenuSelector& operator=(const MenuSelector&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;

    public:
        void SelectorLerpStart();
        SGameEngineRendererBasic* GetSelector();

};


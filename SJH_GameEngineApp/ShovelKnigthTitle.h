#pragma once
#include <SGameEngineScene.h>
#include <SGameEngineDirectory.h>
#include <SGameEngineFile.h>
#include <SGameEngineSound.h>

// 분류 :
// 용도 : 
// 설명 : 
class MenuSelector;
class ShovelKnigthTitle : public SGameEngineScene
{
    private: // Static Var
        static SoundPlayer m_TitleStageBgm;

    public: // Static Func

    private: // member Var
        SGameEngineDirectory m_ResPath;
        MenuSelector* m_MenuSelector;

    private:
        int m_SelectMenu;

    public: // constructer destructer
        ShovelKnigthTitle();
        ~ShovelKnigthTitle();

    public: // delete constructer 
        ShovelKnigthTitle(const ShovelKnigthTitle& _Other) = delete;
        ShovelKnigthTitle(const ShovelKnigthTitle&& _Other) = delete;

    public: // delete operator
        ShovelKnigthTitle& operator=(const ShovelKnigthTitle& _Other) = delete;
        ShovelKnigthTitle& operator=(const ShovelKnigthTitle&& _Other) = delete;

    public: // member Func
        void Start() override;
        void SceneUpdate() override;
        void SceneChangeStart() override;
        void SceneChangeEnd() override;

};


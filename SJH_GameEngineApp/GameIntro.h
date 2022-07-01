#pragma once
#include <SGameEngineScene.h>
#include <SGameEngineDirectory.h>
#include <SGameEngineFile.h>
#include <SGameEngineSound.h>

#include "FadeInOutActor.h"

// 분류 :
// 용도 : 
// 설명 : 
class GameIntro : public SGameEngineScene
{
    private: // Static Var
        static SoundPlayer m_IntroStageBgm;

    public: // Static Func

    private: // member Var
        SGameEngineDirectory m_ResPath;
        FadeInOutActor* m_Fade;

    public: // constructer destructer
        GameIntro();
        virtual ~GameIntro();

    public: // delete constructer 
        GameIntro(const GameIntro& _Other) = delete;
        GameIntro(const GameIntro&& _Other) = delete;

    public: // delete operator
        GameIntro& operator=(const GameIntro& _Other) = delete;
        GameIntro& operator=(const GameIntro&& _Other) = delete;

    public: // member Func
        void Start() override;
        void SceneUpdate() override;
        void SceneChangeStart() override;
        void SceneChangeEnd() override;

};


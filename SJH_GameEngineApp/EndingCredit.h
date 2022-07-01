#pragma once
#include <SGameEngineScene.h>
#include <SGameEngineDirectory.h>
#include <SGameEngineSound.h>

// 분류 :
// 용도 : 
// 설명 : 
class EndingBackDrop;
class CampFire_BackDrop;
class EndingText;
class CampFire;
class Ending_Player;
class EndingCredit : public SGameEngineScene
{
    private: // Static Var
        static SoundPlayer m_EndingStageBgm;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineDirectory m_ResPath;
        EndingBackDrop* m_BackDrop;
        CampFire_BackDrop* m_CampFireBackDrop;
        EndingText* m_EndingText;
        CampFire* m_CampFire;
        Ending_Player* m_PlayerObject;

    public: // constructer destructer
        EndingCredit();
        ~EndingCredit();

    public: // delete constructer 
        EndingCredit(const EndingCredit& _Other) = delete;
        EndingCredit(const EndingCredit&& _Other) = delete;

    public: // delete operator
        EndingCredit& operator=(const EndingCredit& _Other) = delete;
        EndingCredit& operator=(const EndingCredit&& _Other) = delete;

    public: // member Func
        void Start() override;
        void SceneUpdate() override;
        void SceneChangeStart() override;
        void SceneChangeEnd() override;
        void SceneDebugRender() override;

    public:
        // EndingCredit Image Cut
        void EndingCreditImageCut();

        // EndingCredit BackDrop Actor
        void EndingCreditCreateBackDrop();

        // EndingCredit Object Actor
        void EndingCreditCreateObject();

};


#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>
#include <SGameEngineTimeEventer.h>
#include <SGameEngineDebug.h>
#include <SGameEngineSound.h>

#include "GlobalValue.h"
#include "SavePoint.h"              // 세이브포인트정보를 가져오기위해
#include "ShovelKnight.h"        // 메인플레이어의 위치와 카메라 위치를 조정하기위해

// 분류 :
// 용도 : 
// 설명 : 카메라영향을 받지 않으며 플레이어 사망시 On되는 오브젝트
class DeathScreen : public SGameEngineActor
{
    private: // Static Var
        static SoundPlayer m_DeathScreenSound;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;

        SGameEngineRendererBasic* m_DeathScreen;                     // BackDrop DeathScreen

        SGameEngineFSM<DeathScreen> m_DeathScreenFSM;

        // 각 오브젝트를 애니메이션랜더 or 랜더러로 표현한다.

        // 세이브포인트 정보를 통해 None상태인지 아닌지를 판단하며
        // 활성화시 Active 상태애니메이션이 된다.
        SGameEngineRendererAnimation* m_AniPlayerMarker;      // 플레이어 아이콘(액터 On : 활성화세이브포인트지점보다 앞에 위치)
        SGameEngineRendererAnimation* m_AniSavePoint1;         // 첫번째 세이브포인트 오브젝트
        SGameEngineRendererAnimation* m_AniSavePoint2;         // 첫번째 세이브포인트 오브젝트
        SGameEngineRendererAnimation* m_AniSavePoint3;         // 첫번째 세이브포인트 오브젝트
        SGameEngineRendererAnimation* m_AniSavePoint4;         // 첫번째 세이브포인트 오브젝트

        // 기본상태 Off 상태
        // 플레이어 아이콘이 이동을 완료한 뒤
        // 타임이벤터로 시간차로 On상태가된다.
        SGameEngineRendererBasic* m_RecoveryText;

        SGameEngineRendererBasic* m_GoldPouch1;
        SGameEngineRendererBasic* m_GoldPouch2;
        SGameEngineRendererBasic* m_GoldPouch3;

        SGameEngineRendererBasic* m_GoldBox1;
        SGameEngineRendererBasic* m_GoldBox2;
        SGameEngineRendererBasic* m_GoldBox3;

    private:
        SGameEngineTimeEventer<DeathScreen> m_LostGoldEventer;

    private:
        // 마지막활성화 세이브포인트 Index
        int m_iLastSavePointIndex;

        // 플레이어가 회복한 골드량 관리
        int m_iRecoveryGold1;
        int m_iRecoveryGold2;
        int m_iRecoveryGold3;

        // 플레이어의 보유 골드량 관리
        int m_iHoldingGold;

    private: // 플레이어 마커 러프관련
        float m_LerpMoveTime;
        float m_LerpSpeed;
        FLOAT4 m_MovePos;

        // 사망스크린 길의 각 포인트별 위치정보를 저장한다.
        // 생성 시에 위치정보를 가지고있는다.
        FLOAT4 m_LinePos[6];          // 처음지점 ~ 마지막지점까지

    public: // constructer destructer
        DeathScreen();
        virtual ~DeathScreen();

    public: // delete constructer 
        DeathScreen(const DeathScreen& _Other) = delete;
        DeathScreen(const DeathScreen&& _Other) = delete;

    public: // delete operator
        DeathScreen& operator=(const DeathScreen& _Other) = delete;
        DeathScreen& operator=(const DeathScreen&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public: // FSM 관련
        // 처음 등장
        void IDLEStart();
        void IDLEStay();
        void IDLEEnd();

        // 플레이어 아이콘 이동
        void MakerMoveStart();
        void MakerMoveStay();
        void MakerMoveEnd();

        // 잃은 골드 표시
        void GoldDisplayStart();
        void GoldDisplayStay();
        void GoldDisplayEnd();

    public: // 타임이벤터 관련
        void FirstLostGoldInfo();
        void SecondLostGoldInfo();
        void ThirdLostGoldInfo();
        void DeathScreenEnd();

};


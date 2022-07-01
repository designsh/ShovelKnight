#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineInput.h>
#include <SGameEngineFSM.h>
#include <SGameEngineRendererTile.h>
#include <SGameEngineDirectory.h>
#include <SGameEngineSound.h>

// 분류 :
// 용도 : 
// 설명 : 
class PlayerMaker : public SGameEngineActor
{
    private: // Static Var
        static SoundPlayer m_MoveStartSound;
        static SoundPlayer m_CantMoveSound;
        static SoundPlayer m_StageSelectSound;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererAnimation* m_AniPlayer;
        SGameEngineFSM<PlayerMaker> m_PlayerFSM;

    private: // 플레이어는 이동가능한 타일을 알고있다.
        SGameEngineDirectory m_MoveTileFilePath;
        SGameEngineRendererTile* m_MoveTile;
        FLOAT4 m_PlayerPosIndex;

    private:
        FLOAT4 m_LerpPoint[3];

    private: // 벡터 관련
        FLOAT4 m_LerpStartPos;
        FLOAT4 m_LerpEndPos;
        FLOAT4 m_LerpPos;
        bool m_LerpStartMove;
        float m_LerpTime;

    private: // 픽셀체크(제자리점프용)
        FLOAT4 m_PlayerCheckPos;
        FLOAT4 m_PlayerCheckDir;
        int m_iPlayerCheckColor;

    private:
        bool m_bPlayerMove;
        int m_iPlayerMakerPoint;

    public: // constructer destructer
        PlayerMaker();
        ~PlayerMaker();

    public: // delete constructer 
        PlayerMaker(const PlayerMaker& _Other) = delete;
        PlayerMaker(const PlayerMaker&& _Other) = delete;

    public: // delete operator
        PlayerMaker& operator=(const PlayerMaker& _Other) = delete;
        PlayerMaker& operator=(const PlayerMaker&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        // 플레이어 키설정
        void PlayerMaker_CreateKey();

        // 플레이어 애니메이션 설정
        void PlayerMaker_CreateAnimaion();

        // 플레이어 FSM 설정
        void PlayerMaker_CreateFSM();

        // 플레이어 이동가능한 방향 타일 찾기
        void CreateMoveTileMap();
        int GetBrokenTileImageIndex(const FLOAT4& _CheckPos);
        void SetPlayerPosIndex();

    public:
        void PlayerPixelCheck();

    public: // 구름 러프가 완료하면 플레이어 이동가능
        void SetCloudLerpEnd();

    public:
        void SetPlayerLerpPoint(const FLOAT4& _CurPoint, const FLOAT4& _SecondPoint, const FLOAT4& _FinalPoint);

    public:
        // 대기상태
        void IDLEStart();
        void IDLEStay();
        void IDLEEnd();

        // 이동상태
        void MoveStart();
        void MoveStay();
        void MoveEnd();

};


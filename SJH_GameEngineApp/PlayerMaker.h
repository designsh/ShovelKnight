#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineInput.h>
#include <SGameEngineFSM.h>
#include <SGameEngineRendererTile.h>
#include <SGameEngineDirectory.h>
#include <SGameEngineSound.h>

// �з� :
// �뵵 : 
// ���� : 
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

    private: // �÷��̾�� �̵������� Ÿ���� �˰��ִ�.
        SGameEngineDirectory m_MoveTileFilePath;
        SGameEngineRendererTile* m_MoveTile;
        FLOAT4 m_PlayerPosIndex;

    private:
        FLOAT4 m_LerpPoint[3];

    private: // ���� ����
        FLOAT4 m_LerpStartPos;
        FLOAT4 m_LerpEndPos;
        FLOAT4 m_LerpPos;
        bool m_LerpStartMove;
        float m_LerpTime;

    private: // �ȼ�üũ(���ڸ�������)
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
        // �÷��̾� Ű����
        void PlayerMaker_CreateKey();

        // �÷��̾� �ִϸ��̼� ����
        void PlayerMaker_CreateAnimaion();

        // �÷��̾� FSM ����
        void PlayerMaker_CreateFSM();

        // �÷��̾� �̵������� ���� Ÿ�� ã��
        void CreateMoveTileMap();
        int GetBrokenTileImageIndex(const FLOAT4& _CheckPos);
        void SetPlayerPosIndex();

    public:
        void PlayerPixelCheck();

    public: // ���� ������ �Ϸ��ϸ� �÷��̾� �̵�����
        void SetCloudLerpEnd();

    public:
        void SetPlayerLerpPoint(const FLOAT4& _CurPoint, const FLOAT4& _SecondPoint, const FLOAT4& _FinalPoint);

    public:
        // ������
        void IDLEStart();
        void IDLEStay();
        void IDLEEnd();

        // �̵�����
        void MoveStart();
        void MoveStay();
        void MoveEnd();

};


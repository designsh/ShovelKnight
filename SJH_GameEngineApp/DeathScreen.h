#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>
#include <SGameEngineTimeEventer.h>
#include <SGameEngineDebug.h>
#include <SGameEngineSound.h>

#include "GlobalValue.h"
#include "SavePoint.h"              // ���̺�����Ʈ������ ������������
#include "ShovelKnight.h"        // �����÷��̾��� ��ġ�� ī�޶� ��ġ�� �����ϱ�����

// �з� :
// �뵵 : 
// ���� : ī�޶����� ���� ������ �÷��̾� ����� On�Ǵ� ������Ʈ
class DeathScreen : public SGameEngineActor
{
    private: // Static Var
        static SoundPlayer m_DeathScreenSound;

    public: // Static Func

    private: // member Var
        FLOAT4 m_WindowSize;

        SGameEngineRendererBasic* m_DeathScreen;                     // BackDrop DeathScreen

        SGameEngineFSM<DeathScreen> m_DeathScreenFSM;

        // �� ������Ʈ�� �ִϸ��̼Ƿ��� or �������� ǥ���Ѵ�.

        // ���̺�����Ʈ ������ ���� None�������� �ƴ����� �Ǵ��ϸ�
        // Ȱ��ȭ�� Active ���¾ִϸ��̼��� �ȴ�.
        SGameEngineRendererAnimation* m_AniPlayerMarker;      // �÷��̾� ������(���� On : Ȱ��ȭ���̺�����Ʈ�������� �տ� ��ġ)
        SGameEngineRendererAnimation* m_AniSavePoint1;         // ù��° ���̺�����Ʈ ������Ʈ
        SGameEngineRendererAnimation* m_AniSavePoint2;         // ù��° ���̺�����Ʈ ������Ʈ
        SGameEngineRendererAnimation* m_AniSavePoint3;         // ù��° ���̺�����Ʈ ������Ʈ
        SGameEngineRendererAnimation* m_AniSavePoint4;         // ù��° ���̺�����Ʈ ������Ʈ

        // �⺻���� Off ����
        // �÷��̾� �������� �̵��� �Ϸ��� ��
        // Ÿ���̺��ͷ� �ð����� On���°��ȴ�.
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
        // ������Ȱ��ȭ ���̺�����Ʈ Index
        int m_iLastSavePointIndex;

        // �÷��̾ ȸ���� ��差 ����
        int m_iRecoveryGold1;
        int m_iRecoveryGold2;
        int m_iRecoveryGold3;

        // �÷��̾��� ���� ��差 ����
        int m_iHoldingGold;

    private: // �÷��̾� ��Ŀ ��������
        float m_LerpMoveTime;
        float m_LerpSpeed;
        FLOAT4 m_MovePos;

        // �����ũ�� ���� �� ����Ʈ�� ��ġ������ �����Ѵ�.
        // ���� �ÿ� ��ġ������ �������ִ´�.
        FLOAT4 m_LinePos[6];          // ó������ ~ ��������������

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

    public: // FSM ����
        // ó�� ����
        void IDLEStart();
        void IDLEStay();
        void IDLEEnd();

        // �÷��̾� ������ �̵�
        void MakerMoveStart();
        void MakerMoveStay();
        void MakerMoveEnd();

        // ���� ��� ǥ��
        void GoldDisplayStart();
        void GoldDisplayStay();
        void GoldDisplayEnd();

    public: // Ÿ���̺��� ����
        void FirstLostGoldInfo();
        void SecondLostGoldInfo();
        void ThirdLostGoldInfo();
        void DeathScreenEnd();

};


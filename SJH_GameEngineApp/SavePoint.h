#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineCollision.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"

#define BESHOTMAX 4
#define SAVEPOINTMAX 4

// �з� :
// �뵵 : 
// ���� : 

// ���̺� �����ʹ� ������ Ȱ��ȭ�� ���̺��������� ������ �������ִ�.
class SavePointInfo
{
public:
    // �������� ����
    // 1. ī�޶���ġ(�÷��̸� �ٽ� ���󰡾��ϹǷ�)
    // 2. �� ���̺�����Ʈ�� ��ġ(���� �÷��̾� ��Ȱ��ġ)
    // 3. ���������� Ȱ��ȭ�� ���̺�����Ʈ Index(�ʱⰪ 0)
    FLOAT4 m_CamPos;
    FLOAT4 m_SavePointPos;
    int m_iActiveSavePoint;

public:
    // �ʱ� ��ġ�� �÷��̾��� ó�� ������ġ�� �����ϴ�
    SavePointInfo() : m_CamPos(FLOAT4(0.f, 2160.f)), m_SavePointPos({ 100.f, (720.f - 132.f) + 2160.f }), m_iActiveSavePoint(0)
    {

    }
};

class SavePoint : public SGameEngineActor
{
    private: // Static Var
        // ���������� Ȱ��ȭ�� ���̺��������� ������ ������.
        static SavePointInfo m_LastSaveData;

    public: // Static Func
        static SavePointInfo GetLastSaveData();

    private: // member Var
        FLOAT4 m_WindowSize;
        SGameEngineRendererBasic* m_SavePoint;
        SGameEngineCollision* m_SavePointCol;
        SGameEngineFSM<SavePoint> m_SavePointFSM;
        SGameEngineRendererAnimation* m_AniSavePoint;

    private:
        int m_iPlayerAttack; // �÷��̾ ���� ������ Ƚ��

    private:
        bool m_bFirstCollision;

    private:
        // ���� �÷��̾�� �浹�� ���̺� �������� ������ �������ִ�.
        SavePointInfo m_MySaveData;

    public: // constructer destructer
        SavePoint();
        virtual ~SavePoint();

    public: // delete constructer 
        SavePoint(const SavePoint& _Other) = delete;
        SavePoint(const SavePoint&& _Other) = delete;

    public: // delete operator
        SavePoint& operator=(const SavePoint& _Other) = delete;
        SavePoint& operator=(const SavePoint&& _Other) = delete;

    public: // member Func
        void Start() override;
        void Update() override;
        void DebugRender() override;

    public:
        // �÷��̾ ���� ġ�� Ƚ���� ���� �ִϸ��̼� ����
        void ChangeAnimation();

    public: // �浹����
        void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
        void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

    public: // ���°���
        // ������
        void IDLEStart();
        void IDLEStay();
        void IDLEEnd();

        // �浹����
        void ColStart();
        void ColStay();
        void ColEnd();

        // Ȱ��ȭ����
        void ActiveStart();
        void ActiveStay();
        void ActiveEnd();

};


#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>
#include <SGameEngineSound.h>

// �з� :
// �뵵 : 
// ���� : BrokenTile�� �����Ǹ鼭 �� ���͸� �����ϸ� Death �ִϸ��̼��� ������ ���� ���ʹ� �״´�.
class BrokenTileEffect : public SGameEngineActor
{
private: // Static Var
    static SoundPlayer m_BrokenTileSound;

public: // Static Func

private: // member Var
    FLOAT4 m_WindowSize;
    SGameEngineRendererAnimation* m_AniBrokenTileEffect;
    SGameEngineFSM<BrokenTileEffect> m_BrokenTileEffectFSM;

public: // constructer destructer
    BrokenTileEffect();
    ~BrokenTileEffect();

public: // delete constructer 
    BrokenTileEffect(const BrokenTileEffect& _Other) = delete;
    BrokenTileEffect(const BrokenTileEffect&& _Other) = delete;

public: // delete operator
    BrokenTileEffect& operator=(const BrokenTileEffect& _Other) = delete;
    BrokenTileEffect& operator=(const BrokenTileEffect&& _Other) = delete;

public: // member Func
    void Start() override;
    void Update() override;
    void DebugRender() override;

    // FSM ����
public:
    void DeathStart();
    void DeathStay();
    void DeathEnd();

};


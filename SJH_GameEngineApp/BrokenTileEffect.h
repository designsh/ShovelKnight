#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineFSM.h>
#include <SGameEngineSound.h>

// 분류 :
// 용도 : 
// 설명 : BrokenTile이 삭제되면서 이 액터를 생성하며 Death 애니메이션이 끝나면 현재 액터는 죽는다.
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

    // FSM 상태
public:
    void DeathStart();
    void DeathStay();
    void DeathEnd();

};


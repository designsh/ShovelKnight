#include "Enchantress_FinalBoss_RegenSkill.h"
#include <SGameEngineWindow.h>

// Static Var

// Static Func

// member Var
Enchantress_FinalBoss_RegenSkill::Enchantress_FinalBoss_RegenSkill()
    : m_WindowSize(FLOAT4::ZERO), 
    m_fMoveDelay(1.f), m_TargetPos(FLOAT4::ZERO), m_MyIndex(FLOAT4::ZERO), m_fDeathDelay(1.0f),
    m_AniRegenSkillStone(nullptr), m_AniRegenSkillFlame(nullptr), m_RegenSkillCol(nullptr), m_RegenSkillFSM(),
    m_MoveDir(GlobalValue::BasicMoveType::Up), m_PrevMoveDir(GlobalValue::BasicMoveType::None),
    m_CurAniMationName(), m_AniMationName(),
    m_MovePos(FLOAT4::ZERO), m_DirectPos(FLOAT4::ZERO),
    m_LerpPos(FLOAT4::ZERO), m_LerpStartPos(FLOAT4::ZERO), m_LerpEndPos(FLOAT4::ZERO),
    m_LerpStartMove(false), m_LerpTime(0.0f)
{

}

Enchantress_FinalBoss_RegenSkill::~Enchantress_FinalBoss_RegenSkill()
{

}

// member Func
void Enchantress_FinalBoss_RegenSkill::Start()
{
    // 윈도우의 크기를 가져온다.
    m_WindowSize = SGameEngineWindow::GetSize();

    // 애니메이션 생성
    // 리젠스킬 돌덩이
    m_AniRegenSkillStone = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Monster);
    m_AniRegenSkillStone->SetRenderScale({ 150, 150 });
    m_AniRegenSkillStone->SetPivotPos({ GetPosition().x + (32.f * 0.5f), GetPosition().y + (32.f * 0.5f) });
    m_AniRegenSkillStone->CreateAnimation(L"Stone_Create", L"Boss_RegenSkill.bmp", 0, 5);
    m_AniRegenSkillStone->CreateAnimation(L"Stone_Idle", L"Boss_RegenSkill.bmp", 5, 5, 0.1f, false);

    // 리젠스킬 불꽃
    m_AniRegenSkillFlame = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Monster + 1);
    m_AniRegenSkillFlame->SetRenderScale({ 150, 150 });
    m_AniRegenSkillFlame->SetPivotPos({ GetPosition().x + (32.f * 0.5f), GetPosition().y + (32.f * 0.5f) - 32.f });
    m_AniRegenSkillFlame->CreateAnimation(L"Flame_Create", L"Boss_RegenSkill.bmp", 6, 7, 0.3f, false);
    m_AniRegenSkillFlame->CreateAnimation(L"Flame_Idle", L"Boss_RegenSkill.bmp", 8, 11);
    m_AniRegenSkillFlame->Off();

    // 충돌체 생성
    m_RegenSkillCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Monster);
    m_RegenSkillCol->SetScale({ 32, 32 });
    m_RegenSkillCol->SetPivotPos({ GetPosition().x - (32.f * 0.5f), GetPosition().y - (32.f * 0.5f) + 10.f });
    m_RegenSkillCol->AddStartEvent(this, &Enchantress_FinalBoss_RegenSkill::CollisionStart);
    m_RegenSkillCol->AddStayEvent(this, &Enchantress_FinalBoss_RegenSkill::CollisionStay);
    m_RegenSkillCol->AddEndEvent(this, &Enchantress_FinalBoss_RegenSkill::CollisionEnd);
    m_RegenSkillCol->SetCheckData(2);

    // FSM 상태 생성
    m_RegenSkillFSM.CreateState(L"Enchantress_RegenSkill_StoneCreate", this, &Enchantress_FinalBoss_RegenSkill::StoneCreateStay, &Enchantress_FinalBoss_RegenSkill::StoneCreateStart, &Enchantress_FinalBoss_RegenSkill::StoneCreateEnd);
    m_RegenSkillFSM.CreateState(L"Enchantress_RegenSkill_FlameCreate", this, &Enchantress_FinalBoss_RegenSkill::FlameCreateStay, &Enchantress_FinalBoss_RegenSkill::FlameCreateStart, &Enchantress_FinalBoss_RegenSkill::FlameCreateEnd);
    m_RegenSkillFSM.CreateState(L"Enchantress_RegenSkill_Idle", this, &Enchantress_FinalBoss_RegenSkill::RegenSkillIdleStay, &Enchantress_FinalBoss_RegenSkill::RegenSkillIdleStart, &Enchantress_FinalBoss_RegenSkill::RegenSkillIdleEnd);
    m_RegenSkillFSM.CreateState(L"Enchantress_RegenSkill_Move", this, &Enchantress_FinalBoss_RegenSkill::MoveStay, &Enchantress_FinalBoss_RegenSkill::MoveStart, &Enchantress_FinalBoss_RegenSkill::MoveEnd);
    m_RegenSkillFSM.CreateState(L"Enchantress_RegenSkill_Regen", this, &Enchantress_FinalBoss_RegenSkill::TileObjectRegenStay, &Enchantress_FinalBoss_RegenSkill::TileObjectRegenStart, &Enchantress_FinalBoss_RegenSkill::TileObjectRegenEnd);
    m_RegenSkillFSM.CreateState(L"Enchantress_RegenSkill_Death", this, &Enchantress_FinalBoss_RegenSkill::DeathStay, &Enchantress_FinalBoss_RegenSkill::DeathStart, &Enchantress_FinalBoss_RegenSkill::DeathEnd);
    m_RegenSkillFSM.ChangeState(L"Enchantress_RegenSkill_StoneCreate");
}

void Enchantress_FinalBoss_RegenSkill::Update()
{
    m_RegenSkillFSM.Update();
}

void Enchantress_FinalBoss_RegenSkill::DebugRender()
{
    Col2DData ColData;
    ColData.m_Pos = GetCamPosition() - m_RegenSkillCol->GetPivotPos();
    ColData.m_Size = m_RegenSkillCol->GetScale();
    RECT ColRect = { ColData.iLeft(), ColData.iTop(), ColData.iRight(), ColData.iBottom() };
    if (true == m_RegenSkillCol->IsOn())
    {
        FrameRect(SGameEngineWindow::GetBackBufferDC(), &ColRect, SGameEngineWindow::GetGreenBrush());
    }
}

void Enchantress_FinalBoss_RegenSkill::SetTargeIndex(FLOAT4 _Index)
{
    m_MyIndex = _Index;
}

#include "BlackKnight_SkillEffect.h"

#include <SGameEngineWindow.h>

// Static Var

// Static Func

// member Var
BlackKnight_SkillEffect::BlackKnight_SkillEffect()
	: m_WindowSize(FLOAT4::ZERO),
	m_AniSkillEffect(nullptr), m_SkillEffectCol(nullptr), m_SkillEffectFSM(),
	m_MoveDir(GlobalValue::BasicMoveType::Left), m_PrevMoveDir(GlobalValue::BasicMoveType::None),
	m_MaximumRange(0.0f),
	m_CurAniMationName(), m_AniMationName(),
	m_StartPos(FLOAT4::ZERO), m_MovePos(FLOAT4::ZERO),
	m_Speed(150.f)
{

}

BlackKnight_SkillEffect::~BlackKnight_SkillEffect()
{

}

// member Func
void BlackKnight_SkillEffect::Start()
{
	// 현재 윈도우 크기를 가져온다.
	m_WindowSize = SGameEngineWindow::GetSize();

	// 충돌체 생성
	m_SkillEffectCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::UI);
	m_SkillEffectCol->SetScale({ 50, 50 });
	m_SkillEffectCol->AddStartEvent(this, &BlackKnight_SkillEffect::CollisionStart);
	m_SkillEffectCol->AddStayEvent(this, &BlackKnight_SkillEffect::CollisionStay);
	m_SkillEffectCol->AddEndEvent(this, &BlackKnight_SkillEffect::CollisionEnd);
	m_SkillEffectCol->SetCheckData(0);

	// 애니메이션 생성
	m_AniSkillEffect = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Monster);
	m_AniSkillEffect->SetRenderScale({ 300, 300 });
	m_AniSkillEffect->CreateAnimation(L"Left_SkillEffect_Move", L"Left_BlackKnight_Skill.bmp", 0, 3);
	m_AniSkillEffect->CreateAnimation(L"Right_SkillEffect_Move", L"Right_BlackKnight_Skill.bmp", 0, 3);

	// 사망시 모션
	m_AniSkillEffect->CreateAnimation(L"DieMotion", L"poofs.bmp", 0, 4);

	// FSM 상태
	m_SkillEffectFSM.CreateState(L"SkillEffect_Move", this, &BlackKnight_SkillEffect::MoveStay, &BlackKnight_SkillEffect::MoveStart, &BlackKnight_SkillEffect::MoveEnd);
	m_SkillEffectFSM.CreateState(L"SkillEffect_Death", this, &BlackKnight_SkillEffect::DeathStay, &BlackKnight_SkillEffect::DeathStart, &BlackKnight_SkillEffect::DeathEnd);
	m_SkillEffectFSM.ChangeState(L"SkillEffect_Move");
}

void BlackKnight_SkillEffect::Update()
{
	m_MovePos = FLOAT4::ZERO;

	// 방향전환 체크
	DirCheck();

	m_SkillEffectFSM.Update();

	MovePosition(m_MovePos);
}

void BlackKnight_SkillEffect::SetSkillEffectDirect(GlobalValue::BasicMoveType _Direct)
{
	m_MoveDir = _Direct;
}

void BlackKnight_SkillEffect::MovePosCheck()
{
	m_MovePos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_MovePos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_Speed);
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_MovePos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_Speed);
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}

	m_PrevMoveDir = m_MoveDir;
}

void BlackKnight_SkillEffect::MaximumRangeCheck()
{
	// 진행방향이 왼쪽이면 StartPos.x - m_MaximumRange 값보다 내 위치가 작아지면
	// 상태변경
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		if (GetPosition().x <= m_StartPos.x - m_MaximumRange)
		{
			m_SkillEffectFSM.ChangeState(L"SkillEffect_Death");
		}
	}
	// 진행방향이 오른쪽이면 StartPos.x + m_MaximumRange 값보다 내 위치가 커지면
	// 상태 변경
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		if (GetPosition().x >= m_StartPos.x + m_MaximumRange)
		{
			m_SkillEffectFSM.ChangeState(L"SkillEffect_Death");
		}
	}
}

void BlackKnight_SkillEffect::ChangeAniMation(const SGameEngineString& _ChangeAniName)
{
	m_CurAniMationName = L"";
	if (m_MoveDir == (GlobalValue::BasicMoveType::Right))
	{
		m_CurAniMationName = L"Right_";
	}
	if (m_MoveDir == (GlobalValue::BasicMoveType::Left))
	{
		m_CurAniMationName = L"Left_";
	}

	m_AniMationName = _ChangeAniName;
	m_CurAniMationName += _ChangeAniName;

	m_AniSkillEffect->ChangeAnimation(m_CurAniMationName);
}

void BlackKnight_SkillEffect::DirCheck()
{
	if (m_MoveDir != m_PrevMoveDir)
	{
		ChangeAniMation(m_AniMationName);
	}

	m_PrevMoveDir = m_MoveDir;
}

void BlackKnight_SkillEffect::DebugRender()
{
	Col2DData SkillEffectColData;
	SkillEffectColData.m_Pos = GetCamPosition() - m_SkillEffectCol->GetPivotPos();
	SkillEffectColData.m_Size = m_SkillEffectCol->GetScale();
	RECT SkillEffectColRect = { SkillEffectColData.iLeft(), SkillEffectColData.iTop(), SkillEffectColData.iRight(), SkillEffectColData.iBottom() };
	if (true == m_SkillEffectCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &SkillEffectColRect, SGameEngineWindow::GetGreenBrush());
	}
}

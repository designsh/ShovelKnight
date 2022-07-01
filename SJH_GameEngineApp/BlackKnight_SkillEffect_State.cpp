#include "BlackKnight_SkillEffect.h"

// 생성후 움직이는 상태
void BlackKnight_SkillEffect::MoveStart()
{
	ChangeAniMation(L"SkillEffect_Move");

	// 시작위치를 알고있는다.
	m_StartPos = GetPosition();

	// 충돌체 기준점을 옮긴다.
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_SkillEffectCol->SetPivotPos({ 20.f, 0.f });
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_SkillEffectCol->SetPivotPos({ -20.f, 0.f });
	}
}

void BlackKnight_SkillEffect::MoveStay()
{
	// 이동한다.
	MovePosCheck();

	// 만약 최대사거리에 도달하면 상태변경
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		if (GetPosition().x <= m_StartPos.x - m_MaximumRange)
		{
			m_SkillEffectFSM.ChangeState(L"SkillEffect_Death");
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		if (GetPosition().x <= m_StartPos.x + m_MaximumRange)
		{
			m_SkillEffectFSM.ChangeState(L"SkillEffect_Death");
		}
	}
}

void BlackKnight_SkillEffect::MoveEnd()
{

}

// 죽는상태
void BlackKnight_SkillEffect::DeathStart()
{
	m_AniSkillEffect->ChangeAnimation(L"DieMotion");
}

void BlackKnight_SkillEffect::DeathStay()
{
	if (true == m_AniSkillEffect->IsEnd())
	{
		Death();
	}
}

void BlackKnight_SkillEffect::DeathEnd()
{

}

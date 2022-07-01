#include "BlackKnight_SkillEffect.h"

// ������ �����̴� ����
void BlackKnight_SkillEffect::MoveStart()
{
	ChangeAniMation(L"SkillEffect_Move");

	// ������ġ�� �˰��ִ´�.
	m_StartPos = GetPosition();

	// �浹ü �������� �ű��.
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
	// �̵��Ѵ�.
	MovePosCheck();

	// ���� �ִ��Ÿ��� �����ϸ� ���º���
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

// �״»���
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

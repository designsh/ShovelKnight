#include "Enchantress_FinalBoss_RegenSkill.h"
#include "EnchantressBrokenTile.h"
#include "Enchantress_FinalBoss.h"

// Ÿ�� ���� ����
void Enchantress_FinalBoss_RegenSkill::StoneCreateStart()
{
	m_AniRegenSkillStone->ChangeAnimation(L"Stone_Create");
}

void Enchantress_FinalBoss_RegenSkill::StoneCreateStay()
{
	if (true == m_AniRegenSkillStone->IsEnd())
	{
		m_RegenSkillFSM.ChangeState(L"Enchantress_RegenSkill_FlameCreate");
	}
}

void Enchantress_FinalBoss_RegenSkill::StoneCreateEnd()
{

}

// �Ҳ� ���� ����
void Enchantress_FinalBoss_RegenSkill::FlameCreateStart()
{
	m_AniRegenSkillFlame->On();
	m_AniRegenSkillFlame->ChangeAnimation(L"Flame_Create");
	m_AniRegenSkillStone->ChangeAnimation(L"Stone_Idle");
}

void Enchantress_FinalBoss_RegenSkill::FlameCreateStay()
{
	if (true == m_AniRegenSkillFlame->IsEnd())
	{
		m_RegenSkillFSM.ChangeState(L"Enchantress_RegenSkill_Idle");
	}
}

void Enchantress_FinalBoss_RegenSkill::FlameCreateEnd()
{

}

// ���� ��ų ��� ����
void Enchantress_FinalBoss_RegenSkill::RegenSkillIdleStart()
{
	m_AniRegenSkillFlame->ChangeAnimation(L"Flame_Idle");
	m_AniRegenSkillStone->ChangeAnimation(L"Stone_Idle");
}

void Enchantress_FinalBoss_RegenSkill::RegenSkillIdleStay()
{
	// ���⼭ �̵���� ���� �ð� ���� �� ���� ���� ��ȯ
	m_fMoveDelay -= SGameEngineTimer::FDeltaTime();
	if (0.0f >= m_fMoveDelay)
	{
		m_RegenSkillFSM.ChangeState(L"Enchantress_RegenSkill_Move");
		m_fMoveDelay = 1.f;
	}
}

void Enchantress_FinalBoss_RegenSkill::RegenSkillIdleEnd()
{

}

// �����Ϸ� �� ���� ����
void Enchantress_FinalBoss_RegenSkill::MoveStart()
{
	m_AniRegenSkillFlame->ChangeAnimation(L"Flame_Idle");
	m_AniRegenSkillStone->ChangeAnimation(L"Stone_Idle");

	// Ÿ�� ��ġ�� �����ȴ�.
	// �� ��ġ���� 6�� �ε����� ���� ��������� ������
	// �ش� Ÿ�� ��ġ�� �����Ѵ�.
	m_TargetPos = FLOAT4(GetPosition().x, GetPosition().y - (6 * 32.f));

	m_LerpStartPos = GetPosition();
	m_LerpEndPos = m_TargetPos;
	m_LerpStartMove = true;
}

void Enchantress_FinalBoss_RegenSkill::MoveStay()
{
	// ���� Ÿ�� ��ġ���� �����Ѵ�.
	if (true == m_LerpStartMove)
	{
		m_LerpTime += SGameEngineTimer::MainTimer.FDeltaTime(0.4f);
		m_LerpPos = FLOAT4::Lerp2D(m_LerpStartPos, m_LerpEndPos, m_LerpTime);

		SetPosition(m_LerpPos);

		if (1.0f < m_LerpTime)
		{
			// �����Ϸ�� ��� �� �ʱ�ȭ
			m_LerpPos = FLOAT4::ZERO;
			m_LerpStartPos = FLOAT4::ZERO;
			m_LerpEndPos = FLOAT4::ZERO;
			m_LerpTime = 0.0f;
			m_LerpStartMove = false;

			// ���� �Ϸ�� ������ȯ
			m_RegenSkillFSM.ChangeState(L"Enchantress_RegenSkill_Regen");
		}
		return;
	}
}

void Enchantress_FinalBoss_RegenSkill::MoveEnd()
{

}

// �ش� ��ġ ���� �� Ÿ�ϸ��� ����
void Enchantress_FinalBoss_RegenSkill::TileObjectRegenStart()
{
	m_AniRegenSkillFlame->ChangeAnimation(L"Flame_Idle");
	m_AniRegenSkillStone->ChangeAnimation(L"Stone_Idle");
}

void Enchantress_FinalBoss_RegenSkill::TileObjectRegenStay()
{
	// Ÿ����ġ���� �̿��Ͽ� �ε����� ���Ѵ�.
	FLOAT4 FileInfoIndex = { m_TargetPos.ix() / 32, m_TargetPos.iy() / 32 };

	// Ÿ���ε����� ���� �ε����� �̿��Ͽ� BrokenTileObject�� ������Ѵ�.
	bool ReturnValue = GlobalValue::FinalStage_FinalBoss->RegenBrokenObject(FileInfoIndex, m_MyIndex);
	if (true == ReturnValue)
	{
		GlobalValue::FinalStage_FinalBoss->SetRegenSkillingFlagOff();

		m_RegenSkillFSM.ChangeState(L"Enchantress_RegenSkill_Death");
	}
}

void Enchantress_FinalBoss_RegenSkill::TileObjectRegenEnd()
{

}

// ���� �Ϸ� �� ���
void Enchantress_FinalBoss_RegenSkill::DeathStart()
{
	m_AniRegenSkillFlame->ChangeAnimation(L"Flame_Idle");
	m_AniRegenSkillStone->ChangeAnimation(L"Stone_Idle");
}

void Enchantress_FinalBoss_RegenSkill::DeathStay()
{
	// ���� �ð��� ������ ����
	m_fDeathDelay -= SGameEngineTimer::FDeltaTime();
	if (0.0f >= m_fDeathDelay)
	{
		m_fDeathDelay = 1.f;
		Death();
	}
}

void Enchantress_FinalBoss_RegenSkill::DeathEnd()
{

}

#include "Enchantress_FinalBoss_RegenSkill.h"
#include "EnchantressBrokenTile.h"
#include "Enchantress_FinalBoss.h"

// 타일 생성 시작
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

// 불꽃 생성 시작
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

// 리젠 스킬 대기 상태
void Enchantress_FinalBoss_RegenSkill::RegenSkillIdleStart()
{
	m_AniRegenSkillFlame->ChangeAnimation(L"Flame_Idle");
	m_AniRegenSkillStone->ChangeAnimation(L"Stone_Idle");
}

void Enchantress_FinalBoss_RegenSkill::RegenSkillIdleStay()
{
	// 여기서 이동대기 일정 시간 지난 뒤 무브 상태 전환
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

// 생성완료 후 무브 시작
void Enchantress_FinalBoss_RegenSkill::MoveStart()
{
	m_AniRegenSkillFlame->ChangeAnimation(L"Flame_Idle");
	m_AniRegenSkillStone->ChangeAnimation(L"Stone_Idle");

	// 타겟 위치가 결정된다.
	// 내 위치에서 6개 인덱스를 띄우고 만들어졌기 때문에
	// 해당 타겟 위치를 설정한다.
	m_TargetPos = FLOAT4(GetPosition().x, GetPosition().y - (6 * 32.f));

	m_LerpStartPos = GetPosition();
	m_LerpEndPos = m_TargetPos;
	m_LerpStartMove = true;
}

void Enchantress_FinalBoss_RegenSkill::MoveStay()
{
	// 나는 타겟 위치까지 러프한다.
	if (true == m_LerpStartMove)
	{
		m_LerpTime += SGameEngineTimer::MainTimer.FDeltaTime(0.4f);
		m_LerpPos = FLOAT4::Lerp2D(m_LerpStartPos, m_LerpEndPos, m_LerpTime);

		SetPosition(m_LerpPos);

		if (1.0f < m_LerpTime)
		{
			// 러프완료시 모든 값 초기화
			m_LerpPos = FLOAT4::ZERO;
			m_LerpStartPos = FLOAT4::ZERO;
			m_LerpEndPos = FLOAT4::ZERO;
			m_LerpTime = 0.0f;
			m_LerpStartMove = false;

			// 러프 완료시 상태전환
			m_RegenSkillFSM.ChangeState(L"Enchantress_RegenSkill_Regen");
		}
		return;
	}
}

void Enchantress_FinalBoss_RegenSkill::MoveEnd()
{

}

// 해당 위치 도착 후 타일리젠 시작
void Enchantress_FinalBoss_RegenSkill::TileObjectRegenStart()
{
	m_AniRegenSkillFlame->ChangeAnimation(L"Flame_Idle");
	m_AniRegenSkillStone->ChangeAnimation(L"Stone_Idle");
}

void Enchantress_FinalBoss_RegenSkill::TileObjectRegenStay()
{
	// 타겟위치값을 이용하여 인덱스를 구한다.
	FLOAT4 FileInfoIndex = { m_TargetPos.ix() / 32, m_TargetPos.iy() / 32 };

	// 타겟인덱스와 나의 인덱스를 이용하여 BrokenTileObject를 재생성한다.
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

// 리젠 완료 후 사망
void Enchantress_FinalBoss_RegenSkill::DeathStart()
{
	m_AniRegenSkillFlame->ChangeAnimation(L"Flame_Idle");
	m_AniRegenSkillStone->ChangeAnimation(L"Stone_Idle");
}

void Enchantress_FinalBoss_RegenSkill::DeathStay()
{
	// 일정 시간이 지나면 죽임
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

#include "Enchantress_FinalBoss.h"
#include "Enchantress_ShovelKnight.h"

// 대기(정지) 상태
void Enchantress_FinalBoss::IdleState_StateCheck()
{
	// 내 기준 플레이어 위치를 알아낸다.
	// 플레이어가 왼쪽에 위치하면 왼쪽으로 이동
	// 플레이어가 오른쪽에 위치하면 오른쪽으로 이동
	// 단, 랜덤으로 위로 이동하는지 아래로 이동하는지 또는 위,아래 이동없이 이동인지 정해진다.
	// 또한, 각 패턴 시작전 시간텀을 주기 위해서 델타타임으로 카운트한다.
	// 여기서 이동방향과 목표지점이 결정나면 상태를 전환한다.
	m_fPatternStartTime -= SGameEngineTimer::FDeltaTime();
	if (0.0f >= m_fPatternStartTime)
	{
		// 내 기준 플레이어 위치를 알아내어 이동방향이 결정난다.
		FLOAT4 MyPos = GetPosition() - GlobalValue::FinalStage_MainPlayer->GetPosition();
		MyPos.Normalize();
		if (0.0f >= MyPos.x) // 음수이면 플레이어는 나의 오른쪽에 위치
		{
			// 그러므로 나는 오른쪽이 이동방향
			m_MoveDir = GlobalValue::BasicMoveType::Right;
		}
		else // 양수이면 플레이어는 나의 왼쪽에 위치
		{
			// 그러므로 나는 왼쪽이 이동방향
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}

		// 이동방향이 정해지면 위로 이동인지 아래로 이동인지 위,아래 없이 이동인지 랜덤으로 정한다.
		int RandomPattern = rand() % 3;
		if (GlobalValue::BasicMoveType::Right == m_MoveDir)
		{
			if (0 == RandomPattern)             // 위로 이동
			{
				m_MoveTargetPos = FLOAT4(1200.f, 1225.f);
			}
			else if (1 == RandomPattern)      // 아래로 이동
			{
				m_MoveTargetPos = FLOAT4(1200.f, 1660.f);
			}
			else if (2 == RandomPattern)      // 우 이동
			{
				m_MoveTargetPos = FLOAT4(1200.f, 1375.f);
			}
		}
		else if (GlobalValue::BasicMoveType::Left == m_MoveDir)
		{
			if (0 == RandomPattern)             // 위로 이동
			{
				m_MoveTargetPos = FLOAT4(80.f, 1225.f);
			}
			else if (1 == RandomPattern)      // 아래로 이동
			{
				m_MoveTargetPos = FLOAT4(80.f, 1660.f);
			}
			else if (2 == RandomPattern)      // 좌 이동
			{
				m_MoveTargetPos = FLOAT4(80.f, 1375.f);
			}
		}

		// 시간 초기화
		m_fPatternStartTime = 1.f;

		// 목표지점, 이동방향이 결정나면 상태전환
		m_EnchantressFSM.ChangeState(L"Enchantress_Move");

		// 바닥오브젝트 일정개수 이하이면 상태전환
		// 보스는 타일리젠 스킬을 시전한다.
		if (false == m_bRegenSkilling) // 보스가 리젠스킬 발동중이 아닐때만 체크
		{
			BrokenTileObjectCheck();
		}
	}
}

// 이동 상태
void Enchantress_FinalBoss::MoveState_StateCheck()
{

}

// 공격 스킬 장전 상태(좌,우)
void Enchantress_FinalBoss::AttackSkillChargingState_StateCheck()
{
	if (true == m_AniEnchantress->IsEnd())
	{
		m_EnchantressFSM.ChangeState(L"Enchantress_BasicAttackSkillShot");
	}
}

// 공격 스킬 장전 상태(아래)
void Enchantress_FinalBoss::DownAttackSkillChargingState_StateCheck()
{
	if (true == m_AniEnchantress->IsEnd())
	{
		m_EnchantressFSM.ChangeState(L"Enchantress_DownAttackSkillShot");
	}
}

// 공격 스킬 장전 상태(위)
void Enchantress_FinalBoss::UpAttackSkillChargingState_StateCheck()
{
	if (true == m_AniEnchantress->IsEnd())
	{
		m_EnchantressFSM.ChangeState(L"Enchantress_UpAttackSkillShot");
	}
}

// 공격 스틸 발사 상태(좌,우)
void Enchantress_FinalBoss::AttackSkillShotState_StateCheck()
{

}

// 공격 스틸 발사 상태(아래)
void Enchantress_FinalBoss::DownAttackSkillShotState_StateCheck()
{

}

// 공격 스틸 발사 상태(위)
void Enchantress_FinalBoss::UpAttackSkillShotState_StateCheck()
{

}

// 공격 스킬 발사중 이동 상태(아래로발사중)
void Enchantress_FinalBoss::DownAttackSkillShotMoveState_StateCheck()
{
	// 내위치가 타겟위치에 도달하면 상태 체인지
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		if (GetPosition().x <= m_DownShotMove.x)
		{
			m_EnchantressFSM.ChangeState(L"Enchantress_DownAttackSkillShot");
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		if (GetPosition().x >= m_DownShotMove.x)
		{
			m_EnchantressFSM.ChangeState(L"Enchantress_DownAttackSkillShot");
		}
	}
}

// 공격 스킬 발사중 이동 상태(위로발사중)
void Enchantress_FinalBoss::UpAttackSkillShotMoveState_StateCheck()
{
	// 내위치가 타겟위치에 도달하면 상태 체인지
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		if (GetPosition().x <= m_UpShotMove.x)
		{
			m_EnchantressFSM.ChangeState(L"Enchantress_UpAttackSkillShot");
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		if (GetPosition().x >= m_UpShotMove.x)
		{
			m_EnchantressFSM.ChangeState(L"Enchantress_UpAttackSkillShot");
		}
	}
}

// 리젠 스킬 장전 상태
void Enchantress_FinalBoss::RegenSkillChargingState_StateCheck()
{

}

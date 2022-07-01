#include "Enchantress_FinalBoss.h"
#include "Enchantress_ShovelKnight.h"
#include "Enchantress_FinalBoss_AttackSkill.h"
#include "Enchantress_FinalBoss_RegenSkill.h"
#include "EnchantressBrokenTile.h"

// 대기(정지) 상태
void Enchantress_FinalBoss::IdleState_MovePosCheck()
{

}

// 이동 상태
void Enchantress_FinalBoss::MoveState_MovePosCheck()
{
	// 내위치부터 목표지점까지 이동한다.
	if (true == m_LerpStartMove)
	{
		m_LerpTime += SGameEngineTimer::MainTimer.FDeltaTime(0.2f);
		m_LerpMovePos = FLOAT4::Lerp2D(m_LerpStartPos, m_MoveTargetPos, m_LerpTime);

		SetPosition(m_LerpMovePos);

		if (1.0f < m_LerpTime)
		{
			// 러프완료시 모든 값 초기화
			m_LerpMovePos = FLOAT4::ZERO;
			m_LerpTime = 0.0f;
			m_LerpStartMove = false;

			// 방향전환 내 위치기준 플레이어 위치를 통해 방향을 결정
			FLOAT4 MyPos = GetPosition() - GlobalValue::FinalStage_MainPlayer->GetPosition();
			MyPos.Normalize();
			if (0.0f >= MyPos.x)
			{
				m_MoveDir = GlobalValue::BasicMoveType::Right;
			}
			else
			{
				m_MoveDir = GlobalValue::BasicMoveType::Left;
			}

			// 상태 전환
			// 내 현재 m_MoveTargetPos위치에 따라 스킬차징 패턴을 정해준다.
			if (FLOAT4(1200.f, 1225.f) == m_MoveTargetPos || FLOAT4(80.f, 1225.f) == m_MoveTargetPos) // 아래로 스킬차징
			{
				m_EnchantressFSM.ChangeState(L"Enchantress_DownAttackSkillCharging");
			}
			else if (FLOAT4(1200.f, 1660.f) == m_MoveTargetPos || FLOAT4(80.f, 1660.f) == m_MoveTargetPos) // 위로 스킬차징
			{
				m_EnchantressFSM.ChangeState(L"Enchantress_UpAttackSkillCharging");
			}
			else if (FLOAT4(1200.f, 1375.f) == m_MoveTargetPos || FLOAT4(80.f, 1375.f) == m_MoveTargetPos) // 좌,우로 스킬차징
			{
				m_EnchantressFSM.ChangeState(L"Enchantress_AttackSkillCharging");
			}
		}
		return;
	}

	m_LerpStartPos = GetPosition();
	m_LerpStartMove = true;
}

// 공격 스킬 장전 상태(좌,우)
void Enchantress_FinalBoss::AttackSkillChargingState_MovePosCheck()
{

}

// 공격 스킬 장전 상태(아래)
void Enchantress_FinalBoss::DownAttackSkillChargingState_MovePosCheck()
{

}

// 공격 스킬 장전 상태(위)
void Enchantress_FinalBoss::UpAttackSkillChargingState_MovePosCheck()
{

}

// 공격 스틸 발사 상태(좌,우)
void Enchantress_FinalBoss::AttackSkillShotState_MovePosCheck()
{
	if (true == m_AniEnchantress->IsEnd())
	{
		// 발사체 생성
		Enchantress_FinalBoss_AttackSkill* NewAttackSkill = GetScene()->CreateActor<Enchantress_FinalBoss_AttackSkill>();
		if (GlobalValue::BasicMoveType::Left == m_MoveDir)
		{
			NewAttackSkill->SetFirstMoveDirect(GlobalValue::BasicMoveType::Left);
		}
		else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
		{
			NewAttackSkill->SetFirstMoveDirect(GlobalValue::BasicMoveType::Right);
		}
		NewAttackSkill->SetPosition({ GetPosition().x, GetPosition().y - 40.f });

		// 4번 발사했으면 Idle상태로 돌아가고
		// 아니면 현재 상태로 재 전환한다.
		if (3 == m_iBossAttackSkillCnt)
		{
			m_EnchantressFSM.ChangeState(L"Enchantress_Idle");
			m_iBossAttackSkillCnt = 0;
		}
		else
		{
			// 4번 발사중에 애니메이션 End로 판단하기 때문에 애니메이션 변경
			ChangeAniMation(L"Boss_Idle");

			// 상태 전환
			m_EnchantressFSM.ChangeState(L"Enchantress_BasicAttackSkillShot");
			m_iBossAttackSkillCnt++;
		}
	}
}

// 공격 스틸 발사 상태(아래)
void Enchantress_FinalBoss::DownAttackSkillShotState_MovePosCheck()
{
	if (true == m_AniEnchantress->IsEnd())
	{
		// 발사체 생성
		Enchantress_FinalBoss_AttackSkill* NewAttackSkill = GetScene()->CreateActor<Enchantress_FinalBoss_AttackSkill>();
		NewAttackSkill->SetFirstMoveDirect(GlobalValue::BasicMoveType::Down);

		// 플레이어가 내 기준 오른쪽인지 왼쪽인지 알아낸다.
		FLOAT4 TargetPos = GetPosition() - GlobalValue::FinalStage_MainPlayer->GetPosition();
		TargetPos.Normalize();
		if (0.0f >= TargetPos.x)
		{
			NewAttackSkill->SetFirstFireDirect(GlobalValue::BasicMoveType::Right);
		}
		else
		{
			NewAttackSkill->SetFirstFireDirect(GlobalValue::BasicMoveType::Left);
		}
		NewAttackSkill->SetPosition(GetPosition());

		// 4번 발사했으면 Idle상태로 돌아가고
		// 아니면 현재 상태로 재 전환한다.
		// 초기값 0
		if (3 == m_iBossDownAttackSkillCnt)
		{
			m_EnchantressFSM.ChangeState(L"Enchantress_Idle");
			m_iBossDownAttackSkillCnt = 0;
		}
		else
		{
			// 상태 전환
			m_EnchantressFSM.ChangeState(L"Enchantress_DownAttackSkillShotMove");
			m_iBossDownAttackSkillCnt++;
		}
	}
}

// 공격 스틸 발사 상태(위)
void Enchantress_FinalBoss::UpAttackSkillShotState_MovePosCheck()
{
	if (true == m_AniEnchantress->IsEnd())
	{
		// 발사체 생성
		Enchantress_FinalBoss_AttackSkill* NewAttackSkill = GetScene()->CreateActor<Enchantress_FinalBoss_AttackSkill>();
		NewAttackSkill->SetFirstMoveDirect(GlobalValue::BasicMoveType::Up);

		// 플레이어가 내 기준 오른쪽인지 왼쪽인지 알아낸다.
		FLOAT4 TargetPos = GetPosition() - GlobalValue::FinalStage_MainPlayer->GetPosition();
		TargetPos.Normalize();
		if (0.0f >= TargetPos.x)
		{
			NewAttackSkill->SetFirstFireDirect(GlobalValue::BasicMoveType::Right);
		}
		else
		{
			NewAttackSkill->SetFirstFireDirect(GlobalValue::BasicMoveType::Left);
		}
		NewAttackSkill->SetPosition(GetPosition());

		// 4번 발사했으면 Idle상태로 돌아가고
		// 아니면 현재 상태로 재 전환한다.
		// 초기값 0
		if (3 == m_iBossUpAttackSkillCnt)
		{
			m_EnchantressFSM.ChangeState(L"Enchantress_Idle");
			m_iBossUpAttackSkillCnt = 0;
		}
		else
		{
			m_EnchantressFSM.ChangeState(L"Enchantress_UpAttackSkillShotMove");
			m_iBossUpAttackSkillCnt++;
		}
	}
}

// 공격 스킬 발사중 이동 상태(아래로발사중)
void Enchantress_FinalBoss::DownAttackSkillShotMoveState_MovePosCheck()
{
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(200.f);
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(200.f);
	}

	m_MovePos = m_DirectPos;
}

// 공격 스킬 발사중 이동 상태(위로발사중)
void Enchantress_FinalBoss::UpAttackSkillShotMoveState_MovePosCheck()
{
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(200.f);
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(200.f);
	}

	m_MovePos = m_DirectPos;
}

// 리젠 스킬 장전 상태
void Enchantress_FinalBoss::RegenSkillChargingState_MovePosCheck()
{
	// 장전완료시 리젠스킬오브젝트 생성
	// BrokenTile 자료구조의 x값의 랜덤으로 생성
	if (true == m_AniEnchantress->IsEnd())
	{
		// 최대 4개 랜덤 좌표 생성
		for (int x = 0; x < 5; x++)
		{
			int RandomIndex = rand() % m_BrokenObject.size();

			// 리젠스킬 초기 위치를 잡기위해서 이미죽은 타일은 제외한다.
			if (nullptr == m_BrokenObject[RandomIndex].back())
			{
				x--;
				continue;
			}
			else if (nullptr != m_BrokenObject[RandomIndex].back())
			{
				// 현재 BrokenObject 자료구조의 Y축 마지막 데이터의 위치값에
				// +2 인덱스의 위치값 구하고(한 타일의 크기 32.f)
				EnchantressBrokenTile* LastTile = m_BrokenObject[RandomIndex].back();
				FLOAT4 CreatePos = FLOAT4(LastTile->GetPosition().x, LastTile->GetPosition().y + 64.f);

				// 한개의 타일만큼의 크기를 증가 시켜
				// 4개의 리젠스킬을 생성한다.
				for (int y = 0; y < 4; y++)
				{
					// 생성 위치 결정
					CreatePos.y += 32.f;

					// 4개의 리젠스킬 생성
					Enchantress_FinalBoss_RegenSkill* NewRegenSkill = GetScene()->CreateActor<Enchantress_FinalBoss_RegenSkill>();
					NewRegenSkill->SetPosition(CreatePos);

					// 해당 액터의 타겟 인덱스를 저장한다.(추후 재생성할때 사용)
					NewRegenSkill->SetTargeIndex({ RandomIndex, y });
				}
			}
		}

		// 모두 생성 완료하고 리젠 대기상태로 전환한다.
		m_EnchantressFSM.ChangeState(L"Enchantress_BlockRegetSkillShotIdle");
	}
}

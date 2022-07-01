#include "Enchantress_FinalBoss.h"
#include "Enchantress_ShovelKnight.h"
#include "Enchantress_FinalBoss_AttackSkill.h"
#include "Enchantress_FinalBoss_RegenSkill.h"
#include "EnchantressBrokenTile.h"

// ���(����) ����
void Enchantress_FinalBoss::IdleState_MovePosCheck()
{

}

// �̵� ����
void Enchantress_FinalBoss::MoveState_MovePosCheck()
{
	// ����ġ���� ��ǥ�������� �̵��Ѵ�.
	if (true == m_LerpStartMove)
	{
		m_LerpTime += SGameEngineTimer::MainTimer.FDeltaTime(0.2f);
		m_LerpMovePos = FLOAT4::Lerp2D(m_LerpStartPos, m_MoveTargetPos, m_LerpTime);

		SetPosition(m_LerpMovePos);

		if (1.0f < m_LerpTime)
		{
			// �����Ϸ�� ��� �� �ʱ�ȭ
			m_LerpMovePos = FLOAT4::ZERO;
			m_LerpTime = 0.0f;
			m_LerpStartMove = false;

			// ������ȯ �� ��ġ���� �÷��̾� ��ġ�� ���� ������ ����
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

			// ���� ��ȯ
			// �� ���� m_MoveTargetPos��ġ�� ���� ��ų��¡ ������ �����ش�.
			if (FLOAT4(1200.f, 1225.f) == m_MoveTargetPos || FLOAT4(80.f, 1225.f) == m_MoveTargetPos) // �Ʒ��� ��ų��¡
			{
				m_EnchantressFSM.ChangeState(L"Enchantress_DownAttackSkillCharging");
			}
			else if (FLOAT4(1200.f, 1660.f) == m_MoveTargetPos || FLOAT4(80.f, 1660.f) == m_MoveTargetPos) // ���� ��ų��¡
			{
				m_EnchantressFSM.ChangeState(L"Enchantress_UpAttackSkillCharging");
			}
			else if (FLOAT4(1200.f, 1375.f) == m_MoveTargetPos || FLOAT4(80.f, 1375.f) == m_MoveTargetPos) // ��,��� ��ų��¡
			{
				m_EnchantressFSM.ChangeState(L"Enchantress_AttackSkillCharging");
			}
		}
		return;
	}

	m_LerpStartPos = GetPosition();
	m_LerpStartMove = true;
}

// ���� ��ų ���� ����(��,��)
void Enchantress_FinalBoss::AttackSkillChargingState_MovePosCheck()
{

}

// ���� ��ų ���� ����(�Ʒ�)
void Enchantress_FinalBoss::DownAttackSkillChargingState_MovePosCheck()
{

}

// ���� ��ų ���� ����(��)
void Enchantress_FinalBoss::UpAttackSkillChargingState_MovePosCheck()
{

}

// ���� ��ƿ �߻� ����(��,��)
void Enchantress_FinalBoss::AttackSkillShotState_MovePosCheck()
{
	if (true == m_AniEnchantress->IsEnd())
	{
		// �߻�ü ����
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

		// 4�� �߻������� Idle���·� ���ư���
		// �ƴϸ� ���� ���·� �� ��ȯ�Ѵ�.
		if (3 == m_iBossAttackSkillCnt)
		{
			m_EnchantressFSM.ChangeState(L"Enchantress_Idle");
			m_iBossAttackSkillCnt = 0;
		}
		else
		{
			// 4�� �߻��߿� �ִϸ��̼� End�� �Ǵ��ϱ� ������ �ִϸ��̼� ����
			ChangeAniMation(L"Boss_Idle");

			// ���� ��ȯ
			m_EnchantressFSM.ChangeState(L"Enchantress_BasicAttackSkillShot");
			m_iBossAttackSkillCnt++;
		}
	}
}

// ���� ��ƿ �߻� ����(�Ʒ�)
void Enchantress_FinalBoss::DownAttackSkillShotState_MovePosCheck()
{
	if (true == m_AniEnchantress->IsEnd())
	{
		// �߻�ü ����
		Enchantress_FinalBoss_AttackSkill* NewAttackSkill = GetScene()->CreateActor<Enchantress_FinalBoss_AttackSkill>();
		NewAttackSkill->SetFirstMoveDirect(GlobalValue::BasicMoveType::Down);

		// �÷��̾ �� ���� ���������� �������� �˾Ƴ���.
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

		// 4�� �߻������� Idle���·� ���ư���
		// �ƴϸ� ���� ���·� �� ��ȯ�Ѵ�.
		// �ʱⰪ 0
		if (3 == m_iBossDownAttackSkillCnt)
		{
			m_EnchantressFSM.ChangeState(L"Enchantress_Idle");
			m_iBossDownAttackSkillCnt = 0;
		}
		else
		{
			// ���� ��ȯ
			m_EnchantressFSM.ChangeState(L"Enchantress_DownAttackSkillShotMove");
			m_iBossDownAttackSkillCnt++;
		}
	}
}

// ���� ��ƿ �߻� ����(��)
void Enchantress_FinalBoss::UpAttackSkillShotState_MovePosCheck()
{
	if (true == m_AniEnchantress->IsEnd())
	{
		// �߻�ü ����
		Enchantress_FinalBoss_AttackSkill* NewAttackSkill = GetScene()->CreateActor<Enchantress_FinalBoss_AttackSkill>();
		NewAttackSkill->SetFirstMoveDirect(GlobalValue::BasicMoveType::Up);

		// �÷��̾ �� ���� ���������� �������� �˾Ƴ���.
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

		// 4�� �߻������� Idle���·� ���ư���
		// �ƴϸ� ���� ���·� �� ��ȯ�Ѵ�.
		// �ʱⰪ 0
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

// ���� ��ų �߻��� �̵� ����(�Ʒ��ι߻���)
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

// ���� ��ų �߻��� �̵� ����(���ι߻���)
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

// ���� ��ų ���� ����
void Enchantress_FinalBoss::RegenSkillChargingState_MovePosCheck()
{
	// �����Ϸ�� ������ų������Ʈ ����
	// BrokenTile �ڷᱸ���� x���� �������� ����
	if (true == m_AniEnchantress->IsEnd())
	{
		// �ִ� 4�� ���� ��ǥ ����
		for (int x = 0; x < 5; x++)
		{
			int RandomIndex = rand() % m_BrokenObject.size();

			// ������ų �ʱ� ��ġ�� ������ؼ� �̹����� Ÿ���� �����Ѵ�.
			if (nullptr == m_BrokenObject[RandomIndex].back())
			{
				x--;
				continue;
			}
			else if (nullptr != m_BrokenObject[RandomIndex].back())
			{
				// ���� BrokenObject �ڷᱸ���� Y�� ������ �������� ��ġ����
				// +2 �ε����� ��ġ�� ���ϰ�(�� Ÿ���� ũ�� 32.f)
				EnchantressBrokenTile* LastTile = m_BrokenObject[RandomIndex].back();
				FLOAT4 CreatePos = FLOAT4(LastTile->GetPosition().x, LastTile->GetPosition().y + 64.f);

				// �Ѱ��� Ÿ�ϸ�ŭ�� ũ�⸦ ���� ����
				// 4���� ������ų�� �����Ѵ�.
				for (int y = 0; y < 4; y++)
				{
					// ���� ��ġ ����
					CreatePos.y += 32.f;

					// 4���� ������ų ����
					Enchantress_FinalBoss_RegenSkill* NewRegenSkill = GetScene()->CreateActor<Enchantress_FinalBoss_RegenSkill>();
					NewRegenSkill->SetPosition(CreatePos);

					// �ش� ������ Ÿ�� �ε����� �����Ѵ�.(���� ������Ҷ� ���)
					NewRegenSkill->SetTargeIndex({ RandomIndex, y });
				}
			}
		}

		// ��� ���� �Ϸ��ϰ� ���� �����·� ��ȯ�Ѵ�.
		m_EnchantressFSM.ChangeState(L"Enchantress_BlockRegetSkillShotIdle");
	}
}

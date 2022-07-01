#include "Enchantress_FinalBoss.h"
#include "Enchantress_ShovelKnight.h"

// ���(����) ����
void Enchantress_FinalBoss::IdleState_StateCheck()
{
	// �� ���� �÷��̾� ��ġ�� �˾Ƴ���.
	// �÷��̾ ���ʿ� ��ġ�ϸ� �������� �̵�
	// �÷��̾ �����ʿ� ��ġ�ϸ� ���������� �̵�
	// ��, �������� ���� �̵��ϴ��� �Ʒ��� �̵��ϴ��� �Ǵ� ��,�Ʒ� �̵����� �̵����� ��������.
	// ����, �� ���� ������ �ð����� �ֱ� ���ؼ� ��ŸŸ������ ī��Ʈ�Ѵ�.
	// ���⼭ �̵������ ��ǥ������ �������� ���¸� ��ȯ�Ѵ�.
	m_fPatternStartTime -= SGameEngineTimer::FDeltaTime();
	if (0.0f >= m_fPatternStartTime)
	{
		// �� ���� �÷��̾� ��ġ�� �˾Ƴ��� �̵������� ��������.
		FLOAT4 MyPos = GetPosition() - GlobalValue::FinalStage_MainPlayer->GetPosition();
		MyPos.Normalize();
		if (0.0f >= MyPos.x) // �����̸� �÷��̾�� ���� �����ʿ� ��ġ
		{
			// �׷��Ƿ� ���� �������� �̵�����
			m_MoveDir = GlobalValue::BasicMoveType::Right;
		}
		else // ����̸� �÷��̾�� ���� ���ʿ� ��ġ
		{
			// �׷��Ƿ� ���� ������ �̵�����
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}

		// �̵������� �������� ���� �̵����� �Ʒ��� �̵����� ��,�Ʒ� ���� �̵����� �������� ���Ѵ�.
		int RandomPattern = rand() % 3;
		if (GlobalValue::BasicMoveType::Right == m_MoveDir)
		{
			if (0 == RandomPattern)             // ���� �̵�
			{
				m_MoveTargetPos = FLOAT4(1200.f, 1225.f);
			}
			else if (1 == RandomPattern)      // �Ʒ��� �̵�
			{
				m_MoveTargetPos = FLOAT4(1200.f, 1660.f);
			}
			else if (2 == RandomPattern)      // �� �̵�
			{
				m_MoveTargetPos = FLOAT4(1200.f, 1375.f);
			}
		}
		else if (GlobalValue::BasicMoveType::Left == m_MoveDir)
		{
			if (0 == RandomPattern)             // ���� �̵�
			{
				m_MoveTargetPos = FLOAT4(80.f, 1225.f);
			}
			else if (1 == RandomPattern)      // �Ʒ��� �̵�
			{
				m_MoveTargetPos = FLOAT4(80.f, 1660.f);
			}
			else if (2 == RandomPattern)      // �� �̵�
			{
				m_MoveTargetPos = FLOAT4(80.f, 1375.f);
			}
		}

		// �ð� �ʱ�ȭ
		m_fPatternStartTime = 1.f;

		// ��ǥ����, �̵������� �������� ������ȯ
		m_EnchantressFSM.ChangeState(L"Enchantress_Move");

		// �ٴڿ�����Ʈ �������� �����̸� ������ȯ
		// ������ Ÿ�ϸ��� ��ų�� �����Ѵ�.
		if (false == m_bRegenSkilling) // ������ ������ų �ߵ����� �ƴҶ��� üũ
		{
			BrokenTileObjectCheck();
		}
	}
}

// �̵� ����
void Enchantress_FinalBoss::MoveState_StateCheck()
{

}

// ���� ��ų ���� ����(��,��)
void Enchantress_FinalBoss::AttackSkillChargingState_StateCheck()
{
	if (true == m_AniEnchantress->IsEnd())
	{
		m_EnchantressFSM.ChangeState(L"Enchantress_BasicAttackSkillShot");
	}
}

// ���� ��ų ���� ����(�Ʒ�)
void Enchantress_FinalBoss::DownAttackSkillChargingState_StateCheck()
{
	if (true == m_AniEnchantress->IsEnd())
	{
		m_EnchantressFSM.ChangeState(L"Enchantress_DownAttackSkillShot");
	}
}

// ���� ��ų ���� ����(��)
void Enchantress_FinalBoss::UpAttackSkillChargingState_StateCheck()
{
	if (true == m_AniEnchantress->IsEnd())
	{
		m_EnchantressFSM.ChangeState(L"Enchantress_UpAttackSkillShot");
	}
}

// ���� ��ƿ �߻� ����(��,��)
void Enchantress_FinalBoss::AttackSkillShotState_StateCheck()
{

}

// ���� ��ƿ �߻� ����(�Ʒ�)
void Enchantress_FinalBoss::DownAttackSkillShotState_StateCheck()
{

}

// ���� ��ƿ �߻� ����(��)
void Enchantress_FinalBoss::UpAttackSkillShotState_StateCheck()
{

}

// ���� ��ų �߻��� �̵� ����(�Ʒ��ι߻���)
void Enchantress_FinalBoss::DownAttackSkillShotMoveState_StateCheck()
{
	// ����ġ�� Ÿ����ġ�� �����ϸ� ���� ü����
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

// ���� ��ų �߻��� �̵� ����(���ι߻���)
void Enchantress_FinalBoss::UpAttackSkillShotMoveState_StateCheck()
{
	// ����ġ�� Ÿ����ġ�� �����ϸ� ���� ü����
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

// ���� ��ų ���� ����
void Enchantress_FinalBoss::RegenSkillChargingState_StateCheck()
{

}

#include "BlackKnight.h"

// �⺻ �̵� üũ
void BlackKnight::MoveStateCheck()
{
	// �ȼ�üũ�� �Ѵ�.
	BlackKnightPixelCheck();

	// �̵��������� ������ ���� ������ ������ ��ȯ�Ѵ�.
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		// ���� �̵����̶�� ���� �ȼ� üũ�Ͽ� ������ȯ
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MoveDir = GlobalValue::BasicMoveType::Right;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		// ������ �̵����̶�� ������ �ȼ�üũ�Ͽ� ������ȯ
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}
	}

	// �÷��̾�� �����Ÿ��� �Ǹ� ���� ��������
	// �������� ���� �����Ѵ�. 
	FLOAT4 StateDist = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	if (200.f >= FLOAT4::Len2D(StateDist))
	{
		m_RandomState = (rand() % 2) + 1;

		if (m_PrevRandomState != m_RandomState) // �������ϰ� ������ ���� �������
		{
			switch (m_RandomState)
			{
				case 1:
				{
					m_BlackKnightFSM.ChangeState(L"BlackKnight_JumpAttack");
					break;
				}

				case 2:
				{
					m_BlackKnightFSM.ChangeState(L"BlackKnight_SkillCharging");
					break;
				}
			}

			// �������� ����
			m_PrevRandomState = m_RandomState;
		}
	}
}

// �˹� üũ
void BlackKnight::KnockBackStateCheck()
{
	// �ȼ�üũ�� �Ѵ�.
	BlackKnightPixelCheck();

	// �̵��������� ������ ���� ������ m_MovePos.x�� '0.f'�� �ȴ�.
	if (GlobalValue::BasicMoveType::Left == m_KnockBackMoveDir)
	{
		// ���� �̵����̶�� ���� �ȼ� üũ�Ͽ� ������ȯ
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_KnockBackMoveDir)
	{
		// ������ �̵����̶�� ������ �ȼ�üũ�Ͽ� m_MovePos.x�� '0.f'�� �ȴ�.
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
	}

	// �ٴڿ� ������ �˹��� �����ϸ� ���¸� �����Ѵ�.
	if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		// KnockBack Pos���� ��� �ʱ�ȭ
		m_KnockBackMoveDir = GlobalValue::BasicMoveType::None;
		m_KnockBackPos = FLOAT4::ZERO;
		m_KnockBackPower = FLOAT4::ZERO;
		m_KnockBackGravityPower = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		// ���º���
		m_BlackKnightFSM.ChangeState(L"BlackKnight_Idle");
	}
}

// ������ üũ
void BlackKnight::BackJumpStateCheck()
{
	// �ȼ�üũ�� �Ѵ�.
	BlackKnightPixelCheck();

	// �̵��������� ������ ���� ������ m_MovePos.x�� '0.f'�� �ȴ�.
	if (GlobalValue::BasicMoveType::Left == m_BackJumpMoveDir)
	{
		// ���� �̵����̶�� ���� �ȼ� üũ�Ͽ� ������ȯ
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_BackJumpMoveDir)
	{
		// ������ �̵����̶�� ������ �ȼ�üũ�Ͽ� m_MovePos.x�� '0.f'�� �ȴ�.
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
	}

	// �ٴڿ� ������ �������� �����ϸ� ���¸� �����Ѵ�.
	if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		// KnockBack Pos���� ��� �ʱ�ȭ
		m_BackJumpPos = FLOAT4::ZERO;
		m_BackJumpPower = FLOAT4::ZERO;
		m_BackJumpGravityPower = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		// ��������� �÷��̾���� �Ÿ��� üũ�Ͽ� ��Ȳ�� ���� ���º���
		FLOAT4 StateDist = GetPosition() - GlobalValue::MainPlayer->GetPosition();
		if (50.f >= FLOAT4::Len2D(StateDist))
		{
			m_BlackKnightFSM.ChangeState(L"BlackKnight_NomalAttack");
		}
		else
		{
			m_BlackKnightFSM.ChangeState(L"BlackKnight_Laugh");
		}
	}
}

// �������ݽ��� üũ
void BlackKnight::JumpAttackStateCheck()
{
	// �ȼ�üũ�� �Ѵ�.
	BlackKnightPixelCheck();

	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		// ���� �̵����̶�� ���� �ȼ� üũ�Ͽ� ������ȯ
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
			m_MoveDir = GlobalValue::BasicMoveType::Right;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		// ������ �̵����̶�� ������ �ȼ�üũ�Ͽ� m_MovePos.x�� '0.f'�� �ȴ�.
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}
	}
}

void BlackKnight::JumpAttackEndCheck()
{
	// �ȼ�üũ�� �Ѵ�.
	BlackKnightPixelCheck();

	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		// ���� �̵����̶�� ���� �ȼ� üũ�Ͽ� ������ȯ
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
			m_MoveDir = GlobalValue::BasicMoveType::Right;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		// ������ �̵����̶�� ������ �ȼ�üũ�Ͽ� m_MovePos.x�� '0.f'�� �ȴ�.
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}
	}

	// �ٴڿ� ������ ���� ����
	if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		// Pos���� ��� �ʱ�ȭ
		m_JumpAttackPos = FLOAT4::ZERO;
		m_JumpAttackPower = FLOAT4::ZERO;
		m_JumpAttackGravityPower = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		// 4�� �ݺ��� ������ Idle����
		// 4�� �ݺ��� �ȳ������¸� JumpAttack����
		if (4 == m_JumpAttackCnt)
		{
			// ���������� ���� �� �÷��̾���� �Ÿ��� 50�����̸� �������� ���º���
			// �ƴϸ� �����·� ���º����Ѵ�.
			FLOAT4 StateDist = GetPosition() - GlobalValue::MainPlayer->GetPosition();
			if (50.f >= FLOAT4::Len2D(StateDist))
			{
				m_BlackKnightFSM.ChangeState(L"BlackKnight_BackJump");
			}
			else
			{
				m_BlackKnightFSM.ChangeState(L"BlackKnight_Idle");
			}

			m_JumpAttackCnt = 0;
		}
		else
		{
			m_BlackKnightFSM.ChangeState(L"BlackKnight_JumpAttack");
			m_JumpAttackCnt++;
		}
	}
}

void BlackKnight::DeathStateCheck()
{
	// �ȼ�üũ�� �Ѵ�.
	BlackKnightPixelCheck();

	if (GlobalValue::BasicMoveType::Left == m_DeathMoveDir)
	{
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_DeathMoveDir)
	{
		if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right] ||
			RGB(255, 255, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
	}

	// �ٴڿ� ������ ���� ����
	if (RGB(0, 0, 0) == m_iBossCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		// Pos���� ��� �ʱ�ȭ
		m_DeathPos = FLOAT4::ZERO;
		m_DeathPower = FLOAT4::ZERO;
		m_DeathGravityPower = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		m_BlackKnightFSM.ChangeState(L"BlackKnight_DeathMotion");
	}
}

#include "Enchantress_ShovelKnight.h"
#include <SGameEngineInput.h>

// ������ ã���� ������ ����
void Enchantress_ShovelKnight::BossFindIDLE_StateCheck()
{
	// �̵� üũ
	if (true == SGameEngineInput::IsPress(L"LEFT") ||
		true == SGameEngineInput::IsPress(L"RIGHT"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_BossFindMOVE");
	}
}

// ������ ã������ �̵��ϴ� ����
void Enchantress_ShovelKnight::BossFindMOVE_StateCheck()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	// �̵����⺰ �ȼ�üũ�� �ο��Ѵ�.
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		// �������� ������ ����Ұ�
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		// �������� ������ ����Ұ�
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
	}

	// Ű�� �������� IDLE���·� ��ȯ�ȴ�.
	if (true == SGameEngineInput::IsUp(L"LEFT") || true == SGameEngineInput::IsUp(L"RIGHT"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_BossFindIDLE");
		return;
	}

	// ���� ��ġ�� ������ġ�̸� ���� ����
	if (GetPosition().x >= m_PlayerAppearPos.x)
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_CamLerp");
	}
}

// ���(����) ����
void Enchantress_ShovelKnight::Idle_StateCheck()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	// �̵� üũ
	if (true == SGameEngineInput::IsPress(L"PLAYER_LEFT") ||
		true == SGameEngineInput::IsPress(L"PLAYER_RIGHT"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_Move");
	}

	// ���� üũ
	if (true == SGameEngineInput::IsDown(L"PLAYER_JUMP"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_Jump");
	}

	// �⺻���� üũ
	if (true == SGameEngineInput::IsDown(L"PLAYER_DEFAULTATTACK"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_Attack");
	}
}

// �̵� ���� 
void Enchantress_ShovelKnight::Move_StateCheck()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	// �̵����⺰ �ȼ�üũ�� �ο��Ѵ�.
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		// �������� ������ ����Ұ�
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		// �������� ������ ����Ұ�
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
	}

	// Ű�� �������� IDLE���·� ��ȯ�ȴ�.
	if (true == SGameEngineInput::IsUp(L"PLAYER_LEFT") || true == SGameEngineInput::IsUp(L"PLAYER_RIGHT"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_None");
		return;
	}

	// �̵��� AttackŰ�� ������ Attack ���·� ����
	if (true == SGameEngineInput::IsDown(L"PLAYER_DEFAULTATTACK"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_Attack");
	}

	// �̵��� JumpŰ�� ������ Jump ���·� ����
	if (true == SGameEngineInput::IsDown(L"PLAYER_JUMP"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_Jump");
	}
}

// ���� ����
void Enchantress_ShovelKnight::Jump_StateCheck()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	// ���⿡���� �ȼ�üũ
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		// �������� ������ ����Ұ�
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		// �������� ������ ����Ұ�
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
	}

	// �������� ������ȯ
	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_EnchantressPlayerSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

		m_MovePos.y = 0.0f;
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_None");
	}

	// ������ AttackŰ�� ������ Attack ���·� ����
	if (true == SGameEngineInput::IsDown(L"PLAYER_DEFAULTATTACK"))
	{
		// ����� ������ ����ؼ� �������¸� �����ϱ� ���� Flag����
		m_bJumping = true;
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_Attack");
	}

	// ������ LADDERDOWN Key�� Press�ҽ� ��� ����
	if (true == SGameEngineInput::IsPress(L"PLAYER_LADDERDOWN"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_JumpAttack");
	}
}

// ���� ���� ����
void Enchantress_ShovelKnight::JumpAttack_StateCheck()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	// �������� ������ȯ
	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_EnchantressPlayerSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

		m_MovePos.y = 0.0f;
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_None");
	}

	// ���� �������϶� Attack ���� �������û��� ����
	if (true == SGameEngineInput::IsDown(L"PLAYER_DEFAULTATTACK"))
	{
		m_bJumping = true;
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_Attack");
	}
}

// ���������� ������Ʈ�� �浹 ����
void Enchantress_ShovelKnight::JumpAttackCol_StateCheck()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	// ���� �������϶� Attack ���� �������û��� ����
	if (true == SGameEngineInput::IsDown(L"PLAYER_DEFAULTATTACK"))
	{
		m_bJumping = true;
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_Attack");
	}
}

// �˹� ����
void Enchantress_ShovelKnight::KnockBack_StateCheck()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	// �̵������� �ݴ��� �ȼ�üũ
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		// �������� ������ ����Ұ�
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
			m_DirectPos = FLOAT4::ZERO;
		}
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		// �������� ������ ����Ұ�
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
			m_DirectPos = FLOAT4::ZERO;
		}
	}

	// �˹��Ŀ��� 0.0f �̻��̵Ǹ� �ٴ� �浹ü On
	if (0.0f <= m_KnockBackPower.y)
	{
		m_PlayerBotCol->On();
	}
}


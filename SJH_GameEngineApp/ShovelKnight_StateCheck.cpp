#include "ShovelKnight.h"
#include "DeathScreen.h"
#include "BlackKnight.h"
#include "SGameCore.h"

// ���(����)���� üũ
void ShovelKnight::IdleState_Check()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	// �ٴ��� �������� �ƴϰ� �Ǹ� Falling���·� ����
	if (RGB(0, 0, 0) != m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] &&
		RGB(0, 0, 255) != m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_MovePos.y = 0.0f;
		m_ShovelKnightFSM.ChangeState(L"Player_Falling");
	}

	// �̵� üũ
	if (true == SGameEngineInput::IsPress(L"LEFT") ||
		true == SGameEngineInput::IsPress(L"RIGHT"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_Move");
	}

	// ���� üũ
	if (true == SGameEngineInput::IsDown(L"JUMP"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_Jump");
	}

	// �⺻���� üũ
	if (true == SGameEngineInput::IsDown(L"DEFAULTATTACK"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_Attack");
	}

	// ��ٸ�üũ
	if (true == m_bLadderCollision)
	{
		if (true == SGameEngineInput::IsPress(L"LADDERUP") ||
			true == SGameEngineInput::IsPress(L"LADDERDOWN"))
		{
			m_ShovelKnightFSM.ChangeState(L"Player_Ladder");
		}
	}
}

// Falling ���� üũ
void ShovelKnight::FallingState_Check()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	// �ٴ��� �������̸� DeathScreen On
	if (RGB(255, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] && false == m_bInvincibility)
	{
		m_MovePos.y = 0.0f;
		GlobalValue::PlayerDeathScreen->On();
	}

	// �ٴ��� �������� ������ None���·� ����
	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] ||
		RGB(0, 0, 255) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		// ���� ȿ���� ���
		m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}

	// Falling ������ LADDERDOWN Ű�� ������ ���� ����
	if (true == SGameEngineInput::IsPress(L"LADDERDOWN"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_JumpAttack");
	}
}

// �⺻�̵� ���� üũ
void ShovelKnight::MoveState_Check()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	if (true == m_bDirtBlockCollision)
	{
		// �����������δ� �̵��Ұ�
		// ������ �ٲ�� �̵�����
		if (m_MoveDir == m_PrevMoveDir)
		{
			m_MovePos.x = 0.f;
		}
		else
		{
			m_bDirtBlockCollision = false;
		}
	}

	// �ٴ��� �������̸� ����.y�� 0.0�� �Ǿ� �������� �ʴ´�.
	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] ||
		RGB(0, 0, 255) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_MovePos.y = 0.0f;
	}

	// �̵����⺰ �ȼ�üũ�� �ο��Ѵ�.
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		// �������� ������ ����Ұ�
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
		// �ʷϻ��� ������ ī�޶� ����
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_bWallCollision = true;
		}
		// ����Ÿ�� ������ ������ ����
		if (RGB(255, 0, 255) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_bWallCollision = true;
			m_bFinalBossRoom = true;
		}
		// ������� ������ ��ü����(�� ���� óġ�ؾߵ�)
		if (RGB(255, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			//if (true == GlobalValue::FinalBoss->IsDeath())
			if(true == m_bFinalBossDeath)
			{
				SGameCore::SceneManager.ChangeScene(L"LevelMap");
			}
		}
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		// �������� ������ ����Ұ�
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
		// �ʷϻ��� ������ ī�޶� ����
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_bWallCollision = true;
		}
		// ����Ÿ�� ������ ������ ����
		if (RGB(255, 0, 255) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_bWallCollision = true;
			m_bFinalBossRoom = true;
		}
		// ������� ������ ��ü����(�� ���� óġ�ؾߵ�)
		if (RGB(255, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			//if (true == GlobalValue::FinalBoss->IsDeath())
			if (true == m_bFinalBossDeath)
			{
				SGameCore::SceneManager.ChangeScene(L"LevelMap");
			}
		}
	}

	// �����ȼ��� �Ķ����� ������ ��ٸ��� Ż�� ����
	if (RGB(0, 0, 255) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Center])
	{
		m_bLadderCollision = true;
	}

	// Ű�� �������� IDLE���·� ��ȯ�ȴ�.
	if (true == SGameEngineInput::IsUp(L"LEFT") || true == SGameEngineInput::IsUp(L"RIGHT"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_None");
		return;
	}

	// �̵��� AttackŰ�� ������ Attack ���·� ����
	if (true == SGameEngineInput::IsDown(L"DEFAULTATTACK"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_Attack");
	}

	// �̵��� JumpŰ�� ������ Jump ���·� ����
	if (true == SGameEngineInput::IsDown(L"JUMP"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_Jump");
	}

	// �̵��� LADDERUP or LADDERDOWN Ű�� ������ ��ٸ����·� ����
	if (true == m_bLadderCollision)
	{
		if (true == SGameEngineInput::IsPress(L"LADDERUP") ||
			true == SGameEngineInput::IsPress(L"LADDERDOWN"))
		{
			m_ShovelKnightFSM.ChangeState(L"Player_Ladder");
		}
	}
}

// ��ٸ� ���� üũ
void ShovelKnight::LadderMoveState_Check()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	// �̵����⺰ �ȼ�üũ�� �ο��Ѵ�.
	if (m_LadderPrevMoveDir == GlobalValue::BasicMoveType::Up)
	{
		// �ʷϻ��� ������ ī�޶� ����
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Top])
		{
			m_bWallCollision = true;
		}
	}
	else if (m_LadderPrevMoveDir == GlobalValue::BasicMoveType::Down)
	{
		// �ʷϻ��� ������ ī�޶� ����
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			m_bWallCollision = true;
		}
	}

	// �����ȼ��� ����� �Ǹ� ���º���
	if (RGB(255, 255, 255) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Center])
	{
		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}

	// ���� ������ ���º���
	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}

	// 
	if (true == SGameEngineInput::IsDown(L"JUMP"))
	{
		if (true == SGameEngineInput::IsPress(L"LEFT"))
		{
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}
		else if (true == SGameEngineInput::IsPress(L"RIGHT"))
		{
			m_MoveDir = GlobalValue::BasicMoveType::Right;
		}
		m_ShovelKnightFSM.ChangeState(L"Player_LadderJump");
	}
}

// ��ٸ� �̵��� ���� ���� üũ
void ShovelKnight::LadderJumpState_Check()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0;
		}
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			// ���� ȿ���� ���
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

			m_bLadderCollision = false;
			m_ShovelKnightFSM.ChangeState(L"Player_None");
		}
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			m_bWallCollision = true;
			m_ShovelKnightFSM.ChangeState(L"Player_None");
		}
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0;
		}
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			// ���� ȿ���� ���
			m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

			m_bLadderCollision = false;
			m_ShovelKnightFSM.ChangeState(L"Player_None");
		}
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			m_bWallCollision = true;
			m_ShovelKnightFSM.ChangeState(L"Player_None");
		}
	}

	// ��������Ű�� ������ ������������ ���º���
	if (true == SGameEngineInput::IsPress(L"LADDERDOWN"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_JumpAttack");
	}
}

// ���� ���� üũ
void ShovelKnight::JumpState_Check()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	// �ٴ��� �������̸� DeathScreen On
	if (RGB(255, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] && false == m_bInvincibility)
	{
		m_MovePos.y = 0.0f;
		GlobalValue::PlayerDeathScreen->On();
	}

	if (true == m_bDirtBlockCollision)
	{
		// �����������δ� �̵��Ұ�
		// ������ �ٲ�� �̵�����
		if (m_MoveDir == m_PrevMoveDir)
		{
			m_MovePos.x = 0.f;
		}
		else
		{
			m_bDirtBlockCollision = false;
		}
	}

	// �ٴڸ� üũ
	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] ||
		RGB(0, 0, 255) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_JumpGravityPowerPos = FLOAT4::ZERO;
		m_JumpPos = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		// ���� ȿ���� ���
		m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}

	// �Ӹ� üũ
	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Top])
	{
		m_JumpGravityPowerPos = FLOAT4::ZERO;
		m_JumpPos = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		m_ShovelKnightFSM.ChangeState(L"Player_Falling");
	}

	// ���⿡���� �ȼ�üũ
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		// �������� ������ ����Ұ�
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
		// �ʷϻ��� ������ ī�޶� ����
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_bWallCollision = true;
		}
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		// �������� ������ ����Ұ�
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
		// �ʷϻ��� ������ ī�޶� ����
		if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_bWallCollision = true;
		}
	}

	// ������ AttackŰ�� ������ Attack ���·� ����
	if (true == SGameEngineInput::IsDown(L"DEFAULTATTACK"))
	{
		// ����� ������ ����ؼ� �������¸� �����ϱ� ���� Flag����
		m_bJumping = true;

		m_ShovelKnightFSM.ChangeState(L"Player_Attack");
	}

	// ������ LADDERDOWN Key�� Press�ҽ� ��� ����
	if (true == SGameEngineInput::IsPress(L"LADDERDOWN"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_JumpAttack");
	}
}

// ���� ���� ���� üũ
void ShovelKnight::JumpAttackState_Check()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	// �ٴ��� �������̸� DeathScreen On
	if (RGB(255, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] && false == m_bInvincibility)
	{
		m_MovePos.y = 0.0f;
		GlobalValue::PlayerDeathScreen->On();
	}

	if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_bWallCollision = true;
		m_LadderPrevMoveDir = GlobalValue::BasicMoveType::Down;
	}

	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_JumpGravityPowerPos = FLOAT4::ZERO;
		m_JumpPos = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		// ���� ȿ���� ���
		m_ActionSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}

	// ���� �������϶� Attack ���� �������û��� ����
	if (true == SGameEngineInput::IsDown(L"DEFAULTATTACK"))
	{
		m_bJumping = true;
		m_ShovelKnightFSM.ChangeState(L"Player_Attack");
	}
}

// ���� ����(Object or Monster �浹)
void ShovelKnight::JumpAttackColState_Check()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	if (RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_bWallCollision = true;
		m_LadderPrevMoveDir = GlobalValue::BasicMoveType::Down;
	}

	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_JumpGravityPowerPos = FLOAT4::ZERO;
		m_JumpPos = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}

	// ���� �������϶� Attack ���� �������û��� ����
	if (true == SGameEngineInput::IsDown(L"DEFAULTATTACK"))
	{
		m_bJumping = true;
		m_ShovelKnightFSM.ChangeState(L"Player_Attack");
	}
}

// �˹� ���� üũ
void ShovelKnight::KnockBackState_Check()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_KnockBackPos = FLOAT4::ZERO;
		m_KnockBackPower = FLOAT4::ZERO;
		m_KnockBackGravityPowerPos = FLOAT4::ZERO;
		m_GravityPos = FLOAT4::ZERO;
		m_JumpPos = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;
		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}

	// �ٴ��� �������̸� DeathScreen On
	if (RGB(255, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] && false == m_bInvincibility)
	{
		m_MovePos.y = 0.0f;
		GlobalValue::PlayerDeathScreen->On();
	}

	// �̵����� �ݴ�������� �ȼ�üũ
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right] ||
			RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
			m_DirectPos = FLOAT4::ZERO;
		}
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left] ||
			RGB(0, 255, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
			m_DirectPos = FLOAT4::ZERO;
		}
	}
}


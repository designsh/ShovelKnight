#include "ShovelKnight.h"

// ������Ʈ �浹 �� ������ üũ
void ShovelKnight::RideIdleState_Check()
{
	// �̵� üũ
	if (true == SGameEngineInput::IsPress(L"LEFT") ||
		true == SGameEngineInput::IsPress(L"RIGHT"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_RideMove");
	}

	// ���� üũ
	if (true == SGameEngineInput::IsDown(L"JUMP"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_Jump");
	}

	// �⺻���� üũ
	if (true == SGameEngineInput::IsDown(L"DEFAULTATTACK"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_RideAttack");
	}
}

// ������Ʈ �浹 �� ������� üũ
void ShovelKnight::RideMoveState_Check()
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

	// Ű�� �������� IDLE���·� ��ȯ�ȴ�.
	if (true == SGameEngineInput::IsUp(L"LEFT") || true == SGameEngineInput::IsUp(L"RIGHT"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_RideNone");
		return;
	}

	// �̵��� AttackŰ�� ������ Attack ���·� ����
	if (true == SGameEngineInput::IsDown(L"DEFAULTATTACK"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_RideAttack");
	}

	// �̵��� JumpŰ�� ������ Jump ���·� ����
	if (true == SGameEngineInput::IsDown(L"JUMP"))
	{
		m_ShovelKnightFSM.ChangeState(L"Player_Jump");
	}
}

void RideAttackState_Check()
{

}

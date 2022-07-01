#include "BlackKnight.h"

// �⺻
void BlackKnight::BasicDirectCheck()
{
	// ���� �̵����⿡ ������ �ش�.
	FLOAT4 MyPosOnBasePlayer = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPosOnBasePlayer.Normalize();
	if (0.0f >= MyPosOnBasePlayer.x) // �����̸� �÷��̾�� ���� �����ʿ� ��ġ
	{
		// �׷��Ƿ� ������ �̵�
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}
	else if (0.0f < MyPosOnBasePlayer.x) // ����̸� �÷��̾�� ���� ���ʿ� ��ġ
	{
		// �׷��Ƿ� ���� �̵�
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
}

// �˹�
void BlackKnight::KnockBackDirectCheck()
{
	// �÷��̾�� ���� ��ġ�� ���Ͽ�
	// ���� �÷��̾���� ����ʿ� �ִ��� �˾Ƴ��� �˹� ������ ���Ѵ�.
	FLOAT4 MyPosOnBasePlayer = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPosOnBasePlayer.Normalize();
	if (0.0f > MyPosOnBasePlayer.x) // �����̸� �÷��̾�� ���� �����ʿ� ��ġ
	{
		// �׷��Ƿ� �˹������ ����
		m_KnockBackMoveDir = GlobalValue::BasicMoveType::Left;
	}
	else if (0.0f <= MyPosOnBasePlayer.x) // ����̸� �÷��̾�� ���� ���ʿ� ��ġ
	{
		// �׷��Ƿ� �˹������ ������
		m_KnockBackMoveDir = GlobalValue::BasicMoveType::Right;
	}
}

// �����
void BlackKnight::LaughDirectCheck()
{
	// ���� �̵����⿡ ������ �ش�.
	FLOAT4 MyPosOnBasePlayer = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPosOnBasePlayer.Normalize();
	if (0.0f >= MyPosOnBasePlayer.x) // �����̸� �÷��̾�� ���� �����ʿ� ��ġ
	{
		// �׷��Ƿ� ������ �̵�
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}
	else if (0.0f < MyPosOnBasePlayer.x) // ����̸� �÷��̾�� ���� ���ʿ� ��ġ
	{
		// �׷��Ƿ� ���� �̵�
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
}

// ȸ������
void BlackKnight::BackJumpDirectCheck()
{
	// �����̵����⿡ ������ �����ʴ´�.
	FLOAT4 MyPosOnBasePlayer = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPosOnBasePlayer.Normalize();
	if (0.0f > MyPosOnBasePlayer.x) // �����̸� �÷��̾�� ���� �����ʿ� ��ġ
	{
		m_BackJumpMoveDir = GlobalValue::BasicMoveType::Left;
		m_AniBlackKnight->ChangeAnimation(L"Right_BlackKnight_BackJump");
	}
	else if (0.0f <= MyPosOnBasePlayer.x) // ����̸� �÷��̾�� ���� ���ʿ� ��ġ
	{
		m_BackJumpMoveDir = GlobalValue::BasicMoveType::Right;
		m_AniBlackKnight->ChangeAnimation(L"Left_BlackKnight_BackJump");
	}
}

// ��������
void BlackKnight::JumpAttackDirectCheck()
{
	// ���� �̵����⿡ ������ �ش�.
	FLOAT4 MyPosOnBasePlayer = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPosOnBasePlayer.Normalize();
	if (0.0f >= MyPosOnBasePlayer.x) // �����̸� �÷��̾�� ���� �����ʿ� ��ġ
	{
		// �׷��Ƿ� ������ �̵�
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}
	else if (0.0f < MyPosOnBasePlayer.x) // ����̸� �÷��̾�� ���� ���ʿ� ��ġ
	{
		// �׷��Ƿ� ���� �̵�
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
}

// ���
void BlackKnight::DeathDirectCheck()
{
	FLOAT4 MyPosOnBasePlayer = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPosOnBasePlayer.Normalize();
	if (0.0f > MyPosOnBasePlayer.x)
	{
		m_DeathMoveDir = GlobalValue::BasicMoveType::Left;
		m_AniBlackKnight->ChangeAnimation(L"Right_BlackKnight_BackJump");
	}
	else if (0.0f <= MyPosOnBasePlayer.x)
	{
		m_DeathMoveDir = GlobalValue::BasicMoveType::Right;
		m_AniBlackKnight->ChangeAnimation(L"Left_BlackKnight_BackJump");
	}
}

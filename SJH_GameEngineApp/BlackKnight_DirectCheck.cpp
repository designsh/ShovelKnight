#include "BlackKnight.h"

// 기본
void BlackKnight::BasicDirectCheck()
{
	// 기존 이동방향에 영향을 준다.
	FLOAT4 MyPosOnBasePlayer = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPosOnBasePlayer.Normalize();
	if (0.0f >= MyPosOnBasePlayer.x) // 음수이면 플레이어는 나의 오른쪽에 위치
	{
		// 그러므로 오른쪽 이동
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}
	else if (0.0f < MyPosOnBasePlayer.x) // 양수이면 플레이어는 나의 왼쪽에 위치
	{
		// 그러므로 왼쪽 이동
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
}

// 넉백
void BlackKnight::KnockBackDirectCheck()
{
	// 플레이어와 나의 위치를 비교하여
	// 내가 플레이어기준 어느쪽에 있는지 알아내서 넉백 방향을 정한다.
	FLOAT4 MyPosOnBasePlayer = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPosOnBasePlayer.Normalize();
	if (0.0f > MyPosOnBasePlayer.x) // 음수이면 플레이어는 나의 오른쪽에 위치
	{
		// 그러므로 넉백방향은 왼쪽
		m_KnockBackMoveDir = GlobalValue::BasicMoveType::Left;
	}
	else if (0.0f <= MyPosOnBasePlayer.x) // 양수이면 플레이어는 나의 왼쪽에 위치
	{
		// 그러므로 넉백방향은 오른쪽
		m_KnockBackMoveDir = GlobalValue::BasicMoveType::Right;
	}
}

// 비웃음
void BlackKnight::LaughDirectCheck()
{
	// 기존 이동방향에 영향을 준다.
	FLOAT4 MyPosOnBasePlayer = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPosOnBasePlayer.Normalize();
	if (0.0f >= MyPosOnBasePlayer.x) // 음수이면 플레이어는 나의 오른쪽에 위치
	{
		// 그러므로 오른쪽 이동
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}
	else if (0.0f < MyPosOnBasePlayer.x) // 양수이면 플레이어는 나의 왼쪽에 위치
	{
		// 그러므로 왼쪽 이동
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
}

// 회피점프
void BlackKnight::BackJumpDirectCheck()
{
	// 기존이동방향에 영향을 주지않는다.
	FLOAT4 MyPosOnBasePlayer = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPosOnBasePlayer.Normalize();
	if (0.0f > MyPosOnBasePlayer.x) // 음수이면 플레이어는 나의 오른쪽에 위치
	{
		m_BackJumpMoveDir = GlobalValue::BasicMoveType::Left;
		m_AniBlackKnight->ChangeAnimation(L"Right_BlackKnight_BackJump");
	}
	else if (0.0f <= MyPosOnBasePlayer.x) // 양수이면 플레이어는 나의 왼쪽에 위치
	{
		m_BackJumpMoveDir = GlobalValue::BasicMoveType::Right;
		m_AniBlackKnight->ChangeAnimation(L"Left_BlackKnight_BackJump");
	}
}

// 점프공격
void BlackKnight::JumpAttackDirectCheck()
{
	// 기존 이동방향에 영향을 준다.
	FLOAT4 MyPosOnBasePlayer = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPosOnBasePlayer.Normalize();
	if (0.0f >= MyPosOnBasePlayer.x) // 음수이면 플레이어는 나의 오른쪽에 위치
	{
		// 그러므로 오른쪽 이동
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}
	else if (0.0f < MyPosOnBasePlayer.x) // 양수이면 플레이어는 나의 왼쪽에 위치
	{
		// 그러므로 왼쪽 이동
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
}

// 사망
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

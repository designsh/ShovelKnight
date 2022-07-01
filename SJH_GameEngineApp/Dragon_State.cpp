#include "Dragon.h"
#include "DropGold.h"

// 플레이어 찾는 상태
void Dragon::FindStart()
{
	ChangeAniMation(L"DragonFind");
	m_DragonCol->Off();
}

void Dragon::FindStay()
{
	// 카메라위치와 일정거리 가까워지면
	FLOAT4 Dir = GetCamPosition();

	// Beeto Move Start
	if (1000.0f >= FLOAT4::Len2D(Dir))
	{
		// Move State Change
		m_DragonFSM.ChangeState(L"Dragon_Move");
	}
}

void Dragon::FindEnd()
{
	m_DragonCol->On();
}

// 이동상태
void Dragon::MoveStart()
{
	ChangeAniMation(L"DragonMove");

	// 무브 시작할때의 위치를 가지고있는다.
	m_MoveStartPos = GetPosition();
}

void Dragon::MoveStay()
{
	// 이동한다.
	DirPosCheck();

	// 현재 이동방향이 오른쪽이라면 UpMove State
	// 현재 이동방향이 왼쪽이라면 DownMove State
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		FLOAT4 LeftMoveDist = m_MoveStartPos - m_MaxDist;
		if (LeftMoveDist.x >= GetPosition().x)
		{
			m_DragonFSM.ChangeState(L"Dragon_DownMove");
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		FLOAT4 RightMoveDist = m_MoveStartPos + m_MaxDist;
		if (RightMoveDist.x <= GetPosition().x)
		{
			m_DragonFSM.ChangeState(L"Dragon_UpMove");
		}
	}
}

void Dragon::MoveEnd()
{

}

// 하향이동상태
void Dragon::DownMoveStart()
{
	m_DownStartPos = GetPosition();
}

void Dragon::DownMoveStay()
{
	// 하향이동
	DownPosCheck();

	// 하향완료로 인한 상태변경
	FLOAT4 UpMoveDist = m_DownStartPos + FLOAT4(0.f, 20.f);
	if (UpMoveDist.y <= GetPosition().y)
	{
		m_DragonFSM.ChangeState(L"Dragon_Move");
	}
}

void Dragon::DownMoveEnd()
{
	// 상태변경시 현재무브방향을 바꾼다.
	// 왼쪽이동할때 하향무브하므로 현재 이동방향을 오른쪽으로 바꾼다.
	m_MoveDir = GlobalValue::BasicMoveType::Right;
}

// 상향이동상태
void Dragon::UpMoveStart()
{
	m_UpStartPos = GetPosition();
}

void Dragon::UpMoveStay()
{
	// 상향이동
	UpPosCheck();

	// 상향완료로 인한 상태변경
	FLOAT4 UpMoveDist = m_UpStartPos + FLOAT4(0.f, -20.f);
	if (UpMoveDist.y >= GetPosition().y)
	{
		m_DragonFSM.ChangeState(L"Dragon_Move");
	}
}

void Dragon::UpMoveEnd()
{
	// 오른쪽이동할때 상향무브하므로 현재 이동방향을 왼쪽으로 바꾼다.
	m_MoveDir = GlobalValue::BasicMoveType::Left;
}

// 사망상태
void Dragon::DeathStart()
{
	m_DragonActionSound = SGameEngineSound::Play(L"Plains_Basic_Monster_Death.mp3", false, 0);

	m_AniDragon->ChangeAnimation(L"DieMotion");

	// 몸체충돌체 먼저 사망
	m_DragonCol->Death();

	// 혹시 Blink 효과중이라면 해제
	m_bBlinkImage = false;
	m_fBlinkImageTotalTime = 1.f;
	m_BeShotLeftDragon->Off();
	m_BeShotRightDragon->Off();
}

void Dragon::DeathStay()
{
	if (true == m_AniDragon->IsEnd())
	{
		if (true == m_bDropCoin)
		{
			// 드랍하는 골드가 있다
			DropGold* DropGold1 = GetScene()->CreateActor<DropGold>();
			DropGold1->SetDropGold(10);
			DropGold1->SetMoveSpeed(30.f);
			DropGold1->SetPosition({ GetPosition().x, GetPosition().y - 30.f });
		}

		Death();
	}
}

void Dragon::DeathEnd()
{

}

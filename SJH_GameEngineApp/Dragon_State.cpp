#include "Dragon.h"
#include "DropGold.h"

// �÷��̾� ã�� ����
void Dragon::FindStart()
{
	ChangeAniMation(L"DragonFind");
	m_DragonCol->Off();
}

void Dragon::FindStay()
{
	// ī�޶���ġ�� �����Ÿ� ���������
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

// �̵�����
void Dragon::MoveStart()
{
	ChangeAniMation(L"DragonMove");

	// ���� �����Ҷ��� ��ġ�� �������ִ´�.
	m_MoveStartPos = GetPosition();
}

void Dragon::MoveStay()
{
	// �̵��Ѵ�.
	DirPosCheck();

	// ���� �̵������� �������̶�� UpMove State
	// ���� �̵������� �����̶�� DownMove State
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

// �����̵�����
void Dragon::DownMoveStart()
{
	m_DownStartPos = GetPosition();
}

void Dragon::DownMoveStay()
{
	// �����̵�
	DownPosCheck();

	// ����Ϸ�� ���� ���º���
	FLOAT4 UpMoveDist = m_DownStartPos + FLOAT4(0.f, 20.f);
	if (UpMoveDist.y <= GetPosition().y)
	{
		m_DragonFSM.ChangeState(L"Dragon_Move");
	}
}

void Dragon::DownMoveEnd()
{
	// ���º���� ���繫������� �ٲ۴�.
	// �����̵��Ҷ� ���⹫���ϹǷ� ���� �̵������� ���������� �ٲ۴�.
	m_MoveDir = GlobalValue::BasicMoveType::Right;
}

// �����̵�����
void Dragon::UpMoveStart()
{
	m_UpStartPos = GetPosition();
}

void Dragon::UpMoveStay()
{
	// �����̵�
	UpPosCheck();

	// ����Ϸ�� ���� ���º���
	FLOAT4 UpMoveDist = m_UpStartPos + FLOAT4(0.f, -20.f);
	if (UpMoveDist.y >= GetPosition().y)
	{
		m_DragonFSM.ChangeState(L"Dragon_Move");
	}
}

void Dragon::UpMoveEnd()
{
	// �������̵��Ҷ� ���⹫���ϹǷ� ���� �̵������� �������� �ٲ۴�.
	m_MoveDir = GlobalValue::BasicMoveType::Left;
}

// �������
void Dragon::DeathStart()
{
	m_DragonActionSound = SGameEngineSound::Play(L"Plains_Basic_Monster_Death.mp3", false, 0);

	m_AniDragon->ChangeAnimation(L"DieMotion");

	// ��ü�浹ü ���� ���
	m_DragonCol->Death();

	// Ȥ�� Blink ȿ�����̶�� ����
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
			// ����ϴ� ��尡 �ִ�
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

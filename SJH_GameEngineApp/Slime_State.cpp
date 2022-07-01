#include "Slime.h"

#include "ShovelKnight.h"
#include "DropGold.h"

// 정지상태(대기상태)
void Slime::FindStart()
{
	m_AniSlime->ChangeAnimation(L"SlimeFind");
	m_SlimeCol->Off();
}

void Slime::FindStay()
{
	if (nullptr == GlobalValue::MainPlayer)
	{
		return;
	}

	FLOAT4 Dist = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	if (500.f >= FLOAT4::Len2D(Dist))
	{
		m_SlimeFSM.ChangeState(L"Slime_Move");
	}
}

void Slime::FindEnd()
{
	m_SlimeCol->On();
}

// 이동상태
void Slime::MoveStart()
{
	m_AniSlime->ChangeAnimation(L"SlimeMove");

	// 일정시간 점프공격 상태변경을 위해
	if (0 == m_JumpEventer.IsEventSize())
	{
		m_JumpEventer.CreateTimeEventEnd(m_JumpTime, this, &Slime::JumpAttackChange);
	}

	m_JumpEventer.Reset();
}

void Slime::MoveStay()
{
	// 일정거리 움직이다가 일정시간이 되면 점프모션으로 변경한다.
	DirPosCheck();

	m_JumpEventer.Update();
}

void Slime::MoveEnd()
{

}

// 점프 공격상태
void Slime::JumpAttackStart()
{
	m_AniSlime->ChangeAnimation(L"SlimeMove");

	// 점프 파워설정
	m_JumpPos = FLOAT4::ZERO;
	m_JumpPower = FLOAT4({ 0.0f, -600.0f });

	m_GravityPos = FLOAT4::ZERO;
	m_GravityPower = FLOAT4({ 0.0f, 3000.0f });

	// 플레이어와 나의 위치 비교
	FLOAT4 MyPos = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPos.Normalize();
	if (0.0f >= MyPos.x)
	{
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}
	else
	{
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
}

void Slime::JumpAttackStay()
{
	// 플레이어를 향해서 점프이동한다.
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_Speed * 3.f);
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_Speed * 3.f);
	}

	m_JumpPower += m_GravityPower * SGameEngineTimer::FDeltaTime();
	m_JumpPos = m_JumpPower * SGameEngineTimer::FDeltaTime();

	m_MovePos = m_DirectPos + m_JumpPos;

	// 이때 픽셀체크한다.
	SlimePixcelCol();

	// 점프 픽셀체크 및 벽과 충돌시 방향전환
	JumpAttackCheck();

	MovePosition(m_MovePos);
}

void Slime::JumpAttackEnd()
{

}

// 사망상태
void Slime::DieStart()
{
	m_AniSlime->ChangeAnimation(L"SlimeDie");

	m_SlimeActionSound = SGameEngineSound::Play(L"Plains_Basic_Monster_Death.mp3", false, 0);

	// 혹시 Blink 효과중이라면 해제
	m_bBlinkImage = false;
	m_BeShotSlime->Off();
}

void Slime::DieStay()
{
	if (true == m_AniSlime->IsEnd())
	{
		// 죽으면서 골드를 드랍한다.(5골드)
		DropGold* CreateDropGold5 = GetScene()->CreateActor<DropGold>();
		CreateDropGold5->SetDropGold(5);
		CreateDropGold5->SetMoveSpeed(50.f);
		CreateDropGold5->SetPosition({ GetPosition().x, GetPosition().y - 30.f });

		// 죽으면서 골드를 드랍한다.(10골드)
		DropGold* CreateDropGold10 = GetScene()->CreateActor<DropGold>();
		CreateDropGold10->SetDropGold(10);
		CreateDropGold10->SetMoveSpeed(70.f);
		CreateDropGold10->SetPosition({ GetPosition().x, GetPosition().y - 30.f });

		Death();
	}
}

void Slime::DieEnd()
{

}

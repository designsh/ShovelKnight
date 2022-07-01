#include "Dozedrake.h"

#include "ShovelKnight.h"

// 플레이어 찾는 상태
void Dozedrake::FindStart()
{
	m_AniDozedrake->ChangeAnimation(L"DozedrakeIdle");
	m_DozedrakeHeadCol->Off();
	m_DozedrakeBodyCol->Off();
}

void Dozedrake::FindStay()
{
	if (nullptr == GlobalValue::MainPlayer)
	{
		return;
	}

	FLOAT4 Dist = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	if (700.f >= FLOAT4::Len2D(Dist))
	{
		m_DozedrakeFSM.ChangeState(L"Dozedrake_Idle");
	}
}

void Dozedrake::FindEnd()
{
	m_DozedrakeHeadCol->On();
	m_DozedrakeBodyCol->On();

	// 초기위치를 저장한다(이유 : 백무브할때 Limit설정을 위해)
	m_MaxBackPos = GetPosition();
}

// 대기상태
void Dozedrake::IdleStart()
{
	m_AniDozedrake->ChangeAnimation(L"DozedrakeIdle");
}

void Dozedrake::IdleStay()
{
	if (true == m_AniDozedrake->IsEnd())
	{
		// 공격모션
		m_DozedrakeFSM.ChangeState(L"Dozedrake_AttackStart");
	}
}

void Dozedrake::IdleEnd()
{

}

// 앞으로 이동
void Dozedrake::FrontMoveStart()
{
	m_DozedrakeSound = SGameEngineSound::Play(L"Plains_Dragon_Move.mp3", false, 0);

	m_AniDozedrake->ChangeAnimation(L"DozedrakeFrontMove");
}

void Dozedrake::FrontMoveStay()
{
	// 플레이어와 일정거리이면 이동하지않고 공격모션으로 변경한다.
	FLOAT4 Dir = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	if (500.f >= FLOAT4::Len2D(Dir))
	{
		m_DozedrakeFSM.ChangeState(L"Dozedrake_Idle");
		return;
	}

	MoveCheck();

	if (true == m_AniDozedrake->IsEnd())
	{
		// 기본상태로 이동
		m_DozedrakeFSM.ChangeState(L"Dozedrake_Idle");
	}
}

void Dozedrake::FrontMoveEnd()
{

}

// 뒤로 이동
void Dozedrake::BackMoveStart()
{
	m_DozedrakeSound = SGameEngineSound::Play(L"Plains_Dragon_Move.mp3", false, 0);

	m_AniDozedrake->ChangeAnimation(L"DozedrakeBackMove");
}

void Dozedrake::BackMoveStay()
{
	MoveCheck();

	if (true == m_AniDozedrake->IsEnd())
	{
		// 이때 리밋포지션이면 Flag On
		if (0.0f <= GetPosition().x - m_MaxBackPos.x)
		{
			m_LimitBackMove = true;
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}

		// 기본상태로 이동
		m_DozedrakeFSM.ChangeState(L"Dozedrake_Idle");
	}
}

void Dozedrake::BackMoveEnd()
{

}

// 공격모션 시작(물방울 생성)
void Dozedrake::AttackStartStart()
{
	m_DozedrakeSound = SGameEngineSound::Play(L"Plains_Dragon_Shoot.mp3", false, 0);

	m_AniDozedrake->ChangeAnimation(L"DozedrakeAttack");

	// 시간차로 물방울 생성을 위해 타임이벤터 생성
	if (0 == m_BubbleEvent.IsEventSize())
	{
		m_BubbleEvent.CreateTimeEventEnd(0.1f, this, &Dozedrake::AttackBubbleCreate1);
		m_BubbleEvent.CreateTimeEventEnd(0.3f, this, &Dozedrake::AttackBubbleCreate2);
		m_BubbleEvent.CreateTimeEventEnd(0.5f, this, &Dozedrake::AttackBubbleCreate3);
		m_BubbleEvent.CreateTimeEventEnd(1.0f, this, &Dozedrake::AttackBubbleCreateEnd);
	}

	m_BubbleEvent.Reset();
}

void Dozedrake::AttackStartStay()
{
	m_BubbleEvent.Update();
}

void Dozedrake::AttackStartEnd()
{

}

// 공격모션 종료(일정시간 지나면 애니메이션 변경한다.)
void Dozedrake::AttackComplateStart()
{
	if (0 == m_AttackEndEvent.IsEventSize())
	{
		m_AttackEndEvent.CreateTimeEventEnd(1.f, this, &Dozedrake::AttackComplete);
	}

	m_AttackEndEvent.Reset();
}

void Dozedrake::AttackComplateStay()
{
	m_AttackEndEvent.Update();

	if (true == m_AniDozedrake->IsEnd())
	{
		m_DozedrakeFSM.ChangeState(L"Dozedrake_FrontMove");
	}
}

void Dozedrake::AttackComplateEnd()
{
	
}

// 사망상태
void Dozedrake::DeathStart()
{
	m_DozedrakeSound = SGameEngineSound::Play(L"Plains_Dragon_Death.mp3", false, 0);

	// 모든 충돌체가 죽고, 타이머이벤트를 생성한다.
	m_DozedrakeHeadCol->Death();
	m_DozedrakeBodyCol->Death();

	if (0 == m_DeathEvent.IsEventSize())
	{
		m_DeathEvent.CreateTimeEvent(0.5f, this, &Dozedrake::DeathEffectEnd, &Dozedrake::DeathEffectStart, &Dozedrake::DeathEffectStay);
	}

	m_DeathEvent.Reset();
}

void Dozedrake::DeathStay()
{
	// 타임이벤터를 계속하여 업데이트한다.
	m_DeathEvent.Update();
}

void Dozedrake::DeathEnd()
{

}

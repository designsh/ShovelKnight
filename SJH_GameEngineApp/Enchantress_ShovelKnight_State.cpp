#include "Enchantress_ShovelKnight.h"
#include <SGameEngineInput.h>

#include "FadeInOutActor.h"
#include "SGameCore.h"

// ����ã�� ����(�����Ÿ� �̵��ϸ� ���º���)
void Enchantress_ShovelKnight::BossFindIdleStart()
{
	ChangeAniMation(L"PlayerNone");
}

void Enchantress_ShovelKnight::BossFindIdleStay()
{
	BossFindIDLE_MovePosCheck();

	BossFindIDLE_StateCheck();
}

void Enchantress_ShovelKnight::BossFindIdleEnd()
{

}

// ���� ã�� �������((�����Ÿ� �̵��ϸ� ���º���)
void Enchantress_ShovelKnight::BossFindMoveStart()
{
	ChangeAniMation(L"PlayerMove");
}

void Enchantress_ShovelKnight::BossFindMoveStay()
{
	BossFindMOVE_MovePosCheck();

	BossFindMOVE_StateCheck();
}

void Enchantress_ShovelKnight::BossFindMoveEnd()
{

}

// ī�޶��� ������(ī�޶�� ���͸� ã�´�.)
void Enchantress_ShovelKnight::CamLerpingIdleStart()
{
	ChangeAniMation(L"PlayerBossFind");

	// ī�޶� ������ ���� ���� �� ���� ����
	m_CamMoveDir = GlobalValue::BasicMoveType::Up;
	m_bWallCollision = true;
}

void Enchantress_ShovelKnight::CamLerpingIdleStay()
{
	if (false == m_bWallCollision) // ī�޶� �����Ϸ�� ���� ����
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_None");
	}
}

void Enchantress_ShovelKnight::CamLerpingIdleEnd()
{

}

// ���(����) ����
void Enchantress_ShovelKnight::IdleStart()
{
	ChangeAniMation(L"PlayerNone");
}

void Enchantress_ShovelKnight::IdleStay()
{
	Idle_MovePosCheck();

	Idle_StateCheck();
}

void Enchantress_ShovelKnight::IdleEnd()
{

}

// �⺻�̵� ����(��, ��)
void Enchantress_ShovelKnight::MoveStart()
{
	ChangeAniMation(L"PlayerMove");
}

void Enchantress_ShovelKnight::MoveStay()
{
	Move_MovePosCheck();

	Move_StateCheck();
}

void Enchantress_ShovelKnight::MoveEnd()
{

}

// ���� ����
void Enchantress_ShovelKnight::HighJumpCheckEvent()
{
	if (true == SGameEngineInput::IsPress(L"PLAYER_JUMP"))
	{
		m_JumpPower.y = -800.0f;
	}

	if (m_JumpPower.y <= -800.0f)
	{
		m_JumpPower.y = -800.0f;
	}
}

void Enchantress_ShovelKnight::LowJumpCheckEvent()
{
	if (true == SGameEngineInput::IsPress(L"PLAYER_JUMP"))
	{
		m_JumpPower.y = -400.0f;
	}

	if (m_JumpPower.y <= -400.0f)
	{
		m_JumpPower.y = -400.0f;
	}
}

void Enchantress_ShovelKnight::JumpStart()
{
	m_EnchantressPlayerSound = SGameEngineSound::Play(L"ShovelKnight_JumpStart.mp3", false, 0);

	ChangeAniMation(L"PlayerJumpStart");

	// ����, �߷� ����
	m_JumpPos = FLOAT4::ZERO;
	m_JumpPower = FLOAT4({ 0.0f, -300.0f });
	m_JumpGravityPowerPos = FLOAT4({ 0.0f, 3000.0f });

	// �������������� Ÿ���̺��ͻ���
	if (0 == m_JumpEventer.IsEventSize())
	{
		m_JumpEventer.CreateTimeEventStay(0.1f, this, &Enchantress_ShovelKnight::LowJumpCheckEvent);
		m_JumpEventer.CreateTimeEventStay(0.1f, this, &Enchantress_ShovelKnight::HighJumpCheckEvent);
	}
	m_JumpEventer.Reset();

	// ������ Flag On
	m_bJumping = true;
}

void Enchantress_ShovelKnight::JumpStay()
{
	m_JumpEventer.Update();

	Jump_MovePosCheck();

	Jump_StateCheck();
}

void Enchantress_ShovelKnight::JumpEnd()
{

}

// �������� ����
void Enchantress_ShovelKnight::JumpAttackStart()
{
	ChangeAniMation(L"PlayerJumpAttack");

	// �浹ü ����
	m_JumpAttackCol->SetPivotPos({ 0, -50 });

	// �������ݸ�� �浹ü On
	m_JumpAttackCol->On();

	// 
	m_JumpPos = FLOAT4(0.f, -200.f);
	m_JumpGravityPowerPos = FLOAT4({ 0.0f, 3000.0f });
}

void Enchantress_ShovelKnight::JumpAttackStay()
{
	JumpAttack_MovePosCheck();

	JumpAttack_StateCheck();
}

void Enchantress_ShovelKnight::JumpAttackEnd()
{
	// �������ݸ�� �浹ü Off
	m_JumpAttackCol->Off();
}

// ��������(Object �浹)
void Enchantress_ShovelKnight::JumpAttackColStart()
{
	m_EnchantressPlayerSound = SGameEngineSound::Play(L"ShovelKnight_JumpAttack_Col.mp3", false, 0);

	ChangeAniMation(L"PlayerJumpAttack");

	// ����, �߷� ����
	m_JumpPos = FLOAT4::ZERO;
	m_JumpPower = FLOAT4({ 0.0f, -1000.0f });
	m_JumpGravityPowerPos = FLOAT4({ 0.0f, 3000.0f });

	// ���� �ݸ��� On
	m_JumpAttackCol->On();
}

void Enchantress_ShovelKnight::JumpAttackColStay()
{
	JumpAttackCol_MovePosCheck();

	JumpAttackCol_StateCheck();
}

void Enchantress_ShovelKnight::JumpAttackColEnd()
{
	m_JumpAttackCol->Off();
}

// �⺻���� ����
void Enchantress_ShovelKnight::AttackStart()
{
	m_EnchantressPlayerSound = SGameEngineSound::Play(L"ShovelKnight_Attack.mp3", false, 0);

	ChangeAniMation(L"PlayerAttack");

	// �浹ü ����
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		m_AttackCol->SetPivotPos({ 60, 0 });
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		m_AttackCol->SetPivotPos({ -60, 0 });
	}

	// �浹ü On
	m_AttackCol->On();
}

void Enchantress_ShovelKnight::AttackStay()
{
	// �浹ü Off
	m_AttackCol->Off();

	// ������ Attack������
	if (true == m_bJumping)
	{
		m_JumpPower += m_JumpGravityPowerPos * SGameEngineTimer::FDeltaTime();
		m_JumpPos = m_JumpPower * SGameEngineTimer::FDeltaTime();

		m_MovePos = m_JumpPos;

		Jump_StateCheck();
		return;
	}

	// ������ ��Ǳ��� �Ϸ�� ���º���
	if (true == m_AniPlayer->IsEnd())
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_None");
	}
}

void Enchantress_ShovelKnight::AttackEnd()
{

}

// �˹� ����
// ���İ� ����
void Enchantress_ShovelKnight::HitAlphaInStart()
{
	m_AniPlayer->SetAlpha(100);
}
void Enchantress_ShovelKnight::HitAlphaInStay()
{

}
void Enchantress_ShovelKnight::HitAlphaInEnd()
{
	m_AniPlayer->SetAlpha(255);
}

void Enchantress_ShovelKnight::HitAlphaOutStart()
{
	m_AniPlayer->SetAlpha(255);
}
void Enchantress_ShovelKnight::HitAlphaOutStay()
{

}
void Enchantress_ShovelKnight::HitAlphaOutEnd()
{
	m_AniPlayer->SetAlpha(100);
}

void Enchantress_ShovelKnight::KnockBackStart()
{
	m_EnchantressPlayerSound = SGameEngineSound::Play(L"ShovelKnight_KnockBack.mp3", false, 0);

	// �˹� �Ŀ��� ����
	m_KnockBackPos = FLOAT4::ZERO;
	m_KnockBackPower = FLOAT4({ 0.0f, -300.0f });
	m_KnockBackGravityPowerPos = FLOAT4({ 0.0f, 1000.0f });

	// �浹ü Off
	m_PlayerCol->Off();

	// �ִϸ��̼� ����
	ChangeAniMation(L"PlayerKnockBack");

	// ���� ����(�����Ÿ�)
	if (0 == m_KnockBackEventer.IsEventSize())
	{
		m_KnockBackEventer.CreateTimeEvent(0.1f, this, &Enchantress_ShovelKnight::HitAlphaInEnd, &Enchantress_ShovelKnight::HitAlphaInStart, &Enchantress_ShovelKnight::HitAlphaInStay);
		m_KnockBackEventer.CreateTimeEvent(0.1f, this, &Enchantress_ShovelKnight::HitAlphaOutEnd, &Enchantress_ShovelKnight::HitAlphaOutStart, &Enchantress_ShovelKnight::HitAlphaOutStay);
		m_KnockBackEventer.LoopOn();
	}
}

void Enchantress_ShovelKnight::KnockBackStay()
{
	m_KnockBackEventer.Update();

	KnockBack_MovePosCheck();

	KnockBack_StateCheck();
}

void Enchantress_ShovelKnight::KnockBackEnd()
{
	// �˹�Ϸ�Ǹ� �浹ü On
	m_PlayerCol->On();

	// ���ĺ귻�� �������
	m_AniPlayer->SetAlpha(255);
}

// ���б�縦 �޾Ƴ��� ����
void Enchantress_ShovelKnight::ShildKnightColStart()
{
	ChangeAniMation(L"PlayerShildKnightCol");
}

void Enchantress_ShovelKnight::ShildKnightColStay()
{
	// �ȼ� üũ�Ѵ�.
	PlayerPixelCheck();

	// �������� ������ȯ
	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_MovePos.y = 0.0f;
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_EndingSceneChange");
	}

	// ������ ����̵��Ѵ�.
	m_DirectPos = FLOAT4::ZERO;
	m_DirectPos += FLOAT4::DOWN * SGameEngineTimer::FDeltaTime(m_PlayerInfo.GetMoveSpeed());

	m_MovePos = m_DirectPos;
}

void Enchantress_ShovelKnight::ShildKnightColEnd()
{

}

// ��������ȯ ����
void Enchantress_ShovelKnight::EndingSceneChangeStart()
{
	ChangeAniMation(L"PlayerShildKnightColIdle");

	//
	FadeInOutActor::FadeStartFlagOn();
}

void Enchantress_ShovelKnight::EndingSceneChangeStay()
{
	if (true == FadeInOutActor::GetFadeEnd())
	{
		// ���̵� �� ����� �� ü����
		SGameCore::SceneManager.ChangeScene(L"EndingCredit");
	}
}

void Enchantress_ShovelKnight::EndingSceneChangeEnd()
{

}

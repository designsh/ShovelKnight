#include "Enchantress_ShovelKnight.h"
#include <SGameEngineInput.h>

// 보스를 찾는중 정지된 상태
void Enchantress_ShovelKnight::BossFindIDLE_StateCheck()
{
	// 이동 체크
	if (true == SGameEngineInput::IsPress(L"LEFT") ||
		true == SGameEngineInput::IsPress(L"RIGHT"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_BossFindMOVE");
	}
}

// 보스를 찾기위해 이동하는 상태
void Enchantress_ShovelKnight::BossFindMOVE_StateCheck()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	// 이동방향별 픽셀체크를 부여한다.
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		// 검은색을 만나면 진행불가
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		// 검은색을 만나면 진행불가
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
	}

	// 키가 떨어지면 IDLE상태로 전환된다.
	if (true == SGameEngineInput::IsUp(L"LEFT") || true == SGameEngineInput::IsUp(L"RIGHT"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_BossFindIDLE");
		return;
	}

	// 나의 위치가 등장위치이면 상태 변경
	if (GetPosition().x >= m_PlayerAppearPos.x)
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_CamLerp");
	}
}

// 대기(정지) 상태
void Enchantress_ShovelKnight::Idle_StateCheck()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	// 이동 체크
	if (true == SGameEngineInput::IsPress(L"PLAYER_LEFT") ||
		true == SGameEngineInput::IsPress(L"PLAYER_RIGHT"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_Move");
	}

	// 점프 체크
	if (true == SGameEngineInput::IsDown(L"PLAYER_JUMP"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_Jump");
	}

	// 기본공격 체크
	if (true == SGameEngineInput::IsDown(L"PLAYER_DEFAULTATTACK"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_Attack");
	}
}

// 이동 상태 
void Enchantress_ShovelKnight::Move_StateCheck()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	// 이동방향별 픽셀체크를 부여한다.
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		// 검은색을 만나면 진행불가
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		// 검은색을 만나면 진행불가
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
	}

	// 키가 떨어지면 IDLE상태로 전환된다.
	if (true == SGameEngineInput::IsUp(L"PLAYER_LEFT") || true == SGameEngineInput::IsUp(L"PLAYER_RIGHT"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_None");
		return;
	}

	// 이동중 Attack키를 누르면 Attack 상태로 변경
	if (true == SGameEngineInput::IsDown(L"PLAYER_DEFAULTATTACK"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_Attack");
	}

	// 이동중 Jump키를 누르면 Jump 상태로 변경
	if (true == SGameEngineInput::IsDown(L"PLAYER_JUMP"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_Jump");
	}
}

// 점프 상태
void Enchantress_ShovelKnight::Jump_StateCheck()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	// 방향에따라 픽셀체크
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		// 검은색을 만나면 진행불가
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		// 검은색을 만나면 진행불가
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
	}

	// 검은색을 상태전환
	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_EnchantressPlayerSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

		m_MovePos.y = 0.0f;
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_None");
	}

	// 점프중 Attack키를 누르면 Attack 상태로 변경
	if (true == SGameEngineInput::IsDown(L"PLAYER_DEFAULTATTACK"))
	{
		// 모션이 끝난뒤 계속해서 점프상태를 유지하기 위해 Flag설정
		m_bJumping = true;
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_Attack");
	}

	// 점프중 LADDERDOWN Key를 Press할시 모션 변경
	if (true == SGameEngineInput::IsPress(L"PLAYER_LADDERDOWN"))
	{
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_JumpAttack");
	}
}

// 점프 공격 상태
void Enchantress_ShovelKnight::JumpAttack_StateCheck()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	// 검은색을 상태전환
	if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_EnchantressPlayerSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

		m_MovePos.y = 0.0f;
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_None");
	}

	// 점프 어택중일때 Attack 가능 점프어택상태 해제
	if (true == SGameEngineInput::IsDown(L"PLAYER_DEFAULTATTACK"))
	{
		m_bJumping = true;
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_Attack");
	}
}

// 점프공격중 오브젝트와 충돌 상태
void Enchantress_ShovelKnight::JumpAttackCol_StateCheck()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	// 점프 어택중일때 Attack 가능 점프어택상태 해제
	if (true == SGameEngineInput::IsDown(L"PLAYER_DEFAULTATTACK"))
	{
		m_bJumping = true;
		m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_Attack");
	}
}

// 넉백 상태
void Enchantress_ShovelKnight::KnockBack_StateCheck()
{
	// 픽셀 체크한다.
	PlayerPixelCheck();

	// 이동방향의 반대쪽 픽셀체크
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		// 검은색을 만나면 진행불가
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
			m_DirectPos = FLOAT4::ZERO;
		}
	}
	else if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		// 검은색을 만나면 진행불가
		if (RGB(0, 0, 0) == m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
			m_DirectPos = FLOAT4::ZERO;
		}
	}

	// 넉백파워가 0.0f 이상이되면 바닥 충돌체 On
	if (0.0f <= m_KnockBackPower.y)
	{
		m_PlayerBotCol->On();
	}
}


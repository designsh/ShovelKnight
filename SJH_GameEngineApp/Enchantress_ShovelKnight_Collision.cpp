#include "Enchantress_ShovelKnight.h"

#include "EnchantressBrokenTile.h" // 바닥타일
#include "Enchantress_FinalBoss.h" // 보스
#include "Enchantress_FinalBoss_AttackSkill.h"
#include "Enchantress_FinalBoss_RegenSkill.h"

// 몸통(0)
void Enchantress_ShovelKnight::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder())
	{
		if (0 == _Other->GetCheckData())
		{
			//----------------------------------------- 요마몸체 -----------------------------------------//
			// 보스가 사망모션을 끝내고 밑으로 이동(Falling 상태) 중이면 나의 상태를 바꾸고 보스를 죽인다.
			if (true == GlobalValue::FinalStage_FinalBoss->GetBossFallingFlag())
			{
				// 보스를 죽인다.
				GlobalValue::FinalStage_FinalBoss->Death();

				// 나의 상태를 변환한다.
				m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_ShileKnightCol");
			}
			else // 떨어지는 중이아니면 넉백
			{
				Enchantress_FinalBoss* CollisionEnchantress = dynamic_cast<Enchantress_FinalBoss*>(_Other->GetActor());
				if (nullptr != CollisionEnchantress)
				{
					if (false == m_bKnockBack)
					{
						// 충돌시 플레이어 몸체, 바닥 충돌체 Off
						m_PlayerCol->Off();
						m_PlayerBotCol->Off();

						// 넉백 플래그 On
						m_bKnockBack = true;

						// 플레이어의 체력이 깎인다.
						m_PlayerInfo.SubtractCurHP(1);

						// 플레이어의 체력이 모두 소진되면 플레이어는 죽는다.
						if (0 == m_PlayerInfo.GetCurHP())
						{
							// 일부러 작성하지않음
							// 죽이지않을꺼다....

						}
						// 상태 전환
						m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_KnockBack");
					}
				}
			}
		}
		if (1 == _Other->GetCheckData())
		{
			//----------------------------------------- 요마공격스킬 -----------------------------------------//
			Enchantress_FinalBoss_AttackSkill* CollisionEnchantressAttackSkill = dynamic_cast<Enchantress_FinalBoss_AttackSkill*>(_Other->GetActor());
			if (nullptr != CollisionEnchantressAttackSkill)
			{
				if (false == m_bKnockBack)
				{
					// 충돌시 플레이어 몸체, 바닥 충돌체 Off
					m_PlayerCol->Off();
					m_PlayerBotCol->Off();

					// 넉백 플래그 On
					m_bKnockBack = true;

					// 플레이어의 체력이 깎인다.
					m_PlayerInfo.SubtractCurHP(1);

					// 플레이어의 체력이 모두 소진되면 플레이어는 죽는다.
					if (0 == m_PlayerInfo.GetCurHP())
					{
						// 일부러 작성하지않음
						// 죽이지않을꺼다....

					}
					// 상태 전환
					m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_KnockBack");
				}
			}
		}
	}
}

void Enchantress_ShovelKnight::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Enchantress_ShovelKnight::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

// 바닥(1)
void Enchantress_ShovelKnight::BottomCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 바닥면과 바닥타일오브젝트가 충돌하면 상태 전환
	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		if (true == m_bJumping) // 점프 중일때만 체크한다.
		{
			//----------------------------------------- 바닥타일 -----------------------------------------//
			EnchantressBrokenTile* CollisionJump = dynamic_cast<EnchantressBrokenTile*>(_Other->GetActor());
			if (nullptr != CollisionJump)
			{
				// 모든 벡터값 초기화
				m_JumpPos = FLOAT4::ZERO;
				m_JumpPower = FLOAT4::ZERO;
				m_JumpGravityPowerPos = FLOAT4::ZERO;

				m_MovePos.y = 0.0f; // 이동량 없음
				m_bJumping = false; // 점프플래그 해제

				m_EnchantressPlayerSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

				// 상태 전환
				m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_None");
			}
		}
		if (true == m_bKnockBack) // 넉백중일때만 체크한다.
		{
			//----------------------------------------- 바닥타일 -----------------------------------------//
			EnchantressBrokenTile* CollisionKnockBack = dynamic_cast<EnchantressBrokenTile*>(_Other->GetActor());
			if (nullptr != CollisionKnockBack)
			{
				// 모든 벡터값 초기화
				m_KnockBackPos = FLOAT4::ZERO;
				m_KnockBackPower = FLOAT4::ZERO;
				m_KnockBackGravityPowerPos = FLOAT4::ZERO;

				m_MovePos.y = 0.0f; // 이동량 없음
				m_bKnockBack = false; // 넉백플래그 해제

				// 상태 전환
				m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_None");
			}
		}
	}

	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder())
	{
		if (0 == _Other->GetCheckData())
		{
			//----------------------------------------- 요마공격스킬 -----------------------------------------//
			Enchantress_FinalBoss_AttackSkill* CollisionEnchantressAttackSkill = dynamic_cast<Enchantress_FinalBoss_AttackSkill*>(_Other->GetActor());
			if (nullptr != CollisionEnchantressAttackSkill)
			{
				if (false == m_bKnockBack)
				{
					// 충돌시 플레이어 몸체, 바닥 충돌체 Off
					m_PlayerCol->Off();
					m_PlayerBotCol->Off();

					// 넉백 플래그 On
					m_bKnockBack = true;

					// 플레이어의 체력이 깎인다.
					m_PlayerInfo.SubtractCurHP(1);

					// 플레이어의 체력이 모두 소진되면 플레이어는 죽는다.
					if (0 == m_PlayerInfo.GetCurHP())
					{
						// 일부러 작성하지않음
						// 죽이지않을꺼다....

					}
					// 상태 전환
					m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_KnockBack");
				}
			}
		}
		if (1 == _Other->GetCheckData())
		{
			//----------------------------------------- 요마공격스킬 -----------------------------------------//
			Enchantress_FinalBoss_AttackSkill* CollisionEnchantressAttackSkill = dynamic_cast<Enchantress_FinalBoss_AttackSkill*>(_Other->GetActor());
			if (nullptr != CollisionEnchantressAttackSkill)
			{
				if (false == m_bKnockBack)
				{
					// 충돌시 플레이어 몸체, 바닥 충돌체 Off
					m_PlayerCol->Off();
					m_PlayerBotCol->Off();

					// 넉백 플래그 On
					m_bKnockBack = true;

					// 플레이어의 체력이 깎인다.
					m_PlayerInfo.SubtractCurHP(1);

					// 플레이어의 체력이 모두 소진되면 플레이어는 죽는다.
					if (0 == m_PlayerInfo.GetCurHP())
					{
						// 일부러 작성하지않음
						// 죽이지않을꺼다....

					}
					// 상태 전환
					m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_KnockBack");
				}
			}
		}
		if (2 == _Other->GetCheckData())
		{
			//----------------------------------------- 요마리젠스킬 -----------------------------------------//
			Enchantress_FinalBoss_RegenSkill* CollisionEnchantressRegenSkill = dynamic_cast<Enchantress_FinalBoss_RegenSkill*>(_Other->GetActor());
			if (nullptr != CollisionEnchantressRegenSkill)
			{
				if (false == m_bKnockBack)
				{
					// 충돌시 플레이어 몸체, 바닥 충돌체 Off
					m_PlayerCol->Off();
					m_PlayerBotCol->Off();

					// 넉백 플래그 On
					m_bKnockBack = true;

					// 플레이어의 체력이 깎인다.
					m_PlayerInfo.SubtractCurHP(1);

					// 플레이어의 체력이 모두 소진되면 플레이어는 죽는다.
					if (0 == m_PlayerInfo.GetCurHP())
					{
						// 일부러 작성하지않음
						// 죽이지않을꺼다....

					}
					// 상태 전환
					m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_KnockBack");
				}
			}
		}
	}
}

void Enchantress_ShovelKnight::BottomCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Enchantress_ShovelKnight::BottomCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

// 공격모션
void Enchantress_ShovelKnight::AttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Enchantress_ShovelKnight::AttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Enchantress_ShovelKnight::AttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

// 점프공격모션
void Enchantress_ShovelKnight::JumpAttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 점프공격 모션과 바닥타일오브젝트와 충돌하면 상태전환
		// 바닥면과 바닥타일오브젝트가 충돌하면 상태 전환
	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		//----------------------------------------- 바닥타일 -----------------------------------------//
		EnchantressBrokenTile* CollisionBrokenTile = dynamic_cast<EnchantressBrokenTile*>(_Other->GetActor());
		if (nullptr != CollisionBrokenTile)
		{
			m_MovePos.y = 0.0f;
			m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_JumpAttackCol");
		}
	}

	// 몬스터의 몸체와 충돌하면 상태 전환
	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder())
	{
		if (0 == _Other->GetCheckData())
		{
			//----------------------------------------- 요마몸체 -----------------------------------------//
			Enchantress_FinalBoss* CollisionFinalBoss = dynamic_cast<Enchantress_FinalBoss*>(_Other->GetActor());
			if (nullptr != CollisionFinalBoss)
			{
				m_MovePos.y = 0.0f;
				m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_JumpAttackCol");
			}
		}
		else if (1 == _Other->GetCheckData())
		{
			//----------------------------------------- 요마공격스킬 -----------------------------------------//
			Enchantress_FinalBoss_AttackSkill* CollisionFinalBossAttackSkill = dynamic_cast<Enchantress_FinalBoss_AttackSkill*>(_Other->GetActor());
			if (nullptr != CollisionFinalBossAttackSkill)
			{
				if (false == m_bKnockBack)
				{
					// 충돌시 플레이어 몸체, 바닥 충돌체 Off
					m_PlayerCol->Off();
					m_PlayerBotCol->Off();

					// 넉백 플래그 On
					m_bKnockBack = true;

					// 플레이어의 체력이 깎인다.
					m_PlayerInfo.SubtractCurHP(1);

					// 플레이어의 체력이 모두 소진되면 플레이어는 죽는다.
					if (0 == m_PlayerInfo.GetCurHP())
					{
						// 일부러 작성하지않음
						// 죽이지않을꺼다....

					}
					// 상태 전환
					m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_KnockBack");
				}
			}
		}
		else if (2 == _Other->GetCheckData())
		{
			//----------------------------------------- 요마리젠스킬 -----------------------------------------//
			Enchantress_FinalBoss_RegenSkill* CollisionFinalBossRegenSkill = dynamic_cast<Enchantress_FinalBoss_RegenSkill*>(_Other->GetActor());
			if (nullptr != CollisionFinalBossRegenSkill)
			{
				// 충돌시 플레이어 몸체, 바닥 충돌체 Off
				m_PlayerCol->Off();
				m_PlayerBotCol->Off();

				// 넉백 플래그 On
				m_bKnockBack = true;

				// 플레이어의 체력이 깎인다.
				m_PlayerInfo.SubtractCurHP(1);

				// 플레이어의 체력이 모두 소진되면 플레이어는 죽는다.
				if (0 == m_PlayerInfo.GetCurHP())
				{
					// 일부러 작성하지않음
					// 죽이지않을꺼다....

				}
				// 상태 전환
				m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_KnockBack");
			}
		}
	}
}

void Enchantress_ShovelKnight::JumpAttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Enchantress_ShovelKnight::JumpAttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

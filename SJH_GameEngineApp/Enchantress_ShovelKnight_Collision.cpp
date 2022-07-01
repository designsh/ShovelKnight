#include "Enchantress_ShovelKnight.h"

#include "EnchantressBrokenTile.h" // �ٴ�Ÿ��
#include "Enchantress_FinalBoss.h" // ����
#include "Enchantress_FinalBoss_AttackSkill.h"
#include "Enchantress_FinalBoss_RegenSkill.h"

// ����(0)
void Enchantress_ShovelKnight::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder())
	{
		if (0 == _Other->GetCheckData())
		{
			//----------------------------------------- �丶��ü -----------------------------------------//
			// ������ �������� ������ ������ �̵�(Falling ����) ���̸� ���� ���¸� �ٲٰ� ������ ���δ�.
			if (true == GlobalValue::FinalStage_FinalBoss->GetBossFallingFlag())
			{
				// ������ ���δ�.
				GlobalValue::FinalStage_FinalBoss->Death();

				// ���� ���¸� ��ȯ�Ѵ�.
				m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_ShileKnightCol");
			}
			else // �������� ���̾ƴϸ� �˹�
			{
				Enchantress_FinalBoss* CollisionEnchantress = dynamic_cast<Enchantress_FinalBoss*>(_Other->GetActor());
				if (nullptr != CollisionEnchantress)
				{
					if (false == m_bKnockBack)
					{
						// �浹�� �÷��̾� ��ü, �ٴ� �浹ü Off
						m_PlayerCol->Off();
						m_PlayerBotCol->Off();

						// �˹� �÷��� On
						m_bKnockBack = true;

						// �÷��̾��� ü���� ���δ�.
						m_PlayerInfo.SubtractCurHP(1);

						// �÷��̾��� ü���� ��� �����Ǹ� �÷��̾�� �״´�.
						if (0 == m_PlayerInfo.GetCurHP())
						{
							// �Ϻη� �ۼ���������
							// ��������������....

						}
						// ���� ��ȯ
						m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_KnockBack");
					}
				}
			}
		}
		if (1 == _Other->GetCheckData())
		{
			//----------------------------------------- �丶���ݽ�ų -----------------------------------------//
			Enchantress_FinalBoss_AttackSkill* CollisionEnchantressAttackSkill = dynamic_cast<Enchantress_FinalBoss_AttackSkill*>(_Other->GetActor());
			if (nullptr != CollisionEnchantressAttackSkill)
			{
				if (false == m_bKnockBack)
				{
					// �浹�� �÷��̾� ��ü, �ٴ� �浹ü Off
					m_PlayerCol->Off();
					m_PlayerBotCol->Off();

					// �˹� �÷��� On
					m_bKnockBack = true;

					// �÷��̾��� ü���� ���δ�.
					m_PlayerInfo.SubtractCurHP(1);

					// �÷��̾��� ü���� ��� �����Ǹ� �÷��̾�� �״´�.
					if (0 == m_PlayerInfo.GetCurHP())
					{
						// �Ϻη� �ۼ���������
						// ��������������....

					}
					// ���� ��ȯ
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

// �ٴ�(1)
void Enchantress_ShovelKnight::BottomCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// �ٴڸ�� �ٴ�Ÿ�Ͽ�����Ʈ�� �浹�ϸ� ���� ��ȯ
	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		if (true == m_bJumping) // ���� ���϶��� üũ�Ѵ�.
		{
			//----------------------------------------- �ٴ�Ÿ�� -----------------------------------------//
			EnchantressBrokenTile* CollisionJump = dynamic_cast<EnchantressBrokenTile*>(_Other->GetActor());
			if (nullptr != CollisionJump)
			{
				// ��� ���Ͱ� �ʱ�ȭ
				m_JumpPos = FLOAT4::ZERO;
				m_JumpPower = FLOAT4::ZERO;
				m_JumpGravityPowerPos = FLOAT4::ZERO;

				m_MovePos.y = 0.0f; // �̵��� ����
				m_bJumping = false; // �����÷��� ����

				m_EnchantressPlayerSound = SGameEngineSound::Play(L"ShovelKnight_JumpEnd.mp3", false, 0);

				// ���� ��ȯ
				m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_None");
			}
		}
		if (true == m_bKnockBack) // �˹����϶��� üũ�Ѵ�.
		{
			//----------------------------------------- �ٴ�Ÿ�� -----------------------------------------//
			EnchantressBrokenTile* CollisionKnockBack = dynamic_cast<EnchantressBrokenTile*>(_Other->GetActor());
			if (nullptr != CollisionKnockBack)
			{
				// ��� ���Ͱ� �ʱ�ȭ
				m_KnockBackPos = FLOAT4::ZERO;
				m_KnockBackPower = FLOAT4::ZERO;
				m_KnockBackGravityPowerPos = FLOAT4::ZERO;

				m_MovePos.y = 0.0f; // �̵��� ����
				m_bKnockBack = false; // �˹��÷��� ����

				// ���� ��ȯ
				m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_None");
			}
		}
	}

	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder())
	{
		if (0 == _Other->GetCheckData())
		{
			//----------------------------------------- �丶���ݽ�ų -----------------------------------------//
			Enchantress_FinalBoss_AttackSkill* CollisionEnchantressAttackSkill = dynamic_cast<Enchantress_FinalBoss_AttackSkill*>(_Other->GetActor());
			if (nullptr != CollisionEnchantressAttackSkill)
			{
				if (false == m_bKnockBack)
				{
					// �浹�� �÷��̾� ��ü, �ٴ� �浹ü Off
					m_PlayerCol->Off();
					m_PlayerBotCol->Off();

					// �˹� �÷��� On
					m_bKnockBack = true;

					// �÷��̾��� ü���� ���δ�.
					m_PlayerInfo.SubtractCurHP(1);

					// �÷��̾��� ü���� ��� �����Ǹ� �÷��̾�� �״´�.
					if (0 == m_PlayerInfo.GetCurHP())
					{
						// �Ϻη� �ۼ���������
						// ��������������....

					}
					// ���� ��ȯ
					m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_KnockBack");
				}
			}
		}
		if (1 == _Other->GetCheckData())
		{
			//----------------------------------------- �丶���ݽ�ų -----------------------------------------//
			Enchantress_FinalBoss_AttackSkill* CollisionEnchantressAttackSkill = dynamic_cast<Enchantress_FinalBoss_AttackSkill*>(_Other->GetActor());
			if (nullptr != CollisionEnchantressAttackSkill)
			{
				if (false == m_bKnockBack)
				{
					// �浹�� �÷��̾� ��ü, �ٴ� �浹ü Off
					m_PlayerCol->Off();
					m_PlayerBotCol->Off();

					// �˹� �÷��� On
					m_bKnockBack = true;

					// �÷��̾��� ü���� ���δ�.
					m_PlayerInfo.SubtractCurHP(1);

					// �÷��̾��� ü���� ��� �����Ǹ� �÷��̾�� �״´�.
					if (0 == m_PlayerInfo.GetCurHP())
					{
						// �Ϻη� �ۼ���������
						// ��������������....

					}
					// ���� ��ȯ
					m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_KnockBack");
				}
			}
		}
		if (2 == _Other->GetCheckData())
		{
			//----------------------------------------- �丶������ų -----------------------------------------//
			Enchantress_FinalBoss_RegenSkill* CollisionEnchantressRegenSkill = dynamic_cast<Enchantress_FinalBoss_RegenSkill*>(_Other->GetActor());
			if (nullptr != CollisionEnchantressRegenSkill)
			{
				if (false == m_bKnockBack)
				{
					// �浹�� �÷��̾� ��ü, �ٴ� �浹ü Off
					m_PlayerCol->Off();
					m_PlayerBotCol->Off();

					// �˹� �÷��� On
					m_bKnockBack = true;

					// �÷��̾��� ü���� ���δ�.
					m_PlayerInfo.SubtractCurHP(1);

					// �÷��̾��� ü���� ��� �����Ǹ� �÷��̾�� �״´�.
					if (0 == m_PlayerInfo.GetCurHP())
					{
						// �Ϻη� �ۼ���������
						// ��������������....

					}
					// ���� ��ȯ
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

// ���ݸ��
void Enchantress_ShovelKnight::AttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Enchantress_ShovelKnight::AttackCollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Enchantress_ShovelKnight::AttackCollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

// �������ݸ��
void Enchantress_ShovelKnight::JumpAttackCollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// �������� ��ǰ� �ٴ�Ÿ�Ͽ�����Ʈ�� �浹�ϸ� ������ȯ
		// �ٴڸ�� �ٴ�Ÿ�Ͽ�����Ʈ�� �浹�ϸ� ���� ��ȯ
	if ((int)GlobalValue::CollisionGroup::UI == _Other->GetOrder())
	{
		//----------------------------------------- �ٴ�Ÿ�� -----------------------------------------//
		EnchantressBrokenTile* CollisionBrokenTile = dynamic_cast<EnchantressBrokenTile*>(_Other->GetActor());
		if (nullptr != CollisionBrokenTile)
		{
			m_MovePos.y = 0.0f;
			m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_JumpAttackCol");
		}
	}

	// ������ ��ü�� �浹�ϸ� ���� ��ȯ
	if ((int)GlobalValue::CollisionGroup::Monster == _Other->GetOrder())
	{
		if (0 == _Other->GetCheckData())
		{
			//----------------------------------------- �丶��ü -----------------------------------------//
			Enchantress_FinalBoss* CollisionFinalBoss = dynamic_cast<Enchantress_FinalBoss*>(_Other->GetActor());
			if (nullptr != CollisionFinalBoss)
			{
				m_MovePos.y = 0.0f;
				m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_JumpAttackCol");
			}
		}
		else if (1 == _Other->GetCheckData())
		{
			//----------------------------------------- �丶���ݽ�ų -----------------------------------------//
			Enchantress_FinalBoss_AttackSkill* CollisionFinalBossAttackSkill = dynamic_cast<Enchantress_FinalBoss_AttackSkill*>(_Other->GetActor());
			if (nullptr != CollisionFinalBossAttackSkill)
			{
				if (false == m_bKnockBack)
				{
					// �浹�� �÷��̾� ��ü, �ٴ� �浹ü Off
					m_PlayerCol->Off();
					m_PlayerBotCol->Off();

					// �˹� �÷��� On
					m_bKnockBack = true;

					// �÷��̾��� ü���� ���δ�.
					m_PlayerInfo.SubtractCurHP(1);

					// �÷��̾��� ü���� ��� �����Ǹ� �÷��̾�� �״´�.
					if (0 == m_PlayerInfo.GetCurHP())
					{
						// �Ϻη� �ۼ���������
						// ��������������....

					}
					// ���� ��ȯ
					m_ShovelKnightFSM.ChangeState(L"Enchantress_Player_KnockBack");
				}
			}
		}
		else if (2 == _Other->GetCheckData())
		{
			//----------------------------------------- �丶������ų -----------------------------------------//
			Enchantress_FinalBoss_RegenSkill* CollisionFinalBossRegenSkill = dynamic_cast<Enchantress_FinalBoss_RegenSkill*>(_Other->GetActor());
			if (nullptr != CollisionFinalBossRegenSkill)
			{
				// �浹�� �÷��̾� ��ü, �ٴ� �浹ü Off
				m_PlayerCol->Off();
				m_PlayerBotCol->Off();

				// �˹� �÷��� On
				m_bKnockBack = true;

				// �÷��̾��� ü���� ���δ�.
				m_PlayerInfo.SubtractCurHP(1);

				// �÷��̾��� ü���� ��� �����Ǹ� �÷��̾�� �״´�.
				if (0 == m_PlayerInfo.GetCurHP())
				{
					// �Ϻη� �ۼ���������
					// ��������������....

				}
				// ���� ��ȯ
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

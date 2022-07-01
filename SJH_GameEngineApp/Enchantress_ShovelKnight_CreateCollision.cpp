#include "Enchantress_ShovelKnight.h"

void Enchantress_ShovelKnight::CreatePlayerCollision()
{
	// �⺻������ �÷��̾�� ����, �ٴ�, ���ݸ��, �������ݸ���� �浹ü�� ������.
	// �˹������� ���� �浹ü�� �ٸ��׷��� �浹ü�� �浹������ �����Ǹ�
	// ���� ���������� ���ݸ��, �������ݸ�� �浹ü�� �ٸ� �׷��� �浹ü�� �浹������ �����ȴ�.
	// �ٴ��浹ü�� �ٸ��׷��� �浹ü�� �浹������ �÷��̾��� ���º�ȭ�� ���� �����ȴ�.

	// 1. ���� �浹ü
	m_PlayerCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Player);
	m_PlayerCol->SetScale({ 40, 50 });
	m_PlayerCol->AddStartEvent(this, &Enchantress_ShovelKnight::CollisionStart);
	m_PlayerCol->AddStayEvent(this, &Enchantress_ShovelKnight::CollisionStay);
	m_PlayerCol->AddEndEvent(this, &Enchantress_ShovelKnight::CollisionEnd);
	m_PlayerCol->SetCheckData(0);

	// 2. �ٴ� �浹ü
	m_PlayerBotCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Player);
	m_PlayerBotCol->SetScale({ 36, 20 });
	m_PlayerBotCol->SetPivotPos({ 0, -40 });
	m_PlayerBotCol->AddStartEvent(this, &Enchantress_ShovelKnight::BottomCollisionStart);
	m_PlayerBotCol->AddStayEvent(this, &Enchantress_ShovelKnight::BottomCollisionStay);
	m_PlayerBotCol->AddEndEvent(this, &Enchantress_ShovelKnight::BottomCollisionEnd);
	m_PlayerBotCol->SetCheckData(1);

	// 3. ���ݸ�� �浹ü
	m_AttackCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::PlayerAttack);
	m_AttackCol->SetScale({ 30, 40 });
	m_AttackCol->Off();
	m_AttackCol->AddStartEvent(this, &Enchantress_ShovelKnight::AttackCollisionStart);
	m_AttackCol->AddStayEvent(this, &Enchantress_ShovelKnight::AttackCollisionStay);
	m_AttackCol->AddEndEvent(this, &Enchantress_ShovelKnight::AttackCollisionEnd);

	// 4. �������ݸ�� �浹ü
	m_JumpAttackCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::PlayerJumpAttack);
	m_JumpAttackCol->SetScale({ 30, 40 });
	m_JumpAttackCol->Off();
	m_JumpAttackCol->AddStartEvent(this, &Enchantress_ShovelKnight::JumpAttackCollisionStart);
	m_JumpAttackCol->AddStayEvent(this, &Enchantress_ShovelKnight::JumpAttackCollisionStay);
	m_JumpAttackCol->AddEndEvent(this, &Enchantress_ShovelKnight::JumpAttackCollisionEnd);
}

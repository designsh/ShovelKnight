#include "ShovelKnight.h"

void ShovelKnight::CreatePlayerCollision()
{
	// �⺻������ �÷��̾�� ����, �ٴ�, ���ݸ��, �������ݸ���� �浹ü�� ������.
	// �˹������� ���� �浹ü�� �ٸ��׷��� �浹ü�� �浹������ �����Ǹ�
	// ���� ���������� ���ݸ��, �������ݸ�� �浹ü�� �ٸ� �׷��� �浹ü�� �浹������ �����ȴ�.
	// �ٴ��浹ü�� �ٸ��׷��� �浹ü�� �浹������ �÷��̾��� ���º�ȭ�� ���� �����ȴ�.

	// 1. ���� �浹ü
	m_PlayerCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Player);
	m_PlayerCol->SetScale({ 40, 50 });
	m_PlayerCol->AddStartEvent(this, &ShovelKnight::CollisionStart);
	m_PlayerCol->AddStayEvent(this, &ShovelKnight::CollisionStay);
	m_PlayerCol->AddEndEvent(this, &ShovelKnight::CollisionEnd);
	m_PlayerCol->SetCheckData(0);

	// 2. �ٴ� �浹ü
	m_PlayerBotCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Player);
	m_PlayerBotCol->SetScale({ 36, 20 });
	m_PlayerBotCol->SetPivotPos({ 0, -40 });
	m_PlayerBotCol->AddStartEvent(this, &ShovelKnight::BottomCollisionStart);
	m_PlayerBotCol->AddStayEvent(this, &ShovelKnight::BottomCollisionStay);
	m_PlayerBotCol->AddEndEvent(this, &ShovelKnight::BottomCollisionEnd);
	m_PlayerBotCol->SetCheckData(1);

	// 3. ���ݸ�� �浹ü
	m_AttackCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::PlayerAttack);
	m_AttackCol->SetScale({ 30, 40 });
	m_AttackCol->Off();
	m_AttackCol->AddStartEvent(this, &ShovelKnight::AttackCollisionStart);
	m_AttackCol->AddStayEvent(this, &ShovelKnight::AttackCollisionStay);
	m_AttackCol->AddEndEvent(this, &ShovelKnight::AttackCollisionEnd);

	// 4. �������ݸ�� �浹ü
	m_JumpAttackCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::PlayerJumpAttack);
	m_JumpAttackCol->SetScale({ 30, 40 });
	m_JumpAttackCol->Off();
	m_JumpAttackCol->AddStartEvent(this, &ShovelKnight::JumpAttackCollisionStart);
	m_JumpAttackCol->AddStayEvent(this, &ShovelKnight::JumpAttackCollisionStay);
	m_JumpAttackCol->AddEndEvent(this, &ShovelKnight::JumpAttackCollisionEnd);
}

#include "ShovelKnight.h"

void ShovelKnight::CreatePlayerCollision()
{
	// 기본적으로 플레이어는 몸통, 바닥, 공격모션, 점프공격모션의 충돌체를 가진다.
	// 넉백판정은 몸통 충돌체와 다른그룹의 충돌체가 충돌했을때 판정되며
	// 나의 공격판정은 공격모션, 점프공격모션 충돌체가 다른 그룹의 충돌체와 충돌했을때 판정된다.
	// 바닥충돌체는 다른그룹의 충돌체와 충돌했을때 플레이어의 상태변화를 위해 생성된다.

	// 1. 몸통 충돌체
	m_PlayerCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Player);
	m_PlayerCol->SetScale({ 40, 50 });
	m_PlayerCol->AddStartEvent(this, &ShovelKnight::CollisionStart);
	m_PlayerCol->AddStayEvent(this, &ShovelKnight::CollisionStay);
	m_PlayerCol->AddEndEvent(this, &ShovelKnight::CollisionEnd);
	m_PlayerCol->SetCheckData(0);

	// 2. 바닥 충돌체
	m_PlayerBotCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Player);
	m_PlayerBotCol->SetScale({ 36, 20 });
	m_PlayerBotCol->SetPivotPos({ 0, -40 });
	m_PlayerBotCol->AddStartEvent(this, &ShovelKnight::BottomCollisionStart);
	m_PlayerBotCol->AddStayEvent(this, &ShovelKnight::BottomCollisionStay);
	m_PlayerBotCol->AddEndEvent(this, &ShovelKnight::BottomCollisionEnd);
	m_PlayerBotCol->SetCheckData(1);

	// 3. 공격모션 충돌체
	m_AttackCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::PlayerAttack);
	m_AttackCol->SetScale({ 30, 40 });
	m_AttackCol->Off();
	m_AttackCol->AddStartEvent(this, &ShovelKnight::AttackCollisionStart);
	m_AttackCol->AddStayEvent(this, &ShovelKnight::AttackCollisionStay);
	m_AttackCol->AddEndEvent(this, &ShovelKnight::AttackCollisionEnd);

	// 4. 점프공격모션 충돌체
	m_JumpAttackCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::PlayerJumpAttack);
	m_JumpAttackCol->SetScale({ 30, 40 });
	m_JumpAttackCol->Off();
	m_JumpAttackCol->AddStartEvent(this, &ShovelKnight::JumpAttackCollisionStart);
	m_JumpAttackCol->AddStayEvent(this, &ShovelKnight::JumpAttackCollisionStay);
	m_JumpAttackCol->AddEndEvent(this, &ShovelKnight::JumpAttackCollisionEnd);
}

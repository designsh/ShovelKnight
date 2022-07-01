#include "Enchantress.h"
#include "GlobalValue.h"

void Enchantress::EnchantressCreateCollisionGroup()
{
	CollisionGroupLink((int)GlobalValue::CollisionGroup::Player, (int)GlobalValue::CollisionGroup::Monster);                    // 플레이어 <=> 몬스터
	CollisionGroupLink((int)GlobalValue::CollisionGroup::Player, (int)GlobalValue::CollisionGroup::UI);                              // 플레이어 <=> 오브젝트
	CollisionGroupLink((int)GlobalValue::CollisionGroup::Monster, (int)GlobalValue::CollisionGroup::UI);                          // 플레이어 <=> 오브젝트

	CollisionGroupLink((int)GlobalValue::CollisionGroup::PlayerAttack, (int)GlobalValue::CollisionGroup::UI);
	CollisionGroupLink((int)GlobalValue::CollisionGroup::PlayerAttack, (int)GlobalValue::CollisionGroup::Monster);

	CollisionGroupLink((int)GlobalValue::CollisionGroup::PlayerJumpAttack, (int)GlobalValue::CollisionGroup::UI);
	CollisionGroupLink((int)GlobalValue::CollisionGroup::PlayerJumpAttack, (int)GlobalValue::CollisionGroup::Monster);
}

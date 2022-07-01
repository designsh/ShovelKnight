#include "Enchantress.h"
#include "GlobalValue.h"

void Enchantress::EnchantressCreateCollisionGroup()
{
	CollisionGroupLink((int)GlobalValue::CollisionGroup::Player, (int)GlobalValue::CollisionGroup::Monster);                    // �÷��̾� <=> ����
	CollisionGroupLink((int)GlobalValue::CollisionGroup::Player, (int)GlobalValue::CollisionGroup::UI);                              // �÷��̾� <=> ������Ʈ
	CollisionGroupLink((int)GlobalValue::CollisionGroup::Monster, (int)GlobalValue::CollisionGroup::UI);                          // �÷��̾� <=> ������Ʈ

	CollisionGroupLink((int)GlobalValue::CollisionGroup::PlayerAttack, (int)GlobalValue::CollisionGroup::UI);
	CollisionGroupLink((int)GlobalValue::CollisionGroup::PlayerAttack, (int)GlobalValue::CollisionGroup::Monster);

	CollisionGroupLink((int)GlobalValue::CollisionGroup::PlayerJumpAttack, (int)GlobalValue::CollisionGroup::UI);
	CollisionGroupLink((int)GlobalValue::CollisionGroup::PlayerJumpAttack, (int)GlobalValue::CollisionGroup::Monster);
}

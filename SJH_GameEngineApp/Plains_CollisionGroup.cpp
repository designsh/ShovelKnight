#include "Plains.h"
#include "GlobalValue.h"

void Plains::PlainsCreateCollisionGroup()
{
	// �浹�׷� ����
	// �÷��̾� ��ü�� �ٸ� �浹ü �浹
	CollisionGroupLink((int)GlobalValue::CollisionGroup::Player, (int)GlobalValue::CollisionGroup::Monster);                    // �÷��̾� <=> ����
	CollisionGroupLink((int)GlobalValue::CollisionGroup::Player, (int)GlobalValue::CollisionGroup::UI);                              // �÷��̾� <=> ������Ʈ
	CollisionGroupLink((int)GlobalValue::CollisionGroup::Player, (int)GlobalValue::CollisionGroup::MovingPlatform);       // �÷��̾� <=> �����÷���(����Ÿ��)

	// �÷��̾� �Ϲ� ���ݸ�ǰ� �ٸ� �浹ü �浹
	CollisionGroupLink((int)GlobalValue::CollisionGroup::PlayerAttack, (int)GlobalValue::CollisionGroup::UI);
	CollisionGroupLink((int)GlobalValue::CollisionGroup::PlayerAttack, (int)GlobalValue::CollisionGroup::Monster);

	// �÷��̾� ���� ���ݸ�ǰ� �ٸ� �浹ü �浹
	CollisionGroupLink((int)GlobalValue::CollisionGroup::PlayerJumpAttack, (int)GlobalValue::CollisionGroup::UI);
	CollisionGroupLink((int)GlobalValue::CollisionGroup::PlayerJumpAttack, (int)GlobalValue::CollisionGroup::Monster);

	// ���Ϳ� ������Ʈ �浹
	CollisionGroupLink((int)GlobalValue::CollisionGroup::Monster, (int)GlobalValue::CollisionGroup::UI);
}

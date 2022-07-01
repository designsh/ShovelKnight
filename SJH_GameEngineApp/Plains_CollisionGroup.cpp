#include "Plains.h"
#include "GlobalValue.h"

void Plains::PlainsCreateCollisionGroup()
{
	// 충돌그룹 생성
	// 플레이어 몸체와 다른 충돌체 충돌
	CollisionGroupLink((int)GlobalValue::CollisionGroup::Player, (int)GlobalValue::CollisionGroup::Monster);                    // 플레이어 <=> 몬스터
	CollisionGroupLink((int)GlobalValue::CollisionGroup::Player, (int)GlobalValue::CollisionGroup::UI);                              // 플레이어 <=> 오브젝트
	CollisionGroupLink((int)GlobalValue::CollisionGroup::Player, (int)GlobalValue::CollisionGroup::MovingPlatform);       // 플레이어 <=> 무빙플랫폼(러프타일)

	// 플레이어 일반 공격모션과 다른 충돌체 충돌
	CollisionGroupLink((int)GlobalValue::CollisionGroup::PlayerAttack, (int)GlobalValue::CollisionGroup::UI);
	CollisionGroupLink((int)GlobalValue::CollisionGroup::PlayerAttack, (int)GlobalValue::CollisionGroup::Monster);

	// 플레이어 점프 공격모션과 다른 충돌체 충돌
	CollisionGroupLink((int)GlobalValue::CollisionGroup::PlayerJumpAttack, (int)GlobalValue::CollisionGroup::UI);
	CollisionGroupLink((int)GlobalValue::CollisionGroup::PlayerJumpAttack, (int)GlobalValue::CollisionGroup::Monster);

	// 몬스터와 오브젝트 충돌
	CollisionGroupLink((int)GlobalValue::CollisionGroup::Monster, (int)GlobalValue::CollisionGroup::UI);
}

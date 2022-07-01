#include "Beeto.h"

void Beeto::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 플레이어의 기본공격모션 or 점프공격모션 충돌체와 충돌시
	// Beeto의 충돌체는 먼저죽는다.
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		// 내 체력을 깍고 나는 죽는다.
		m_BeetoBasicInfo.SubtractHP(1);

		if (0 == m_BeetoBasicInfo.GetHP())
		{
			// Beeto 죽는 모션으로 넘어갈때 충돌체는 먼저 죽는다.
			m_BeetoCol->Death();

			// 상태를 바꾼다.
			m_BeetoFSM.ChangeState(L"Beeto_Die");
		}
	}
}

void Beeto::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Beeto::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

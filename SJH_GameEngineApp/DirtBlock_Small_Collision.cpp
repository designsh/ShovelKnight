#include "DirtBlock_Small.h"

void DirtBlock_Small::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		// ³ª´Â Á×´Â´Ù.
		m_DirtBlockFSM.ChangeState(L"DirtSmall_BeShot");
	}
}

void DirtBlock_Small::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void DirtBlock_Small::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

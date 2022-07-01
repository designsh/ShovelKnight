#include "DirtBlock.h"

void DirtBlock::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		// �÷��̾��� ���� ��� or ���� ���ݸ�ǰ� �浹�� ���� �״´�.
		m_DirtBlockFSM.ChangeState(L"DirtBlock_BeShot");
	}
}

void DirtBlock::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void DirtBlock::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

#include "PileBubbles.h"

void PileBubbles::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// �÷��̾��� ���ݸ��, �������ݸ��, ��ü �浹�� PileBubbles_BeShot ���·� �����ϸ�
	// ���� �浹ü�� �״´�.
	if (((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||                                                   // �÷��̾� ���ݸ�� �浹ü�� ���
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder()) ||                                          // �÷��̾� �������ݸ�� �浹ü�� ���
		((int)GlobalValue::CollisionGroup::Player == _Other->GetOrder() && 0 == _Other->GetCheckData()))    // �÷��̾��̸� �÷��̾� ��ü �浹ü�� ���
	{
		// ���º���
		m_PileBubblesFSM.ChangeState(L"PileBubbles_BeShot");
	}
}

void PileBubbles::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void PileBubbles::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

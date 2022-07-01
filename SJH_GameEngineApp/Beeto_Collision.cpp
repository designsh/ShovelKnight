#include "Beeto.h"

void Beeto::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// �÷��̾��� �⺻���ݸ�� or �������ݸ�� �浹ü�� �浹��
	// Beeto�� �浹ü�� �����״´�.
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder() ||
		(int)GlobalValue::CollisionGroup::PlayerJumpAttack == _Other->GetOrder())
	{
		// �� ü���� ��� ���� �״´�.
		m_BeetoBasicInfo.SubtractHP(1);

		if (0 == m_BeetoBasicInfo.GetHP())
		{
			// Beeto �״� ������� �Ѿ�� �浹ü�� ���� �״´�.
			m_BeetoCol->Death();

			// ���¸� �ٲ۴�.
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

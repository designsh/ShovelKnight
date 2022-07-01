#include "EnchantressBrokenTile.h"
#include "Enchantress_FinalBoss.h"

// ��������
void EnchantressBrokenTile::IdleStart()
{
	m_AniBrokenObject->ChangeAnimation(L"BrokenObject_Idle");
}

void EnchantressBrokenTile::IdleStay()
{

}

void EnchantressBrokenTile::IdleEnd()
{

}

// �������
void EnchantressBrokenTile::DieStart()
{
	m_AniBrokenObject->ChangeAnimation(L"BrokenObject_Death");
}

void EnchantressBrokenTile::DieStay()
{
	if (true == m_AniBrokenObject->IsEnd())
	{
		// ������ ����ִ� �ڷᱸ���� �������ش�.
		GlobalValue::FinalStage_FinalBoss->DelBrokenObject(m_iMyIndexX, m_iMyIndexY);

		// ���� �״´�.
		Death();
	}
}

void EnchantressBrokenTile::DieEnd()
{

}
#include "EnchantressBrokenTile.h"
#include "Enchantress_FinalBoss.h"

// 생성상태
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

// 사망상태
void EnchantressBrokenTile::DieStart()
{
	m_AniBrokenObject->ChangeAnimation(L"BrokenObject_Death");
}

void EnchantressBrokenTile::DieStay()
{
	if (true == m_AniBrokenObject->IsEnd())
	{
		// 보스가 들고있는 자료구조도 삭제해준다.
		GlobalValue::FinalStage_FinalBoss->DelBrokenObject(m_iMyIndexX, m_iMyIndexY);

		// 나는 죽는다.
		Death();
	}
}

void EnchantressBrokenTile::DieEnd()
{

}
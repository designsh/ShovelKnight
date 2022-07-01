#include "Enchantress_ShovelKnight.h"

void Enchantress_ShovelKnight::SetPlayerInfomation()
{
	m_PlayerInfo.SetMoveSpeed(200.f);
	m_PlayerInfo.SetHoldingGold(0);
	m_PlayerInfo.SetMaxHoldingGold(9999);
	m_PlayerInfo.SetCurHP(8);
	m_PlayerInfo.SetMaxHP(8);
	m_PlayerInfo.SetCurMP(30);
	m_PlayerInfo.SetMaxMP(30);
}

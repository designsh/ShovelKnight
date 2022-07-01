#include "LevelMap.h"

#include "GlobalValue.h"
#include "PlayerMaker.h"

#include "Plains_Icon.h"             // 스테이지1 아이콘
#include "None_Icon.h"             // 경유지       아이콘
#include "Enchantress_Icon.h"  // 최종보스    아이콘
#include "MapCloud.h"             // 맵 가림막(구름)

void LevelMap::LevelMapCreateObject()
{
	//---------------------------------------------- Level Map Icon ----------------------------------------------//
	m_PlainsIcon = CreateActor<Plains_Icon>();
	m_PlainsIcon->SetPosition({ 272.f, 592.f });

	m_NoneIcon = CreateActor<None_Icon>();
	m_NoneIcon->SetPosition({ 272.f, 336.f });

	m_EnchantressIcon = CreateActor<Enchantress_Icon>();
	m_EnchantressIcon->SetPosition({ 560.f, 336.f });

	m_MapCloud = CreateActor<MapCloud>();
	m_MapCloud->SetPosition({ 860.f, 360.f });

	// 각 아이콘 위치를 이용하여 플레이어의 러프 포인트를 알아낸다.
	GlobalValue::LevelMapPlayer->SetPlayerLerpPoint(m_PlainsIcon->GetPosition(), m_NoneIcon->GetPosition(), m_EnchantressIcon->GetPosition());
}

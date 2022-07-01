#include "LevelMap.h"

#include "GlobalValue.h"
#include "PlayerMaker.h"

#include "Plains_Icon.h"             // ��������1 ������
#include "None_Icon.h"             // ������       ������
#include "Enchantress_Icon.h"  // ��������    ������
#include "MapCloud.h"             // �� ������(����)

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

	// �� ������ ��ġ�� �̿��Ͽ� �÷��̾��� ���� ����Ʈ�� �˾Ƴ���.
	GlobalValue::LevelMapPlayer->SetPlayerLerpPoint(m_PlainsIcon->GetPosition(), m_NoneIcon->GetPosition(), m_EnchantressIcon->GetPosition());
}

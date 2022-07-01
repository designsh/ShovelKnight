#include "Enchantress_FinalBoss.h"

void Enchantress_FinalBoss::Create_BossBeShotImage()
{
	// ���� Ÿ���̹���
	m_LeftBeShotImage = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::Monster + 1);
	m_LeftBeShotImage->TransCenterSetting(L"Left_The_Enchantress_BeShot.bmp", { 512.f, 2688.f });
	m_LeftBeShotImage->SetCutData(0);
	m_LeftBeShotImage->SetRenderScale({ 350, 350 });
	m_LeftBeShotImage->Off();

	// ������ Ÿ���̹���
	m_RightBeShotImage = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::Monster + 1);
	m_RightBeShotImage->TransCenterSetting(L"Right_The_Enchantress_BeShot.bmp", { 512.f, 2688.f });
	m_RightBeShotImage->SetCutData(0);
	m_RightBeShotImage->SetRenderScale({ 350, 350 });
	m_RightBeShotImage->Off();
}

#include "Enchantress_StateBar.h"
#include <SGameEngineWindow.h>

#include "GlobalValue.h"
#include "Enchantress_ShovelKnight.h"
#include "Enchantress_FinalBoss.h"

// Static Var

// Static Func

// member Var
Enchantress_StateBar::Enchantress_StateBar()
	: m_WindowSize(FLOAT4::ZERO),
	m_TopBar(nullptr), m_PlayerHP(nullptr), m_FinalBossHP(nullptr),
	m_ListPlayerHP(), m_ListPlayerHoldingGold(), m_ListPlayerMP(), m_ListFinalBossHP(),
	m_iPlayerHP(0), m_iPlayerMaxHP(0), m_iPlayerMP(0), m_iPlayerMaxMP(0), m_iPlayerHoldingGold(0), m_iPlayerMaxHoldingGold(0),
	m_iFinalBossHP(0), m_iFinalBossMaxHP(0),
	m_iPrevGold(0)
{

}

Enchantress_StateBar::~Enchantress_StateBar()
{

}

// member Func
void Enchantress_StateBar::Start()
{
	// 현재 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 이미지 Setting

	// 상태바 전체
	m_TopBar = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::StateBar);
	m_TopBar->TransCenterSetting(L"Enchantress_PlayerStateBar.bmp", { 1280, 50 });
	m_TopBar->SetPivotPos({ m_WindowSize.x * 0.5f, m_WindowSize.y * 0.5f - 335.f });
	m_TopBar->CamEffectOff();

	// Player 체력
	// 플레이어 체력가져와서 Max체력만큼 생성
	if (nullptr == GlobalValue::FinalStage_MainPlayer)
	{
		return;
	}
	m_iPlayerHP = GlobalValue::FinalStage_MainPlayer->m_PlayerInfo.GetCurHP();
	m_iPlayerMaxHP = GlobalValue::FinalStage_MainPlayer->m_PlayerInfo.GetMaxHP();
	m_iPlayerMP = GlobalValue::FinalStage_MainPlayer->m_PlayerInfo.GetCurMP();
	m_iPlayerMaxMP = GlobalValue::FinalStage_MainPlayer->m_PlayerInfo.GetMaxMP();
	m_iPlayerHoldingGold = GlobalValue::FinalStage_MainPlayer->m_PlayerInfo.GetHoldingGold();

	// 하트 1개당 체력 2
	// 빈 : 0, 중간 : 1, 꽉 : 2
	for (int i = 0; i < m_iPlayerMaxHP / 2; i++)
	{
		SGameEngineRendererBasic* PlayerHPRenderer = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::StateBar + 1);
		PlayerHPRenderer->TransCenterSetting(L"Enchantress_PlayerHP.bmp", { 40,38 });
		PlayerHPRenderer->SetPivotPos(FLOAT4(570.f + (36.f * i), 34.f));
		PlayerHPRenderer->SetCutData(2);
		PlayerHPRenderer->CamEffectOff();
		m_ListPlayerHP.push_back(PlayerHPRenderer);
	}

	// 골드량
	m_iPlayerHoldingGold = GlobalValue::FinalStage_MainPlayer->m_PlayerInfo.GetHoldingGold();
	m_iPlayerMaxHoldingGold = GlobalValue::FinalStage_MainPlayer->m_PlayerInfo.GetMaxHoldingGold();
	SGameEngineString GoldText = SGameEngineString::ToString(m_iPlayerMaxHoldingGold);
	int GoldTextLen = static_cast<int>(GoldText.size());
	for (int i = 0; i < GoldTextLen; i++)
	{
		SGameEngineRendererBasic* PlayerGoldRenderer = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::StateBar + 1);
		PlayerGoldRenderer->TransCenterSetting(L"Enchantress_NumberText.bmp", { 60, 20 });
		PlayerGoldRenderer->SetPivotPos(FLOAT4(65.f + (25.f * i), 36.f));
		PlayerGoldRenderer->SetCutData(0);
		PlayerGoldRenderer->CamEffectOff();
		PlayerGoldRenderer->Off();
		m_ListPlayerHoldingGold.push_back(PlayerGoldRenderer);
	}

	// 마력
	m_iPlayerMP = GlobalValue::FinalStage_MainPlayer->m_PlayerInfo.GetCurMP();
	m_iPlayerMaxMP = GlobalValue::FinalStage_MainPlayer->m_PlayerInfo.GetMaxMP();
	SGameEngineString MPText = SGameEngineString::ToString(m_iPlayerMaxMP);
	int MPTextLen = static_cast<int>(MPText.size());
	for (int i = 0; i < MPTextLen; i++)
	{
		SGameEngineRendererBasic* PlayerMPRenderer = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::StateBar + 1);
		PlayerMPRenderer->TransCenterSetting(L"Enchantress_NumberTextColor.bmp", { 60, 20 });
		PlayerMPRenderer->SetPivotPos(FLOAT4(308.f + (25.f * i), 36.f));
		PlayerMPRenderer->SetCutData(0);
		PlayerMPRenderer->CamEffectOff();
		PlayerMPRenderer->Off();
		m_ListPlayerMP.push_back(PlayerMPRenderer);
	}

	// FinalBoss 체력
	if (nullptr == GlobalValue::FinalBoss)
	{
		return;
	}

	m_iFinalBossHP = GlobalValue::FinalStage_FinalBoss->m_EnchantressInfo.GetHP();
	m_iFinalBossMaxHP = GlobalValue::FinalStage_FinalBoss->m_EnchantressInfo.GetMaxHP();

	// 하트 1개당 체력 2
	// 빈 : 0, 중간 : 1, 꽉 : 2
	for (int i = 0; i < m_iFinalBossMaxHP / 2; i++)
	{
		SGameEngineRendererBasic* FinalBossHPRenderer = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::StateBar + 1);
		FinalBossHPRenderer->TransCenterSetting(L"Enchantress_FinalBossHP.bmp", { 40,38 });
		FinalBossHPRenderer->SetPivotPos(FLOAT4(1100.f + (36.f * i), 34.f));
		FinalBossHPRenderer->SetCutData(2);
		FinalBossHPRenderer->CamEffectOff();
		m_ListFinalBossHP.push_back(FinalBossHPRenderer);
	}
}

void Enchantress_StateBar::Update()
{
	// 플레이어 체력 갱신
	int PlayerHP = GlobalValue::FinalStage_MainPlayer->m_PlayerInfo.GetCurHP();
	int PlayerMaxHP = GlobalValue::FinalStage_MainPlayer->m_PlayerInfo.GetMaxHP();

	std::list<SGameEngineRendererBasic*>::iterator PlayerHPRendererStart = m_ListPlayerHP.begin();
	std::list<SGameEngineRendererBasic*>::iterator PlayerHPRendererEnd = m_ListPlayerHP.end();
	for (; PlayerHPRendererStart != PlayerHPRendererEnd; ++PlayerHPRendererStart)
	{
		if (PlayerHP >= 2)
		{
			(*PlayerHPRendererStart)->SetCutData(0);
			PlayerHP = PlayerHP - 2;
		}
		else if (PlayerHP >= 1)
		{
			(*PlayerHPRendererStart)->SetCutData(1);
			PlayerHP = PlayerHP - 1;
		}
		else
		{
			(*PlayerHPRendererStart)->SetCutData(2);
		}
	}

	// 플레이어 골드량 갱신
	int PlayerGold = GlobalValue::FinalStage_MainPlayer->m_PlayerInfo.GetHoldingGold();
	SGameEngineString GoldText = SGameEngineString::ToString(PlayerGold);
	std::list<SGameEngineRendererBasic*>::iterator PlayerGoldRendererStart = m_ListPlayerHoldingGold.begin();
	std::list<SGameEngineRendererBasic*>::iterator PlayerGoldRendererEnd = m_ListPlayerHoldingGold.end();
	for (int Textindex = 0; Textindex < GoldText.size(); ++Textindex)
	{
		(*PlayerGoldRendererStart)->On();

		char Text = static_cast<char>(GoldText[Textindex]);
		if ('0' == Text)
		{
			(*PlayerGoldRendererStart)->SetCutData(0);
		}
		else if ('1' == Text)
		{
			(*PlayerGoldRendererStart)->SetCutData(1);
		}
		else if ('2' == Text)
		{
			(*PlayerGoldRendererStart)->SetCutData(2);
		}
		else if ('3' == Text)
		{
			(*PlayerGoldRendererStart)->SetCutData(3);
		}
		else if ('4' == Text)
		{
			(*PlayerGoldRendererStart)->SetCutData(4);
		}
		else if ('5' == Text)
		{
			(*PlayerGoldRendererStart)->SetCutData(5);
		}
		else if ('6' == Text)
		{
			(*PlayerGoldRendererStart)->SetCutData(6);
		}
		else if ('7' == Text)
		{
			(*PlayerGoldRendererStart)->SetCutData(7);
		}
		else if ('8' == Text)
		{
			(*PlayerGoldRendererStart)->SetCutData(8);
		}
		else if ('9' == Text)
		{
			(*PlayerGoldRendererStart)->SetCutData(9);
		}

		PlayerGoldRendererStart++;
	}

	// 플레이어 마력 갱신
	int PlayerMP = GlobalValue::FinalStage_MainPlayer->m_PlayerInfo.GetCurMP();
	SGameEngineString MPText = SGameEngineString::ToString(PlayerMP);
	std::list<SGameEngineRendererBasic*>::iterator PlayerMPRendererStart = m_ListPlayerMP.begin();
	std::list<SGameEngineRendererBasic*>::iterator PlayerMPRendererEnd = m_ListPlayerMP.end();
	for (int Textindex = 0; Textindex < MPText.size(); ++Textindex)
	{
		(*PlayerMPRendererStart)->On();

		char Text = static_cast<char>(MPText[Textindex]);
		if ('0' == Text)
		{
			(*PlayerMPRendererStart)->SetCutData(0);
		}
		else if ('1' == Text)
		{
			(*PlayerMPRendererStart)->SetCutData(1);
		}
		else if ('2' == Text)
		{
			(*PlayerMPRendererStart)->SetCutData(2);
		}
		else if ('3' == Text)
		{
			(*PlayerMPRendererStart)->SetCutData(3);
		}
		else if ('4' == Text)
		{
			(*PlayerMPRendererStart)->SetCutData(4);
		}
		else if ('5' == Text)
		{
			(*PlayerMPRendererStart)->SetCutData(5);
		}
		else if ('6' == Text)
		{
			(*PlayerMPRendererStart)->SetCutData(6);
		}
		else if ('7' == Text)
		{
			(*PlayerMPRendererStart)->SetCutData(7);
		}
		else if ('8' == Text)
		{
			(*PlayerMPRendererStart)->SetCutData(8);
		}
		else if ('9' == Text)
		{
			(*PlayerMPRendererStart)->SetCutData(9);
		}

		PlayerMPRendererStart++;
	}

	// 보스 체력갱신
	FLOAT4 BossHPCreatePos = GetScene()->GetCamPos() - GlobalValue::FinalStage_FinalBoss->GetPosition();
	if (1280.0f >= FLOAT4::Len2D(BossHPCreatePos))
	{
		int FinalBossHP = GlobalValue::FinalStage_FinalBoss->m_EnchantressInfo.GetHP();
		int FinalBossMaxHP = GlobalValue::FinalStage_FinalBoss->m_EnchantressInfo.GetMaxHP();

		std::list<SGameEngineRendererBasic*>::iterator FinalBossHPRendererStart = m_ListFinalBossHP.begin();
		std::list<SGameEngineRendererBasic*>::iterator FinalBossHPRendererEnd = m_ListFinalBossHP.end();
		for (; FinalBossHPRendererStart != FinalBossHPRendererEnd; ++FinalBossHPRendererStart)
		{
			if (FinalBossHP >= 2)
			{
				(*FinalBossHPRendererStart)->SetCutData(0);
				FinalBossHP = FinalBossHP - 2;
			}
			else if (FinalBossHP >= 1)
			{
				(*FinalBossHPRendererStart)->SetCutData(1);
				FinalBossHP = FinalBossHP - 1;
			}
			else
			{
				(*FinalBossHPRendererStart)->SetCutData(2);
			}
		}
	}
}

void Enchantress_StateBar::DebugRender()
{

}

#include "Plains.h"
#include "Beeto.h"                        // 기본급 몬스터(Beeto)
#include "SkullSoldier.h"               // 기본급 몬스터(SkullSoldier)
#include "Slime.h"                         // 기본급 몬스터(Slime)
#include "Dragon.h"                     // 기본급 몬스터(Dragon)
#include "Dozedrake.h"                // 중간보스급 몬스터(Dozedrake)
#include "BlackKnight.h"              // 최종보스급 본스터(BlackKnight)

#include "GlobalValue.h"

void Plains::PlainsCreateMonster()
{
	//---------------------------------------------- Beeto ----------------------------------------------//
	m_Beeto1 = CreateActor<Beeto>();
	m_Beeto1->SetPosition({ 1700.f, 2789.f });
	m_Beeto1->SetMoveDirect(GlobalValue::BasicMoveType::Left);

	m_Beeto2 = CreateActor<Beeto>();
	m_Beeto2->SetPosition({ 2115.f, 2562.f });
	m_Beeto2->SetMoveDirect(GlobalValue::BasicMoveType::Left);

	m_Beeto3 = CreateActor<Beeto>();
	m_Beeto3->SetPosition({ 2984.f, 2789.f });
	m_Beeto3->SetMoveDirect(GlobalValue::BasicMoveType::Left);

	m_Beeto4 = CreateActor<Beeto>();
	m_Beeto4->SetPosition({ 2780.f, 2789.f });
	m_Beeto4->SetMoveDirect(GlobalValue::BasicMoveType::Left);

	m_Beeto5 = CreateActor<Beeto>();
	m_Beeto5->SetPosition({ 3430.f, 2789.f });
	m_Beeto5->SetMoveDirect(GlobalValue::BasicMoveType::Left);

	m_Beeto6 = CreateActor<Beeto>();
	m_Beeto6->SetPosition({ 3660.f, 2789.f });
	m_Beeto6->SetMoveDirect(GlobalValue::BasicMoveType::Left);

	m_Beeto7 = CreateActor<Beeto>();
	m_Beeto7->SetPosition({ 6150.f, 2789.f });
	m_Beeto7->SetMoveDirect(GlobalValue::BasicMoveType::Left);

	m_Beeto8 = CreateActor<Beeto>();
	m_Beeto8->SetPosition({ 7630.f, 1795.f });
	m_Beeto8->SetMoveDirect(GlobalValue::BasicMoveType::Left);

	m_Beeto9 = CreateActor<Beeto>();
	m_Beeto9->SetPosition({ 9979.f, 4162.f });
	m_Beeto9->SetMoveDirect(GlobalValue::BasicMoveType::Left);

	m_Beeto10 = CreateActor<Beeto>();
	m_Beeto10->SetPosition({ 18565.f, 520.f });
	m_Beeto10->SetMoveDirect(GlobalValue::BasicMoveType::Right);

	m_Beeto11 = CreateActor<Beeto>();
	m_Beeto11->SetPosition({ 18886.f, 616.f });
	m_Beeto11->SetMoveDirect(GlobalValue::BasicMoveType::Left);

	//---------------------------------------------- SkullSoldier ----------------------------------------------//
	m_SkullSoldier1 = CreateActor<SkullSoldier>();
	m_SkullSoldier1->SetPosition({ 9330.f, 2590.f });
	m_SkullSoldier1->SetMoveDiect(GlobalValue::BasicMoveType::Right);

	m_SkullSoldier2 = CreateActor<SkullSoldier>();
	m_SkullSoldier2->SetPosition({ 9200.f, 4126.f });
	m_SkullSoldier2->SetMoveDiect(GlobalValue::BasicMoveType::Right);

	m_SkullSoldier3 = CreateActor<SkullSoldier>();
	m_SkullSoldier3->SetPosition({ 18536.f, 1980.f });
	m_SkullSoldier3->SetMoveDiect(GlobalValue::BasicMoveType::Right);

	m_SkullSoldier4 = CreateActor<SkullSoldier>();
	m_SkullSoldier4->SetPosition({ 13506.f, 2492.f });
	m_SkullSoldier4->SetMoveDiect(GlobalValue::BasicMoveType::Right);

	//---------------------------------------------- Slime ----------------------------------------------//
	//m_Slime1 = CreateActor<Slime>();
	//m_Slime1->SetPosition({ 9680.f, 3060.f });
	//m_Slime1->SetInitMove(GlobalValue::BasicMoveType::Left);
	//m_Slime1->SetJumpTime(3.0f);

	//m_Slime2 = CreateActor<Slime>();
	//m_Slime2->SetPosition({ 9880.f, 3060.f });
	//m_Slime2->SetInitMove(GlobalValue::BasicMoveType::Left);
	//m_Slime2->SetJumpTime(5.0f);

	m_Slime3 = CreateActor<Slime>();
	m_Slime3->SetPosition({ 10655.f, 4180.f });
	m_Slime3->SetInitMove(GlobalValue::BasicMoveType::Right);
	m_Slime3->SetJumpTime(3.0f);

	m_Slime4 = CreateActor<Slime>();
	m_Slime4->SetPosition({ 14988.f, 1974.f });
	m_Slime4->SetInitMove(GlobalValue::BasicMoveType::Left);
	m_Slime4->SetJumpTime(3.0f);

	m_Slime5 = CreateActor<Slime>();
	m_Slime5->SetPosition({ 18772.f, 1400.f });
	m_Slime5->SetInitMove(GlobalValue::BasicMoveType::Left);
	m_Slime5->SetJumpTime(3.0f);

	m_Slime6 = CreateActor<Slime>();
	m_Slime6->SetPosition({ 18472.f, 1400.f });
	m_Slime6->SetInitMove(GlobalValue::BasicMoveType::Right);
	m_Slime6->SetJumpTime(1.0f);

	//---------------------------------------------- Dragon ----------------------------------------------//
	m_Dragon1 = CreateActor<Dragon>();
	m_Dragon1->SetPosition({ 10930.f, 3890.f });
	m_Dragon1->SetStartMoveDirect(GlobalValue::BasicMoveType::Right);
	m_Dragon1->SetMaxMoveDist(FLOAT4(200.f, 0.f));
	m_Dragon1->DropCoinOn();

	m_Dragon2 = CreateActor<Dragon>();
	m_Dragon2->SetPosition({ 13113.f, 3274.f });
	m_Dragon2->SetStartMoveDirect(GlobalValue::BasicMoveType::Right);
	m_Dragon2->SetMaxMoveDist(FLOAT4(30.f, 0.f));
	m_Dragon2->DropCoinOn();

	m_Dragon3 = CreateActor<Dragon>();
	m_Dragon3->SetPosition({ 14334.f, 1754.f });
	m_Dragon3->SetStartMoveDirect(GlobalValue::BasicMoveType::Right);
	m_Dragon3->SetMaxMoveDist(FLOAT4(200.f, 0.f));
	m_Dragon3->DropCoinOn();

	m_Dragon4 = CreateActor<Dragon>();
	m_Dragon4->SetPosition({ 12970.f, 2492.f });
	m_Dragon4->SetStartMoveDirect(GlobalValue::BasicMoveType::Right);
	m_Dragon4->SetMaxMoveDist(FLOAT4(100.f, 0.f));
	m_Dragon4->DropCoinOn();

	m_Dragon5 = CreateActor<Dragon>();
	m_Dragon5->SetPosition({ 18182.f, 330.f });
	m_Dragon5->SetStartMoveDirect(GlobalValue::BasicMoveType::Right);
	m_Dragon5->SetMaxMoveDist(FLOAT4(100.f, 0.f));

	//---------------------------------------------- Dozedrake ----------------------------------------------//
	m_Dozedrake1 = CreateActor<Dozedrake>();
	m_Dozedrake1->SetPosition({ 9710.f, 2020.f });

	m_Dozedrake2 = CreateActor<Dozedrake>();
	m_Dozedrake2->SetPosition({ 17400.f, 2125.f });

	//-------------------------------------------- Black Knight ----------------------------------------------//
	m_FinalBoss = CreateActor<BlackKnight>();
	m_FinalBoss->SetPosition({ 21524.f, 600.f }); // 원래 위치
	m_FinalBoss->SetMoveDirect(GlobalValue::BasicMoveType::Left);
	GlobalValue::FinalBoss = m_FinalBoss;

}

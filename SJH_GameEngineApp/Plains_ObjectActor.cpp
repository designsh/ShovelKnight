#include "Plains.h"
#include "StoneObject.h"             // 광산더미
#include "DirtBlock.h"                  // 흙더미
#include "DirtBlock_Small.h"       // 흙더미(Small)
#include "PileBubbles.h"              // 말뚝 거품
#include "SavePoint.h"                 // 체크포인트(SavePoint)
#include "GoldObject.h"              // 골드오브젝트
#include "Platter.h"                      // 체력박스(Platter)

#include "GlobalValue.h"

void Plains::PlainsCreateObject()
{
	//---------------------------------------------- Stone ----------------------------------------------//
	m_Stone1 = CreateActor<StoneObject>();
	m_Stone1->SetPosition({ 1040.f, 2770.f });

	m_Stone2 = CreateActor<StoneObject>();
	m_Stone2->SetPosition({ 2782.f, 2770.f });

	m_Stone3 = CreateActor<StoneObject>();
	m_Stone3->SetPosition({ 6000.f, 2770.f });

	m_Stone4 = CreateActor<StoneObject>();
	m_Stone4->SetPosition({ 9147.f, 3538.f });

	m_Stone5 = CreateActor<StoneObject>();
	m_Stone5->SetPosition({ 8291.f, 4144.f });

	m_Stone6 = CreateActor<StoneObject>();
	m_Stone6->SetPosition({ 13616.f, 2512.f });

	m_Stone7 = CreateActor<StoneObject>();
	m_Stone7->SetPosition({ 18551.f, 1074.f });

	m_Stone8 = CreateActor<StoneObject>();
	m_Stone8->SetPosition({ 18082.f, 1234.f });

	m_Stone9 = CreateActor<StoneObject>();
	m_Stone9->SetPosition({ 16642.f, 626.f });

	//---------------------------------------------- DirtBlock ----------------------------------------------//
	m_DirtBlock1 = CreateActor<DirtBlock>();
	m_DirtBlock1->SetPosition({ 2671.f, 2526.f });
	m_DirtBlock1->DropCoinOn();

	m_DirtBlock2 = CreateActor<DirtBlock>();
	m_DirtBlock2->SetPosition({ 3472.f, 2462.f });
	m_DirtBlock2->DropCoinOn();

	m_DirtBlock3 = CreateActor<DirtBlock>();
	m_DirtBlock3->SetPosition({ 4749.f, 2654.f });

	m_DirtBlock4 = CreateActor<DirtBlock>();
	m_DirtBlock4->SetPosition({ 4749.f, 2586.f });

	m_DirtBlock5 = CreateActor<DirtBlock>();
	m_DirtBlock5->SetPosition({ 4749.f, 2518.f });

	m_DirtBlock6 = CreateActor<DirtBlock>();
	m_DirtBlock6->SetPosition({ 4749.f, 2450.f });

	m_DirtBlock7 = CreateActor<DirtBlock>();
	m_DirtBlock7->SetPosition({ 5376.f, 2658.f });
	m_DirtBlock7->DropCoinOn();

	m_DirtBlock8 = CreateActor<DirtBlock>();
	m_DirtBlock8->SetPosition({ 5662.f, 2594.f });

	m_DirtBlock9 = CreateActor<DirtBlock>();
	m_DirtBlock9->SetPosition({ 5662.f, 2662.f });

	m_DirtBlock10 = CreateActor<DirtBlock>();
	m_DirtBlock10->SetPosition({ 7935.f, 1984.f });
	m_DirtBlock10->DropCoinOn();

	m_DirtBlock11 = CreateActor<DirtBlock>();
	m_DirtBlock11->SetPosition({ 8782.f, 1984.f });
	m_DirtBlock11->DropCoinOn();

	m_DirtBlock12 = CreateActor<DirtBlock>();
	m_DirtBlock12->SetPosition({ 10015.f, 3180.f });

	m_DirtBlock13 = CreateActor<DirtBlock>();
	m_DirtBlock13->SetPosition({ 10015.f, 3248.f });

	m_DirtBlock14 = CreateActor<DirtBlock>();
	m_DirtBlock14->SetPosition({ 10015.f, 3316.f });

	m_DirtBlock15 = CreateActor<DirtBlock>();
	m_DirtBlock15->SetPosition({ 10015.f, 3384.f });

	m_DirtBlock16 = CreateActor<DirtBlock>();
	m_DirtBlock16->SetPosition({ 10655.f, 3845.f });

	m_DirtBlock17 = CreateActor<DirtBlock>();
	m_DirtBlock17->SetPosition({ 10720.f, 3845.f });

	m_DirtBlock18 = CreateActor<DirtBlock>();
	m_DirtBlock18->SetPosition({ 10655.f, 3910.f });

	m_DirtBlock19 = CreateActor<DirtBlock>();
	m_DirtBlock19->SetPosition({ 10720.f, 3910.f });

	m_DirtBlock20 = CreateActor<DirtBlock>();
	m_DirtBlock20->SetPosition({ 10788.f, 4160.f });

	m_DirtBlock21 = CreateActor<DirtBlock>();
	m_DirtBlock21->SetPosition({ 10856.f, 4160.f });

	m_DirtBlock22 = CreateActor<DirtBlock>();
	m_DirtBlock22->SetPosition({ 10788.f, 4095.f });

	m_DirtBlock23 = CreateActor<DirtBlock>();
	m_DirtBlock23->SetPosition({ 10856.f, 4095.f });

	m_DirtBlock24 = CreateActor<DirtBlock>();
	m_DirtBlock24->SetPosition({ 10788.f, 4030.f });

	m_DirtBlock25 = CreateActor<DirtBlock>();
	m_DirtBlock25->SetPosition({ 10856.f, 4030.f });

	m_DirtBlock26 = CreateActor<DirtBlock>();
	m_DirtBlock26->SetPosition({ 10788.f, 3965.f });

	m_DirtBlock27 = CreateActor<DirtBlock>();
	m_DirtBlock27->SetPosition({ 10856.f, 3965.f });

	m_DirtBlock28 = CreateActor<DirtBlock>();
	m_DirtBlock28->SetPosition({ 11098.f, 4160.f });

	m_DirtBlock29 = CreateActor<DirtBlock>();
	m_DirtBlock29->SetPosition({ 11165.f, 4160.f });

	m_DirtBlock30 = CreateActor<DirtBlock>();
	m_DirtBlock30->SetPosition({ 11165.f, 4093.f });

	m_DirtBlock31 = CreateActor<DirtBlock>();
	m_DirtBlock31->SetPosition({ 11232.f, 4160.f });

	m_DirtBlock32 = CreateActor<DirtBlock>();
	m_DirtBlock32->SetPosition({ 11232.f, 4093.f });

	m_DirtBlock33 = CreateActor<DirtBlock>();
	m_DirtBlock33->SetPosition({ 11232.f, 4026.f });

	m_DirtBlock34 = CreateActor<DirtBlock>();
	m_DirtBlock34->SetPosition({ 11299.f, 4160.f });

	m_DirtBlock35 = CreateActor<DirtBlock>();
	m_DirtBlock35->SetPosition({ 11299.f, 4093.f });

	m_DirtBlock36 = CreateActor<DirtBlock>();
	m_DirtBlock36->SetPosition({ 11299.f, 4026.f });

	m_DirtBlock37 = CreateActor<DirtBlock>();
	m_DirtBlock37->SetPosition({ 11299.f, 3959.f });

	m_DirtBlock38 = CreateActor<DirtBlock>();
	m_DirtBlock38->SetPosition({ 11366.f, 4160.f });

	m_DirtBlock39 = CreateActor<DirtBlock>();
	m_DirtBlock39->SetPosition({ 11366.f, 4093.f });

	m_DirtBlock40 = CreateActor<DirtBlock>();
	m_DirtBlock40->SetPosition({ 11366.f, 4026.f });

	m_DirtBlock41 = CreateActor<DirtBlock>();
	m_DirtBlock41->SetPosition({ 11366.f, 3959.f });

	m_DirtBlock42 = CreateActor<DirtBlock>();
	m_DirtBlock42->SetPosition({ 11366.f, 3892.f });

	m_DirtBlock43 = CreateActor<DirtBlock>();
	m_DirtBlock43->SetPosition({ 11433.f, 4026.f });

	m_DirtBlock44 = CreateActor<DirtBlock>();
	m_DirtBlock44->SetPosition({ 11433.f, 3959.f });

	m_DirtBlock45 = CreateActor<DirtBlock>();
	m_DirtBlock45->SetPosition({ 11433.f, 3892.f });

	m_DirtBlock46 = CreateActor<DirtBlock>();
	m_DirtBlock46->SetPosition({ 11500.f, 4026.f });

	m_DirtBlock47 = CreateActor<DirtBlock>();
	m_DirtBlock47->SetPosition({ 11500.f, 3959.f });

	m_DirtBlock48 = CreateActor<DirtBlock>();
	m_DirtBlock48->SetPosition({ 11500.f, 3892.f });

	m_DirtBlock49 = CreateActor<DirtBlock>();
	m_DirtBlock49->SetPosition({ 11567.f, 4160.f });

	m_DirtBlock50 = CreateActor<DirtBlock>();
	m_DirtBlock50->SetPosition({ 11567.f, 4093.f });

	m_DirtBlock51 = CreateActor<DirtBlock>();
	m_DirtBlock51->SetPosition({ 11567.f, 4026.f });

	m_DirtBlock52 = CreateActor<DirtBlock>();
	m_DirtBlock52->SetPosition({ 11567.f, 3959.f });

	m_DirtBlock53 = CreateActor<DirtBlock>();
	m_DirtBlock53->SetPosition({ 11567.f, 3892.f });

	m_DirtBlock54 = CreateActor<DirtBlock>();
	m_DirtBlock54->SetPosition({ 11634.f, 4160.f });

	m_DirtBlock55 = CreateActor<DirtBlock>();
	m_DirtBlock55->SetPosition({ 11634.f, 4093.f });

	m_DirtBlock56 = CreateActor<DirtBlock>();
	m_DirtBlock56->SetPosition({ 11634.f, 4026.f });

	m_DirtBlock57 = CreateActor<DirtBlock>();
	m_DirtBlock57->SetPosition({ 11634.f, 3959.f });

	m_DirtBlock58 = CreateActor<DirtBlock>();
	m_DirtBlock58->SetPosition({ 11701.f, 4160.f });

	m_DirtBlock59 = CreateActor<DirtBlock>();
	m_DirtBlock59->SetPosition({ 11701.f, 4093.f });

	m_DirtBlock60 = CreateActor<DirtBlock>();
	m_DirtBlock60->SetPosition({ 11701.f, 4026.f });

	m_DirtBlock61 = CreateActor<DirtBlock>();
	m_DirtBlock61->SetPosition({ 11768.f, 4160.f });

	m_DirtBlock62 = CreateActor<DirtBlock>();
	m_DirtBlock62->SetPosition({ 14900.f, 3328.f });
	m_DirtBlock62->DropCoinOn();

	m_DirtBlock63 = CreateActor<DirtBlock>();
	m_DirtBlock63->SetPosition({ 16576.f, 1858.f });

	m_DirtBlock64 = CreateActor<DirtBlock>();
	m_DirtBlock64->SetPosition({ 16643.f, 1858.f });

	m_DirtBlock65 = CreateActor<DirtBlock>();
	m_DirtBlock65->SetPosition({ 18664.f, 1124.f });

	m_DirtBlock66 = CreateActor<DirtBlock>();
	m_DirtBlock66->SetPosition({ 18734.f, 1124.f });

	m_DirtBlock67 = CreateActor<DirtBlock>();
	m_DirtBlock67->SetPosition({ 18804.f, 1124.f });

	m_DirtBlock68 = CreateActor<DirtBlock>();
	m_DirtBlock68->SetPosition({ 18874.f, 1124.f });

	//---------------------------------------------- DirtBlock(Small) ----------------------------------------------//
	m_DirtSmall1 = CreateActor<DirtBlock_Small>();
	m_DirtSmall1->SetPosition({ 7918.f, 1933.f });
	m_DirtSmall1->DropCoinOn();

	m_DirtSmall2 = CreateActor<DirtBlock_Small>();
	m_DirtSmall2->SetPosition({ 8730.f, 2000.f });
	m_DirtSmall2->DropCoinOn();

	m_DirtSmall3 = CreateActor<DirtBlock_Small>();
	m_DirtSmall3->SetPosition({ 9072.f, 2642.f });

	m_DirtSmall4 = CreateActor<DirtBlock_Small>();
	m_DirtSmall4->SetPosition({ 9106.f, 2642.f });

	m_DirtSmall5 = CreateActor<DirtBlock_Small>();
	m_DirtSmall5->SetPosition({ 9072.f, 2675.f });

	m_DirtSmall6 = CreateActor<DirtBlock_Small>();
	m_DirtSmall6->SetPosition({ 9106.f, 2675.f });

	m_DirtSmall7 = CreateActor<DirtBlock_Small>();
	m_DirtSmall7->SetPosition({ 9072.f, 2707.f });

	m_DirtSmall8 = CreateActor<DirtBlock_Small>();
	m_DirtSmall8->SetPosition({ 9106.f, 2707.f });

	m_DirtSmall9 = CreateActor<DirtBlock_Small>();
	m_DirtSmall9->SetPosition({ 9430.f, 4144.f });

	m_DirtSmall10 = CreateActor<DirtBlock_Small>();
	m_DirtSmall10->SetPosition({ 14849.f, 3344.f });
	m_DirtSmall10->DropCoinOn();

	//---------------------------------------------- PileBubbles ----------------------------------------------//
	m_PileBubbles1 = CreateActor<PileBubbles>();
	m_PileBubbles1->SetPosition({ 6990.f, 2848.f });                        // 초기위치
	m_PileBubbles1->SetMoveTargetPos({ 6990.f, 2550.f });           // 러프 도착점
	m_PileBubbles1->SetLerpSpeed(0.5f);                                         // 러프시간

	m_PileBubbles2 = CreateActor<PileBubbles>();
	m_PileBubbles2->SetPosition({ 13350.f, 4427.f });                        // 초기위치
	m_PileBubbles2->SetMoveTargetPos({ 13350.f, 4200.f });           // 러프 도착점
	m_PileBubbles2->SetLerpSpeed(0.3f);                                         // 러프시간

	m_PileBubbles3 = CreateActor<PileBubbles>();
	m_PileBubbles3->SetPosition({ 14352.f, 3800.f });                        // 초기위치
	m_PileBubbles3->SetMoveTargetPos({ 14352.f, 3400.f });           // 러프 도착점
	m_PileBubbles3->SetLerpSpeed(0.3f);                                         // 러프시간

	m_PileBubbles4 = CreateActor<PileBubbles>();
	m_PileBubbles4->SetPosition({ 14499.f, 3800.f });                        // 초기위치
	m_PileBubbles4->SetMoveTargetPos({ 14499.f, 3380.f });           // 러프 도착점
	m_PileBubbles4->SetLerpSpeed(0.2f);                                         // 러프시간

	m_PileBubbles5 = CreateActor<PileBubbles>();
	m_PileBubbles5->SetPosition({ 15150.f, 3800.f });                        // 초기위치
	m_PileBubbles5->SetMoveTargetPos({ 15150.f, 3400.f });           // 러프 도착점
	m_PileBubbles5->SetLerpSpeed(0.3f);                                         // 러프시간

	m_PileBubbles6 = CreateActor<PileBubbles>();
	m_PileBubbles6->SetPosition({ 15280.f, 3800.f });                        // 초기위치
	m_PileBubbles6->SetMoveTargetPos({ 15280.f, 3380.f });           // 러프 도착점
	m_PileBubbles6->SetLerpSpeed(0.2f);                                         // 러프시간

	m_PileBubbles7 = CreateActor<PileBubbles>();
	m_PileBubbles7->SetPosition({ 17147.f, 803.f });                        // 초기위치
	m_PileBubbles7->SetMoveTargetPos({ 17147.f, 503.f });           // 러프 도착점
	m_PileBubbles7->SetLerpSpeed(0.2f);                                         // 러프시간

	//---------------------------------------------- SavePoint ----------------------------------------------//
	m_SavePoint1 = CreateActor<SavePoint>();
	m_SavePoint1->SetPosition({ 7000.f, 2049.f });

	m_SavePoint2 = CreateActor<SavePoint>();
	m_SavePoint2->SetPosition({ 13025.f, 4129.f });

	m_SavePoint3 = CreateActor<SavePoint>();
	m_SavePoint3->SetPosition({ 13755.f, 1792.f });

	m_SavePoint4 = CreateActor<SavePoint>();
	m_SavePoint4->SetPosition({ 19721.f, 384.f });

	//---------------------------------------------- GoldObject ----------------------------------------------//
	m_GoldObject1 = CreateActor<GoldObject>();
	m_GoldObject1->SetPosition({ 7847.f, 4142.f });
	m_GoldObject1->SetAmountOfGold(50);

	m_GoldObject2 = CreateActor<GoldObject>();
	m_GoldObject2->SetPosition({ 7947.f, 4142.f });
	m_GoldObject2->SetAmountOfGold(50);

	m_GoldObject3 = CreateActor<GoldObject>();
	m_GoldObject3->SetPosition({ 10990.f, 3700.f });
	m_GoldObject3->SetAmountOfGold(50);

	m_GoldObject4 = CreateActor<GoldObject>();
	m_GoldObject4->SetPosition({ 11629.f, 3790.f });
	m_GoldObject4->SetAmountOfGold(100);

	m_GoldObject5 = CreateActor<GoldObject>();
	m_GoldObject5->SetPosition({ 15475.f, 3340.f });
	m_GoldObject5->SetAmountOfGold(50);

	m_GoldObject6 = CreateActor<GoldObject>();
	m_GoldObject6->SetPosition({ 15575.f, 3340.f });
	m_GoldObject6->SetAmountOfGold(50);

	//m_GoldObject7 = CreateActor<GoldObject>();
	//m_GoldObject7->SetPosition({ 15575.f, 3340.f });
	//m_GoldObject7->SetAmountOfGold(50);

	m_GoldObject8 = CreateActor<GoldObject>();
	m_GoldObject8->SetPosition({ 19542.f, 618.f });
	m_GoldObject8->SetAmountOfGold(50);

	m_GoldObject9 = CreateActor<GoldObject>();
	m_GoldObject9->SetPosition({ 6793.f, 1602.f });
	m_GoldObject9->SetAmountOfGold(10);

	m_GoldObject10 = CreateActor<GoldObject>();
	m_GoldObject10->SetPosition({ 6953.f, 1602.f });
	m_GoldObject10->SetAmountOfGold(10);

	m_GoldObject11 = CreateActor<GoldObject>();
	m_GoldObject11->SetPosition({ 7113.f, 1602.f });
	m_GoldObject11->SetAmountOfGold(10);

	m_GoldObject12 = CreateActor<GoldObject>();
	m_GoldObject12->SetPosition({ 13375.f, 2670.f });
	m_GoldObject12->SetAmountOfGold(50);

	m_GoldObject13 = CreateActor<GoldObject>();
	m_GoldObject13->SetPosition({ 13516.f, 2670.f });
	m_GoldObject13->SetAmountOfGold(50);

	m_GoldObject14 = CreateActor<GoldObject>();
	m_GoldObject14->SetPosition({ 13649.f, 2670.f });
	m_GoldObject14->SetAmountOfGold(50);

	m_GoldObject15 = CreateActor<GoldObject>();
	m_GoldObject15->SetPosition({ 13687.f, 2120.f });
	m_GoldObject15->SetAmountOfGold(100);

	m_GoldObject16 = CreateActor<GoldObject>();
	m_GoldObject16->SetPosition({ 13487.f, 2120.f });
	m_GoldObject16->SetAmountOfGold(100);

	m_GoldObject17 = CreateActor<GoldObject>();
	m_GoldObject17->SetPosition({ 17995.f, 1390.f });
	m_GoldObject17->SetAmountOfGold(100);

	m_GoldObject18 = CreateActor<GoldObject>();
	m_GoldObject18->SetPosition({ 18060.f, 1390.f });
	m_GoldObject18->SetAmountOfGold(50);

	m_GoldObject19 = CreateActor<GoldObject>();
	m_GoldObject19->SetPosition({ 18126.f, 1390.f });
	m_GoldObject19->SetAmountOfGold(50);

	//------------------------------------------------- Platter -------------------------------------------------//
	m_Platter1 = CreateActor<Platter>();
	m_Platter1->SetPosition({ 11471.f, 4174.f });
}

// 오브젝트 재생성 타임이벤터
void Plains::ResurrectObject()
{
	if (true == m_PileBubbles1->IsDeath())
	{
		m_PileBubbles1 = CreateActor<PileBubbles>();
		m_PileBubbles1->SetLerpSpeed(0.5f);
		m_PileBubbles1->SetPosition({ 6990.f, 2848.f });
		m_PileBubbles1->SetMoveTargetPos({ 6990.f, 2550.f });
	}

	if (true == m_PileBubbles2->IsDeath())
	{
		m_PileBubbles2 = CreateActor<PileBubbles>();
		m_PileBubbles2->SetPosition({ 13350.f, 4427.f });
		m_PileBubbles2->SetMoveTargetPos({ 13350.f, 4200.f });
		m_PileBubbles2->SetLerpSpeed(0.3f);
	}

	if (true == m_PileBubbles3->IsDeath())
	{
		m_PileBubbles3 = CreateActor<PileBubbles>();
		m_PileBubbles3->SetPosition({ 14352.f, 3800.f });                        // 초기위치
		m_PileBubbles3->SetMoveTargetPos({ 14352.f, 3400.f });           // 러프 도착점
		m_PileBubbles3->SetLerpSpeed(0.3f);                                         // 러프시간
	}

	if (true == m_PileBubbles4->IsDeath())
	{
		m_PileBubbles4 = CreateActor<PileBubbles>();
		m_PileBubbles4->SetPosition({ 14499.f, 3800.f });                        // 초기위치
		m_PileBubbles4->SetMoveTargetPos({ 14499.f, 3380.f });           // 러프 도착점
		m_PileBubbles4->SetLerpSpeed(0.2f);                                         // 러프시간
	}

	if (true == m_PileBubbles5->IsDeath())
	{
		m_PileBubbles5 = CreateActor<PileBubbles>();
		m_PileBubbles5->SetPosition({ 15100.f, 3800.f });                        // 초기위치
		m_PileBubbles5->SetMoveTargetPos({ 15100.f, 3400.f });           // 러프 도착점
		m_PileBubbles5->SetLerpSpeed(0.3f);                                         // 러프시간
	}

	if (true == m_PileBubbles6->IsDeath())
	{
		m_PileBubbles6 = CreateActor<PileBubbles>();
		m_PileBubbles6->SetPosition({ 15280.f, 3800.f });                        // 초기위치
		m_PileBubbles6->SetMoveTargetPos({ 15280.f, 3380.f });           // 러프 도착점
		m_PileBubbles6->SetLerpSpeed(0.2f);                                         // 러프시간
	}

	if (true == m_PileBubbles7->IsDeath())
	{
		m_PileBubbles7 = CreateActor<PileBubbles>();
		m_PileBubbles7->SetPosition({ 17147.f, 803.f });                        // 초기위치
		m_PileBubbles7->SetMoveTargetPos({ 17147.f, 503.f });           // 러프 도착점
		m_PileBubbles7->SetLerpSpeed(0.2f);                                         // 러프시간
	}
}








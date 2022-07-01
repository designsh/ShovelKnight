#include "EndingCredit.h"
#include "EndingText.h"                 // Ending Text(Ending Credit)
#include "CampFire.h"                    // Ending CampFire
#include "Ending_Player.h"            // Ending Player Object

void EndingCredit::EndingCreditCreateObject()
{
	// EndingCredit Scene은 EndingText(엔딩글씨)을 생성한다.
	m_EndingText = CreateActor<EndingText>();
	m_EndingText->SetPosition({ 1280.f * 0.5f, 200.f });

	// EndingCredit Scene은 CampFire(캠프파이어)를 생성한다.
	m_CampFire = CreateActor<CampFire>();
	m_CampFire->SetPosition({ 1280.f * 0.5f, 450.f });

	// EndingCredit Scene은 CampFire(캠프파이어)를 생성한다.
	m_PlayerObject = CreateActor<Ending_Player>();
	m_PlayerObject->SetPosition({ 511.f, 477.f });
}

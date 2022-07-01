#include "EndingCredit.h"
#include "EndingText.h"                 // Ending Text(Ending Credit)
#include "CampFire.h"                    // Ending CampFire
#include "Ending_Player.h"            // Ending Player Object

void EndingCredit::EndingCreditCreateObject()
{
	// EndingCredit Scene�� EndingText(�����۾�)�� �����Ѵ�.
	m_EndingText = CreateActor<EndingText>();
	m_EndingText->SetPosition({ 1280.f * 0.5f, 200.f });

	// EndingCredit Scene�� CampFire(ķ�����̾�)�� �����Ѵ�.
	m_CampFire = CreateActor<CampFire>();
	m_CampFire->SetPosition({ 1280.f * 0.5f, 450.f });

	// EndingCredit Scene�� CampFire(ķ�����̾�)�� �����Ѵ�.
	m_PlayerObject = CreateActor<Ending_Player>();
	m_PlayerObject->SetPosition({ 511.f, 477.f });
}

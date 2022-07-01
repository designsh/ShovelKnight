#include "EndingCredit.h"
#include "EndingBackDrop.h"        // Ending 배경
#include "CampFire_BackDrop.h"  // 캠프파이어 배경

void EndingCredit::EndingCreditCreateBackDrop()
{
	// EndingCredit Scene은 EndingBackDrop(엔딩배경)을 생성한다.
	m_BackDrop = CreateActor<EndingBackDrop>();

	// EndingCredit Scene은 EndingBackDrop(엔딩배경)을 생성한다.
	m_CampFireBackDrop = CreateActor<CampFire_BackDrop>();
	//m_CampFireBackDrop->SetPosition({ 0.f, 360.f });
}

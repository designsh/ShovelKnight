#include "EndingCredit.h"
#include "EndingBackDrop.h"        // Ending ���
#include "CampFire_BackDrop.h"  // ķ�����̾� ���

void EndingCredit::EndingCreditCreateBackDrop()
{
	// EndingCredit Scene�� EndingBackDrop(�������)�� �����Ѵ�.
	m_BackDrop = CreateActor<EndingBackDrop>();

	// EndingCredit Scene�� EndingBackDrop(�������)�� �����Ѵ�.
	m_CampFireBackDrop = CreateActor<CampFire_BackDrop>();
	//m_CampFireBackDrop->SetPosition({ 0.f, 360.f });
}

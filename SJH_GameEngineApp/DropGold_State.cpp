#include "DropGold.h"

// ������(��尡 ����Ǵ� ���⼳������)
void DropGold::IDLEStart()
{
	// �÷��̾� ��ġ�� ���� ���� ���⼳��
	SetMoveDirect();
}

void DropGold::IDLEStay()
{
	m_DropGoldFSM.ChangeState(L"DropGold_Move");
}

void DropGold::IDLEEnd()
{

}

// ��� ������λ���
void DropGold::MoveStart()
{
	SetDropGoldImage(m_DropGold);

	// ����߿� �浹ü Off
	m_DropGoldCol->Off();

	// ��� �Ŀ�����
	m_DropPos = FLOAT4::ZERO;
	m_DropPower = FLOAT4(0.f, -300.f);
	m_DropGravityPower = FLOAT4(0.f, 1000.f);

	// �÷��̾� ��ġ�� ���� ���� ���⼳��
	SetMoveDirect();
}

void DropGold::MoveStay()
{
	MovePosCheck();

	MoveStateCheck();
}

void DropGold::MoveEnd()
{

}

// ��� Blink ������ Delay
void DropGold::TimeDelayStart()
{

}

void DropGold::TimeDelayStay()
{
	// ��� ���� ������Ÿ��
	m_DelayTime -= SGameEngineTimer::FDeltaTime();
	if (0.0f >= m_DelayTime)
	{
		m_DelayTime = 2.f;

		m_DropGoldFSM.ChangeState(L"DropGold_Death");
	}
}

void DropGold::TimeDelayEnd()
{

}

// ��� Blink �� ���� ����
void DropGold::GoldEvaporationStart()
{
	if (0 == m_AlphaEventer.IsEventSize())
	{
		m_AlphaEventer.CreateTimeEvent(0.1f, this, &DropGold::TimeAlphaInEnd, &DropGold::TimeAlphaInStart, &DropGold::TimeAlphaInStay);
		m_AlphaEventer.CreateTimeEvent(0.1f, this, &DropGold::TimeAlphaOutEnd, &DropGold::TimeAlphaOutStart, &DropGold::TimeAlphaOutStay);
		m_AlphaEventer.LoopOn();
	}
}

void DropGold::GoldEvaporationStay()
{
	m_AlphaEventer.Update();

	// �״� Ÿ�̹� �ð� ���
	m_DeathTime -= SGameEngineTimer::FDeltaTime();
	if (0.0f >= m_DeathTime)
	{
		m_DeathTime = 3.f;

		Death();
	}
}

void DropGold::GoldEvaporationEnd()
{

}

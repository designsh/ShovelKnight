#include "SGameEngineCollision.h"
#include "SGameEngineActor.h"

#include <SGameEngineWindow.h>

// Static Var

// Static Func

// member Var
SGameEngineCollision::SGameEngineCollision()
	: m_Actor(nullptr), m_PivotPos(FLOAT4::ZERO), m_ColScale(FLOAT4::ONE), m_Order(0),
	m_Type(COLTYPE::RECT), m_Data(), m_iCheckData(-1)
{
	// �ʱ� �浹ü ������ �⺻�� ����
	// ũ�� : (1, 1)
	// ��ġ : (0, 0)
	// Ÿ�� : Rectangle
}

SGameEngineCollision::~SGameEngineCollision()
{
	// �Ʒ��� ���� �浹ü�� �浹����, �浹��, �浹���� �� 
	// ó���� �̺�Ʈ���� �����Ҵ��ϹǷ�
	// �ش� �浹ü �Ҹ�� �޸𸮸� �����Ѵ�.
	// std::vector<EventBase*> m_StartEvent;
	// std::vector<EventBase*> m_StayEvent;
	// std::vector<EventBase*> m_EndEvent;

	// �浹���� �̺�Ʈ �޸�����
	for (size_t i = 0; i < m_StartEvent.size(); i++)
	{
		delete m_StartEvent[i];
	}

	// �浹�� �̺�Ʈ �޸�����
	for (size_t i = 0; i < m_StartEvent.size(); i++)
	{
		delete m_StayEvent[i];
	}

	// �浹���� �̺�Ʈ �޸�����
	for (size_t i = 0; i < m_StartEvent.size(); i++)
	{
		delete m_EndEvent[i];
	}
}

// member Func
void SGameEngineCollision::SetCheckData(int _iCheckData)
{
	m_iCheckData = _iCheckData;
}

int SGameEngineCollision::GetCheckData()
{
	return m_iCheckData;
}

FLOAT4 SGameEngineCollision::GetPivotPos()
{
	return m_PivotPos;
}

void SGameEngineCollision::SetPivotPos(FLOAT4 _PivotPos)
{
	m_PivotPos = _PivotPos;
}

FLOAT4 SGameEngineCollision::GetPos()
{
	return m_Data.m_Pos;
}

void SGameEngineCollision::SetPos(FLOAT4 _Pos)
{
	m_Data.m_Pos = _Pos;
}

FLOAT4 SGameEngineCollision::GetScale()
{
	return m_Data.m_Size;
}

void SGameEngineCollision::SetScale(FLOAT4 _Scale)
{
	m_Data.m_Size = _Scale;
}

void SGameEngineCollision::SetOrder(int _Order)
{
	m_Order = _Order;
}

int SGameEngineCollision::GetOrder()
{
	return m_Order;
}

void SGameEngineCollision::SetActor(SGameEngineActor* _Actor)
{
	m_Actor = _Actor;
}

SGameEngineActor* SGameEngineCollision::GetActor()
{
	return m_Actor;
}

void SGameEngineCollision::SetCollisionType(COLTYPE _Type)
{
	m_Type = _Type;
}

// ���� ������ ����� ���� �浹ü ������
// �ʱⰪ(��ġ {0,0})�� �����Ƿ� �ش� �浹ü�� ������������ ����Ͽ�
// ��ġ�� �����Ѵ�.
void SGameEngineCollision::CollisionDataUpdate()
{
	m_Data.m_Pos = GetActor()->GetPosition() - m_PivotPos;
}

// �� �浹ü�� �浹�� üũ�Ѵ�.
void SGameEngineCollision::CollisionCheck(SGameEngineCollision* _Other)
{
	COLTYPE ThisColType = m_Type;
	COLTYPE OtherColType = _Other->m_Type;
	
	// �Լ� �����͸� �̿��Ͽ� �� �׷��� �浹ü�� Ÿ���� �����Ѵ�.
	if (true == Coliison2DCheck::ColFunc[(int)ThisColType][(int)OtherColType](m_Data, _Other->m_Data))
	{
		// ���� �浹ü�� �浹�¿� _Other�浹ü�� ���ٸ�
		// ������ �浹�� ���ο��浹�� �浹������ ��Ÿ����.
		if (m_ColSet.end() == m_ColSet.find(_Other))
		{
			UpdateStartEvent(this, _Other);
			_Other->UpdateStartEvent(_Other, this);
		}
		// ���� �浹ü�� �浹�¿� �̹� _Other �浹ü�� �����Ѵٸ�
		// ������ �浹�Ͽ����� ���絵 �浹���� ���¸� ��Ÿ����.
		else
		{
			UpdateStayEvent(this, _Other);
			_Other->UpdateStayEvent(_Other, this);
		}
	}
	// �� �浹ü�� �浹���� �ʾҴٸ�
	else
	{
		// �� �浹ü�� �浹�� ���� ��Ȳ���� 
		// ���� ���� �浹�¿� _Other �浹ü�� �ִٸ�
		// ���� �����ӱ��� ���� _Other�� �浹ü�� �浹���¿�����
		// ���� �����ӿ� ������ �����̴�.
		if (m_ColSet.end() != m_ColSet.find(_Other))
		{
			UpdateEndEvent(this, _Other);
			_Other->UpdateEndEvent(_Other, this);
		}
	}
}

void SGameEngineCollision::ReleaseUpdate()
{
	DebugCheck();

	std::set<SGameEngineCollision*>::iterator ColSetStart = m_ColSet.begin();
	std::set<SGameEngineCollision*>::iterator ColSetEnd = m_ColSet.end();
	for (; ColSetStart != ColSetEnd;)
	{
		for (size_t i = 0; i < m_EndEvent.size(); i++)
		{
			m_EndEvent[i]->CallBack(this, (*ColSetStart));
		}
		(*ColSetStart)->UpdateEndEvent(*ColSetStart, this);
		ColSetStart = m_ColSet.erase(ColSetStart);
	}
}

void SGameEngineCollision::DeathTask()
{
	ReleaseUpdate();
}

void SGameEngineCollision::OffTask()
{
	ReleaseUpdate();
}

void SGameEngineCollision::DebugRender()
{
	//RECT DebugRenderRectangle = {};

	//DebugRenderRectangle.left = static_cast<LONG>(m_Data.Left());
	//DebugRenderRectangle.right = static_cast<LONG>(m_Data.Right());
	//DebugRenderRectangle.top = static_cast<LONG>(m_Data.Top());
	//DebugRenderRectangle.bottom = static_cast<LONG>(m_Data.Bottom());

	//switch (m_Type)
	//{
	//case COLTYPE::RECT:
	//	FrameRect(SGameEngineWindow::GetBackBufferDC(), &DebugRenderRectangle, SGameEngineWindow::GetGreenBrush());
	//	break;
	//case COLTYPE::CIRCLE:
	//	break;
	//case COLTYPE::POINT:
	//	break;
	//}
}

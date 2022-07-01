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
	// 초기 충돌체 생성시 기본값 셋팅
	// 크기 : (1, 1)
	// 위치 : (0, 0)
	// 타입 : Rectangle
}

SGameEngineCollision::~SGameEngineCollision()
{
	// 아래와 같이 충돌체가 충돌시작, 충돌중, 충돌종료 시 
	// 처리할 이벤트들을 동적할당하므로
	// 해당 충돌체 소멸시 메모리를 해제한다.
	// std::vector<EventBase*> m_StartEvent;
	// std::vector<EventBase*> m_StayEvent;
	// std::vector<EventBase*> m_EndEvent;

	// 충돌시작 이벤트 메모리해제
	for (size_t i = 0; i < m_StartEvent.size(); i++)
	{
		delete m_StartEvent[i];
	}

	// 충돌중 이벤트 메모리해제
	for (size_t i = 0; i < m_StartEvent.size(); i++)
	{
		delete m_StayEvent[i];
	}

	// 충돌종료 이벤트 메모리해제
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

// 위의 생성자 설명과 같이 충돌체 생성시
// 초기값(위치 {0,0})을 가지므로 해당 충돌체가 움직였을때를 대비하여
// 위치를 수정한다.
void SGameEngineCollision::CollisionDataUpdate()
{
	m_Data.m_Pos = GetActor()->GetPosition() - m_PivotPos;
}

// 각 충돌체의 충돌을 체크한다.
void SGameEngineCollision::CollisionCheck(SGameEngineCollision* _Other)
{
	COLTYPE ThisColType = m_Type;
	COLTYPE OtherColType = _Other->m_Type;
	
	// 함수 포인터를 이용하여 두 그룹의 충돌체의 타입을 구분한다.
	if (true == Coliison2DCheck::ColFunc[(int)ThisColType][(int)OtherColType](m_Data, _Other->m_Data))
	{
		// 현재 충돌체의 충돌셋에 _Other충돌체가 없다면
		// 현시점 충돌은 새로운충돌로 충돌시작을 나타낸다.
		if (m_ColSet.end() == m_ColSet.find(_Other))
		{
			UpdateStartEvent(this, _Other);
			_Other->UpdateStartEvent(_Other, this);
		}
		// 현재 충돌체의 충돌셋에 이미 _Other 충돌체가 존재한다면
		// 이전에 충돌하였으며 현재도 충돌중인 상태를 나타낸다.
		else
		{
			UpdateStayEvent(this, _Other);
			_Other->UpdateStayEvent(_Other, this);
		}
	}
	// 두 충돌체가 충돌하지 않았다면
	else
	{
		// 두 충돌체가 충돌이 없는 상황에서 
		// 현재 나의 충돌셋에 _Other 충돌체가 있다면
		// 이전 프레임까지 나와 _Other의 충돌체는 충돌상태였으며
		// 현재 프레임에 해제된 상태이다.
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

#include "SGameEngineActor.h"
#include "SGameEngineRenderer.h"
#include "SGameEngineCollision.h"

// Static Var

// Static Func

// member Var
SGameEngineActor::SGameEngineActor() : m_Position(), m_Scene(nullptr), m_OldPosition(), m_Collision(), m_Renderer()
{

}

SGameEngineActor::~SGameEngineActor()
{
	// 랜더 리스트 생성했으므로
	// 객체 소멸시 해당 리스트 소멸시킨다.
	std::list<SGameEngineRenderer*>::iterator RenderStart = m_Renderer.begin();
	std::list<SGameEngineRenderer*>::iterator RenderEnd = m_Renderer.end();
	for (; RenderStart != RenderEnd; ++RenderStart)
	{
		delete* RenderStart;
		*RenderStart = nullptr;
	}

	m_Renderer.clear();

	// 충돌 리스트를 생성했으므로 
	// 객체 소멸시 해당 리스트를 소멸시킨다.
	std::list<SGameEngineCollision*>::iterator ColStart = m_Collision.begin();
	std::list<SGameEngineCollision*>::iterator ColEnd = m_Collision.end();
	for (; ColStart != ColEnd; ++ColStart)
	{
		delete* ColStart;
		*ColStart = nullptr;
	}

	m_Collision.clear();
}

// member Func
void SGameEngineActor::Start()
{
	// 부모는 가상함수만 선언해주고 자식에서 기능 구현
	// 이유 : 각 오브젝트마다 기능이 다르기 때문에 관리는 부모가하지만
	//           기능 구현은 각 콘텐츠(오브젝트)들이 해야함
}

void SGameEngineActor::Update()
{
	// 부모는 가상함수만 선언해주고 자식에서 기능 구현
	// 이유 : 각 오브젝트마다 기능이 다르기 때문에 관리는 부모가하지만
	//           기능 구현은 각 콘텐츠(오브젝트)들이 해야함
}

void SGameEngineActor::DebugRender()
{
	// 부모는 가상함수만 선언해주고 자식에서 기능 구현
	// 이유 : 각 오브젝트마다 기능이 다르기 때문에 관리는 부모가하지만
	//           기능 구현은 각 콘텐츠(오브젝트)들이 해야함
}

void SGameEngineActor::Release()
{
	// 액터는 살아있으나 충돌체, 랜더러만 Death했을 경우
	// 충돌체와 랜더러만 삭제해주고 액터의 메모리는 정리되지않는다.

	// 랜더러 정리
	std::list<SGameEngineRenderer*>::iterator RendererStart = m_Renderer.begin();
	std::list<SGameEngineRenderer*>::iterator RendererEnd = m_Renderer.end();
	for (; RendererStart != RendererEnd; )
	{
		if (false == (*RendererStart)->IsDeath())
		{
			++RendererStart;
			continue;
		}
		// 해당 랜더러가 Death할때 할일
		(*RendererStart)->DeathTask();
		delete (*RendererStart);
		RendererStart = m_Renderer.erase(RendererStart);
	}

	// 충돌체 정리
	std::list<SGameEngineCollision*>::iterator CollisionStart = m_Collision.begin();
	std::list<SGameEngineCollision*>::iterator CollisionEnd = m_Collision.end();
	for (; CollisionStart != CollisionEnd; )
	{
		if (false == (*CollisionStart)->IsDeath())
		{
			++CollisionStart;
			continue;
		}
		// 해당 충돌체가 Death할때 할일
		(*CollisionStart)->DeathTask();
		delete (*CollisionStart);
		CollisionStart = m_Collision.erase(CollisionStart);
	}
}

void SGameEngineActor::DeathTask()
{
	std::list<SGameEngineRenderer*>::iterator RendererStart = m_Renderer.begin();
	std::list<SGameEngineRenderer*>::iterator RendererEnd = m_Renderer.end();
	for (; RendererStart != RendererEnd; ++RendererStart)
	{
		(*RendererStart)->DeathTask();
	}

	// 충돌체 정리
	std::list<SGameEngineCollision*>::iterator CollisionStart = m_Collision.begin();
	std::list<SGameEngineCollision*>::iterator CollisionEnd = m_Collision.end();
	for (; CollisionStart != CollisionEnd; ++CollisionStart)
	{
		(*CollisionStart)->DeathTask();
	}
}

FLOAT4 SGameEngineActor::GetCamPosition()
{
	return m_Position - m_Scene->GetCamPos();
}

FLOAT4 SGameEngineActor::GetPosition()
{
    return m_Position;
}

void SGameEngineActor::SetPosition(const FLOAT4& _Other)
{
    m_Position = _Other;
}

FLOAT4 SGameEngineActor::GetOldPosition()
{
	return m_OldPosition;
}

void SGameEngineActor::SetOldPosition(const FLOAT4& _Other)
{
	m_OldPosition = _Other;
}

SGameEngineScene* SGameEngineActor::GetScene()
{
	return m_Scene;
}

void SGameEngineActor::SetScene(SGameEngineScene* _Scene)
{
	m_Scene = _Scene;
}

void SGameEngineActor::MovePosition(const FLOAT4& _Other)
{
	m_OldPosition = m_Position;
	m_Position += _Other;
}

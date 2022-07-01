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
	// ���� ����Ʈ ���������Ƿ�
	// ��ü �Ҹ�� �ش� ����Ʈ �Ҹ��Ų��.
	std::list<SGameEngineRenderer*>::iterator RenderStart = m_Renderer.begin();
	std::list<SGameEngineRenderer*>::iterator RenderEnd = m_Renderer.end();
	for (; RenderStart != RenderEnd; ++RenderStart)
	{
		delete* RenderStart;
		*RenderStart = nullptr;
	}

	m_Renderer.clear();

	// �浹 ����Ʈ�� ���������Ƿ� 
	// ��ü �Ҹ�� �ش� ����Ʈ�� �Ҹ��Ų��.
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
	// �θ�� �����Լ��� �������ְ� �ڽĿ��� ��� ����
	// ���� : �� ������Ʈ���� ����� �ٸ��� ������ ������ �θ�������
	//           ��� ������ �� ������(������Ʈ)���� �ؾ���
}

void SGameEngineActor::Update()
{
	// �θ�� �����Լ��� �������ְ� �ڽĿ��� ��� ����
	// ���� : �� ������Ʈ���� ����� �ٸ��� ������ ������ �θ�������
	//           ��� ������ �� ������(������Ʈ)���� �ؾ���
}

void SGameEngineActor::DebugRender()
{
	// �θ�� �����Լ��� �������ְ� �ڽĿ��� ��� ����
	// ���� : �� ������Ʈ���� ����� �ٸ��� ������ ������ �θ�������
	//           ��� ������ �� ������(������Ʈ)���� �ؾ���
}

void SGameEngineActor::Release()
{
	// ���ʹ� ��������� �浹ü, �������� Death���� ���
	// �浹ü�� �������� �������ְ� ������ �޸𸮴� ���������ʴ´�.

	// ������ ����
	std::list<SGameEngineRenderer*>::iterator RendererStart = m_Renderer.begin();
	std::list<SGameEngineRenderer*>::iterator RendererEnd = m_Renderer.end();
	for (; RendererStart != RendererEnd; )
	{
		if (false == (*RendererStart)->IsDeath())
		{
			++RendererStart;
			continue;
		}
		// �ش� �������� Death�Ҷ� ����
		(*RendererStart)->DeathTask();
		delete (*RendererStart);
		RendererStart = m_Renderer.erase(RendererStart);
	}

	// �浹ü ����
	std::list<SGameEngineCollision*>::iterator CollisionStart = m_Collision.begin();
	std::list<SGameEngineCollision*>::iterator CollisionEnd = m_Collision.end();
	for (; CollisionStart != CollisionEnd; )
	{
		if (false == (*CollisionStart)->IsDeath())
		{
			++CollisionStart;
			continue;
		}
		// �ش� �浹ü�� Death�Ҷ� ����
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

	// �浹ü ����
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

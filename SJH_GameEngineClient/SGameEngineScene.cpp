#include "SGameEngineScene.h"
#include "SGameEngineActor.h"
#include "SGameEngineRenderer.h"
#include <SGameEngineWindow.h>
#include "SGameEngineCollision.h"

// Static Var
bool SGameEngineScene::m_bIsDebugRender = false;

// Static Func
void SGameEngineScene::IsDebugRenderOn()
{
	m_bIsDebugRender = true;
}

void SGameEngineScene::IsDebugRenderOff()
{
	m_bIsDebugRender = false;
}

// member Var
SGameEngineScene::SGameEngineScene()
{

}

SGameEngineScene::~SGameEngineScene()
{
	// �����Ҵ� ����
	std::list<SGameEngineActor*>::iterator Start = m_Actors.begin();
	std::list<SGameEngineActor*>::iterator End = m_Actors.end();
	for (; Start != End; ++Start)
	{
		if (nullptr != *Start)
		{
			delete* Start;
			*Start = nullptr;
		}
	}
	m_Actors.clear();
}

// member Func
void SGameEngineScene::Start()
{
	// �θ�� �����Լ��� �������ְ� �ڽĿ��� ��� ����
	// ���� : �� ������Ʈ���� ����� �ٸ��� ������ ������ �θ�������
	//           ��� ������ �� ������(������Ʈ)���� �ؾ���
}

// Scene�� Change�ѵ� Start�ϴ� ����
void SGameEngineScene::SceneChangeStart()
{

}

// Scene�� Change�ѵ� End�ϴ� ����
void SGameEngineScene::SceneChangeEnd()
{

}

void SGameEngineScene::SceneUpdate()
{

}

void SGameEngineScene::SceneDebugRender()
{

}

void SGameEngineScene::Progress()
{
	// �浹ü�� üũ�Ѵ�.
	CollisionProcess();

	// ������ ������Ʈ
	// ���� ȭ�� �̵�
	SceneUpdate();

	// �� ���͵� ������Ʈ
	// ��ġ, ũ�⸦ �����ϰų� Ű���ۿ� ���� ��ȭ
	std::list<SGameEngineActor*>::iterator UpdateStart = m_Actors.begin();
	std::list<SGameEngineActor*>::iterator UpdateEnd = m_Actors.end();
	for (; UpdateStart != UpdateEnd; ++UpdateStart)
	{
		if (false == (*UpdateStart)->IsOn())
		{
			continue;
		}

		(*UpdateStart)->Update();
	}

	// ������Ʈ �Ϸ� �� Rendering
	Render();

	// �׸��� ���� �� ���͵��� DebugRender() ����
	// m_bIsDebugRender == true �϶��� DebugRender�� Ȱ��ȭ�Ѵ�.
	if (true == m_bIsDebugRender)
	{
		// ���� �����
		std::list<SGameEngineActor*>::iterator DebugStart = m_Actors.begin();
		std::list<SGameEngineActor*>::iterator DebugEnd = m_Actors.end();
		for (; DebugStart != DebugEnd; ++DebugStart)
		{
			if (false == (*DebugStart)->IsOn())
			{
				continue;
			}

			(*DebugStart)->DebugRender();
		}

		// �� �����
		SceneDebugRender();
	}

	// Rendering �Ϸ��� BackBuffer�� Copy
	SGameEngineWindow::BackBufferCopy();

	// �������� On/Off ���¸� üũ�Ѵ�.
	OnOffCheck();

	// ��� ������ �Ϸ� �� �� 
	// �ش� �浹���� ��ü�� ������� ���
	// ���� ������ �����Ѵ�.
	Release();
}

void SGameEngineScene::PushRenderer(SGameEngineRenderer* _Renderer)
{
	if (m_RendererList.end() == m_RendererList.find(_Renderer->GetOrder()))
	{
		m_RendererList.insert(std::map<int, std::list<SGameEngineRenderer*>>::value_type(_Renderer->GetOrder(), std::list<SGameEngineRenderer*>()));
	}

	m_RendererList[_Renderer->GetOrder()].push_back(_Renderer);
}

void SGameEngineScene::Render()
{
	std::map<int, std::list<SGameEngineRenderer*>>::iterator LayerStart = m_RendererList.begin();
	std::map<int, std::list<SGameEngineRenderer*>>::iterator LayerEnd = m_RendererList.end();
	for (; LayerStart != LayerEnd; ++LayerStart)
	{
		std::list<SGameEngineRenderer*>& _RenderLayer = LayerStart->second;
		std::list<SGameEngineRenderer*>::iterator RenderStart = _RenderLayer.begin();
		std::list<SGameEngineRenderer*>::iterator RenderEnd = _RenderLayer.end();
		for (; RenderStart != RenderEnd; ++RenderStart)
		{
			if (false == (*RenderStart)->IsOn())
			{
				continue;
			}

			(*RenderStart)->Render();
		}
	}
}

FLOAT4 SGameEngineScene::GetCamPos()
{
	return m_CamPos;
}

void SGameEngineScene::SetCamPos(const FLOAT4& _CamPos)
{
	m_CamPos = _CamPos;
}

void SGameEngineScene::SetCamMove(const FLOAT4& _CamPos)
{
	m_CamPos += _CamPos;
}

void SGameEngineScene::CollisionGroupLink(int _Left, int _Right)
{
	if (m_LinkCollisionGroup[_Left].end() != m_LinkCollisionGroup[_Left].find(_Right))
	{
		return;
	}

	// �̹� �׷��� �����ϴٸ� ���� �ƴϸ� �߰�
	// map���� m_LinkCollisionGroup[_Left] �̿� ���� ����ϸ�
	// Insert�� Find�� ��� �����ϰ� ���� Ű�� ���� ���� ��ȯ���ִ� ����
	m_LinkCollisionGroup[_Left].insert(_Right);
}

void SGameEngineScene::PushCollision(SGameEngineCollision* _Collision)
{
	if (m_CollisionList.end() == m_CollisionList.find(_Collision->GetOrder()))
	{
		m_CollisionList.insert(std::map<int, std::list<SGameEngineCollision*>>::value_type(_Collision->GetOrder(), std::list<SGameEngineCollision*> ()));
	}

	m_CollisionList[_Collision->GetOrder()].push_back(_Collision);
}

void SGameEngineScene::CollisionPosSet()
{
	std::map<int, std::list<SGameEngineCollision*>>::iterator Start = m_CollisionList.begin();
	std::map<int, std::list<SGameEngineCollision*>>::iterator End = m_CollisionList.end();
	for (; Start != End; ++Start)
	{
		std::list<SGameEngineCollision*>::iterator ColStart = Start->second.begin();
		std::list<SGameEngineCollision*>::iterator ColEnd = Start->second.end();
		for (; ColStart != ColEnd; ++ColStart)
		{
			if (false == (*ColStart)->IsOn())
			{
				continue;
			}

			(*ColStart)->CollisionDataUpdate();
		}
	}
}

void SGameEngineScene::CollisionProcess()
{
	// ��� �浹ü�� �ڱ� ��ġ�� ������ �� �浹ü�� ���Եȴ�.
	CollisionPosSet();

	std::map<int, std::set<int>>::iterator LeftGroupStart = m_LinkCollisionGroup.begin();
	std::map<int, std::set<int>>::iterator LeftGroupEnd = m_LinkCollisionGroup.end();

	for (; LeftGroupStart != LeftGroupEnd; ++LeftGroupStart)
	{
		std::set<int>::iterator RightGroupStart = LeftGroupStart->second.begin();
		std::set<int>::iterator RightGroupEnd = LeftGroupStart->second.end();

		for (; RightGroupStart != RightGroupEnd; ++RightGroupStart)
		{
			int LeftGroupIndex = LeftGroupStart->first;
			int RightGroupIndex = *RightGroupStart;

			// Left�浹ü�� Right �浹ü�� �浹�� üũ

			// ���δٸ� �׷�(����)�� �浹
			if (LeftGroupIndex != RightGroupIndex)
			{
				CollisionGroupOtherCheck(LeftGroupIndex, RightGroupIndex);
			}
			else // ���� �׷�(����)�� �浹
			{
				CollisionGroupThisCheck(LeftGroupIndex);
			}
		}
	}
}

// ���� �ٸ� �׷�(����)�� �浹
void SGameEngineScene::CollisionGroupOtherCheck(int _Left, int _Right)
{
	// ���� �ٸ� �׷��� �浹ü�� �浹�� Ƚ��
	// ���� �ٸ� �׷��̱� ������ �׷찣 ���� �浹�� Ƚ����
	// LeftGroup * RightGroup ���� ����.
	std::list<SGameEngineCollision*>& LeftGroup = m_CollisionList[_Left];
	std::list<SGameEngineCollision*>& RightGroup = m_CollisionList[_Right];

	// LeftGoup�� ��ü�� ã�Ƴ���.
	std::list<SGameEngineCollision*>::iterator LeftGroupStart = LeftGroup.begin();
	std::list<SGameEngineCollision*>::iterator LeftGroupEnd = LeftGroup.end();
	for (; LeftGroupStart != LeftGroupEnd; ++LeftGroupStart)
	{
		if (false == (*LeftGroupStart)->IsOn())
		{
			continue;
		}

		// RightGroup�� ��ü�� ���� ���Ѵ�.
		std::list<SGameEngineCollision*>::iterator RightGroupStart = RightGroup.begin();
		std::list<SGameEngineCollision*>::iterator RightGroupEnd = RightGroup.end();
		for (; RightGroupStart != RightGroupEnd; ++RightGroupStart)
		{
			if (false == (*RightGroupStart)->IsOn())
			{
				continue;
			}

			(*LeftGroupStart)->CollisionCheck(*RightGroupStart);
		}
	}
}

// ���� ���� �׷�(����)�� �浹
void SGameEngineScene::CollisionGroupThisCheck(int _Value)
{
	// ���� ���� �׷��� �浹ü�� �浹�� Ƚ��
	std::list<SGameEngineCollision*>::iterator	Start = m_CollisionList[_Value].begin();
	std::list<SGameEngineCollision*>::iterator	End = m_CollisionList[_Value].end();
	std::list<SGameEngineCollision*>::iterator   This = Start;

	for (; Start != End;)
	{
		(*Start)->CollisionCheck(*This);

		++This;

		if (This == End)
		{
			++Start;
			This = Start;
		}
	}
}

// ���� ����
void SGameEngineScene::Release()
{
	// ������ ����
	std::map<int, std::list<SGameEngineRenderer*>>::iterator MapRenderStart = m_RendererList.begin();
	std::map<int, std::list<SGameEngineRenderer*>>::iterator MapRenderEnd = m_RendererList.end();
	for (; MapRenderStart != MapRenderEnd; ++MapRenderStart)
	{
		std::list<SGameEngineRenderer*>& Render = MapRenderStart->second;
		std::list<SGameEngineRenderer*>::iterator RendererStart = Render.begin();
		std::list<SGameEngineRenderer*>::iterator RendererEnd = Render.end();

		for (; RendererStart != RendererEnd;)
		{
			// �ش� ������ ��������ʾ����� iterator�� �������� �ѱ��
			if (false == (*RendererStart)->IsDeath())
			{
				++RendererStart;
				continue;
			}

			// �ƴ϶�� �ش� ������ �����Ѵ�.
			RendererStart = Render.erase(RendererStart);
		}
	}

	// �浹ü ����
	std::map<int, std::list<SGameEngineCollision*>>::iterator MapColStart = m_CollisionList.begin();
	std::map<int, std::list<SGameEngineCollision*>>::iterator MapColEnd = m_CollisionList.end();
	for (; MapColStart != MapColEnd; ++MapColStart)
	{
		std::list<SGameEngineCollision*>::iterator ColStart = MapColStart->second.begin();
		std::list<SGameEngineCollision*>::iterator ColEnd = MapColStart->second.end();

		for (; ColStart != ColEnd; )
		{
			// �ش� �浹ü�� ��������ʾ������ ���� iterator�� �ѱ��
			if (false == (*ColStart)->IsDeath())
			{
				++ColStart;
				continue;
			}

			// �ƴϸ� �ش� �浹ü�� �����Ѵ�.
			ColStart = MapColStart->second.erase(ColStart);
		}
	}

	// �޸� ����
	std::list<SGameEngineActor*>::iterator ActorStart = m_Actors.begin();
	std::list<SGameEngineActor*>::iterator ActorEnd = m_Actors.end();
	for (; ActorStart != ActorEnd; )
	{
		if (false == (*ActorStart)->IsDeath())
		{
			(*ActorStart)->Release();
			++ActorStart;
			continue;
		}

		(*ActorStart)->DebugCheck();

		// �ش� ���Ͱ� �޸𸮿��� �����Ǳ����� ����
		(*ActorStart)->DeathTask();

		// �ش� ���͸� �����ϰ�
		delete (*ActorStart);
		
		// ���� ����Ʈ�� �ش� ���͸� �����Ѵ�.
		ActorStart = m_Actors.erase(ActorStart);
	}

}

// On/Off Check
void SGameEngineScene::OnOffCheck()
{
	// ������ CallOffTask
	std::map<int, std::list<SGameEngineRenderer*>>::iterator CallOffTaskRenderStart = m_RendererList.begin();
	std::map<int, std::list<SGameEngineRenderer*>>::iterator CallOffTaskRenderEnd = m_RendererList.end();

	for (; CallOffTaskRenderStart != CallOffTaskRenderEnd; ++CallOffTaskRenderStart)
	{
		std::list<SGameEngineRenderer*>& CallOffTaskRenderValue = CallOffTaskRenderStart->second;
		std::list<SGameEngineRenderer*>::iterator RenderCallOffTaskStart = CallOffTaskRenderValue.begin();
		std::list<SGameEngineRenderer*>::iterator RenderCallOffTaskEnd = CallOffTaskRenderValue.end();

		for (; RenderCallOffTaskStart != RenderCallOffTaskEnd; ++RenderCallOffTaskStart)
		{
			(*RenderCallOffTaskStart)->CallOffTask();
			(*RenderCallOffTaskStart)->CallOnTask();
		}
	}

	//�浹ü CallOffTask
	std::map<int, std::list<SGameEngineCollision*>>::iterator CallOffTaskCollisionStart = m_CollisionList.begin();
	std::map<int, std::list<SGameEngineCollision*>>::iterator CallOffTaskCollisionEnd = m_CollisionList.end();

	for (; CallOffTaskCollisionStart != CallOffTaskCollisionEnd; ++CallOffTaskCollisionStart)
	{
		std::list<SGameEngineCollision*>::iterator CollisionCallOffTaskStart = CallOffTaskCollisionStart->second.begin();
		std::list<SGameEngineCollision*>::iterator CollisionCallOffTaskEnd = CallOffTaskCollisionStart->second.end();

		for (; CollisionCallOffTaskStart != CollisionCallOffTaskEnd; ++CollisionCallOffTaskStart)
		{
			(*CollisionCallOffTaskStart)->CallOffTask();
			(*CollisionCallOffTaskStart)->CallOnTask();
		}
	}

	// ���� CallOffTask
	std::list<SGameEngineActor*>::iterator CallOffTaskActorStart = m_Actors.begin();
	std::list<SGameEngineActor*>::iterator CallOffTaskActorEnd = m_Actors.end();
	for (; CallOffTaskActorStart != CallOffTaskActorEnd; ++CallOffTaskActorStart)
	{
		(*CallOffTaskActorStart)->CallOnTask();
		(*CallOffTaskActorStart)->CallOffTask();
	}
}

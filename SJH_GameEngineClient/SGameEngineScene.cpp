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
	// 동적할당 해제
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
	// 부모는 가상함수만 선언해주고 자식에서 기능 구현
	// 이유 : 각 오브젝트마다 기능이 다르기 때문에 관리는 부모가하지만
	//           기능 구현은 각 콘텐츠(오브젝트)들이 해야함
}

// Scene이 Change한뒤 Start하는 시점
void SGameEngineScene::SceneChangeStart()
{

}

// Scene이 Change한뒤 End하는 시점
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
	// 충돌체를 체크한다.
	CollisionProcess();

	// 씬동작 업데이트
	// 보통 화면 이동
	SceneUpdate();

	// 각 액터들 업데이트
	// 위치, 크기를 변경하거나 키조작에 따른 변화
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

	// 업데이트 완료 후 Rendering
	Render();

	// 그리고 난뒤 각 액터들의 DebugRender() 실행
	// m_bIsDebugRender == true 일때만 DebugRender를 활성화한다.
	if (true == m_bIsDebugRender)
	{
		// 액터 디버그
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

		// 씬 디버그
		SceneDebugRender();
	}

	// Rendering 완료후 BackBuffer에 Copy
	SGameEngineWindow::BackBufferCopy();

	// 릴리즈전 On/Off 상태를 체크한다.
	OnOffCheck();

	// 모든 랜더를 완료 한 뒤 
	// 해당 충돌에서 객체가 사망했을 경우
	// 삭제 로직을 실행한다.
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

	// 이미 그룹이 존재하다면 생성 아니면 추가
	// map에서 m_LinkCollisionGroup[_Left] 이와 같이 사용하면
	// Insert와 Find를 모두 수행하고 맵의 키와 값중 값을 반환해주는 문법
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
	// 모든 충돌체는 자기 위치를 수정한 뒤 충돌체에 삽입된다.
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

			// Left충돌체와 Right 충돌체의 충돌을 체크

			// 서로다른 그룹(오더)의 충돌
			if (LeftGroupIndex != RightGroupIndex)
			{
				CollisionGroupOtherCheck(LeftGroupIndex, RightGroupIndex);
			}
			else // 같은 그룹(오더)의 충돌
			{
				CollisionGroupThisCheck(LeftGroupIndex);
			}
		}
	}
}

// 서로 다른 그룹(오더)의 충돌
void SGameEngineScene::CollisionGroupOtherCheck(int _Left, int _Right)
{
	// 서로 다른 그룹의 충돌체가 충돌할 횟수
	// 서로 다른 그룹이기 때문에 그룹간 서로 충돌할 횟수는
	// LeftGroup * RightGroup 수와 같다.
	std::list<SGameEngineCollision*>& LeftGroup = m_CollisionList[_Left];
	std::list<SGameEngineCollision*>& RightGroup = m_CollisionList[_Right];

	// LeftGoup의 전체를 찾아낸다.
	std::list<SGameEngineCollision*>::iterator LeftGroupStart = LeftGroup.begin();
	std::list<SGameEngineCollision*>::iterator LeftGroupEnd = LeftGroup.end();
	for (; LeftGroupStart != LeftGroupEnd; ++LeftGroupStart)
	{
		if (false == (*LeftGroupStart)->IsOn())
		{
			continue;
		}

		// RightGroup의 전체와 각각 비교한다.
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

// 서로 같은 그룹(오더)의 충돌
void SGameEngineScene::CollisionGroupThisCheck(int _Value)
{
	// 서로 같은 그룹의 충돌체가 충돌할 횟수
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

// 삭제 로직
void SGameEngineScene::Release()
{
	// 랜더러 정리
	std::map<int, std::list<SGameEngineRenderer*>>::iterator MapRenderStart = m_RendererList.begin();
	std::map<int, std::list<SGameEngineRenderer*>>::iterator MapRenderEnd = m_RendererList.end();
	for (; MapRenderStart != MapRenderEnd; ++MapRenderStart)
	{
		std::list<SGameEngineRenderer*>& Render = MapRenderStart->second;
		std::list<SGameEngineRenderer*>::iterator RendererStart = Render.begin();
		std::list<SGameEngineRenderer*>::iterator RendererEnd = Render.end();

		for (; RendererStart != RendererEnd;)
		{
			// 해당 랜더가 사망하지않았으면 iterator를 다음으로 넘기고
			if (false == (*RendererStart)->IsDeath())
			{
				++RendererStart;
				continue;
			}

			// 아니라면 해당 랜더를 삭제한다.
			RendererStart = Render.erase(RendererStart);
		}
	}

	// 충돌체 정리
	std::map<int, std::list<SGameEngineCollision*>>::iterator MapColStart = m_CollisionList.begin();
	std::map<int, std::list<SGameEngineCollision*>>::iterator MapColEnd = m_CollisionList.end();
	for (; MapColStart != MapColEnd; ++MapColStart)
	{
		std::list<SGameEngineCollision*>::iterator ColStart = MapColStart->second.begin();
		std::list<SGameEngineCollision*>::iterator ColEnd = MapColStart->second.end();

		for (; ColStart != ColEnd; )
		{
			// 해당 충돌체가 사망하지않았을경우 다음 iterator로 넘기고
			if (false == (*ColStart)->IsDeath())
			{
				++ColStart;
				continue;
			}

			// 아니면 해당 충돌체를 삭제한다.
			ColStart = MapColStart->second.erase(ColStart);
		}
	}

	// 메모리 정리
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

		// 해당 액터가 메모리에서 해제되기전에 할일
		(*ActorStart)->DeathTask();

		// 해당 액터를 삭제하고
		delete (*ActorStart);
		
		// 액터 리스트에 해당 액터를 삭제한다.
		ActorStart = m_Actors.erase(ActorStart);
	}

}

// On/Off Check
void SGameEngineScene::OnOffCheck()
{
	// 랜더러 CallOffTask
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

	//충돌체 CallOffTask
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

	// 액터 CallOffTask
	std::list<SGameEngineActor*>::iterator CallOffTaskActorStart = m_Actors.begin();
	std::list<SGameEngineActor*>::iterator CallOffTaskActorEnd = m_Actors.end();
	for (; CallOffTaskActorStart != CallOffTaskActorEnd; ++CallOffTaskActorStart)
	{
		(*CallOffTaskActorStart)->CallOnTask();
		(*CallOffTaskActorStart)->CallOffTask();
	}
}

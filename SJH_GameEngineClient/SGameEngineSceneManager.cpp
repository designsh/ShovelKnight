#include "SGameEngineSceneManager.h"
#include <SGameEngineDebug.h>

// Static Var

// Static Func

// member Var
SGameEngineSceneManager::SGameEngineSceneManager() : m_CurScene(nullptr), m_NextScene(nullptr)
{

}

SGameEngineSceneManager::~SGameEngineSceneManager()
{
	// 메모리 해제
	std::map<SGameEngineString, SGameEngineScene*>::iterator Start = m_AllScene.begin();
	std::map<SGameEngineString, SGameEngineScene*>::iterator End = m_AllScene.end();
	for (; Start != End; ++Start)
	{
		if (nullptr != Start->second)
		{
			delete Start->second;
			Start->second = nullptr;
		}
	}
	m_AllScene.clear();
}

// member Func
SGameEngineScene* SGameEngineSceneManager::FindScene(const SGameEngineString& _SceneName)
{
	// 찾지 못했으면 NULL 반환
	if (m_AllScene.end() == m_AllScene.find(_SceneName))
	{
		return nullptr;
	}

	return m_AllScene[_SceneName];
}

void SGameEngineSceneManager::ChangeScene(const SGameEngineString& _SceneName)
{
	m_NextScene = FindScene(_SceneName);

	if (nullptr == m_NextScene)
	{
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_NextScene)");
	}
}

void SGameEngineSceneManager::ChangeCheck()
{
	// 새로운 장면이 준비되었다면
	if (nullptr != m_NextScene)
	{
		// 현재 씬은 Next 씬이 되고
		// Next씬은 null이 된다.
		if (nullptr != m_CurScene)
		{
			m_CurScene->SceneChangeEnd();
		}

		m_CurScene = m_NextScene;

		m_CurScene->SceneChangeStart();

		m_NextScene = nullptr;
	}
}
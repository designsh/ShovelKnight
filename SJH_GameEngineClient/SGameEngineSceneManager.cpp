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
	// �޸� ����
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
	// ã�� �������� NULL ��ȯ
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
	// ���ο� ����� �غ�Ǿ��ٸ�
	if (nullptr != m_NextScene)
	{
		// ���� ���� Next ���� �ǰ�
		// Next���� null�� �ȴ�.
		if (nullptr != m_CurScene)
		{
			m_CurScene->SceneChangeEnd();
		}

		m_CurScene = m_NextScene;

		m_CurScene->SceneChangeStart();

		m_NextScene = nullptr;
	}
}
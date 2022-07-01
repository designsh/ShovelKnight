#include "SGameCore.h"
#include "ShovelKnigthTitle.h"      // Ÿ��Ʋ ȭ��
#include "TileMapEditor.h"            // Map Editor ȭ��
#include "GameIntro.h"                  // Shovel Knight Intro ȭ��
#include "Plains.h"                          // Stage1(����Ǳ�) ȭ��
#include "LevelMap.h"                    // Level Map(�����) ȭ��
#include "Enchantress.h"                // Final Boss(�丶) ȭ��
#include "EndingCredit.h"              // Ending Credit(����) ȭ��

#include <SGameEngineSound.h>
#include <SGameEngineFile.h>

// Static Var
SGameEngineSceneManager SGameCore::SceneManager;

// Static Func
void SGameCore::GameStart()
{
	// ���� ����� Ȯ���� .mp3�� ���带 ���δ� �����ͼ� Vector�� ���� ��
	// m_SoundMap�� �����Ѵ�.
	SGameEngineDirectory m_SoundPath;
	m_SoundPath.MoveParentsFolder(L"ShovelKnight");
	m_SoundPath.MoveChildFolder(L"Resource");
	m_SoundPath.MoveChildFolder(L"Sound");
	std::vector<SGameEngineFile> AllSoundFile = m_SoundPath.FindDirectoryAllFileToVector(L"*.mp3");
	for (size_t i = 0; i < AllSoundFile.size(); i++)
	{
		SGameEngineSound::Load(AllSoundFile[i].GetPath());
	}

	// Scene�� �����Ѵ�.
	// ShovelKnigthTitle : Ÿ��Ʋ ��
	// TileMapEditor : �� ������ ��
	// GameIntro : ��Ʈ�� ��
	// Plains : ����Ǳ�(��������1) ��
	// LevelMap : �����(������) ��
	// Enchantress : ����(1������ ���� �� ����) ��
	// EndingCredit : ���� ��
	// �� ������ Start()�Լ��� ���� ���� �ش��ϴ� ���ҽ��� �ҷ��´�.
	SceneManager.CreateScene<ShovelKnigthTitle>(L"ShovelKnigthTitle");
	SceneManager.CreateScene<Plains>(L"Plains");						// �̰����� State1(Plains Collision Map)�� �ε� : ���������� ���ҽ��ε�
	SceneManager.CreateScene<GameIntro>(L"GameIntro");
	SceneManager.CreateScene<LevelMap>(L"LevelMap");
	SceneManager.CreateScene<Enchantress>(L"Enchantress");
	SceneManager.CreateScene<EndingCredit>(L"EndingCredit");

	// Plains�� TileMapEditor�� ���� �浹���� ����ؾ��ϹǷ� TileMapEditor�� ���� ���߿� ����
	SceneManager.CreateScene<TileMapEditor>(L"TileMapEditor");

	// ���� ���� ����
	SceneManager.ChangeScene(L"ShovelKnigthTitle");
}

void SGameCore::GameUpdate()
{
	SceneManager.ChangeCheck();

	SceneManager.GetCurScene()->Progress();
}

void SGameCore::GameEnd()
{
	SGameEngineSound::Release();
}

// member Var
SGameCore::SGameCore()
{

}

SGameCore::~SGameCore()
{

}

// member Func
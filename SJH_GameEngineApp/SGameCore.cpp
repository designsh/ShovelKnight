#include "SGameCore.h"
#include "ShovelKnigthTitle.h"      // 타이틀 화면
#include "TileMapEditor.h"            // Map Editor 화면
#include "GameIntro.h"                  // Shovel Knight Intro 화면
#include "Plains.h"                          // Stage1(평원의길) 화면
#include "LevelMap.h"                    // Level Map(월드맵) 화면
#include "Enchantress.h"                // Final Boss(요마) 화면
#include "EndingCredit.h"              // Ending Credit(엔딩) 화면

#include <SGameEngineSound.h>
#include <SGameEngineFile.h>

// Static Var
SGameEngineSceneManager SGameCore::SceneManager;

// Static Func
void SGameCore::GameStart()
{
	// 현재 경로의 확장자 .mp3인 사운드를 전부다 가져와서 Vector에 저장 후
	// m_SoundMap에 저장한다.
	SGameEngineDirectory m_SoundPath;
	m_SoundPath.MoveParentsFolder(L"ShovelKnight");
	m_SoundPath.MoveChildFolder(L"Resource");
	m_SoundPath.MoveChildFolder(L"Sound");
	std::vector<SGameEngineFile> AllSoundFile = m_SoundPath.FindDirectoryAllFileToVector(L"*.mp3");
	for (size_t i = 0; i < AllSoundFile.size(); i++)
	{
		SGameEngineSound::Load(AllSoundFile[i].GetPath());
	}

	// Scene을 생성한다.
	// ShovelKnigthTitle : 타이틀 씬
	// TileMapEditor : 맵 에디터 씬
	// GameIntro : 인트로 씬
	// Plains : 평원의길(스테이지1) 씬
	// LevelMap : 월드맵(레벨맵) 씬
	// Enchantress : 보스(1페이즈 종료 후 엔딩) 씬
	// EndingCredit : 엔딩 씬
	// 씬 생성시 Start()함수시 현재 씬에 해당하는 리소스를 불러온다.
	SceneManager.CreateScene<ShovelKnigthTitle>(L"ShovelKnigthTitle");
	SceneManager.CreateScene<Plains>(L"Plains");						// 이곳에서 State1(Plains Collision Map)을 로드 : 레벨생성시 리소스로드
	SceneManager.CreateScene<GameIntro>(L"GameIntro");
	SceneManager.CreateScene<LevelMap>(L"LevelMap");
	SceneManager.CreateScene<Enchantress>(L"Enchantress");
	SceneManager.CreateScene<EndingCredit>(L"EndingCredit");

	// Plains와 TileMapEditor는 같은 충돌맵을 사용해야하므로 TileMapEditor는 가장 나중에 생성
	SceneManager.CreateScene<TileMapEditor>(L"TileMapEditor");

	// 현재 씬을 설정
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
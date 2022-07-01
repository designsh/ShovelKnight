#include "GameIntro.h"
#include "IntroBackDrop.h"     // 인트로 배경(총 7개의 배경을 페이드인아웃으로 관리)
#include "FadeInOutActor.h"

#include <SGameEngineWindow.h>
#include <SGameEngineInput.h>
#include <SGameEngineResMgr.h>

// Static Var
SoundPlayer GameIntro::m_IntroStageBgm;

// Static Func

// member Var
GameIntro::GameIntro() : m_ResPath(), m_Fade(nullptr)
{

}

GameIntro::~GameIntro()
{

}

// member Func
void GameIntro::Start()
{
	// 건너뛰기 있는 키 생성
	SGameEngineInput::CreateKey(L"Skip", '`');

	// 리소스 파일 전체 들고오기
	m_ResPath.MoveParentsFolder(L"ShovelKnight");
	m_ResPath.MoveChildFolder(L"Resource");
	m_ResPath.MoveChildFolder(L"Image");
	m_ResPath.MoveChildFolder(L"Intro");

	// 현재 경로의 확장자 .bmp인 이미지를 전부다 가져와서 Vector에 저장
	std::vector<SGameEngineFile> AllImageFile = m_ResPath.FindDirectoryAllFileToVector(L"*.bmp");
	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		SGameEngineResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	// 이미지 잘라놓기
	SGameEngineResMgr::Inst().FindImage(L"FadeInOut.bmp")->SetTransColor(RGB(255, 0, 255));
	SGameEngineResMgr::Inst().FindImage(L"FadeInOut.bmp")->ImageCut(1, 1);

	// GameIntro Scene은 IntroBackDrop(인트로배경)을 생성한다.
	CreateActor<IntroBackDrop>();
}

void GameIntro::SceneUpdate()
{

}

void GameIntro::SceneChangeStart()
{
	// 배경음악 지정
	m_IntroStageBgm = SGameEngineSound::Play(L"Intro.mp3", true, 100);
}

void GameIntro::SceneChangeEnd()
{
	// 배경음악 종료
	m_IntroStageBgm.Stop();
}

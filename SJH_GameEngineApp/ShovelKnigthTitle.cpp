#include "ShovelKnigthTitle.h"
#include "TitleBackDrop.h"       // 타이틀 배경
#include "MenuButton.h"         // 타이틀 메뉴 리스트
#include "MenuSelector.h"       // 타이틀 메뉴 선택 아이콘(삽)
#include "TitleEffect.h"             // 타이틀 게임이름 이펙트(별)
#include "SGameCore.h"

#include <SGameEngineWindow.h>
#include <SGameEngineInput.h>
#include <SGameEngineResMgr.h>

// Static Var
SoundPlayer ShovelKnigthTitle::m_TitleStageBgm;

// Static Func

// member Var
ShovelKnigthTitle::ShovelKnigthTitle() 
	: m_SelectMenu(1), m_ResPath(), m_MenuSelector(nullptr)
{

}

ShovelKnigthTitle::~ShovelKnigthTitle()
{

}

// member Func
void ShovelKnigthTitle::Start()
{
	// 리소스 파일 전체 들고오기
	m_ResPath.MoveParentsFolder(L"ShovelKnight");
	m_ResPath.MoveChildFolder(L"Resource");
	m_ResPath.MoveChildFolder(L"Image");
	m_ResPath.MoveChildFolder(L"Title");

	// 현재 경로의 확장자 .bmp인 이미지를 전부다 가져와서 Vector에 저장
	std::vector<SGameEngineFile> AllImageFile = m_ResPath.FindDirectoryAllFileToVector(L"*.bmp");
	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		SGameEngineResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	// Game Title Effect.bmp SetTransColor & ImageCut
	SGameEngineResMgr::Inst().FindImage(L"Game Title Effect.bmp")->SetTransColor(RGB(255, 255, 255));
	SGameEngineResMgr::Inst().FindImage(L"Game Title Effect.bmp")->ImageCut(5, 1);

	// Title Scene은 TitleBackDrop(타이틀배경)을 생성한다.(검은색배경)
	SGameEngineResMgr::Inst().FindImage(L"BackGround.bmp")->SetTransColor(RGB(255, 255, 255));
	SGameEngineResMgr::Inst().FindImage(L"Title Text.bmp")->SetTransColor(RGB(0, 0, 0));
	CreateActor<TitleBackDrop>();

	// Title Scene은 TitleEffect(타이틀이펙트)을 생성한다.(별모양)
	CreateActor<TitleEffect>();

	// Title Scene은 MenuButton(메뉴버튼 리스트)을 생성한다.
	CreateActor<MenuButton>();

	// Title Scene은 MenuSelector(메뉴선택 아이콘)을 생성한다.
	SGameEngineResMgr::Inst().FindImage(L"Menu Selector.bmp")->SetTransColor(RGB(0, 255, 0));
	m_MenuSelector = CreateActor<MenuSelector>();
}

void ShovelKnigthTitle::SceneUpdate()
{

}

void ShovelKnigthTitle::SceneChangeStart()
{
	m_TitleStageBgm = SGameEngineSound::Play(L"Background_music.mp3", true, 100);
}

void ShovelKnigthTitle::SceneChangeEnd()
{
	m_TitleStageBgm.Stop();
}

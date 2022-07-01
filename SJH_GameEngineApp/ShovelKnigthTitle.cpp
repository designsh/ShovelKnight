#include "ShovelKnigthTitle.h"
#include "TitleBackDrop.h"       // Ÿ��Ʋ ���
#include "MenuButton.h"         // Ÿ��Ʋ �޴� ����Ʈ
#include "MenuSelector.h"       // Ÿ��Ʋ �޴� ���� ������(��)
#include "TitleEffect.h"             // Ÿ��Ʋ �����̸� ����Ʈ(��)
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
	// ���ҽ� ���� ��ü ������
	m_ResPath.MoveParentsFolder(L"ShovelKnight");
	m_ResPath.MoveChildFolder(L"Resource");
	m_ResPath.MoveChildFolder(L"Image");
	m_ResPath.MoveChildFolder(L"Title");

	// ���� ����� Ȯ���� .bmp�� �̹����� ���δ� �����ͼ� Vector�� ����
	std::vector<SGameEngineFile> AllImageFile = m_ResPath.FindDirectoryAllFileToVector(L"*.bmp");
	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		SGameEngineResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	// Game Title Effect.bmp SetTransColor & ImageCut
	SGameEngineResMgr::Inst().FindImage(L"Game Title Effect.bmp")->SetTransColor(RGB(255, 255, 255));
	SGameEngineResMgr::Inst().FindImage(L"Game Title Effect.bmp")->ImageCut(5, 1);

	// Title Scene�� TitleBackDrop(Ÿ��Ʋ���)�� �����Ѵ�.(���������)
	SGameEngineResMgr::Inst().FindImage(L"BackGround.bmp")->SetTransColor(RGB(255, 255, 255));
	SGameEngineResMgr::Inst().FindImage(L"Title Text.bmp")->SetTransColor(RGB(0, 0, 0));
	CreateActor<TitleBackDrop>();

	// Title Scene�� TitleEffect(Ÿ��Ʋ����Ʈ)�� �����Ѵ�.(�����)
	CreateActor<TitleEffect>();

	// Title Scene�� MenuButton(�޴���ư ����Ʈ)�� �����Ѵ�.
	CreateActor<MenuButton>();

	// Title Scene�� MenuSelector(�޴����� ������)�� �����Ѵ�.
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

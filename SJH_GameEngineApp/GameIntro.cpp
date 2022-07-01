#include "GameIntro.h"
#include "IntroBackDrop.h"     // ��Ʈ�� ���(�� 7���� ����� ���̵��ξƿ����� ����)
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
	// �ǳʶٱ� �ִ� Ű ����
	SGameEngineInput::CreateKey(L"Skip", '`');

	// ���ҽ� ���� ��ü ������
	m_ResPath.MoveParentsFolder(L"ShovelKnight");
	m_ResPath.MoveChildFolder(L"Resource");
	m_ResPath.MoveChildFolder(L"Image");
	m_ResPath.MoveChildFolder(L"Intro");

	// ���� ����� Ȯ���� .bmp�� �̹����� ���δ� �����ͼ� Vector�� ����
	std::vector<SGameEngineFile> AllImageFile = m_ResPath.FindDirectoryAllFileToVector(L"*.bmp");
	for (size_t i = 0; i < AllImageFile.size(); i++)
	{
		SGameEngineResMgr::Inst().ImageLoad(AllImageFile[i].GetPath());
	}

	// �̹��� �߶����
	SGameEngineResMgr::Inst().FindImage(L"FadeInOut.bmp")->SetTransColor(RGB(255, 0, 255));
	SGameEngineResMgr::Inst().FindImage(L"FadeInOut.bmp")->ImageCut(1, 1);

	// GameIntro Scene�� IntroBackDrop(��Ʈ�ι��)�� �����Ѵ�.
	CreateActor<IntroBackDrop>();
}

void GameIntro::SceneUpdate()
{

}

void GameIntro::SceneChangeStart()
{
	// ������� ����
	m_IntroStageBgm = SGameEngineSound::Play(L"Intro.mp3", true, 100);
}

void GameIntro::SceneChangeEnd()
{
	// ������� ����
	m_IntroStageBgm.Stop();
}

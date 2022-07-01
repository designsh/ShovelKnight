#include "PlayerMaker.h"
#include "GlobalValue.h"

void PlayerMaker::PlayerMaker_CreateAnimaion()
{
	// �⺻ �÷��̾� �ִϸ��̼�
	m_AniPlayer = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Player);
	m_AniPlayer->SetRenderScale({ 300, 300 });
	m_AniPlayer->CreateAnimation(L"PlayerMakerNone", L"LevelMap_Player.bmp", 0, 0);
	m_AniPlayer->CreateAnimation(L"PlayerMakerMove", L"LevelMap_Player.bmp", 0, 1);

}

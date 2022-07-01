#include "PlayerMaker.h"
#include "GlobalValue.h"

void PlayerMaker::PlayerMaker_CreateAnimaion()
{
	// 기본 플레이어 애니메이션
	m_AniPlayer = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Player);
	m_AniPlayer->SetRenderScale({ 300, 300 });
	m_AniPlayer->CreateAnimation(L"PlayerMakerNone", L"LevelMap_Player.bmp", 0, 0);
	m_AniPlayer->CreateAnimation(L"PlayerMakerMove", L"LevelMap_Player.bmp", 0, 1);

}

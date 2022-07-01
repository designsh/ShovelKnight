#include "PlayerMaker.h"

void PlayerMaker::PlayerMaker_CreateKey()
{
	// Å°¼³Á¤
	SGameEngineInput::CreateKey(L"MakerLeft", VK_LEFT);
	SGameEngineInput::CreateKey(L"MakerRight", VK_RIGHT);
	SGameEngineInput::CreateKey(L"MakerUp", VK_UP);
	SGameEngineInput::CreateKey(L"MakerDown", VK_DOWN);
	SGameEngineInput::CreateKey(L"MakerMapSelect", VK_SPACE);
}

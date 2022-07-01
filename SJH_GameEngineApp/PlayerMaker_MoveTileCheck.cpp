#include "PlayerMaker.h"
#include "GlobalValue.h"

void PlayerMaker::CreateMoveTileMap()
{
	// Broken TileMap File ���
	m_MoveTileFilePath.MoveParentsFolder(L"ShovelKnight");
	m_MoveTileFilePath.MoveChildFolder(L"Resource");
	m_MoveTileFilePath.MoveChildFolder(L"Image");
	m_MoveTileFilePath.MoveChildFolder(L"LevelMap");
	m_MoveTileFilePath.MoveChildFolder(L"TileSet");

	// ���Ͽ� ����� Ÿ������ ��������
	m_MoveTile = CreateRenderer<SGameEngineRendererTile>((int)GlobalValue::RenderGroup::MoveTile);
	m_MoveTile->TileMapStart(L"LevelMapMoveTile.bmp", { 32.f, 32.f }, { 32.f, 32.f }, 40, 23);
	SGameEngineString LoadPath = m_MoveTileFilePath.GetPath();
	LoadPath += L"LevelMapMoveTile.dat";
	m_MoveTile->LoadTile(LoadPath);

	// �⺻������ Off ����
	m_MoveTile->Off();
}

int PlayerMaker::GetBrokenTileImageIndex(const FLOAT4& _CheckPos)
{
	// ���ϴ� �ε����� �̹����ε��� ���� ��������
	return m_MoveTile->GetTileImageIndex({ _CheckPos.ix(), _CheckPos.iy() });
}

void PlayerMaker::SetPlayerPosIndex()
{
	// �÷��̾� ��ġ ��� ����
	m_PlayerPosIndex = { GetPosition().x / 32.f, GetPosition().y / 32.f };
}


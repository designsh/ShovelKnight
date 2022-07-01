#pragma once

// �з� :
// �뵵 : 
// ���� : 
class PlainsTileMap;          // TileMap
class ShovelKnight;           // Player
class Beeto;                       // Beeto Monster
class BlackKnight;
class PlayerMaker;
class DeathScreen;
class Enchantress_ShovelKnight;
class Enchantress_FinalBoss;
class GlobalValue
{
public:
	enum class RenderGroup
	{
		SkyBackGround = 0,            // ���(�ϴ�)
		CastleBackGround = 1,       // ���(��)
		LightTreeBackGround = 2,  // ���(���ѳ���)
		ThickTreeBackGound = 3,   // ���(£������)
		CollistionMap = 100,             // �浹��
		GoldObject = 120,                // ��������������Ʈ
		TileMap = 200,                        // Ÿ��
		BrokenTile = 250,                    // �μ����� Ÿ��
		MoveTile = 250,                      // �̵������� Ÿ��
		UI = 300,                                  // UI
		StateBar = 320,                       // ���¹�
		Monster = 400,                       // ����
		MonsterEffect = 410,             // ��������Ʈ
		Player = 450,                          // �÷��̾�
		LevelMapCloud = 500,          // ����� ������
		DeathScreen = 500,              // �÷��̾� �����ũ��(ī�޶��� x)
		DeathScreen_Object = 600, // �÷��̾� �����ũ������ ������Ʈ
		DeathScreen_Maker = 700,
		ClearEffect = 700,
	};

	enum class CollisionGroup  // �浹ü �׷�
	{
		Player,                         // �÷��̾�
		PlayerAttack,                   // �÷��̾� ���ݸ��
		PlayerJumpAttack,      // �÷��̾� �������ݸ��
		Monster,                     // ����
		MovingPlatform,                // �����̴� Ÿ��
		UI,                               // UI
		Mouse                       // ���콺������
	};

	enum class CollisionType // �浹Ÿ��
	{
		Player,
		PlayerAttack,
		Monster,
		MovingTile,
		UI,
		Mouse
	};

	enum class BasicMoveType
	{
		None = 0,
		Left,
		Right,
		Up,
		Down
	};

	enum class JumpState
	{
		JumpNone,
		JumpStart,
		JumpStay,
		JumpEnd
	};

	enum class PixelCheckDirect
	{
		Left,
		Right,
		Top,
		Bottom,
		Center,
	};

public:
	// Plains
	static ShovelKnight* MainPlayer;
	static PlainsTileMap* MainTileMap;
	static BlackKnight* FinalBoss;
	static DeathScreen* PlayerDeathScreen;

	// LevelMap(Wolrd Map)
	static PlayerMaker* LevelMapPlayer;

	// Enchantress
	static Enchantress_ShovelKnight* FinalStage_MainPlayer;
	static Enchantress_FinalBoss* FinalStage_FinalBoss;
};


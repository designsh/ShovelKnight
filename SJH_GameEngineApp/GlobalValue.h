#pragma once

// 분류 :
// 용도 : 
// 설명 : 
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
		SkyBackGround = 0,            // 배경(하늘)
		CastleBackGround = 1,       // 배경(성)
		LightTreeBackGround = 2,  // 배경(연한나무)
		ThickTreeBackGound = 3,   // 배경(짙은나무)
		CollistionMap = 100,             // 충돌맵
		GoldObject = 120,                // 숨겨진골드오브젝트
		TileMap = 200,                        // 타일
		BrokenTile = 250,                    // 부서지는 타일
		MoveTile = 250,                      // 이동가능한 타일
		UI = 300,                                  // UI
		StateBar = 320,                       // 상태바
		Monster = 400,                       // 몬스터
		MonsterEffect = 410,             // 몬스터이펙트
		Player = 450,                          // 플레이어
		LevelMapCloud = 500,          // 월드맵 가림막
		DeathScreen = 500,              // 플레이어 사망스크린(카메라영향 x)
		DeathScreen_Object = 600, // 플레이어 사망스크린위의 오브젝트
		DeathScreen_Maker = 700,
		ClearEffect = 700,
	};

	enum class CollisionGroup  // 충돌체 그룹
	{
		Player,                         // 플레이어
		PlayerAttack,                   // 플레이어 공격모션
		PlayerJumpAttack,      // 플레이어 점프공격모션
		Monster,                     // 몬스터
		MovingPlatform,                // 움직이는 타일
		UI,                               // UI
		Mouse                       // 마우스포인터
	};

	enum class CollisionType // 충돌타입
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


#include "ShovelKnight.h"
#include <SGameEngineWindow.h>

#include "BlackKnight.h"

// Static Var
SoundPlayer ShovelKnight::m_StageBgm;
SoundPlayer ShovelKnight::m_ActionSound;

// Static Func

// member Var
ShovelKnight::ShovelKnight()
	: m_PlayerInfo(), m_WindowSize(FLOAT4::ZERO),
	m_AniPlayer(nullptr), m_ShovelKnightFSM(),
	m_PlayerCol(nullptr), m_PlayerBotCol(nullptr), m_AttackCol(nullptr), m_JumpAttackCol(nullptr),
	m_MoveDir(GlobalValue::BasicMoveType::Right), m_PrevMoveDir(GlobalValue::BasicMoveType::None), m_LadderPrevMoveDir(GlobalValue::BasicMoveType::None),
	m_fAngle(0.0f),
	m_JumpEventer(), m_KnockBackEventer(),
	m_bJumping(false), m_bLadderCollision(false), m_bDirtBlockCollision(false), m_bFinalBossRoom(false), m_bFinalBossHPCharge(false), m_bEffectSound(false), m_bAppearIdle(false),
	m_CurAniMationName(), m_AniMationName(),
	m_PlayerCheckPos(FLOAT4::ZERO), m_PlayerCheckDir(), m_iPlayerCheckColor(),
	m_CamCheckPos(FLOAT4::ZERO), m_CamCheckDir(), m_iCamCheckColor(),
	m_BrokenTileFilePath(), m_BrokenTile(nullptr), m_PlayerPosIndex(FLOAT4::ZERO), m_PlayerAttackPosIndex(FLOAT4::ZERO), m_BrokenAllTile(), m_BrokenEventer(),
	m_bWallCollision(false), m_LerpStartMove(false), m_LerpCamPos(FLOAT4::ZERO), m_LerpStartPos(FLOAT4::ZERO), m_LerpEndPos(FLOAT4::ZERO), m_LerpTime(0.0f),
	m_MovePos(FLOAT4::ZERO), m_DirectPos(FLOAT4::ZERO), m_GravityPos(FLOAT4::ZERO),
	m_JumpPos(FLOAT4::ZERO), m_JumpPower(FLOAT4::ZERO), m_JumpGravityPowerPos(FLOAT4::ZERO),
	m_KnockBackPos(FLOAT4::ZERO), m_KnockBackPower(FLOAT4::ZERO), m_KnockBackGravityPowerPos(FLOAT4::ZERO),
	m_bInvincibility(false), m_bTelePort(false),
	m_PlayerTeleportStartPos(FLOAT4::ZERO), m_CamTeleportStartPos(FLOAT4::ZERO),
	m_bFinalBossDeath(false)
{

}

ShovelKnight::~ShovelKnight()
{
	m_BrokenAllTile.clear();
}

// member Func
void ShovelKnight::Start()
{
	// ������ ũ�⸦ �����´�.
	m_WindowSize = SGameEngineWindow::GetSize();

	// �÷��̾��� �⺻������ �����Ѵ�.
	SetPlayerInfomation();

	// �÷��̾� �׼�Ű �����Ѵ�.
	CreateActionKey();

	// �÷��̾� ���ݿ� �μ����� Ÿ������ �ε�
	LoadBrokenTileMap();

	// �÷��̾� �浹ü ����
	CreatePlayerCollision();

	// �÷��̾� �ִϸ��̼� ����
	CreatePlayerAnimation();

	// �÷��̾� FSM ���� ����
	CreatePlayerFSMState();

	// Broken Tile TimeEventer ����
	m_BrokenEventer.CreateTimeEventStart(0.1f, this, &ShovelKnight::BrokenTileStay);
	m_BrokenEventer.LoopOn();
}

void ShovelKnight::Update()
{
	CheetKeyDownCheck();

	if (true == m_bFinalBossRoom)
	{
		// ������ ���� üũ
		CheckFinalBossRoom();
	}

	if (true == m_bFinalBossHPCharge)
	{
		return;
	}

	// �÷��̾� Ÿ�ϱ��� �ε��� ���� ������Ʈ
	SetPlayerPosIndex();

	// �����Ӹ��� �̵� ���� �ʱ�ȭ
	m_MovePos = FLOAT4::ZERO;

	// �̵����⿡ ���� �ִϸ��̼� ����(��, ��)
	DirCheck();

	// ī�޶� ����(�÷��̾ �̵��� �ʷϻ��� ������)
	if (true == m_bWallCollision)
	{
		LerpCamMove();
		return;
	}

	// �÷��̾� FSM ���� ������Ʈ
	m_ShovelKnightFSM.Update();

	// ī�޶� �ȼ�üũ(ȭ��ũ�⸸ŭ ������)
	CamPixelCheck();

	// �÷��̾� ���� �̵�
	MovePosition(m_MovePos);
}

void ShovelKnight::DebugRender()
{
	// �÷��̾� �ȼ� ǥ��
	FLOAT4 PlayerPixelLeft = m_PlayerCheckDir[0] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), PlayerPixelLeft.ix() - 2, PlayerPixelLeft.iy() - 2, PlayerPixelLeft.ix() + 2, PlayerPixelLeft.iy() + 2);

	FLOAT4 PlayerPixelRight = m_PlayerCheckDir[1] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), PlayerPixelRight.ix() - 2, PlayerPixelRight.iy() - 2, PlayerPixelRight.ix() + 2, PlayerPixelRight.iy() + 2);

	FLOAT4 PlayerPixelTop = m_PlayerCheckDir[2] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), PlayerPixelTop.ix() - 2, PlayerPixelTop.iy() - 2, PlayerPixelTop.ix() + 2, PlayerPixelTop.iy() + 2);

	FLOAT4 PlayerPixelBottom = m_PlayerCheckDir[3] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), PlayerPixelBottom.ix() - 2, PlayerPixelBottom.iy() - 2, PlayerPixelBottom.ix() + 2, PlayerPixelBottom.iy() + 2);

	FLOAT4 PlayerPixelCenter = m_PlayerCheckDir[4] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), PlayerPixelCenter.ix() - 2, PlayerPixelCenter.iy() - 2, PlayerPixelCenter.ix() + 2, PlayerPixelCenter.iy() + 2);

	// �÷��̾� ��ü �浹ü ǥ��
	Col2DData ColData;
	ColData.m_Pos = GetCamPosition() - m_PlayerCol->GetPivotPos();
	ColData.m_Size = m_PlayerCol->GetScale();
	RECT ColRect = { ColData.iLeft(), ColData.iTop(), ColData.iRight(), ColData.iBottom() };
	if (true == m_PlayerCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &ColRect, SGameEngineWindow::GetGreenBrush());
	}

	Col2DData BottomColData;
	BottomColData.m_Pos = GetCamPosition() - m_PlayerBotCol->GetPivotPos();
	BottomColData.m_Size = m_PlayerBotCol->GetScale();
	RECT BottomColDataRect = { BottomColData.iLeft(), BottomColData.iTop(), BottomColData.iRight(), BottomColData.iBottom() };
	if (true == m_PlayerBotCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &BottomColDataRect, SGameEngineWindow::GetGreenBrush());
	}

	// �÷��̾� ���ݸ�� �浹ü ǥ��
	Col2DData AttackColData;
	AttackColData.m_Pos = GetCamPosition() - m_AttackCol->GetPivotPos();
	AttackColData.m_Size = m_AttackCol->GetScale();
	RECT AttackColDataRect = { AttackColData.iLeft(), AttackColData.iTop(), AttackColData.iRight(), AttackColData.iBottom() };
	if (true == m_AttackCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &AttackColDataRect, SGameEngineWindow::GetGreenBrush());
	}

	// �÷��̾� �������ݸ�� �浹ü ǥ��
	Col2DData JumpAttackColData;
	JumpAttackColData.m_Pos = GetCamPosition() - m_JumpAttackCol->GetPivotPos();
	JumpAttackColData.m_Size = m_JumpAttackCol->GetScale();
	RECT JumpAttackColDataRect = { JumpAttackColData.iLeft(), JumpAttackColData.iTop(), JumpAttackColData.iRight(), JumpAttackColData.iBottom() };
	if (true == m_JumpAttackCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &JumpAttackColDataRect, SGameEngineWindow::GetGreenBrush());
	}

	// �÷��̾� ���� Ÿ�ϱ��� �ε���
	FLOAT4 TilePlayerIndex = m_PlayerPosIndex;
	SGameEngineString TilePlayerIndexText = L"TilePlayerIndex";
	TilePlayerIndexText += L"X : ";
	TilePlayerIndexText += SGameEngineString::ToString(TilePlayerIndex.ix());
	TilePlayerIndexText += L"Y : ";
	TilePlayerIndexText += SGameEngineString::ToString(TilePlayerIndex.iy());
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 440, TilePlayerIndexText.c_str(), lstrlen(TilePlayerIndexText.c_str()));

	int PlayerPosTileImage = m_BrokenTile->GetTileImageIndex(m_PlayerPosIndex);
	SGameEngineString PlayerPosTileImageText = L"PlayerPosTileImage";
	PlayerPosTileImageText += L"ImageIndex : ";
	PlayerPosTileImageText += SGameEngineString::ToString(PlayerPosTileImage);
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 460, PlayerPosTileImageText.c_str(), lstrlen(PlayerPosTileImageText.c_str()));

	FLOAT4 PlayerAttackIndex = m_PlayerAttackPosIndex;
	SGameEngineString PlayerAttackIndexText = L"PlayerAttackIndex";
	PlayerAttackIndexText += L"X : ";
	PlayerAttackIndexText += SGameEngineString::ToString(PlayerAttackIndex.ix());
	PlayerAttackIndexText += L"Y : ";
	PlayerAttackIndexText += SGameEngineString::ToString(PlayerAttackIndex.iy());
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 480, PlayerAttackIndexText.c_str(), lstrlen(PlayerAttackIndexText.c_str()));

	int PlayerAttackPosTileImage = m_BrokenTile->GetTileImageIndex(m_PlayerAttackPosIndex);
	SGameEngineString PlayerAttackPosTileImageText = L"PlayerAttackPosTileImage";
	PlayerAttackPosTileImageText += L"ImageIndex : ";
	PlayerAttackPosTileImageText += SGameEngineString::ToString(PlayerAttackPosTileImage);
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 500, PlayerAttackPosTileImageText.c_str(), lstrlen(PlayerAttackPosTileImageText.c_str()));

	SGameEngineString JumpText = L"JumpPower : ";
	JumpText += SGameEngineString::ToString(m_JumpPower.y);
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 520, JumpText.c_str(), lstrlen(JumpText.c_str()));

	SGameEngineString JumpPos = L"JumpPos";
	JumpPos += L"X : ";
	JumpPos += SGameEngineString::ToString(m_JumpPos.x);
	JumpPos += L"Y : ";
	JumpPos += SGameEngineString::ToString(m_JumpPos.y);
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 540, JumpPos.c_str(), lstrlen(JumpPos.c_str()));

	SGameEngineString GravityPos = L"GravityPos";
	GravityPos += L"X : ";
	GravityPos += SGameEngineString::ToString(m_GravityPos.x);
	GravityPos += L"Y : ";
	GravityPos += SGameEngineString::ToString(m_GravityPos.y);
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 560, GravityPos.c_str(), lstrlen(GravityPos.c_str()));

	SGameEngineString PlayerTopColor = L"PlayerTopColor";
	PlayerTopColor += SGameEngineString::ToString(m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Top]);
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 580, PlayerTopColor.c_str(), lstrlen(PlayerTopColor.c_str()));

	SGameEngineString PlayerBotColor = L"PlayerBotColor";
	PlayerBotColor += SGameEngineString::ToString(m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom]);
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 600, PlayerBotColor.c_str(), lstrlen(PlayerBotColor.c_str()));

	SGameEngineString PlayerLeftColor = L"PlayerLeftColor";
	PlayerLeftColor += SGameEngineString::ToString(m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Left]);
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 620, PlayerLeftColor.c_str(), lstrlen(PlayerLeftColor.c_str()));

	SGameEngineString PlayerRightColor = L"PlayerRightColor";
	PlayerRightColor += SGameEngineString::ToString(m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Right]);
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 640, PlayerRightColor.c_str(), lstrlen(PlayerRightColor.c_str()));

	SGameEngineString PlayerCenterColor = L"PlayerCenterColor";
	PlayerCenterColor += SGameEngineString::ToString(m_iPlayerCheckColor[(int)GlobalValue::PixelCheckDirect::Center]);
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 660, PlayerCenterColor.c_str(), lstrlen(PlayerCenterColor.c_str()));

	FLOAT4 Pos = GetPosition();
	SGameEngineString PlayerPos = L"PlayerPos";
	PlayerPos += L"X : ";
	PlayerPos += SGameEngineString::ToString(Pos.ix());
	PlayerPos += L"		";
	PlayerPos += L"Y : ";
	PlayerPos += SGameEngineString::ToString(Pos.iy());
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 680, PlayerPos.c_str(), lstrlen(PlayerPos.c_str()));

	FLOAT4 CamPos = GetScene()->GetCamPos();
	SGameEngineString CameraPos = L"CameraPos";
	CameraPos += L"X : ";
	CameraPos += SGameEngineString::ToString(CamPos.ix());
	CameraPos += L"Y : ";
	CameraPos += SGameEngineString::ToString(CamPos.iy());
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 700, CameraPos.c_str(), lstrlen(CameraPos.c_str()));

	FLOAT4 TopBarPos = GetScene()->GetCamPos();
	SGameEngineString TopBar = L"TopBar";
	TopBar += L"X : ";
	TopBar += SGameEngineString::ToString(TopBarPos.ix());
	TopBar += L"Y : ";
	TopBar += SGameEngineString::ToString(TopBarPos.iy());
	TextOut(SGameEngineWindow::GetBackBufferDC(), 1000, 520, TopBar.c_str(), lstrlen(TopBar.c_str()));

	SGameEngineString TopCenterCamColor = L"CamTopCenterCamColor";
	TopCenterCamColor += SGameEngineString::ToString(m_iCamCheckColor[(int)GlobalValue::PixelCheckDirect::Top]);
	TextOut(SGameEngineWindow::GetBackBufferDC(), 1000, 540, TopCenterCamColor.c_str(), lstrlen(TopCenterCamColor.c_str()));

	SGameEngineString LeftCenterCamColor = L"CamLeftCenterCamColor";
	LeftCenterCamColor += SGameEngineString::ToString(m_iCamCheckColor[(int)GlobalValue::PixelCheckDirect::Left]);
	TextOut(SGameEngineWindow::GetBackBufferDC(), 1000, 560, LeftCenterCamColor.c_str(), lstrlen(LeftCenterCamColor.c_str()));

	SGameEngineString RightCenterCamColor = L"CamRightCenterCamColor";
	RightCenterCamColor += SGameEngineString::ToString(m_iCamCheckColor[(int)GlobalValue::PixelCheckDirect::Right]);
	TextOut(SGameEngineWindow::GetBackBufferDC(), 1000, 580, RightCenterCamColor.c_str(), lstrlen(RightCenterCamColor.c_str()));

	SGameEngineString BottomCenterCamColor = L"CamBottomCenterCamColor";
	BottomCenterCamColor += SGameEngineString::ToString(m_iCamCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom]);
	TextOut(SGameEngineWindow::GetBackBufferDC(), 1000, 600, BottomCenterCamColor.c_str(), lstrlen(BottomCenterCamColor.c_str()));

	FLOAT4 CheckCamPos1 = GetScene()->GetCamPos();
	SGameEngineString TopCenterCheckPos = L"TopCenterCheckPos";
	TopCenterCheckPos += L"X : ";
	TopCenterCheckPos += SGameEngineString::ToString(CheckCamPos1.ix() + m_WindowSize.HarfX());
	TopCenterCheckPos += L"Y : ";
	TopCenterCheckPos += SGameEngineString::ToString(CheckCamPos1.iy());
	TextOut(SGameEngineWindow::GetBackBufferDC(), 1000, 620, TopCenterCheckPos.c_str(), lstrlen(TopCenterCheckPos.c_str()));

	FLOAT4 CheckCamPos2 = GetScene()->GetCamPos();
	SGameEngineString LeftCenterCheckPos = L"LeftCenterCheckPos";
	LeftCenterCheckPos += L"X : ";
	LeftCenterCheckPos += SGameEngineString::ToString(CheckCamPos2.ix());
	LeftCenterCheckPos += L"Y : ";
	LeftCenterCheckPos += SGameEngineString::ToString(CheckCamPos2.iy() + m_WindowSize.HarfY());
	TextOut(SGameEngineWindow::GetBackBufferDC(), 1000, 640, LeftCenterCheckPos.c_str(), lstrlen(LeftCenterCheckPos.c_str()));

	FLOAT4 CheckCamPos3 = GetScene()->GetCamPos();
	SGameEngineString RightCenterCheckPos = L"RightCenterCheckPos";
	RightCenterCheckPos += L"X : ";
	RightCenterCheckPos += SGameEngineString::ToString(CheckCamPos3.ix() + m_WindowSize.ix());
	RightCenterCheckPos += L"Y : ";
	RightCenterCheckPos += SGameEngineString::ToString(m_WindowSize.HarfY());
	TextOut(SGameEngineWindow::GetBackBufferDC(), 1000, 660, RightCenterCheckPos.c_str(), lstrlen(RightCenterCheckPos.c_str()));

	FLOAT4 CheckCamPos4 = GetScene()->GetCamPos();
	SGameEngineString BottomCenterCheckPos = L"BottomCenterCheckPos";
	BottomCenterCheckPos += L"X : ";
	BottomCenterCheckPos += SGameEngineString::ToString(CheckCamPos4.ix() + m_WindowSize.HarfX());
	BottomCenterCheckPos += L"Y : ";
	BottomCenterCheckPos += SGameEngineString::ToString(CheckCamPos4.iy() + m_WindowSize.iy());
	TextOut(SGameEngineWindow::GetBackBufferDC(), 1000, 680, BottomCenterCheckPos.c_str(), lstrlen(BottomCenterCheckPos.c_str()));

	FLOAT4 PivotPos = m_AniPlayer->GetPivotPos();
	SGameEngineString PivotPosText = L"PivotPos";
	PivotPosText += L"X : ";
	PivotPosText += SGameEngineString::ToString(PivotPos.ix());
	PivotPosText += L"Y : ";
	PivotPosText += SGameEngineString::ToString(PivotPos.iy());
	TextOut(SGameEngineWindow::GetBackBufferDC(), 1000, 700, PivotPosText.c_str(), lstrlen(PivotPosText.c_str()));
}

// ������ ����� �÷��̾� �̵��Ұ�
// ���� ü������ �Ϸ� �� �̵�����
void ShovelKnight::CheckFinalBossRoom()
{
	// ������ �����Ÿ��� Flag On���� �÷��̾� �̵��Ұ�
	// ���� ü�� ���� �Ϸ�� ��������
	FLOAT4 Dir = GlobalValue::FinalBoss->GetPosition() - GetPosition();
	if (800.0f >= FLOAT4::Len2D(Dir))
	{
		m_bFinalBossHPCharge = true;
		ChangeAniMation(L"PlayerNone");
	}

	if (GlobalValue::FinalBoss->m_BlackKnightInfo.GetHP() == GlobalValue::FinalBoss->m_BlackKnightInfo.GetMaxHP())
	{
		// ������ ����� ���� ��ü
		m_StageBgm.Stop();
		m_StageBgm = SGameEngineSound::Play(L"Plains_Boss_Battle.mp3", true, 100);

		m_bFinalBossHPCharge = false;
		m_bFinalBossRoom = false;
	}
}

// �÷��̾� ���� Get
ShovelKnightInfo& ShovelKnight::GetPlayerInfo()
{
	return m_PlayerInfo;
}

// �̵��� ���� �ִϸ��̼� ����
void ShovelKnight::ChangeAniMation(const SGameEngineString& _ChangeAniName)
{
	if (0 == _ChangeAniName.size())
	{
		// ���� ������ �ȵ�
		SGameEngineDebug::AssertMsg(L"if (0 == _ChangeAniName.size())");
	}

	m_CurAniMationName = L"";
	if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		m_CurAniMationName = L"Right";
	}
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		m_CurAniMationName = L"Left";
	}

	m_AniMationName = _ChangeAniName;
	m_CurAniMationName += _ChangeAniName;

	m_AniPlayer->ChangeAnimation(m_CurAniMationName);
}

void ShovelKnight::DirCheck()
{
	if (m_MoveDir != m_PrevMoveDir)
	{
		ChangeAniMation(m_AniMationName);
	}

	m_PrevMoveDir = m_MoveDir;
}

void ShovelKnight::BossVictoryStateChagne()
{
	m_ShovelKnightFSM.ChangeState(L"Player_Victory");
}

void ShovelKnight::CheetKeyDownCheck()
{
	// �������(ü�°��� o, �˹� o, ��� x)
	if (true == SGameEngineInput::IsDown(L"Player_InvincibilityOn"))
	{
		m_bInvincibility = true;
	}
	if (true == SGameEngineInput::IsDown(L"Player_InvincibilityOff"))
	{
		m_bInvincibility = false;
	}

	// �ӵ� ����, �ӵ� �������
	if (true == SGameEngineInput::IsDown(L"Player_SpeedUp"))
	{
		m_PlayerInfo.SetMoveSpeed(400.f);
	}
	if (true == SGameEngineInput::IsDown(L"Player_SpeedDown"))
	{
		m_PlayerInfo.SetMoveSpeed(200.f);
	}

	// �÷��̾� ��ġ �̵�(������ ���������� �̵�)
	if (true == SGameEngineInput::IsDown(L"Player_Teleportation"))
	{
		// ���� �÷��̾� ��ġ, ī�޶���ġ ����
		m_PlayerTeleportStartPos = GetPosition();
		m_CamTeleportStartPos = GetScene()->GetCamPos();

		// �÷��̾� ��ġ, ī�޶� ��ġ ����
		SetPosition({ 19721.f, 384.f });
		GetScene()->SetCamPos({ 19200.f, 0.f });

		m_bTelePort = true;
	}
	// �ѹ��� �ڷ���Ʈ�� ���� ��츸 ����
	if (true == m_bTelePort)
	{
		if (true == SGameEngineInput::IsDown(L"Player_PrevTeleportation"))
		{
			// �÷��̾� ��ġ, ī�޶� ��ġ �ڷ���Ʈ �� ��ġ�� ����
			SetPosition(m_PlayerTeleportStartPos);
			GetScene()->SetCamPos(m_CamTeleportStartPos);

			m_bTelePort = false;
		}
	}

	// ���� ��� ų
	if (true == SGameEngineInput::IsDown(L"Player_BossKill"))
	{
		// ������ ����ְ�, ü���� �����Ҷ� ����
		if (false == GlobalValue::FinalBoss->IsDeath())
		{
			if (0 != GlobalValue::FinalBoss->m_BlackKnightInfo.GetHP())
			{
				GlobalValue::FinalBoss->PlayerCheetBossDeath();
			}
		}
	}

	// �������(ġƮ) On/Off(��� ������Ʈ�� �����ϰ� �����δ�.
	if (true == SGameEngineInput::IsDown(L"Player_FreeModeOn"))
	{
		m_PlayerInfo.SetMoveSpeed(400.f);
		m_ShovelKnightFSM.ChangeState(L"Player_CheetFree");
	}
	else if (true == SGameEngineInput::IsDown(L"Player_FreeModeOff"))
	{
		m_PlayerInfo.SetMoveSpeed(200.f);
		m_ShovelKnightFSM.ChangeState(L"Player_None");
	}
}

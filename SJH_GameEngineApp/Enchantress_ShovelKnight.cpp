#include "Enchantress_ShovelKnight.h"
#include <SGameEngineWindow.h>
#include <SGameEngineRendererBasic.h>

#include "GlobalValue.h"
#include "SGameCore.h"
#include "Enchantress_FinalBoss.h"

// Static Var
SoundPlayer Enchantress_ShovelKnight::m_EnchantressPlayerSound;

// Static Func

// member Var
Enchantress_ShovelKnight::Enchantress_ShovelKnight()
	: m_WindowSize(FLOAT4::ZERO), m_bJumping(false), m_bKnockBack(false),
	m_AniPlayer(nullptr), m_ShovelKnightFSM(), m_PlayerInfo(), m_PlayerAppearPos(FLOAT4(400.f, 0.f)),
	m_PlayerCol(nullptr), m_PlayerBotCol(nullptr), m_AttackCol(nullptr), m_JumpAttackCol(nullptr),
	m_MoveDir(GlobalValue::BasicMoveType::Right), m_PrevMoveDir(GlobalValue::BasicMoveType::None),
	m_CamMoveDir(GlobalValue::BasicMoveType::Up), m_PrevCamMoveDir(GlobalValue::BasicMoveType::None),
	m_CurAniMationName(), m_AniMationName(),
	m_JumpEventer(), m_KnockBackEventer(),
	m_bWallCollision(false), m_LerpStartMove(false), m_LerpCamPos(FLOAT4::ZERO), m_LerpStartPos(FLOAT4::ZERO), m_LerpEndPos(FLOAT4::ZERO), m_LerpTime(0.0f),
	m_PlayerCheckPos(FLOAT4::ZERO), m_PlayerCheckDir(), m_iPlayerCheckColor(),
	m_CamCheckPos(FLOAT4::ZERO), m_CamCheckDir(), m_iCamCheckColor(),
	m_MovePos(FLOAT4::ZERO), 
	m_DirectPos(FLOAT4::ZERO),
	m_JumpPos(FLOAT4::ZERO), m_JumpPower(FLOAT4::ZERO), m_JumpGravityPowerPos(FLOAT4::ZERO),
	m_KnockBackPos(FLOAT4::ZERO), m_KnockBackPower(FLOAT4::ZERO), m_KnockBackGravityPowerPos(FLOAT4::ZERO)
{

}

Enchantress_ShovelKnight::~Enchantress_ShovelKnight()
{

}

// member Func
void Enchantress_ShovelKnight::Start()
{
    // ������ ũ�⸦ �����´�.
    m_WindowSize = SGameEngineWindow::GetSize();

	// �÷��̾��� �⺻������ �����Ѵ�.
	SetPlayerInfomation();

	// �÷��̾� �׼�Ű �����Ѵ�.
	CreateActionKey();

	// �÷��̾� �浹ü ����
	CreatePlayerCollision();

	// �÷��̾� �ִϸ��̼� ����
	CreatePlayerAnimation();

	// �÷��̾� FSM ���� ����
	CreatePlayerFSMState();
}

void Enchantress_ShovelKnight::Update()
{
	CheetCheck();

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

void Enchantress_ShovelKnight::DebugRender()
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
}

void Enchantress_ShovelKnight::ChangeAniMation(const SGameEngineString& _ChangeAniName)
{
	m_CurAniMationName = L"";
	if (m_MoveDir == GlobalValue::BasicMoveType::Right)
	{
		m_CurAniMationName = L"Right_";
	}
	if (m_MoveDir == GlobalValue::BasicMoveType::Left)
	{
		m_CurAniMationName = L"Left_";
	}

	m_AniMationName = _ChangeAniName;
	m_CurAniMationName += _ChangeAniName;

	m_AniPlayer->ChangeAnimation(m_CurAniMationName);
}

void Enchantress_ShovelKnight::DirCheck()
{
	if (m_MoveDir != m_PrevMoveDir)
	{
		ChangeAniMation(m_AniMationName);
	}

	m_PrevMoveDir = m_MoveDir;
}

ShovelKnightInfo& Enchantress_ShovelKnight::GetPlayerInfo()
{
	return m_PlayerInfo;
}

void Enchantress_ShovelKnight::CheetCheck()
{
	if (true == SGameEngineInput::IsDown(L"PLAYER_ENCHANTRESSKILL"))
	{
		// ���� ��� ����(ü�¸�� ��Ƴ��� ������ ��������� ���Ѵ�.)
		GlobalValue::FinalStage_FinalBoss->FinalBoss_InstantKill();
	}
}

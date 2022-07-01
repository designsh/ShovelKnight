#include "BlackKnight.h"
#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>

#include "GlobalValue.h"
#include "ShovelKnight.h"

// Static Var
SoundPlayer BlackKnight::m_BlackKnightActionSound;

// Static Func

// member Var
BlackKnight::BlackKnight()
	: m_WindowSize(FLOAT4::ZERO), m_BlackKnightInfo(),
	m_AniBlackKnight(nullptr), m_BeShotLeftBlackKnight(nullptr), m_BeShotRightBlackKnight(nullptr), m_BlackKnightFSM(),
	m_BlackKnightCol(nullptr), m_BlackKnightNomalAttackCol(nullptr), m_BlackKnightJumpAttackCol(nullptr),
	m_Speed(200.f), m_MoveDir(GlobalValue::BasicMoveType::Left), m_PrevMoveDir(GlobalValue::BasicMoveType::None),m_KnockBackMoveDir(GlobalValue::BasicMoveType::None), m_BackJumpMoveDir(GlobalValue::BasicMoveType::None), m_DeathMoveDir(GlobalValue::BasicMoveType::None),
	m_CurAniMationName(), m_AniMationName(), 
	m_MovePos(FLOAT4::ZERO), 
	m_DirectPos(FLOAT4::ZERO), 
	m_KnockBackPos(FLOAT4::ZERO), m_KnockBackPower(FLOAT4::ZERO), m_KnockBackGravityPower(FLOAT4::ZERO),
	m_BackJumpPos(FLOAT4::ZERO), m_BackJumpPower(FLOAT4::ZERO), m_BackJumpGravityPower(FLOAT4::ZERO),
	m_DeathPos(FLOAT4::ZERO), m_DeathPower(FLOAT4::ZERO), m_DeathGravityPower(FLOAT4::ZERO),
	m_JumpAttackPos(FLOAT4::ZERO), m_JumpAttackPower(FLOAT4::ZERO), m_JumpAttackGravityPower(FLOAT4::ZERO),
	m_LaughEventer(),
	m_BossCheckPos(FLOAT4::ZERO), m_BossCheckDir(), m_iBossCheckColor(),
	m_bBlinkImage(false), m_fBlinkImageOnTime(0.2f), m_fBlinkImageOffTime(0.3f), m_fBlinkImageTotalTime(1.f),
	m_JumpAttackCnt(1), m_RandomState(0), m_PrevRandomState(0),
	m_HPChargeTime(0.5f), m_bFirstAppear(false)
{

}

BlackKnight::~BlackKnight()
{

}

// member Func
void BlackKnight::Start()
{
	// ���� ������ ũ�⸦ �����´�.
	m_WindowSize = SGameEngineWindow::GetSize();

	// ������ ������ �����Ѵ�.
	m_BlackKnightInfo.SetMaxHP(12);

	// ���� �浹ü ����
	// (0 : ��ü, 1 : �Ϲݰ���, 2 : ��������)
	m_BlackKnightCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Monster);
	m_BlackKnightCol->SetScale({ 40, 50 });
	m_BlackKnightCol->SetCheckData(0);
	m_BlackKnightCol->AddStartEvent(this, &BlackKnight::CollisionStart);
	m_BlackKnightCol->AddStayEvent(this, &BlackKnight::CollisionStay);
	m_BlackKnightCol->AddEndEvent(this, &BlackKnight::CollisionEnd);

	m_BlackKnightNomalAttackCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Monster);
	m_BlackKnightNomalAttackCol->SetScale({ 30, 40 });
	m_BlackKnightNomalAttackCol->SetCheckData(1);
	m_BlackKnightNomalAttackCol->AddStartEvent(this, &BlackKnight::AttackCollisionStart);
	m_BlackKnightNomalAttackCol->AddStayEvent(this, &BlackKnight::AttackCollisionStay);
	m_BlackKnightNomalAttackCol->AddEndEvent(this, &BlackKnight::AttackCollisionEnd);
	m_BlackKnightNomalAttackCol->Off();

	m_BlackKnightJumpAttackCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Monster);
	m_BlackKnightJumpAttackCol->SetScale({ 40, 10 });
	m_BlackKnightJumpAttackCol->SetPivotPos({ 0.f, -50.f });
	m_BlackKnightJumpAttackCol->SetCheckData(2);
	m_BlackKnightJumpAttackCol->AddStartEvent(this, &BlackKnight::JumpAttackCollisionStart);
	m_BlackKnightJumpAttackCol->AddStayEvent(this, &BlackKnight::JumpAttackCollisionStay);
	m_BlackKnightJumpAttackCol->AddEndEvent(this, &BlackKnight::JumpAttackCollisionEnd);
	m_BlackKnightJumpAttackCol->Off();

	// �⺻ ���� �ִϸ��̼�
	m_AniBlackKnight = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Monster);
	m_AniBlackKnight->SetRenderScale({ 300, 300 });

	// ���� �ִϸ��̼�
	m_AniBlackKnight->CreateAnimation(L"Left_BlackKnight_Find", L"Left_BlackKnight.bmp", 0, 0);
	m_AniBlackKnight->CreateAnimation(L"Left_BlackKnight_Idle", L"Left_BlackKnight.bmp", 0, 1, 0.5f);
	m_AniBlackKnight->CreateAnimation(L"Left_BlackKnight_Move", L"Left_BlackKnight.bmp", 5, 9);
	m_AniBlackKnight->CreateAnimation(L"Left_BlackKnight_BackJump", L"Left_BlackKnight.bmp", 10, 10);
	m_AniBlackKnight->CreateAnimation(L"Left_BlackKnight_Laugh", L"Left_BlackKnight.bmp", 2, 3);
	m_AniBlackKnight->CreateAnimation(L"Left_BlackKnight_JumpStart", L"Left_BlackKnight.bmp", 12, 12);
	m_AniBlackKnight->CreateAnimation(L"Left_BlackKnight_JumpHighPoint", L"Left_BlackKnight.bmp", 25, 27, 0.08f, false);
	m_AniBlackKnight->CreateAnimation(L"Left_BlackKnight_NomalAttack", L"Left_BlackKnight.bmp", 13, 16);
	m_AniBlackKnight->CreateAnimation(L"Left_BlackKnight_SkillCharging", L"Left_BlackKnight.bmp", 17, 20);
	m_AniBlackKnight->CreateAnimation(L"Left_BlackKnight_SkillAttack", L"Left_BlackKnight.bmp", 21, 24);
	m_AniBlackKnight->CreateAnimation(L"Left_BlackKnight_KnockBack", L"Left_BlackKnight.bmp", 28, 28);
	m_AniBlackKnight->CreateAnimation(L"Left_BlackKnight_Death", L"Left_BlackKnight.bmp", 29, 29);
	m_AniBlackKnight->CreateAnimation(L"Left_BlackKnight_DeathMotion", L"Left_BlackKnight.bmp", 30, 33, 0.3f);

	// ������ �ִϸ��̼�
	m_AniBlackKnight->CreateAnimation(L"Right_BlackKnight_Find", L"Right_BlackKnight.bmp", 0, 0);
	m_AniBlackKnight->CreateAnimation(L"Right_BlackKnight_Idle", L"Right_BlackKnight.bmp", 0, 1, 0.5f);
	m_AniBlackKnight->CreateAnimation(L"Right_BlackKnight_Move", L"Right_BlackKnight.bmp", 5, 9);
	m_AniBlackKnight->CreateAnimation(L"Right_BlackKnight_BackJump", L"Right_BlackKnight.bmp", 10, 10);
	m_AniBlackKnight->CreateAnimation(L"Right_BlackKnight_Laugh", L"Right_BlackKnight.bmp", 2, 3);
	m_AniBlackKnight->CreateAnimation(L"Right_BlackKnight_JumpStart", L"Right_BlackKnight.bmp", 12, 12);
	m_AniBlackKnight->CreateAnimation(L"Right_BlackKnight_JumpHighPoint", L"Right_BlackKnight.bmp", 25, 27, 0.08f, false);
	m_AniBlackKnight->CreateAnimation(L"Right_BlackKnight_NomalAttack", L"Right_BlackKnight.bmp", 13, 16);
	m_AniBlackKnight->CreateAnimation(L"Right_BlackKnight_SkillCharging", L"Right_BlackKnight.bmp", 17, 20);
	m_AniBlackKnight->CreateAnimation(L"Right_BlackKnight_SkillAttack", L"Right_BlackKnight.bmp", 21, 24);
	m_AniBlackKnight->CreateAnimation(L"Right_BlackKnight_KnockBack", L"Right_BlackKnight.bmp", 28, 28);
	m_AniBlackKnight->CreateAnimation(L"Right_BlackKnight_Death", L"Right_BlackKnight.bmp", 29, 29);
	m_AniBlackKnight->CreateAnimation(L"Right_BlackKnight_DeathMotion", L"Right_BlackKnight.bmp", 30, 33, 0.3f);

	// ���� Ÿ���̹���
	m_BeShotLeftBlackKnight = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::Monster + 1);
	m_BeShotLeftBlackKnight->TransCenterSetting(L"Left_BeShotBlackKnight.bmp", { 512.f, 1152.f });
	m_BeShotLeftBlackKnight->SetCutData(0);
	m_BeShotLeftBlackKnight->SetRenderScale({ 300, 300 });
	m_BeShotLeftBlackKnight->Off();

	// ������ Ÿ���̹���
	m_BeShotRightBlackKnight = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::Monster + 1);
	m_BeShotRightBlackKnight->TransCenterSetting(L"Right_BeShotBlackKnight.bmp", { 512.f, 1152.f });
	m_BeShotRightBlackKnight->SetCutData(0);
	m_BeShotRightBlackKnight->SetRenderScale({ 300, 300 });
	m_BeShotRightBlackKnight->Off();

	// FSM ����
	m_BlackKnightFSM.CreateState(L"BlackKnight_Find", this, &BlackKnight::FindStay, &BlackKnight::FindStart, &BlackKnight::FindEnd);
	m_BlackKnightFSM.CreateState(L"BlackKnight_Idle", this, &BlackKnight::IdleStay, &BlackKnight::IdleStart, &BlackKnight::IdleEnd);
	m_BlackKnightFSM.CreateState(L"BlackKnight_Move", this, &BlackKnight::MoveStay, &BlackKnight::MoveStart, &BlackKnight::MoveEnd);
	m_BlackKnightFSM.CreateState(L"BlackKnight_BackJump", this, &BlackKnight::BackJumpStay, &BlackKnight::BackJumpStart, &BlackKnight::BackJumpEnd);
	m_BlackKnightFSM.CreateState(L"BlackKnight_Laugh", this, &BlackKnight::LaughStay, &BlackKnight::LaughStart, &BlackKnight::LaughEnd);
	m_BlackKnightFSM.CreateState(L"BlackKnight_JumpAttack", this, &BlackKnight::JumpAttackStay, &BlackKnight::JumpAttackStart, &BlackKnight::JumpAttackEnd);
	m_BlackKnightFSM.CreateState(L"BlackKnight_JumpAttackHightPoint", this, &BlackKnight::JumpAttackHighPointStay, &BlackKnight::JumpAttackHighPointStart, &BlackKnight::JumpAttackHighPointEnd);
	m_BlackKnightFSM.CreateState(L"BlackKnight_NomalAttack", this, &BlackKnight::NomalAttackStay, &BlackKnight::NomalAttackStart, &BlackKnight::NomalAttackEnd);
	m_BlackKnightFSM.CreateState(L"BlackKnight_SkillCharging", this, &BlackKnight::SkillChargingStay, &BlackKnight::SkillChargingStart, &BlackKnight::SkillChargingEnd);
	m_BlackKnightFSM.CreateState(L"BlackKnight_SkillAttack", this, &BlackKnight::SkillAttackStay, &BlackKnight::SkillAttackStart, &BlackKnight::SkillAttackEnd);
	m_BlackKnightFSM.CreateState(L"BlackKnight_KnockBack", this, &BlackKnight::KnockBackStay, &BlackKnight::KnockBackStart, &BlackKnight::KnockBackEnd);
	m_BlackKnightFSM.CreateState(L"BlackKnight_Death", this, &BlackKnight::DeathStay, &BlackKnight::DeathStart, &BlackKnight::DeathEnd);
	m_BlackKnightFSM.CreateState(L"BlackKnight_DeathMotion", this, &BlackKnight::DeathMotionStay, &BlackKnight::DeathMotionStart, &BlackKnight::DeathMotionEnd);

	// �ʱ���� ����
	m_BlackKnightFSM.ChangeState(L"BlackKnight_Find");
}

void BlackKnight::Update()
{
	// ������ ���� : m_MovePos �ʱ�ȭ
	m_MovePos = FLOAT4::ZERO;

	// ����üũ
	DirCheck();

	m_BlackKnightFSM.Update();

	// ���ݹ����� Image Blink
	BeShotImageBlink();

	// �̵�
	MovePosition(m_MovePos);
}

void BlackKnight::SetMoveDirect(GlobalValue::BasicMoveType _MoveDirect)
{
	m_MoveDir = _MoveDirect;
}

void BlackKnight::ChangeAniMation(const SGameEngineString& _ChangeAniName)
{
	m_CurAniMationName = L"";
	if (m_MoveDir == (GlobalValue::BasicMoveType::Right))
	{
		m_CurAniMationName = L"Right_";
	}
	if (m_MoveDir == (GlobalValue::BasicMoveType::Left))
	{
		m_CurAniMationName = L"Left_";
	}

	m_AniMationName = _ChangeAniName;
	m_CurAniMationName += _ChangeAniName;

	m_AniBlackKnight->ChangeAnimation(m_CurAniMationName);
}

void BlackKnight::DirCheck()
{
	if (m_MoveDir != m_PrevMoveDir)
	{
		ChangeAniMation(m_AniMationName);
	}

	m_PrevMoveDir = m_MoveDir;
}

void BlackKnight::BeShotImageBlink()
{
	if (true == m_bBlinkImage)
	{
		m_fBlinkImageTotalTime -= SGameEngineTimer::FDeltaTime();
		if (0.0f >= m_fBlinkImageTotalTime)
		{
			// Flag ����
			m_bBlinkImage = false;
			m_fBlinkImageTotalTime = 1.f;

			// �ش� �̹����� Off ��Ų��.
			DirectCheckImage()->Off();
		}

		m_fBlinkImageOnTime -= SGameEngineTimer::FDeltaTime(5.f);
		if (0.0f >= m_fBlinkImageOnTime)
		{
			DirectCheckImage()->SetCutData(m_AniBlackKnight->GetCurFrame());
			DirectCheckImage()->On();

			m_fBlinkImageOnTime = 0.2f;
		}

		m_fBlinkImageOffTime -= SGameEngineTimer::FDeltaTime(5.f);
		if (0.0f >= m_fBlinkImageOffTime)
		{
			DirectCheckImage()->Off();

			m_fBlinkImageOffTime = 0.3f;
		}
	}
}

SGameEngineRendererBasic* BlackKnight::DirectCheckImage()
{
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		return m_BeShotLeftBlackKnight;
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		return m_BeShotRightBlackKnight;
	}

	// �̰��� ���� ����
	return nullptr;
}

void BlackKnight::BlackKnightPixelCheck()
{
	// �ʳ����� �̵��ϱ� ���� �ȼ�üũ
	m_BossCheckPos = GetPosition() + m_MovePos;
	m_BossCheckDir[(int)GlobalValue::PixelCheckDirect::Left] = { m_BossCheckPos.ix() - 15, m_BossCheckPos.iy() };
	m_BossCheckDir[(int)GlobalValue::PixelCheckDirect::Right] = { m_BossCheckPos.ix() + 15, m_BossCheckPos.iy() };
	m_BossCheckDir[(int)GlobalValue::PixelCheckDirect::Top] = { m_BossCheckPos.ix(), m_BossCheckPos.iy() - 30 };
	m_BossCheckDir[(int)GlobalValue::PixelCheckDirect::Bottom] = { m_BossCheckPos.ix(), m_BossCheckPos.iy() + 40 };

	SGameEngineWinImage* FindImage = SGameEngineResMgr::Inst().FindImage(L"Plains.bmp");
	if (nullptr != FindImage)
	{
		for (int i = 0; i < 4; i++)
		{
			m_iBossCheckColor[i] = FindImage->GetPixelColor(m_BossCheckDir[i].ix(), m_BossCheckDir[i].iy());
		}
	}
}

void BlackKnight::PlayerCheetBossDeath()
{
	// ���� ���� ü���� ��� ��Ƴ���.
	m_BlackKnightInfo.SubtractHPAll();

	m_BlackKnightFSM.ChangeState(L"BlackKnight_Death");
}

void BlackKnight::DebugRender()
{
	// ���������� �ȼ�üũ ����Ʈ
	FLOAT4 BossPixelLeft = m_BossCheckDir[0] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), BossPixelLeft.ix() - 2, BossPixelLeft.iy() - 2, BossPixelLeft.ix() + 2, BossPixelLeft.iy() + 2);

	FLOAT4 BossPixelRight = m_BossCheckDir[1] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), BossPixelRight.ix() - 2, BossPixelRight.iy() - 2, BossPixelRight.ix() + 2, BossPixelRight.iy() + 2);

	FLOAT4 BossPixelTop = m_BossCheckDir[2] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), BossPixelTop.ix() - 2, BossPixelTop.iy() - 2, BossPixelTop.ix() + 2, BossPixelTop.iy() + 2);

	FLOAT4 BossPixelBot = m_BossCheckDir[3] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), BossPixelBot.ix() - 2, BossPixelBot.iy() - 2, BossPixelBot.ix() + 2, BossPixelBot.iy() + 2);

	// ��ü �浹ü
	Col2DData BlackKnightColData;
	BlackKnightColData.m_Pos = GetCamPosition() - m_BlackKnightCol->GetPivotPos();
	BlackKnightColData.m_Size = m_BlackKnightCol->GetScale();
	RECT BlackKnightColRect = { BlackKnightColData.iLeft(), BlackKnightColData.iTop(), BlackKnightColData.iRight(), BlackKnightColData.iBottom() };
	if (true == m_BlackKnightCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &BlackKnightColRect, SGameEngineWindow::GetGreenBrush());
	}

	// ���ݸ�� �浹ü
	Col2DData BlackKnightNomalAttackColData;
	BlackKnightNomalAttackColData.m_Pos = GetCamPosition() - m_BlackKnightNomalAttackCol->GetPivotPos();
	BlackKnightNomalAttackColData.m_Size = m_BlackKnightNomalAttackCol->GetScale();
	RECT BlackKnightNomalAttackColRect = { BlackKnightNomalAttackColData.iLeft(), BlackKnightNomalAttackColData.iTop(), BlackKnightNomalAttackColData.iRight(), BlackKnightNomalAttackColData.iBottom() };
	if (true == m_BlackKnightNomalAttackCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &BlackKnightNomalAttackColRect, SGameEngineWindow::GetGreenBrush());
	}

	// �������ݸ�� �浹ü
	Col2DData BlackKnightJumpAttackColData;
	BlackKnightJumpAttackColData.m_Pos = GetCamPosition() - m_BlackKnightJumpAttackCol->GetPivotPos();
	BlackKnightJumpAttackColData.m_Size = m_BlackKnightJumpAttackCol->GetScale();
	RECT BlackKnightJumpAttackColRect = { BlackKnightJumpAttackColData.iLeft(), BlackKnightJumpAttackColData.iTop(), BlackKnightJumpAttackColData.iRight(), BlackKnightJumpAttackColData.iBottom() };
	if (true == m_BlackKnightJumpAttackCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &BlackKnightJumpAttackColRect, SGameEngineWindow::GetGreenBrush());
	}
}

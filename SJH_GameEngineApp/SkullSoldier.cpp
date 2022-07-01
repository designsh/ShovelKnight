#include "SkullSoldier.h"

#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>

// Static Var
SoundPlayer SkullSoldier::m_SkullSoldierActionSound;

// Static Func

// member Var
SkullSoldier::SkullSoldier()
	: m_WindowSize(FLOAT4::ZERO), m_SkullSoldierInfo(),
	m_AniSkullSoldier(nullptr), m_SkullSoldierCol(nullptr), m_SkullSoldierAttackCol(nullptr), m_SkullSoldierFSM(), m_BeShotLeftSkullSoldier(nullptr), m_BeShotRightSkullSoldier(nullptr),
	m_bBlinkImage(false), m_fBlinkImageOnTime(0.2f), m_fBlinkImageOffTime(0.3f), m_fBlinkImageTotalTime(0.5f),
	m_MoveDir(GlobalValue::BasicMoveType::Right), m_PrevMoveDir(GlobalValue::BasicMoveType::None),
	m_AniMationName(), m_CurAniMationName(),
	m_MovePos(FLOAT4::ZERO), m_DirectPos(FLOAT4::ZERO),
	m_SkullCheckPos(FLOAT4::ZERO), m_SkullCheckDir(), m_iSkullCheckColor(),
	m_BackMoveStartPos(FLOAT4::ZERO), m_BackMoveMaxDistance(0.0f),
	m_KnockBackStartPos(FLOAT4::ZERO), m_KnockBackMaxDistance(0.0f),
	m_KnockBackMoveDir(GlobalValue::BasicMoveType::None), m_BackMoveDir(GlobalValue::BasicMoveType::None),
	m_PlayerBaseMyPos(GlobalValue::BasicMoveType::Right), m_PrevPlayerBaseMyPos(GlobalValue::BasicMoveType::Right),
	m_bDirtBlockCol(false), m_bDirtBlockSmallCol(false)
{

}

SkullSoldier::~SkullSoldier()
{

}

// member Func
void SkullSoldier::Start()
{
	// ���� ������ ũ�⸦ �����´�.
	m_WindowSize = SGameEngineWindow::GetSize();

	// ���� �⺻���� ����
	m_SkullSoldierInfo.SetDropCoin(20);
	m_SkullSoldierInfo.SetHP(2);
	m_SkullSoldierInfo.SetMaxHP(2);
	m_SkullSoldierInfo.SetMoveSpeed(150.f);
	m_SkullSoldierInfo.SetDropCoin(10);

	// ���� ��ü�浹ü ����
	m_SkullSoldierCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Monster);
	m_SkullSoldierCol->SetScale({ 40, 40 });
	m_SkullSoldierCol->AddStartEvent(this, &SkullSoldier::CollisionStart);
	m_SkullSoldierCol->AddStayEvent(this, &SkullSoldier::CollisionStay);
	m_SkullSoldierCol->AddEndEvent(this, &SkullSoldier::CollisionEnd);
	m_SkullSoldierCol->SetCheckData(0);

	// ���� ���ݸ���浹ü ����
	m_SkullSoldierAttackCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Monster);
	m_SkullSoldierAttackCol->SetScale({ 10, 20 });
	m_SkullSoldierAttackCol->AddStartEvent(this, &SkullSoldier::CollisionAttackStart);
	m_SkullSoldierAttackCol->AddStayEvent(this, &SkullSoldier::CollisionAttackStay);
	m_SkullSoldierAttackCol->AddEndEvent(this, &SkullSoldier::CollisionAttackEnd);
	m_SkullSoldierAttackCol->SetCheckData(1);
	m_SkullSoldierAttackCol->Off();

	// �⺻ ���� �ִϸ��̼�
	m_AniSkullSoldier = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Monster);
	m_AniSkullSoldier->SetRenderScale({ 300, 300 });

	// ���� �ִϸ��̼�
	m_AniSkullSoldier->CreateAnimation(L"LeftSkullFind", L"Skull_soldier_Left.bmp", 0, 0);
	m_AniSkullSoldier->CreateAnimation(L"LeftSkullMove", L"Skull_soldier_Left.bmp", 1, 5);
	m_AniSkullSoldier->CreateAnimation(L"LeftSkullAttackIdle", L"Skull_soldier_Left.bmp", 9, 10, 0.5f);
	m_AniSkullSoldier->CreateAnimation(L"LeftSkullAttack", L"Skull_soldier_Left.bmp", 11, 11);

	// ������ �ִϸ��̼�
	m_AniSkullSoldier->CreateAnimation(L"RightSkullFind", L"Skull_soldier_Right.bmp", 0, 0);
	m_AniSkullSoldier->CreateAnimation(L"RightSkullMove", L"Skull_soldier_Right.bmp", 0, 5);
	m_AniSkullSoldier->CreateAnimation(L"RightSkullAttackIdle", L"Skull_soldier_Right.bmp", 9, 10, 0.5f);
	m_AniSkullSoldier->CreateAnimation(L"RightSkullAttack", L"Skull_soldier_Right.bmp", 11, 11);

	// ����� �ִϸ��̼�
	m_AniSkullSoldier->CreateAnimation(L"SkullDieMotion", L"poofs.bmp", 0, 4);

	// ���� �ǰ��̹���
	m_BeShotLeftSkullSoldier = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::Monster + 1);
	m_BeShotLeftSkullSoldier->TransCenterSetting(L"BeShot_Skull_soldier_Left.bmp", { 768.f, 256.f });
	m_BeShotLeftSkullSoldier->SetCutData(0);
	m_BeShotLeftSkullSoldier->SetRenderScale({ 300, 300 });
	m_BeShotLeftSkullSoldier->Off();

	m_BeShotRightSkullSoldier = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::Monster + 1);
	m_BeShotRightSkullSoldier->TransCenterSetting(L"BeShot_Skull_soldier_Right.bmp", { 768.f, 256.f });
	m_BeShotRightSkullSoldier->SetCutData(0);
	m_BeShotRightSkullSoldier->SetRenderScale({ 300, 300 });
	m_BeShotRightSkullSoldier->Off();

	// FSM ����
	m_SkullSoldierFSM.CreateState(L"Skull_Find", this, &SkullSoldier::FindStay, &SkullSoldier::FindStart, &SkullSoldier::FindEnd);
	m_SkullSoldierFSM.CreateState(L"Skull_Move", this, &SkullSoldier::MoveStay, &SkullSoldier::MoveStart, &SkullSoldier::MoveEnd);
	m_SkullSoldierFSM.CreateState(L"Skull_BackMove", this, &SkullSoldier::BackMoveStay, &SkullSoldier::BackMoveStart, &SkullSoldier::BackMoveEnd);
	m_SkullSoldierFSM.CreateState(L"Skull_AttackIdle", this, &SkullSoldier::AttackIdleStay, &SkullSoldier::AttackIdleStart, &SkullSoldier::AttackIdleEnd);
	m_SkullSoldierFSM.CreateState(L"Skull_Attack", this, &SkullSoldier::AttackStay, &SkullSoldier::AttackStart, &SkullSoldier::AttackEnd);
	m_SkullSoldierFSM.CreateState(L"Skull_KnockBack", this, &SkullSoldier::KnockBackStay, &SkullSoldier::KnockBackStart, &SkullSoldier::KnockBackEnd);
	m_SkullSoldierFSM.CreateState(L"Skull_DieMotion", this, &SkullSoldier::DieMotionStay, &SkullSoldier::DieMotionStart, &SkullSoldier::DieMotionEnd);
	m_SkullSoldierFSM.ChangeState(L"Skull_Find");
}

void SkullSoldier::Update()
{
	// ������ ���� : m_MovePos �ʱ�ȭ
	m_MovePos = FLOAT4::ZERO;

	// ����üũ(���⺰ �ִϸ��̼�)
	DirCheck();

	// ���� ������Ʈ
	m_SkullSoldierFSM.Update();

	// Blink Check
	SetBlinkImage();

	MovePosition(m_MovePos);
}

SGameEngineRendererBasic* SkullSoldier::BlinkImageDirCheck()
{
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		return m_BeShotLeftSkullSoldier;
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		return m_BeShotRightSkullSoldier;
	}

	// �̰��� ���� ������ �ȵ�
	return nullptr;
}

void SkullSoldier::DirCheck()
{
	if (m_MoveDir != m_PrevMoveDir)
	{
		ChangeAniMation(m_AniMationName);
	}

	m_PrevMoveDir = m_MoveDir;
}

void SkullSoldier::MyPosOnBasePlayer()
{
	// �÷��̾�� �����Ÿ� �̻� ����������
	FLOAT4 MyPosOnBasePlayer = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPosOnBasePlayer.Normalize();
	if (0.0f > MyPosOnBasePlayer.x) // �����̸� �÷��̾�� ���� �����ʿ� ��ġ
	{
		m_PlayerBaseMyPos = GlobalValue::BasicMoveType::Right;
	}
	else if (0.0f <= MyPosOnBasePlayer.x) // ����̸� �÷��̾�� ���� ���ʿ� ��ġ
	{
		m_PlayerBaseMyPos = GlobalValue::BasicMoveType::Left;
	}

	if (m_PlayerBaseMyPos != m_PrevPlayerBaseMyPos)
	{
		m_PrevPlayerBaseMyPos = m_PlayerBaseMyPos;

		//// ������ȯ
		//if (GlobalValue::BasicMoveType::Left == m_MoveDir)
		//{
		//	m_MoveDir = GlobalValue::BasicMoveType::Right;
		//}
		//else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
		//{
		//	m_MoveDir = GlobalValue::BasicMoveType::Left;
		//}

		m_SkullSoldierFSM.ChangeState(L"Skull_BackMove");
	}
}

void SkullSoldier::MoveStateCheck()
{
	// �ȼ� üũ
	BlackKnightPixelCheck();

	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		if (RGB(255, 255, 255) != m_iSkullCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			// ������ȯ
			m_MovePos.x = 0.0f;
			m_MoveDir = GlobalValue::BasicMoveType::Right;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		if (RGB(255, 255, 255) != m_iSkullCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			// ������ȯ
			m_MovePos.x = 0.0f;
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}
	}

	if (RGB(0, 0, 0) != m_iSkullCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		// ���� �̵����⿡�� ��ȯ
		if (GlobalValue::BasicMoveType::Left == m_MoveDir)
		{
			m_MoveDir = GlobalValue::BasicMoveType::Right;
		}
		else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
		{
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}
	}

	// �̵��� UI�� �浹�ߴٸ� �鹫�� ���� ��ȯ
	if (true == m_bDirtBlockCol)
	{
		// ���� �̵����⿡�� ��ȯ
		if (GlobalValue::BasicMoveType::Left == m_MoveDir)
		{
			m_MoveDir = GlobalValue::BasicMoveType::Right;
		}
		else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
		{
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}

		m_bDirtBlockCol = false;
	}

	if (true == m_bDirtBlockSmallCol)
	{

		// ���� �̵����⿡�� ��ȯ
		m_SkullSoldierFSM.ChangeState(L"Skull_BackMove");

		m_bDirtBlockSmallCol = false;
	}

	// �̵� �� �÷��̾�� �����Ÿ��� �Ǹ� �鹫��� ���º�ȯ
	FLOAT4 MoveDist = GlobalValue::MainPlayer->GetPosition() - GetPosition();
	if (50.0f >= FLOAT4::Len2D(MoveDist))
	{
		m_SkullSoldierFSM.ChangeState(L"Skull_AttackIdle");
	}
}

void SkullSoldier::BackMoveStateCheck()
{
	// �ȼ� üũ
	BlackKnightPixelCheck();

	if (GlobalValue::BasicMoveType::Left == m_BackMoveDir)
	{
		if (RGB(255, 255, 255) != m_iSkullCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			// ������ȯ
			m_MovePos.x = 0.0f;
			m_SkullSoldierFSM.ChangeState(L"Skull_Move");
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_BackMoveDir)
	{
		if (RGB(255, 255, 255) != m_iSkullCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			// ������ȯ
			m_MovePos.x = 0.0f;
			m_SkullSoldierFSM.ChangeState(L"Skull_Move");
		}
	}

	if (RGB(0, 0, 0) != m_iSkullCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_MovePos.y = 0.0f;

		// ���º�ȯ
		m_SkullSoldierFSM.ChangeState(L"Skull_Move");
	}

	// �̵��� UI�� �浹�ߴٸ� ���� ���� ��ȯ
	if (true == m_bDirtBlockCol)
	{
		m_SkullSoldierFSM.ChangeState(L"Skull_Move");
	}

	if (true == m_bDirtBlockSmallCol)
	{
		m_SkullSoldierFSM.ChangeState(L"Skull_Move");
	}

	// �ִ��̵��Ÿ����� �̵��ߴٸ� Move�� ���º�ȯ
	if (GlobalValue::BasicMoveType::Left == m_BackMoveDir)
	{
		if (GetPosition().x <= m_BackMoveStartPos.x - m_BackMoveMaxDistance)
		{
			m_SkullSoldierFSM.ChangeState(L"Skull_Move");
		}
	}
	else 	if (GlobalValue::BasicMoveType::Right == m_BackMoveDir)
	{
		if (GetPosition().x >= m_BackMoveStartPos.x + m_BackMoveMaxDistance)
		{
			m_SkullSoldierFSM.ChangeState(L"Skull_Move");
		}
	}
}

void SkullSoldier::KnockBackStateCheck()
{
	// �ȼ� üũ
	BlackKnightPixelCheck();

	if (GlobalValue::BasicMoveType::Left == m_KnockBackMoveDir)
	{
		if (RGB(0, 0, 0) == m_iSkullCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			// ������ȯ
			m_MovePos.x = 0.0f;
			m_SkullSoldierFSM.ChangeState(L"Skull_Move");
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_KnockBackMoveDir)
	{
		if (RGB(0, 0, 0) == m_iSkullCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			// ������ȯ
			m_MovePos.x = 0.0f;
			m_SkullSoldierFSM.ChangeState(L"Skull_Move");
		}
	}

	if (RGB(0, 0, 0) != m_iSkullCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_MovePos.y = 0.0f;

		// ���º�ȯ
		m_SkullSoldierFSM.ChangeState(L"Skull_Move");
	}

	// �ִ��̵��Ÿ����� �̵��ߴٸ� Move�� ���º�ȯ
	if (GlobalValue::BasicMoveType::Left == m_KnockBackMoveDir)
	{
		if (GetPosition().x <= m_KnockBackStartPos.x - m_KnockBackMaxDistance)
		{
			m_SkullSoldierFSM.ChangeState(L"Skull_Move");
		}
	}
	else 	if (GlobalValue::BasicMoveType::Right == m_KnockBackMoveDir)
	{
		if (GetPosition().x >= m_KnockBackStartPos.x + m_KnockBackMaxDistance)
		{
			m_SkullSoldierFSM.ChangeState(L"Skull_Move");
		}
	}
}

void SkullSoldier::ChangeAniMation(const SGameEngineString& _ChangeAniName)
{
	m_CurAniMationName = L"";
	if (m_MoveDir == (GlobalValue::BasicMoveType::Right))
	{
		m_CurAniMationName = L"Right";
	}
	if (m_MoveDir == (GlobalValue::BasicMoveType::Left))
	{
		m_CurAniMationName = L"Left";
	}

	m_AniMationName = _ChangeAniName;
	m_CurAniMationName += _ChangeAniName;

	m_AniSkullSoldier->ChangeAnimationContinue(m_CurAniMationName);
}

void SkullSoldier::SetBlinkImage()
{
	if (true == m_bBlinkImage)
	{
		m_fBlinkImageOnTime -= SGameEngineTimer::FDeltaTime(5.f);
		if (0.0f >= m_fBlinkImageOnTime)
		{
			BlinkImageDirCheck()->SetCutData(m_AniSkullSoldier->GetCurFrame());
			BlinkImageDirCheck()->On();

			m_fBlinkImageOnTime = 0.2f;
		}

		m_fBlinkImageOffTime -= SGameEngineTimer::FDeltaTime(5.f);
		if (0.0f >= m_fBlinkImageOffTime)
		{
			BlinkImageDirCheck()->Off();

			m_fBlinkImageOffTime = 0.3f;
		}

		m_fBlinkImageTotalTime -= SGameEngineTimer::FDeltaTime();
		if (0.0f >= m_fBlinkImageTotalTime)
		{
			// Flag ����
			m_bBlinkImage = false;
			m_fBlinkImageTotalTime = 0.5f;

			BlinkImageDirCheck()->Off();
		}
	}
}

void SkullSoldier::SetMoveDiect(GlobalValue::BasicMoveType _MoveDir)
{
	m_MoveDir = _MoveDir;
}

void SkullSoldier::BlackKnightPixelCheck()
{
	// �ʳ����� �̵��ϱ� ���� �ȼ�üũ
	m_SkullCheckPos = GetPosition() + m_MovePos;
	m_SkullCheckDir[(int)GlobalValue::PixelCheckDirect::Left] = { m_SkullCheckPos.ix() - 20, m_SkullCheckPos.iy() };
	m_SkullCheckDir[(int)GlobalValue::PixelCheckDirect::Right] = { m_SkullCheckPos.ix() + 20, m_SkullCheckPos.iy() };
	m_SkullCheckDir[(int)GlobalValue::PixelCheckDirect::Top] = { m_SkullCheckPos.ix(), m_SkullCheckPos.iy() - 30 };
	m_SkullCheckDir[(int)GlobalValue::PixelCheckDirect::Bottom] = { m_SkullCheckPos.ix(), m_SkullCheckPos.iy() + 36 };

	SGameEngineWinImage* FindImage = SGameEngineResMgr::Inst().FindImage(L"Plains.bmp");
	if (nullptr != FindImage)
	{
		for (int i = 0; i < 4; i++)
		{
			m_iSkullCheckColor[i] = FindImage->GetPixelColor(m_SkullCheckDir[i].ix(), m_SkullCheckDir[i].iy());
		}
	}
}

void SkullSoldier::DebugRender()
{
	Col2DData SkullSoldierColData;
	SkullSoldierColData.m_Pos = GetCamPosition() - m_SkullSoldierCol->GetPivotPos();
	SkullSoldierColData.m_Size = m_SkullSoldierCol->GetScale();
	RECT SkullSoldierColRect = { SkullSoldierColData.iLeft(), SkullSoldierColData.iTop(), SkullSoldierColData.iRight(), SkullSoldierColData.iBottom() };
	if (true == m_SkullSoldierCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &SkullSoldierColRect, SGameEngineWindow::GetGreenBrush());
	}

	Col2DData SkullSoldierAttackColData;
	SkullSoldierAttackColData.m_Pos = GetCamPosition() - m_SkullSoldierAttackCol->GetPivotPos();
	SkullSoldierAttackColData.m_Size = m_SkullSoldierAttackCol->GetScale();
	RECT SkullSoldierAttackColRect = { SkullSoldierAttackColData.iLeft(), SkullSoldierAttackColData.iTop(), SkullSoldierAttackColData.iRight(), SkullSoldierAttackColData.iBottom() };
	if (true == m_SkullSoldierAttackCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &SkullSoldierAttackColRect, SGameEngineWindow::GetGreenBrush());
	}

	FLOAT4 SkullPixelLeft = m_SkullCheckDir[0] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), SkullPixelLeft.ix() - 2, SkullPixelLeft.iy() - 2, SkullPixelLeft.ix() + 2, SkullPixelLeft.iy() + 2);

	FLOAT4 SkullPixelRight = m_SkullCheckDir[1] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), SkullPixelRight.ix() - 2, SkullPixelRight.iy() - 2, SkullPixelRight.ix() + 2, SkullPixelRight.iy() + 2);

	FLOAT4 SkullPixelTop = m_SkullCheckDir[2] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), SkullPixelTop.ix() - 2, SkullPixelTop.iy() - 2, SkullPixelTop.ix() + 2, SkullPixelTop.iy() + 2);

	FLOAT4 SkullPixelBottom = m_SkullCheckDir[3] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), SkullPixelBottom.ix() - 2, SkullPixelBottom.iy() - 2, SkullPixelBottom.ix() + 2, SkullPixelBottom.iy() + 2);
}

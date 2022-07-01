#include "Beeto.h"

#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>

#include "ShovelKnight.h"

// Static Var
SoundPlayer Beeto::m_BeetoActionSound;

// Static Func

// member Var
Beeto::Beeto()
	: m_BeetoBasicInfo(), m_BeetoFSM(), m_AniBeeto(nullptr), m_BeetoCol(nullptr),
	m_MoveDir(GlobalValue::BasicMoveType::Left), m_PrevMoveDir(GlobalValue::BasicMoveType::None),
	m_MovePos(FLOAT4::ZERO), m_DirectPos(FLOAT4::ZERO), 
	m_DeathPos(FLOAT4::ZERO), m_DeathPower(FLOAT4::ZERO), m_DeathGravityPower(FLOAT4::ZERO),
	m_BeetoCheckPos(FLOAT4::ZERO), m_BeetoCheckDir(), m_iBeetoCheckColor()
{

}

Beeto::~Beeto()
{

}

// member Func
void Beeto::Start()
{
	// ���� ������ ũ�⸦ �����´�.
	m_WindowSize = SGameEngineWindow::GetSize();

	// ������ �⺻���� �ʱ�ȭ
	m_BeetoBasicInfo.SetMaxHP(1);
	m_BeetoBasicInfo.SetHP(1);
	m_BeetoBasicInfo.SetDropCoin(5);
	m_BeetoBasicInfo.SetMoveSpeed(50.f);

	// ���� �浹ü ����
	// �÷��̾� ��ü�� �浹, �÷��̾� ���ݸ�ǰ� �浹
	m_BeetoCol= CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Monster);
	m_BeetoCol->SetScale({ 50, 50 });
	m_BeetoCol->AddStartEvent(this, &Beeto::CollisionStart);
	m_BeetoCol->AddStayEvent(this, &Beeto::CollisionStay);
	m_BeetoCol->AddEndEvent(this, &Beeto::CollisionEnd);

	// �⺻ ���� �ִϸ��̼�
	m_AniBeeto = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Monster);
	m_AniBeeto->SetRenderScale({ 300, 300 });

	// �����̵�
	m_AniBeeto->CreateAnimation(L"LeftBeetoFind", L"Beeto_Left.bmp", 0, 0);
	m_AniBeeto->CreateAnimation(L"LeftBeetoMove", L"Beeto_Left.bmp", 0, 3, 0.5f, true);
	m_AniBeeto->CreateAnimation(L"LeftBeetoDie", L"Beeto_Left.bmp", 4, 5);

	// �������̵�
	m_AniBeeto->CreateAnimation(L"RightBeetoFind", L"Beeto_Right.bmp", 0, 0);
	m_AniBeeto->CreateAnimation(L"RightBeetoMove", L"Beeto_Right.bmp", 0, 3, 0.5f, true);
	m_AniBeeto->CreateAnimation(L"RightBeetoDie", L"Beeto_Right.bmp", 4, 5);

	// ����� ���
	m_AniBeeto->CreateAnimation(L"DieMotion", L"poofs.bmp", 0, 4);

	m_BeetoFSM.CreateState(L"Beeto_Find", this, &Beeto::FindStay, &Beeto::FindStart, &Beeto::FindEnd);
	m_BeetoFSM.CreateState(L"Beeto_Move", this, &Beeto::MoveStay, &Beeto::MoveStart, &Beeto::MoveEnd);
	m_BeetoFSM.CreateState(L"Beeto_Die", this, &Beeto::DieStay, &Beeto::DieStart, &Beeto::DieEnd);
	m_BeetoFSM.CreateState(L"Beeto_DieMotion", this, &Beeto::DieMotionStay, &Beeto::DieMotionStart, &Beeto::DieMotionEnd);

	// �ʱ���� ����
	m_BeetoFSM.ChangeState(L"Beeto_Find");
}

void Beeto::Update()
{
	m_MovePos = FLOAT4::ZERO;

	DirCheck();

	m_BeetoFSM.Update();

	MovePosition(m_MovePos);
}

void Beeto::MoveStateCheck()
{
	// �ȼ�üũ
	BeetoPixelCheck();

	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		if (RGB(0, 0, 0) == m_iBeetoCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			// ������ȯ
			m_MovePos.x = 0.0f;
			m_MoveDir = GlobalValue::BasicMoveType::Right;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		if (RGB(0, 0, 0) == m_iBeetoCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			// ������ȯ
			m_MovePos.x = 0.0f;
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}
	}

	if (RGB(0, 0, 0) != m_iBeetoCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
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
}

void Beeto::DieStateCheck()
{
	// �ȼ�üũ
	BeetoPixelCheck();

	if (0.0f <= m_DeathPower.y)
	{
		if (RGB(0, 0, 0) == m_iBeetoCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			m_DeathPos = FLOAT4::ZERO;
			m_DeathPower = FLOAT4::ZERO;
			m_DeathGravityPower = FLOAT4::ZERO;

			// �ٴڿ� ������ ������ȯ
			m_BeetoFSM.ChangeState(L"Beeto_DieMotion");
		}
	}
}

void Beeto::DirCheck()
{
	if (m_MoveDir != m_PrevMoveDir)
	{
		ChangeAniMation(m_AniMationName);
	}

	m_PrevMoveDir = m_MoveDir;
}

void Beeto::ChangeAniMation(const SGameEngineString& _ChangeAniName)
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

	m_AniBeeto->ChangeAnimationContinue(m_CurAniMationName);
}

void Beeto::SetMoveDirect(GlobalValue::BasicMoveType _MoveDir)
{
	m_MoveDir = _MoveDir;
}

void Beeto::BeetoPixelCheck()
{
	// �ʳ����� �̵��ϱ� ���� �ȼ�üũ
	m_BeetoCheckPos = GetPosition() + m_MovePos;
	m_BeetoCheckDir[(int)GlobalValue::PixelCheckDirect::Left] = { m_BeetoCheckPos.ix() - 20, m_BeetoCheckPos.iy() - 20 };
	m_BeetoCheckDir[(int)GlobalValue::PixelCheckDirect::Right] = { m_BeetoCheckPos.ix() + 20, m_BeetoCheckPos.iy() - 20 };
	m_BeetoCheckDir[(int)GlobalValue::PixelCheckDirect::Top] = { m_BeetoCheckPos.ix(), m_BeetoCheckPos.iy() - 30 };
	m_BeetoCheckDir[(int)GlobalValue::PixelCheckDirect::Bottom] = { m_BeetoCheckPos.ix(), m_BeetoCheckPos.iy() };

	SGameEngineWinImage* FindImage = SGameEngineResMgr::Inst().FindImage(L"Plains.bmp");
	if (nullptr != FindImage)
	{
		for (int i = 0; i < 4; i++)
		{
			m_iBeetoCheckColor[i] = FindImage->GetPixelColor(m_BeetoCheckDir[i].ix(), m_BeetoCheckDir[i].iy());
		}
	}
}

void Beeto::DebugRender()
{
	FLOAT4 BeetoPixelLeft = m_BeetoCheckDir[0] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), BeetoPixelLeft.ix() - 2, BeetoPixelLeft.iy() - 2, BeetoPixelLeft.ix() + 2, BeetoPixelLeft.iy() + 2);

	FLOAT4 BeetoPixelRight = m_BeetoCheckDir[1] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), BeetoPixelRight.ix() - 2, BeetoPixelRight.iy() - 2, BeetoPixelRight.ix() + 2, BeetoPixelRight.iy() + 2);

	FLOAT4 BeetoPixelTop = m_BeetoCheckDir[2] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), BeetoPixelTop.ix() - 2, BeetoPixelTop.iy() - 2, BeetoPixelTop.ix() + 2, BeetoPixelTop.iy() + 2);

	FLOAT4 BeetoPixelBottom = m_BeetoCheckDir[3] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), BeetoPixelBottom.ix() - 2, BeetoPixelBottom.iy() - 2, BeetoPixelBottom.ix() + 2, BeetoPixelBottom.iy() + 2);

	Col2DData ColData;
	ColData.m_Pos = GetCamPosition() - m_BeetoCol->GetPivotPos();
	ColData.m_Size = m_BeetoCol->GetScale();
	RECT ColRect = { ColData.iLeft(), ColData.iTop(), ColData.iRight(), ColData.iBottom() };
	if (true == m_BeetoCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &ColRect, SGameEngineWindow::GetGreenBrush());
	}
}

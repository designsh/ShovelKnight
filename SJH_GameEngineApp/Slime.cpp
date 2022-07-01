#include "Slime.h"

#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>

#include "ShovelKnight.h"

// Static Var
SoundPlayer Slime::m_SlimeActionSound;

// Static Func

// member Var
Slime::Slime()
	: m_WindowSize(FLOAT4::ZERO), m_SlimeInfo(), m_Speed(50.f),
	m_AniSlime(nullptr), m_SlimeCol(nullptr), m_BeShotSlime(nullptr), m_SlimeFSM(),
	m_bBlinkImage(false), m_fBlinkImageOnTime(0.2f), m_fBlinkImageOffTime(0.3f), m_fBlinkImageTotalTime(0.5f),
	m_GravityPos(FLOAT4::ZERO), m_GravityPower(FLOAT4::ZERO), m_JumpPos(FLOAT4::ZERO), m_JumpPower(FLOAT4::ZERO),
	m_MovePos(FLOAT4::ZERO), m_DirectPos(FLOAT4::ZERO),
	m_JumpEventer(),
	m_MoveDir(GlobalValue::BasicMoveType::None), m_PrevMoveDir(GlobalValue::BasicMoveType::None),
	m_SlimeCheckPos(FLOAT4::ZERO), m_SlimeCheckDir(), m_iSlimeCheckColor(), m_JumpTime(0.0f),
	m_DirtBlockCol(false), m_DirtBlockSmallCol(false)
{

}

Slime::~Slime()
{

}

// member Func
void Slime::Start()
{
	// 현재 윈도우 크기를 가져온다.
	m_WindowSize = SGameEngineWindow::GetSize();

	// 몬스터 기본정보 설정
	m_SlimeInfo.SetHP(2);
	m_SlimeInfo.SetMaxHP(2);
	m_SlimeInfo.SetMoveSpeed(50.f);
	m_SlimeInfo.SetDropCoin(15);

	// 몬스터 충돌체 생성
	m_SlimeCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Monster);
	m_SlimeCol->SetScale({ 50, 50 });
	m_SlimeCol->AddStartEvent(this, &Slime::CollisionStart);
	m_SlimeCol->AddStayEvent(this, &Slime::CollisionStay);
	m_SlimeCol->AddEndEvent(this, &Slime::CollisionEnd);

	// 기본 몬스터 애니메이션
	m_AniSlime = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Monster);
	m_AniSlime->SetRenderScale({ 300, 300 });
	m_AniSlime->CreateAnimation(L"SlimeFind", L"Slime.bmp", 0, 0);
	m_AniSlime->CreateAnimation(L"SlimeMove", L"Slime.bmp", 0, 3);

	// 사망시 모션
	m_AniSlime->CreateAnimation(L"SlimeDie", L"poofs.bmp", 0, 4);

	// 몬스터 피격시 이미지
	m_BeShotSlime = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::Monster + 1);
	m_BeShotSlime->TransCenterSetting(L"BeShotSlime.bmp", { 512.f, 128.f });
	m_BeShotSlime->SetCutData(0);
	m_BeShotSlime->SetRenderScale({ 300, 300 });
	m_BeShotSlime->Off();

	m_SlimeFSM.CreateState(L"Slime_Find", this, &Slime::FindStay, &Slime::FindStart, &Slime::FindEnd);
	m_SlimeFSM.CreateState(L"Slime_Move", this, &Slime::MoveStay, &Slime::MoveStart, &Slime::MoveEnd);
	m_SlimeFSM.CreateState(L"Slime_Attack", this, &Slime::JumpAttackStay, &Slime::JumpAttackStart, &Slime::JumpAttackEnd);
	m_SlimeFSM.CreateState(L"Slime_Death", this, &Slime::DieStay, &Slime::DieStart, &Slime::DieEnd);

	// 초기상태 지정
	m_SlimeFSM.ChangeState(L"Slime_Find");
}

void Slime::Update()
{
	m_SlimeFSM.Update();

	// 피격판정시 Blink처리
	SetBlinkImage();
}

void Slime::SetBlinkImage()
{
	if (true == m_bBlinkImage)
	{
		m_fBlinkImageOnTime -= SGameEngineTimer::FDeltaTime(5.f);
		if (0.0f >= m_fBlinkImageOnTime)
		{
			m_BeShotSlime->SetCutData(m_AniSlime->GetCurFrame());
			m_BeShotSlime->On();

			m_fBlinkImageOnTime = 0.2f;
		}

		m_fBlinkImageOffTime -= SGameEngineTimer::FDeltaTime(5.f);
		if (0.0f >= m_fBlinkImageOffTime)
		{
			m_BeShotSlime->Off();

			m_fBlinkImageOffTime = 0.3f;
		}

		m_fBlinkImageTotalTime -= SGameEngineTimer::FDeltaTime();
		if (0.0f >= m_fBlinkImageTotalTime)
		{
			// Flag 해제
			m_bBlinkImage = false;
			m_fBlinkImageTotalTime = 0.5f;

			m_BeShotSlime->Off();
		}
	}
}

void Slime::JumpAttackChange()
{
	if (false == m_DirtBlockCol)
	{
		// 일정시간이 지나면 점프어택으로 상태 변경
		m_SlimeFSM.ChangeState(L"Slime_Attack");
	}
	else if (false == m_DirtBlockSmallCol)
	{
		// 일정시간이 지나면 점프어택으로 상태 변경
		m_SlimeFSM.ChangeState(L"Slime_Attack");
	}
}

void Slime::SetInitMove(GlobalValue::BasicMoveType _MoveDirect)
{
	m_MoveDir = _MoveDirect;
}

void Slime::DirPosCheck()
{
	m_DirectPos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(m_Speed);
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(m_Speed);
	}

	m_MovePos = m_DirectPos;

	// 이때 픽셀체크한다.
	SlimePixcelCol();

	// 점프 픽셀체크 및 벽과 충돌시 방향전환
	MoveCheck();

	MovePosition(m_MovePos);

	m_PrevMoveDir = m_MoveDir;
}

void Slime::SlimePixcelCol()
{
	// 충돌시 방향전환과 진행안되도록 픽셀충돌 생성
	m_SlimeCheckPos = GetPosition() + m_MovePos;
	m_SlimeCheckDir[(int)GlobalValue::PixelCheckDirect::Left] = { m_SlimeCheckPos.ix() - 20, m_SlimeCheckPos.iy() };
	m_SlimeCheckDir[(int)GlobalValue::PixelCheckDirect::Right] = { m_SlimeCheckPos.ix() + 20, m_SlimeCheckPos.iy() };
	m_SlimeCheckDir[(int)GlobalValue::PixelCheckDirect::Top] = { m_SlimeCheckPos.ix(), m_SlimeCheckPos.iy() - 20 };
	m_SlimeCheckDir[(int)GlobalValue::PixelCheckDirect::Bottom] = { m_SlimeCheckPos.ix(), m_SlimeCheckPos.iy() + 10 };
	SGameEngineWinImage* FindImage = SGameEngineResMgr::Inst().FindImage(L"Plains.bmp");
	if (nullptr != FindImage)
	{
		for (int i = 0; i < 4; i++)
		{
			m_iSlimeCheckColor[i] = FindImage->GetPixelColor(m_SlimeCheckDir[i].ix(), m_SlimeCheckDir[i].iy());
		}
	}
}

void Slime::MoveCheck()
{
	// 현재 이동방향에서 충돌시 방향 전환
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		if (RGB(0, 0, 0) == m_iSlimeCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MoveDir = GlobalValue::BasicMoveType::Right;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		if (RGB(0, 0, 0) == m_iSlimeCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}
	}
}

void Slime::JumpAttackCheck()
{
	if (RGB(0, 0, 0) == m_iSlimeCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		m_MovePos.y = 0.0f;
		m_JumpPos = FLOAT4::ZERO;
		m_JumpPower = FLOAT4::ZERO;
		m_GravityPos = FLOAT4::ZERO;
		m_GravityPower = FLOAT4::ZERO;

		// 상태 변경
		m_SlimeFSM.ChangeState(L"Slime_Move");
	}

	// 바닥에 떨어지면 죽는다.
	if (RGB(255, 0, 0) == m_iSlimeCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		Death();
	}

	// 현재 이동방향에서 충돌시 방향 전환
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		if (RGB(0, 0, 0) == m_iSlimeCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MoveDir = GlobalValue::BasicMoveType::Right;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		if (RGB(0, 0, 0) == m_iSlimeCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MoveDir = GlobalValue::BasicMoveType::Left;
		}
	}
}

void Slime::SetJumpTime(float _JumpTime)
{
	m_JumpTime = _JumpTime;
}

void Slime::DebugRender()
{
	Col2DData ColData;
	ColData.m_Pos = GetCamPosition() - m_SlimeCol->GetPivotPos();
	ColData.m_Size = m_SlimeCol->GetScale();
	RECT ColRect = { ColData.iLeft(), ColData.iTop(), ColData.iRight(), ColData.iBottom() };
	if (true == m_SlimeCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &ColRect, SGameEngineWindow::GetGreenBrush());
	}

	FLOAT4 SlimePixelLeft = FLOAT4(GetPosition().x - GetScene()->GetCamPos().x - 20.f, GetPosition().y - GetScene()->GetCamPos().y);
	Rectangle(SGameEngineWindow::GetBackBufferDC(),
		SlimePixelLeft.ix() - 2,
		SlimePixelLeft.iy() - 2,
		SlimePixelLeft.ix() + 2,
		SlimePixelLeft.iy() + 2);

	FLOAT4 SlimePixelRight = FLOAT4(GetPosition().x - GetScene()->GetCamPos().x + 20.f, GetPosition().y - GetScene()->GetCamPos().y);
	Rectangle(SGameEngineWindow::GetBackBufferDC(),
		SlimePixelRight.ix() - 2,
		SlimePixelRight.iy() - 2,
		SlimePixelRight.ix() + 2,
		SlimePixelRight.iy() + 2);

	FLOAT4 SlimePixelTop = FLOAT4(GetPosition().x - GetScene()->GetCamPos().x, GetPosition().y - GetScene()->GetCamPos().y - 20.f);
	Rectangle(SGameEngineWindow::GetBackBufferDC(),
		SlimePixelTop.ix() - 2,
		SlimePixelTop.iy() - 2,
		SlimePixelTop.ix() + 2,
		SlimePixelTop.iy() + 2);

	FLOAT4 SlimePixelBottom = FLOAT4(GetPosition().x - GetScene()->GetCamPos().x, GetPosition().y - GetScene()->GetCamPos().y + 10.f);
	Rectangle(SGameEngineWindow::GetBackBufferDC(),
		SlimePixelBottom.ix() - 2,
		SlimePixelBottom.iy() - 2,
		SlimePixelBottom.ix() + 2,
		SlimePixelBottom.iy() + 2);
}

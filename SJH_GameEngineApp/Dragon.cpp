#include "Dragon.h"
#include <SGameEngineWindow.h>

// Static Var
SoundPlayer Dragon::m_DragonActionSound;

// Static Func

// member Var
Dragon::Dragon()
	: m_WindowSize(FLOAT4::ZERO), m_DragonInfo(),
	m_AniDragon(nullptr), m_DragonCol(nullptr), m_DragonFSM(), m_BeShotLeftDragon(nullptr), m_BeShotRightDragon(nullptr),
	m_MoveDir(GlobalValue::BasicMoveType::Right), m_PrevMoveDir(GlobalValue::BasicMoveType::None),
	m_bBlinkImage(false), m_fBlinkImageOnTime(0.2f), m_fBlinkImageOffTime(0.3f), m_fBlinkImageTotalTime(0.5f),
	m_MoveStartPos(FLOAT4::ZERO), m_DirectPos(FLOAT4::ZERO), m_MovePos(FLOAT4::ZERO), m_UpPos(FLOAT4::ZERO), m_DownPos(FLOAT4::ZERO), m_Speed(50.f), m_MaxDist(FLOAT4::ZERO),
	m_UpStartPos(FLOAT4::ZERO), m_DownStartPos(FLOAT4::ZERO),
	m_bDropCoin(false)
{

}

Dragon::~Dragon()
{

}

// member Func
void Dragon::Start()
{
	// 현재 윈도우 크기를 가져온다.
	m_WindowSize = SGameEngineWindow::GetSize();

	// 몬스터 기본정보를 설정한다.
	m_DragonInfo.SetHP(2);
	m_DragonInfo.SetMaxHP(2);
	m_DragonInfo.SetDropCoin(10);

	// 몬스터 충돌체 생성
	// 플레이어 몸체와 충돌, 플레이어 공격모션과 충돌
	m_DragonCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Monster);
	m_DragonCol->SetScale({ 50, 50 });
	m_DragonCol->AddStartEvent(this, &Dragon::CollisionStart);
	m_DragonCol->AddStayEvent(this, &Dragon::CollisionStay);
	m_DragonCol->AddEndEvent(this, &Dragon::CollisionEnd);

	// 기본 몬스터 애니메이션
	m_AniDragon = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Monster);
	m_AniDragon->SetRenderScale({ 300, 300 });

	// 왼쪽이동
	m_AniDragon->CreateAnimation(L"LeftDragonFind", L"Dragon_Left.bmp", 0, 0);
	m_AniDragon->CreateAnimation(L"LeftDragonMove", L"Dragon_Left.bmp", 0, 3);

	// 오른쪽이동
	m_AniDragon->CreateAnimation(L"RightDragonFind", L"Dragon_Right.bmp", 0, 0);
	m_AniDragon->CreateAnimation(L"RightDragonMove", L"Dragon_Right.bmp", 0, 3);

	// 사망시 모션
	m_AniDragon->CreateAnimation(L"DieMotion", L"poofs.bmp", 0, 4);

	// 왼쪽 타격이미지
	m_BeShotLeftDragon = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::Monster + 1);
	m_BeShotLeftDragon->TransCenterSetting(L"BeShot_Dragon_Left.bmp", { 640.f, 384.f });
	m_BeShotLeftDragon->SetCutData(0);
	m_BeShotLeftDragon->SetRenderScale({ 300, 300 });
	m_BeShotLeftDragon->Off();

	// 오른쪽 타격이미지
	m_BeShotRightDragon = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::Monster + 1);
	m_BeShotRightDragon->TransCenterSetting(L"BeShot_Dragon_Right.bmp", { 640.f, 384.f });
	m_BeShotRightDragon->SetCutData(0);
	m_BeShotRightDragon->SetRenderScale({ 300, 300 });
	m_BeShotRightDragon->Off();

	// FSM 상태
	m_DragonFSM.CreateState(L"Dragon_Find", this, &Dragon::FindStay, &Dragon::FindStart, &Dragon::FindEnd);
	m_DragonFSM.CreateState(L"Dragon_Move", this, &Dragon::MoveStay, &Dragon::MoveStart, &Dragon::MoveEnd);
	m_DragonFSM.CreateState(L"Dragon_DownMove", this, &Dragon::DownMoveStay, &Dragon::DownMoveStart, &Dragon::DownMoveEnd);
	m_DragonFSM.CreateState(L"Dragon_UpMove", this, &Dragon::UpMoveStay, &Dragon::UpMoveStart, &Dragon::UpMoveEnd);
	m_DragonFSM.CreateState(L"Dragon_Death", this, &Dragon::DeathStay, &Dragon::DeathStart, &Dragon::DeathEnd);

	// 초기상태 지정
	m_DragonFSM.ChangeState(L"Dragon_Find");
}

void Dragon::Update()
{
	m_DragonFSM.Update();

	BeShotBlink();
}

bool Dragon::IsDropCoin()
{
	return m_bDropCoin;
}

void Dragon::DropCoinOn()
{
	m_bDropCoin = true;
}

void Dragon::DropCoinOff()
{
	m_bDropCoin = false;
}

void Dragon::ChangeAniMation(const SGameEngineString& _ChangeAniName)
{
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

	m_AniDragon->ChangeAnimationContinue(m_CurAniMationName);
}

void Dragon::SetStartMoveDirect(GlobalValue::BasicMoveType _Direct)
{
	m_MoveDir = _Direct;
}

void Dragon::SetMaxMoveDist(FLOAT4 _MaxDist)
{
	m_MaxDist = _MaxDist;
}

SGameEngineRendererBasic* Dragon::DirectCheck()
{
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		return m_BeShotLeftDragon;
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		return m_BeShotRightDragon;
	}

	// 이곳에 오면 에러
	return nullptr;
}

void Dragon::BeShotBlink()
{
	if (true == m_bBlinkImage)
	{
		m_fBlinkImageOnTime -= SGameEngineTimer::FDeltaTime(5.f);
		if (0.0f >= m_fBlinkImageOnTime)
		{
			DirectCheck()->SetCutData(m_AniDragon->GetCurFrame());
			DirectCheck()->On();

			m_fBlinkImageOnTime = 0.2f;
		}

		m_fBlinkImageOffTime -= SGameEngineTimer::FDeltaTime(5.f);
		if (0.0f >= m_fBlinkImageOffTime)
		{
			DirectCheck()->Off();

			m_fBlinkImageOffTime = 0.3f;
		}

		m_fBlinkImageTotalTime -= SGameEngineTimer::FDeltaTime();
		if (0.0f >= m_fBlinkImageTotalTime)
		{
			// Flag 해제
			m_bBlinkImage = false;
			m_fBlinkImageTotalTime = 0.5f;

			m_BeShotLeftDragon->Off();
			m_BeShotRightDragon->Off();
		}
	}
}

void Dragon::DirPosCheck()
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

	MovePosition(m_MovePos);
}

void Dragon::UpPosCheck()
{
	m_DirectPos = FLOAT4::ZERO;

	m_DirectPos += FLOAT4::UP * SGameEngineTimer::FDeltaTime(m_Speed);

	m_MovePos = m_DirectPos;

	MovePosition(m_MovePos);
}

void Dragon::DownPosCheck()
{
	m_DirectPos = FLOAT4::ZERO;

	m_DirectPos += FLOAT4::DOWN * SGameEngineTimer::FDeltaTime(m_Speed);

	m_MovePos = m_DirectPos;

	MovePosition(m_MovePos);
}

void Dragon::DebugRender()
{
	Col2DData DragonColData;
	DragonColData.m_Pos = GetCamPosition() - m_DragonCol->GetPivotPos();
	DragonColData.m_Size = m_DragonCol->GetScale();
	RECT DragonColRect = { DragonColData.iLeft(), DragonColData.iTop(), DragonColData.iRight(), DragonColData.iBottom() };
	if (true == m_DragonCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &DragonColRect, SGameEngineWindow::GetGreenBrush());
	}
}

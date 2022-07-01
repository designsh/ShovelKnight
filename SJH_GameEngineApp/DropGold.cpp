#include "DropGold.h"
#include "ShovelKnight.h"
#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>

// Static Var

// Static Func

// member Var
DropGold::DropGold()
	: m_WindowSize(FLOAT4::ZERO), 
	m_DropGoldRender(nullptr), m_DropGoldCol(nullptr), m_AniDropGold(nullptr), m_DropGoldFSM(),
	m_DropGold(0), m_Speed(50.f), m_DelayTime(2.f), m_DeathTime(3.f),
	m_MoveDir(GlobalValue::BasicMoveType::Right), 
	m_MovePos(FLOAT4::ZERO), m_DirectPos(FLOAT4::ZERO), m_DropPos(FLOAT4::ZERO), m_DropPower(FLOAT4::ZERO), m_DropGravityPower(FLOAT4::ZERO),
	m_DropGoldCheckPos(FLOAT4::ZERO), m_DropGoldCheckDir(), m_iDropGoldCheckColor(),
	m_EvaporationEventer()
{

}

DropGold::~DropGold()
{

}

// member Func
void DropGold::Start()
{
	// 현재 윈도우 크기를 가져온다.
	m_WindowSize = SGameEngineWindow::GetSize();

	// 몬스터 충돌체 생성
	// 플레이어 몸체와 충돌, 플레이어 공격모션과 충돌
	m_DropGoldCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::UI);
	m_DropGoldCol->SetScale({ 50, 50 });
	m_DropGoldCol->AddStartEvent(this, &DropGold::CollisionStart);
	m_DropGoldCol->AddStayEvent(this, &DropGold::CollisionStay);
	m_DropGoldCol->AddEndEvent(this, &DropGold::CollisionEnd);
	m_DropGoldCol->SetCheckData(0);

	// 애니메이션
	m_AniDropGold = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniDropGold->SetRenderScale({ 150, 150 });
	m_AniDropGold->CreateAnimation(L"DropGold1", L"Gold.bmp", 0, 0); // 골드량 1
	m_AniDropGold->CreateAnimation(L"DropGold5", L"Gold.bmp", 1, 1); // 골드량 5
	m_AniDropGold->CreateAnimation(L"DropGold10", L"Gold.bmp", 2, 2); // 골드량 10
	m_AniDropGold->CreateAnimation(L"DropGold20", L"Gold.bmp", 3, 3); // 골드량 20
	m_AniDropGold->CreateAnimation(L"DropGold50", L"Gold.bmp", 4, 4); // 골드량 50
	m_AniDropGold->CreateAnimation(L"DropGold100", L"Gold.bmp", 5, 5); // 골드량 100

	// FSM 상태
	m_DropGoldFSM.CreateState(L"DropGold_Idle", this, &DropGold::IDLEStay, &DropGold::IDLEStart, &DropGold::IDLEEnd);
	m_DropGoldFSM.CreateState(L"DropGold_Move", this, &DropGold::MoveStay, &DropGold::MoveStart, &DropGold::MoveEnd);
	m_DropGoldFSM.CreateState(L"DropGold_TimeDelay", this, &DropGold::TimeDelayStay, &DropGold::TimeDelayStart, &DropGold::TimeDelayEnd);
	m_DropGoldFSM.CreateState(L"DropGold_Death", this, &DropGold::GoldEvaporationStay, &DropGold::GoldEvaporationStart, &DropGold::GoldEvaporationEnd);

	// 초기상태 지정
	m_DropGoldFSM.ChangeState(L"DropGold_Idle");
}

void DropGold::Update()
{
	m_MovePos = FLOAT4::ZERO;

	m_DropGoldFSM.Update();

	MovePosition(m_MovePos);
}

void DropGold::SetMoveSpeed(float _MoveSpeed)
{
	m_Speed = _MoveSpeed;
}

void DropGold::SetDropGold(int _DropGold)
{
	m_DropGold = _DropGold;
}

int DropGold::GetDropGold()
{
	return m_DropGold;
}

void DropGold::SetDropGoldImage(int _DropGold)
{
	SGameEngineString CurDropGold = L"";
	CurDropGold = L"DropGold";
	CurDropGold += SGameEngineString::ToString(_DropGold);

	m_AniDropGold->ChangeAnimation(CurDropGold);
}

void DropGold::MovePosCheck()
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

	m_DropPower += m_DropGravityPower * SGameEngineTimer::FDeltaTime();
	m_DropPos = m_DropPower * SGameEngineTimer::FDeltaTime();
}

void DropGold::GoldPixelCheck()
{
	m_DropGoldCheckPos = GetPosition() + m_MovePos;
	m_DropGoldCheckDir[(int)GlobalValue::PixelCheckDirect::Left] = { m_DropGoldCheckPos.ix() - 10, m_DropGoldCheckPos.iy()};
	m_DropGoldCheckDir[(int)GlobalValue::PixelCheckDirect::Right] = { m_DropGoldCheckPos.ix() + 10, m_DropGoldCheckPos.iy()};
	m_DropGoldCheckDir[(int)GlobalValue::PixelCheckDirect::Top] = { m_DropGoldCheckPos.ix(), m_DropGoldCheckPos.iy() - 2 };
	m_DropGoldCheckDir[(int)GlobalValue::PixelCheckDirect::Bottom] = { m_DropGoldCheckPos.ix(), m_DropGoldCheckPos.iy() + 15 };

	SGameEngineWinImage* FindImage = SGameEngineResMgr::Inst().FindImage(L"Plains.bmp");
	if (nullptr != FindImage)
	{
		for (int i = 0; i < 4; i++)
		{
			m_iDropGoldCheckColor[i] = FindImage->GetPixelColor(m_DropGoldCheckDir[i].ix(), m_DropGoldCheckDir[i].iy());
		}
	}
}

void DropGold::MoveStateCheck()
{
	// 벡터의 값을 더한다.
	m_MovePos = m_DirectPos + m_DropPos;

	// 픽셀체크
	GoldPixelCheck();

	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		if (RGB(0, 0, 0) == m_iDropGoldCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_MovePos.x = 0.0f;
		}
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		if (RGB(0, 0, 0) == m_iDropGoldCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_MovePos.x = 0.0f;
		}
	}

	if (RGB(0, 0, 0) == m_iDropGoldCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] ||
		RGB(255, 0, 0) == m_iDropGoldCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
	{
		// 바닥에 닿으면서 충돌체 On
		m_DropGoldCol->On();

		m_DirectPos = FLOAT4::ZERO;
		m_DirectPos = FLOAT4::ZERO;
		m_DropPower = FLOAT4::ZERO;
		m_DropGravityPower = FLOAT4::ZERO;
		m_MovePos.y = 0.0f;

		m_DropGoldFSM.ChangeState(L"DropGold_TimeDelay");
	}
}

void DropGold::SetMoveDirect()
{
	FLOAT4 MyPosBaseOnPlayer = GetPosition() - GlobalValue::MainPlayer->GetPosition();
	MyPosBaseOnPlayer.Normalize();
	if (0.0f > MyPosBaseOnPlayer.x)
	{
		m_MoveDir = GlobalValue::BasicMoveType::Left;
	}
	else if (0.0f <= MyPosBaseOnPlayer.x)
	{
		m_MoveDir = GlobalValue::BasicMoveType::Right;
	}
}

void DropGold::TimeAlphaInStart()
{
	m_AniDropGold->SetAlpha(100);
}

void DropGold::TimeAlphaInStay()
{

}

void DropGold::TimeAlphaInEnd()
{
	m_AniDropGold->SetAlpha(255);
}

void DropGold::TimeAlphaOutStart()
{
	m_AniDropGold->SetAlpha(255);
}

void DropGold::TimeAlphaOutStay()
{

}

void DropGold::TimeAlphaOutEnd()
{
	m_AniDropGold->SetAlpha(100);
}

void DropGold::DebugRender()
{
	FLOAT4 DropGoldPixelLeft = m_DropGoldCheckDir[0] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), DropGoldPixelLeft.ix() - 2, DropGoldPixelLeft.iy() - 2, DropGoldPixelLeft.ix() + 2, DropGoldPixelLeft.iy() + 2);

	FLOAT4 DropGoldPixelRight = m_DropGoldCheckDir[1] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), DropGoldPixelRight.ix() - 2, DropGoldPixelRight.iy() - 2, DropGoldPixelRight.ix() + 2, DropGoldPixelRight.iy() + 2);

	FLOAT4 DropGoldPixelTop = m_DropGoldCheckDir[2] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), DropGoldPixelTop.ix() - 2, DropGoldPixelTop.iy() - 2, DropGoldPixelTop.ix() + 2, DropGoldPixelTop.iy() + 2);

	FLOAT4 DropGoldPixelBot = m_DropGoldCheckDir[3] - GetScene()->GetCamPos();
	Rectangle(SGameEngineWindow::GetBackBufferDC(), DropGoldPixelBot.ix() - 2, DropGoldPixelBot.iy() - 2, DropGoldPixelBot.ix() + 2, DropGoldPixelBot.iy() + 2);

	Col2DData ColData;
	ColData.m_Pos = GetCamPosition() - m_DropGoldCol->GetPivotPos();
	ColData.m_Size = m_DropGoldCol->GetScale();
	RECT ColRect = { ColData.iLeft(), ColData.iTop(), ColData.iRight(), ColData.iBottom() };
	if (true == m_DropGoldCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &ColRect, SGameEngineWindow::GetGreenBrush());
	}
}

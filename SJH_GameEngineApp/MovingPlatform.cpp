#include "MovingPlatform.h"
#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>

// Static Var

// Static Func

// member Var
MovingPlatform::MovingPlatform()
	: m_WindowSize(FLOAT4::ZERO), m_MovingPlatform(nullptr), m_MovingPlatformCol(nullptr), m_MovingPlatformFSM(), m_AniMovingPlatform(nullptr),
	m_LerpMoveTime(0.0f), m_fLerpSpeed(0.0f), m_MoveStartPos(FLOAT4::ZERO), m_MoveTargetPos(FLOAT4::ZERO), m_MovePos(FLOAT4::ZERO),
	m_CurDirect(GlobalValue::BasicMoveType::None),
	m_PlayerMovePos(FLOAT4::ZERO)
{

}

MovingPlatform::~MovingPlatform()
{

}

// member Func
void MovingPlatform::Start()
{
	// 현재 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 충돌체 생성
	m_MovingPlatformCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::MovingPlatform);
	m_MovingPlatformCol->SetScale({ 100, 20 });
	m_MovingPlatformCol->SetPivotPos({ 0.f, -5.f });
	m_MovingPlatformCol->AddStartEvent(this, &MovingPlatform::CollisionStart);
	m_MovingPlatformCol->AddStayEvent(this, &MovingPlatform::CollisionStay);
	m_MovingPlatformCol->AddEndEvent(this, &MovingPlatform::CollisionEnd);

	// 애니메이션(초기 Off)
	m_AniMovingPlatform = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniMovingPlatform->SetRenderScale({ 96, 32 });
	m_AniMovingPlatform->CreateAnimation(L"MOVINGIDLE", L"Moving_Platform.bmp", 0, 0);
	m_AniMovingPlatform->ChangeAnimation(L"MOVINGIDLE");
	m_AniMovingPlatform->Off();

	// FSM 설정
	m_MovingPlatformFSM.CreateState(L"MOVINGFIND", this, &MovingPlatform::PlatformFindStay, &MovingPlatform::PlatformFindStart, &MovingPlatform::PlatformFindEnd);
	m_MovingPlatformFSM.CreateState(L"MOVINGIDLE", this, &MovingPlatform::PlatformIdleStay, &MovingPlatform::PlatformIdleStart, &MovingPlatform::PlatformIdleEnd);
	m_MovingPlatformFSM.CreateState(L"MOVINGMOVE", this, &MovingPlatform::PlatformMoveStay, &MovingPlatform::PlatformMoveStart, &MovingPlatform::PlatformMoveEnd);
	m_MovingPlatformFSM.ChangeState(L"MOVINGFIND");
}

void MovingPlatform::Update()
{
	m_MovingPlatformFSM.Update();
}

// 러프 속도 설정
float MovingPlatform::GetLerpSpeed()
{
	return m_fLerpSpeed;
}

void MovingPlatform::SetLerpSpeed(float _Speed)
{
	m_fLerpSpeed = _Speed;
}

// 러프 시작위치 설정
FLOAT4 MovingPlatform::GetMoveStartPos()
{
	return m_MoveStartPos;
}

void MovingPlatform::SetMoveStartPos(FLOAT4 _StartPos)
{
	m_MoveStartPos = _StartPos;
}

// 러프 목표위치 설정
FLOAT4 MovingPlatform::GetMoveTargetPos()
{
	return m_MoveTargetPos;
}

void MovingPlatform::SetMoveTargetPos(FLOAT4 _TargetPos)
{
	m_MoveTargetPos = _TargetPos;
}

// 현재 러프 진행방향
GlobalValue::BasicMoveType MovingPlatform::GetCurLerpDirect()
{
	return m_CurDirect;
}

void MovingPlatform::SetCurLerpDirect(FLOAT4 _StartPos, FLOAT4 _EndPos)
{
	// 값이 있을경우만 설정
	if (_StartPos != FLOAT4::ZERO && _EndPos != FLOAT4::ZERO)
	{
		// 단위벡터를 구함
		FLOAT4 SettingPos = _EndPos - _StartPos;
		SettingPos.Normalize();

		// 현재방향이 왼쪽 or 오른쪽이면 x값을 비교
		if (m_CurDirect == GlobalValue::BasicMoveType::Left || m_CurDirect == GlobalValue::BasicMoveType::Right)
		{
			if (0.0f > SettingPos.x)
			{
				m_CurDirect = GlobalValue::BasicMoveType::Left;
			}
			else
			{
				m_CurDirect = GlobalValue::BasicMoveType::Right;
			}
		}
		// 현재방향이 위쪽 or 아래쪽이면 y값을 비교
		else if (m_CurDirect == GlobalValue::BasicMoveType::Up || m_CurDirect == GlobalValue::BasicMoveType::Down)
		{
			if (0.0f > SettingPos.y)
			{
				m_CurDirect = GlobalValue::BasicMoveType::Up;
			}
			else
			{
				m_CurDirect = GlobalValue::BasicMoveType::Down;
			}
		}
		else if (m_CurDirect == GlobalValue::BasicMoveType::None)
		{
			if (SettingPos.x != 0.0f)
			{
				if (0.0f > SettingPos.x)
				{
					m_CurDirect = GlobalValue::BasicMoveType::Left;
				}
				else
				{
					m_CurDirect = GlobalValue::BasicMoveType::Right;
				}
			}
			else
			{
				if (0.0f > SettingPos.y)
				{
					m_CurDirect = GlobalValue::BasicMoveType::Up;
				}
				else
				{
					m_CurDirect = GlobalValue::BasicMoveType::Down;
				}
			}
		}
	}
}

// 디버그 랜더
void MovingPlatform::DebugRender()
{
#ifdef DEBUG
	Col2DData MovingPlatformColData;
	MovingPlatformColData.m_Pos = GetCamPosition() - m_MovingPlatformCol->GetPivotPos();
	MovingPlatformColData.m_Size = m_MovingPlatformCol->GetScale();
	RECT MovingPlatformColRect = { MovingPlatformColData.iLeft(), MovingPlatformColData.iTop(), MovingPlatformColData.iRight(), MovingPlatformColData.iBottom() };
	if (true == m_MovingPlatformCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &MovingPlatformColRect, SGameEngineWindow::GetGreenBrush());
	}
#endif
}
#include "SavePoint.h"
#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>

#include "ShovelKnight.h"

// Static Var
SavePointInfo SavePoint::m_LastSaveData;

// Static Func
SavePointInfo SavePoint::GetLastSaveData()
{
	return m_LastSaveData;
}

// member Var
SavePoint::SavePoint()
    : m_WindowSize(FLOAT4::ZERO),
    m_SavePoint(nullptr), m_SavePointCol(nullptr), m_AniSavePoint(nullptr), m_SavePointFSM(),
	m_iPlayerAttack(0), m_bFirstCollision(false),
	m_MySaveData()
{

}

SavePoint::~SavePoint()
{

}

// member Func
void SavePoint::Start()
{
	// 현재 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 충돌체 생성
	m_SavePointCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::UI);
	m_SavePointCol->SetScale({ 70, 50 });
	m_SavePointCol->SetPivotPos({ 0.f, 20.f });
	m_SavePointCol->AddStartEvent(this, &SavePoint::CollisionStart);
	m_SavePointCol->AddStayEvent(this, &SavePoint::CollisionStay);
	m_SavePointCol->AddEndEvent(this, &SavePoint::CollisionEnd);
	m_SavePointCol->SetCheckData(1);

	// 애니메이션 설정
	m_AniSavePoint = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniSavePoint->SetRenderScale({ 300, 300 });
	m_AniSavePoint->CreateAnimation(L"SavePoint_None", L"SavePoint_TotalState.bmp", 0, 0); // 대기애니메이션
	m_AniSavePoint->CreateAnimation(L"SavePoint_Beshot1", L"SavePoint_TotalState.bmp", 1, 1); // 플레이어 첫번째 공격 애니메이션
	m_AniSavePoint->CreateAnimation(L"SavePoint_Beshot2", L"SavePoint_TotalState.bmp", 2, 2); // 플레이어 두번째 공격 애니메이션
	m_AniSavePoint->CreateAnimation(L"SavePoint_Beshot3", L"SavePoint_TotalState.bmp", 3, 3); // 플레이어 세번째 공격 애니메이션
	m_AniSavePoint->CreateAnimation(L"SavePoint_Beshot4", L"SavePoint_TotalState.bmp", 4, 4); // 플레이어 네번째 공격 애니메이션
	m_AniSavePoint->CreateAnimation(L"SavePoint_Collision", L"SavePoint_TotalState.bmp", 5, 9); // 플레이어와의 충돌애니메이션
	m_AniSavePoint->CreateAnimation(L"SavePoint_Activation", L"SavePoint_TotalState.bmp", 10, 12); // 활성화 애니메이션

	// FSM 설정
	m_SavePointFSM.CreateState(L"SavePointIdle", this, &SavePoint::IDLEStay, &SavePoint::IDLEStart, &SavePoint::IDLEEnd);
	m_SavePointFSM.CreateState(L"SavePointCollision", this, &SavePoint::ColStay, &SavePoint::ColStart, &SavePoint::ColEnd);
	m_SavePointFSM.CreateState(L"SavePointActivation", this, &SavePoint::ActiveStay, &SavePoint::ActiveStart, &SavePoint::ActiveEnd);

	m_SavePointFSM.ChangeState(L"SavePointIdle");
}

void SavePoint::Update()
{
	m_SavePointFSM.Update();
}

void SavePoint::ChangeAnimation()
{
	// 예외처리
	if (BESHOTMAX < m_iPlayerAttack)
	{
		// 어택횟수를 넘어가면 리턴한다.
		return;
	}

	// 초기값 0
	m_iPlayerAttack++;

	// 충돌시에 현재 카운트를 이용하여 애니메이션 변경
	SGameEngineString CountString;
	CountString += L"SavePoint_Beshot";
	CountString += CountString.ToString(m_iPlayerAttack);

	// 만약 마지막 애니메이션이면 이 액터는 사망
	if (BESHOTMAX == m_iPlayerAttack)
	{
		// 마지막 플레이어 공격을 받으면 충돌체를 제거한다.
		m_SavePointCol->Off();
	}
	else // 아니면 애니메이션 변경
	{
		m_AniSavePoint->ChangeAnimation(CountString);
	}
}

void SavePoint::DebugRender()
{
	Col2DData BodyColData;
	BodyColData.m_Pos = GetCamPosition() - m_SavePointCol->GetPivotPos();
	BodyColData.m_Size = m_SavePointCol->GetScale();
	RECT BodyColRect = { BodyColData.iLeft(), BodyColData.iTop(), BodyColData.iRight(), BodyColData.iBottom() };
	if (true == m_SavePointCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &BodyColRect, SGameEngineWindow::GetGreenBrush());
	}
}

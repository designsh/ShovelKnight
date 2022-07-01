#include "StoneObject.h"
#include "ShovelKnight.h"
#include <SGameEngineWindow.h>
#include <SGameEngineCollision.h>

#define CHANGE_MAX 4

// Static Var
FLOAT4 StoneObject::m_FragmentMoveDirect;

// Static Func
FLOAT4 StoneObject::GetFragmentDirect()
{
	return m_FragmentMoveDirect;
}

// constructer destructer
StoneObject::StoneObject()
	: m_AniStone(nullptr), m_Stone(nullptr), m_WindowSize(FLOAT4::ZERO), m_StoneCol(nullptr),
	m_iPlayerAttack(0),
	m_Fragment1(nullptr), m_Fragment2(nullptr), m_Fragment3(nullptr), m_Fragment4(nullptr)
{

}

StoneObject::~StoneObject()
{

}

//member Func
void StoneObject::Start()
{
	// 현재 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 충돌체 생성
	m_StoneCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::UI);
	m_StoneCol->SetScale({ 70, 50 });
	m_StoneCol->AddStartEvent(this, &StoneObject::CollisionStart);
	m_StoneCol->AddStayEvent(this, &StoneObject::CollisionStay);
	m_StoneCol->AddEndEvent(this, &StoneObject::CollisionEnd);
	m_StoneCol->SetCheckData(0);

	// 이미지 초기위치 Setting
	m_AniStone = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniStone->SetRenderScale({ 300, 300 });

	m_AniStone->CreateAnimation(L"STONEATTACK0", L"Stone_Object.bmp", 0, 0); // 기본생성 이미지
	m_AniStone->CreateAnimation(L"STONEATTACK1", L"Stone_Object.bmp", 1, 1); // 플레이어의 첫번째공격
	m_AniStone->CreateAnimation(L"STONEATTACK2", L"Stone_Object.bmp", 2, 2); // 플레이어의 두번째공격
	m_AniStone->CreateAnimation(L"STONEATTACK3", L"Stone_Object.bmp", 3, 3); // 플레이어의 세번째공격
	m_AniStone->CreateAnimation(L"STONEATTACK4", L"Stone_Object.bmp", 4, 4); // 플레이어의 네번째공격

	m_AniStone->ChangeAnimation(L"STONEATTACK0");

	// 공격횟수 초기화
	m_iPlayerAttack = 0;
}

void StoneObject::Update()
{

}

void StoneObject::ChangeAnimation()
{
	// 초기값 0
	m_iPlayerAttack++;

	// 내 기준 플레이어 위치를 알아낸다.
	ThisPivotPlayerPos();

	// 충돌시에 현재 카운트를 이용하여 애니메이션 변경
	SGameEngineString CountString;
	CountString += L"STONEATTACK";
	CountString += CountString.ToString(m_iPlayerAttack);

	// 만약 마지막 애니메이션이면 이 액터는 사망
	if (CHANGE_MAX == m_iPlayerAttack)
	{
		// 마지막 플레이어 공격을 받으면 자신은 죽는다.
		Death();
	}
	else // 아니면 애니메이션 변경
	{
		m_AniStone->ChangeAnimation(CountString);
	}
}

void StoneObject::ThisPivotPlayerPos()
{
	FLOAT4 Pos = GlobalValue::MainPlayer->GetPosition() - GetPosition();
	if (0.0f > Pos.x) // 음수이면 광물더미보다 플레이어가 왼쪽에 위치
	{
		// 그러므로 파편의 이동방향은 오른쪽
		m_FragmentMoveDirect = FLOAT4::RIGHT;
	}
	else // 양수이면 광물더미가 플레이어보다 왼쪽에 위치
	{
		// 그러므로 파편의 이동방향은 왼쪽
		m_FragmentMoveDirect = FLOAT4::LEFT;
	}
}

void StoneObject::DebugRender()
{
	Col2DData StoneColData;
	StoneColData.m_Pos = GetCamPosition() - m_StoneCol->GetPivotPos();
	StoneColData.m_Size = m_StoneCol->GetScale();
	RECT StoneColRect = { StoneColData.iLeft(), StoneColData.iTop(), StoneColData.iRight(), StoneColData.iBottom() };
	FrameRect(SGameEngineWindow::GetBackBufferDC(), &StoneColRect, SGameEngineWindow::GetGreenBrush());
}

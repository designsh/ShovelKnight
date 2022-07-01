#include "EnchantressBrokenTile.h"
#include <SGameEngineWindow.h>
#include <SGameEngineDebug.h>

// Static Var
int EnchantressBrokenTile::m_BrokenTileTotalCount;

// Static Func

// member Var
EnchantressBrokenTile::EnchantressBrokenTile()
	: m_WindowSize(FLOAT4::ZERO),
	m_BrokenObjectCol(nullptr), m_AniBrokenObject(nullptr), m_BrokenObjectColFSM(),
	m_iMyIndexX(-1), m_iMyIndexY(-1)
{
	// 생성시 카운트를 한개 증가
	m_BrokenTileTotalCount = m_BrokenTileTotalCount + 1;
}

EnchantressBrokenTile::~EnchantressBrokenTile()
{
	// 소멸시 카운트 한개 감소
	if (0 == m_BrokenTileTotalCount)
	{
		// 여기들어오면 안됨
		SGameEngineDebug::AssertMsg(L"if (0 == BrokenTileTotalCount)");
	}
	else
	{
		m_BrokenTileTotalCount = m_BrokenTileTotalCount - 1;
	}
}

// member Func
void EnchantressBrokenTile::Start()
{
	// 윈도우크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 애니메이션 생성
	m_AniBrokenObject = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniBrokenObject->SetRenderScale({ 150, 150 });
	m_AniBrokenObject->SetPivotPos({ GetPosition().x + (32.f * 0.5f), GetPosition().y + (32.f * 0.5f) });
	m_AniBrokenObject->CreateAnimation(L"BrokenObject_Idle", L"Enchantress_BlockSmall.bmp", 0, 0);
	m_AniBrokenObject->CreateAnimation(L"BrokenObject_Death", L"Enchantress_BlockSmall.bmp", 1, 3);

	// 충돌체 생성
	m_BrokenObjectCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::UI);
	m_BrokenObjectCol->SetScale({ 32, 32 });
	m_BrokenObjectCol->SetPivotPos({ GetPosition().x - (32.f * 0.5f), GetPosition().y - (32.f * 0.5f) });
	m_BrokenObjectCol->AddStartEvent(this, &EnchantressBrokenTile::CollisionStart);
	m_BrokenObjectCol->AddStayEvent(this, &EnchantressBrokenTile::CollisionStay);
	m_BrokenObjectCol->AddEndEvent(this, &EnchantressBrokenTile::CollisionEnd);

	// FSM 생성
	m_BrokenObjectColFSM.CreateState(L"BrokenObjectIdle", this, &EnchantressBrokenTile::IdleStay, &EnchantressBrokenTile::IdleStart, &EnchantressBrokenTile::IdleEnd);
	m_BrokenObjectColFSM.CreateState(L"BrokenObjectDeath", this, &EnchantressBrokenTile::DieStay, &EnchantressBrokenTile::DieStart, &EnchantressBrokenTile::DieEnd);
	m_BrokenObjectColFSM.ChangeState(L"BrokenObjectIdle");
}

void EnchantressBrokenTile::Update()
{
	m_BrokenObjectColFSM.Update();
}

void EnchantressBrokenTile::DebugRender()
{
	Col2DData ColData;
	ColData.m_Pos = GetCamPosition() - m_BrokenObjectCol->GetPivotPos();
	ColData.m_Size = m_BrokenObjectCol->GetScale();
	RECT ColRect = { ColData.iLeft(), ColData.iTop(), ColData.iRight(), ColData.iBottom() };
	if (true == m_BrokenObjectCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &ColRect, SGameEngineWindow::GetGreenBrush());
	}
}

void EnchantressBrokenTile::SetMyIndex(int _x, int _y)
{
	m_iMyIndexX = _x;
	m_iMyIndexY = _y;
}

FLOAT4 EnchantressBrokenTile::GetMyIndex()
{
	return FLOAT4(static_cast<float>(m_iMyIndexX), static_cast<float>(m_iMyIndexY));
}

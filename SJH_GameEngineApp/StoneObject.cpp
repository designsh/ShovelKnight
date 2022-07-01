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
	// ���� ������ ũ�� ��������
	m_WindowSize = SGameEngineWindow::GetSize();

	// �浹ü ����
	m_StoneCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::UI);
	m_StoneCol->SetScale({ 70, 50 });
	m_StoneCol->AddStartEvent(this, &StoneObject::CollisionStart);
	m_StoneCol->AddStayEvent(this, &StoneObject::CollisionStay);
	m_StoneCol->AddEndEvent(this, &StoneObject::CollisionEnd);
	m_StoneCol->SetCheckData(0);

	// �̹��� �ʱ���ġ Setting
	m_AniStone = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniStone->SetRenderScale({ 300, 300 });

	m_AniStone->CreateAnimation(L"STONEATTACK0", L"Stone_Object.bmp", 0, 0); // �⺻���� �̹���
	m_AniStone->CreateAnimation(L"STONEATTACK1", L"Stone_Object.bmp", 1, 1); // �÷��̾��� ù��°����
	m_AniStone->CreateAnimation(L"STONEATTACK2", L"Stone_Object.bmp", 2, 2); // �÷��̾��� �ι�°����
	m_AniStone->CreateAnimation(L"STONEATTACK3", L"Stone_Object.bmp", 3, 3); // �÷��̾��� ����°����
	m_AniStone->CreateAnimation(L"STONEATTACK4", L"Stone_Object.bmp", 4, 4); // �÷��̾��� �׹�°����

	m_AniStone->ChangeAnimation(L"STONEATTACK0");

	// ����Ƚ�� �ʱ�ȭ
	m_iPlayerAttack = 0;
}

void StoneObject::Update()
{

}

void StoneObject::ChangeAnimation()
{
	// �ʱⰪ 0
	m_iPlayerAttack++;

	// �� ���� �÷��̾� ��ġ�� �˾Ƴ���.
	ThisPivotPlayerPos();

	// �浹�ÿ� ���� ī��Ʈ�� �̿��Ͽ� �ִϸ��̼� ����
	SGameEngineString CountString;
	CountString += L"STONEATTACK";
	CountString += CountString.ToString(m_iPlayerAttack);

	// ���� ������ �ִϸ��̼��̸� �� ���ʹ� ���
	if (CHANGE_MAX == m_iPlayerAttack)
	{
		// ������ �÷��̾� ������ ������ �ڽ��� �״´�.
		Death();
	}
	else // �ƴϸ� �ִϸ��̼� ����
	{
		m_AniStone->ChangeAnimation(CountString);
	}
}

void StoneObject::ThisPivotPlayerPos()
{
	FLOAT4 Pos = GlobalValue::MainPlayer->GetPosition() - GetPosition();
	if (0.0f > Pos.x) // �����̸� �������̺��� �÷��̾ ���ʿ� ��ġ
	{
		// �׷��Ƿ� ������ �̵������� ������
		m_FragmentMoveDirect = FLOAT4::RIGHT;
	}
	else // ����̸� �������̰� �÷��̾�� ���ʿ� ��ġ
	{
		// �׷��Ƿ� ������ �̵������� ����
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

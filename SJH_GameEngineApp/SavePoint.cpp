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
	// ���� ������ ũ�� ��������
	m_WindowSize = SGameEngineWindow::GetSize();

	// �浹ü ����
	m_SavePointCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::UI);
	m_SavePointCol->SetScale({ 70, 50 });
	m_SavePointCol->SetPivotPos({ 0.f, 20.f });
	m_SavePointCol->AddStartEvent(this, &SavePoint::CollisionStart);
	m_SavePointCol->AddStayEvent(this, &SavePoint::CollisionStay);
	m_SavePointCol->AddEndEvent(this, &SavePoint::CollisionEnd);
	m_SavePointCol->SetCheckData(1);

	// �ִϸ��̼� ����
	m_AniSavePoint = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::UI);
	m_AniSavePoint->SetRenderScale({ 300, 300 });
	m_AniSavePoint->CreateAnimation(L"SavePoint_None", L"SavePoint_TotalState.bmp", 0, 0); // ���ִϸ��̼�
	m_AniSavePoint->CreateAnimation(L"SavePoint_Beshot1", L"SavePoint_TotalState.bmp", 1, 1); // �÷��̾� ù��° ���� �ִϸ��̼�
	m_AniSavePoint->CreateAnimation(L"SavePoint_Beshot2", L"SavePoint_TotalState.bmp", 2, 2); // �÷��̾� �ι�° ���� �ִϸ��̼�
	m_AniSavePoint->CreateAnimation(L"SavePoint_Beshot3", L"SavePoint_TotalState.bmp", 3, 3); // �÷��̾� ����° ���� �ִϸ��̼�
	m_AniSavePoint->CreateAnimation(L"SavePoint_Beshot4", L"SavePoint_TotalState.bmp", 4, 4); // �÷��̾� �׹�° ���� �ִϸ��̼�
	m_AniSavePoint->CreateAnimation(L"SavePoint_Collision", L"SavePoint_TotalState.bmp", 5, 9); // �÷��̾���� �浹�ִϸ��̼�
	m_AniSavePoint->CreateAnimation(L"SavePoint_Activation", L"SavePoint_TotalState.bmp", 10, 12); // Ȱ��ȭ �ִϸ��̼�

	// FSM ����
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
	// ����ó��
	if (BESHOTMAX < m_iPlayerAttack)
	{
		// ����Ƚ���� �Ѿ�� �����Ѵ�.
		return;
	}

	// �ʱⰪ 0
	m_iPlayerAttack++;

	// �浹�ÿ� ���� ī��Ʈ�� �̿��Ͽ� �ִϸ��̼� ����
	SGameEngineString CountString;
	CountString += L"SavePoint_Beshot";
	CountString += CountString.ToString(m_iPlayerAttack);

	// ���� ������ �ִϸ��̼��̸� �� ���ʹ� ���
	if (BESHOTMAX == m_iPlayerAttack)
	{
		// ������ �÷��̾� ������ ������ �浹ü�� �����Ѵ�.
		m_SavePointCol->Off();
	}
	else // �ƴϸ� �ִϸ��̼� ����
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

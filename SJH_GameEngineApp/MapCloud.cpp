#include "MapCloud.h"
#include <SGameEngineWindow.h>

#include "GlobalValue.h"
#include "PlayerMaker.h"

// Static Var

// Static Func

// member Var
MapCloud::MapCloud()
	: m_WindowSize(FLOAT4::ZERO), 
	m_Cloud(nullptr),
	m_LerpStartPos(FLOAT4::ZERO), m_LerpEndPos(FLOAT4::ZERO), m_LerpMyPos(FLOAT4::ZERO), m_LerpTime(0.0f),
	m_LerpStartMove(false), m_SceneStart(true)
{

}

MapCloud::~MapCloud()
{

}

// member Func
void MapCloud::Start()
{
	m_WindowSize = SGameEngineWindow::GetSize();

	// ������ ����
	m_Cloud = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::LevelMapCloud);
	m_Cloud->TransCenterSetting(L"LevelMap_Cloud.bmp", { 840, 720 });
}

void MapCloud::Update()
{
	// ���۽� ��ǥ�������� �����Ѵ�.
	if (true == m_LerpStartMove)
	{
		m_LerpTime += SGameEngineTimer::MainTimer.FDeltaTime(0.1f);
		m_LerpMyPos = FLOAT4::Lerp2D(m_LerpStartPos, m_LerpEndPos, m_LerpTime);

		SetPosition(m_LerpMyPos);

		if (1.0f < m_LerpTime)
		{
			// �����Ϸ�� ��� �� �ʱ�ȭ
			m_LerpMyPos = FLOAT4::ZERO;
			m_LerpTime = 0.0f;
			m_SceneStart = false;
			m_LerpStartMove = false;

			// �÷��̾�� ������ �̵��� ������ �����ϼ��ִ�.
			GlobalValue::LevelMapPlayer->SetCloudLerpEnd();
		}
		return;
	}

	if (true == m_SceneStart)
	{
		m_LerpStartPos = GetPosition();
		m_LerpEndPos = { GetPosition().x + 150.f, GetPosition().y };
		m_LerpStartMove = true;
	}
}

void MapCloud::DebugRender()
{

}

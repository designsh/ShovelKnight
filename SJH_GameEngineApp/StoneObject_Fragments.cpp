#include "StoneObject_Fragments.h"
#include "StoneObject.h"
#include <SGameEngineWindow.h>

#include "GlobalValue.h"


// Static Var
// Static Func

// constructer destructer
StoneObject_Fragments::StoneObject_Fragments()
	:m_WindowSize(FLOAT4::ZERO), m_Fragment(nullptr), m_InitPos(FLOAT4::ZERO)
{

}

StoneObject_Fragments::~StoneObject_Fragments()
{

}

//member Func
void StoneObject_Fragments::Start()
{
	// �̹��� Setting
	m_Fragment = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::UI);
	m_Fragment->TransCenterSetting(L"Fragments_Type1.bmp", { 300, 300 });

	// Move Setting
	m_GravityPower = FLOAT4({ 0.f, 1000.f });
	m_GoupPower = FLOAT4({ 0.f, -450.f });
}

void StoneObject_Fragments::Update()
{
	FragmentMove();
}

void StoneObject_Fragments::FragmentMove()
{
	m_GoupPower += m_GravityPower * SGameEngineTimer::FDeltaTime();
	m_GoupPos = m_GoupPower * SGameEngineTimer::FDeltaTime();

	// ����� �������� ���ϰ� ������ �Ʒ������ϴ� ���� ���Ͽ� MovePos�� �����Ѵ�.
	m_MovePos = (StoneObject::GetFragmentDirect() * SGameEngineTimer::FDeltaTime(100.f)) + m_GoupPos;

	MovePosition(m_MovePos);

	FragmentMoveEnd();
}

void StoneObject_Fragments::FragmentMoveEnd()
{
	// ���ؿ� �����ϸ� �ش� ���� ����
	// �ʱ���ġ���� Ŀ����
	if (GetPosition().y >= m_InitPos.y + 300.f)
	{
		Death();
	}
}

void StoneObject_Fragments::FragmentSettingInitPos(FLOAT4 _InitPos)
{
	m_InitPos = _InitPos;
}

void StoneObject_Fragments::DebugRender()
{
#ifdef DEBUG
	//SGameEngineString FragmentPos = L"FragmentPos";
	//FragmentPos += L"X : ";
	//FragmentPos += SGameEngineString::ToString(GetPosition().x);
	//FragmentPos += L"Y : ";
	//FragmentPos += SGameEngineString::ToString(GetPosition().y);
	//TextOut(SGameEngineWindow::GetBackBufferDC(), 1000, 40, FragmentPos.c_str(), lstrlen(FragmentPos.c_str()));
#endif
}

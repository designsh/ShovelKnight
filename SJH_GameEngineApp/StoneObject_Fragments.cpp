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
	// 이미지 Setting
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

	// 방향과 프레임을 곱하고 위에서 아래로향하는 값을 더하여 MovePos를 결정한다.
	m_MovePos = (StoneObject::GetFragmentDirect() * SGameEngineTimer::FDeltaTime(100.f)) + m_GoupPos;

	MovePosition(m_MovePos);

	FragmentMoveEnd();
}

void StoneObject_Fragments::FragmentMoveEnd()
{
	// 기준에 도달하면 해당 액터 죽음
	// 초기위치보다 커지면
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

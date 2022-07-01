#include "EnchantressCollisionMap.h"
#include <SGameEngineWindow.h>

#include "GlobalValue.h"

// Static Var

// Static Func

// member Var
EnchantressCollisionMap::EnchantressCollisionMap()
	: m_WindowSize(FLOAT4::ZERO),
	m_CollistionMap(nullptr)
{

}

EnchantressCollisionMap::~EnchantressCollisionMap()
{

}

// member Func
void EnchantressCollisionMap::Start()
{
	// 키생성
	SGameEngineInput::CreateKey(L"EnchantressCollisionMapOff", 'Z');
	SGameEngineInput::CreateKey(L"EnchantressCollisionMapOn", 'X');

	// 윈도우 크기 가져오기
	m_WindowSize = SGameEngineWindow::GetSize();

	// 0, 0을 맞추는 충돌배경
	m_CollistionMap = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::CollistionMap);
	m_CollistionMap->TransCenterSetting(L"Enchantress_CollistionMap.bmp", { 1280.f, 2880.f });
	m_CollistionMap->SetPivotPos({ 1280.f * 0.5f, 2880.f * 0.5f });

	// 초기값 Off
	m_CollistionMap->Off();
}

void EnchantressCollisionMap::Update()
{
	if (true == SGameEngineInput::IsPress(L"EnchantressCollisionMapOff"))
	{
		m_CollistionMap->Off();
	}

	if (true == SGameEngineInput::IsPress(L"EnchantressCollisionMapOn"))
	{
		m_CollistionMap->On();
	}
}

void EnchantressCollisionMap::DebugRender()
{

}

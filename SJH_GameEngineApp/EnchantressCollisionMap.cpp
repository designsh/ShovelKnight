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
	// Ű����
	SGameEngineInput::CreateKey(L"EnchantressCollisionMapOff", 'Z');
	SGameEngineInput::CreateKey(L"EnchantressCollisionMapOn", 'X');

	// ������ ũ�� ��������
	m_WindowSize = SGameEngineWindow::GetSize();

	// 0, 0�� ���ߴ� �浹���
	m_CollistionMap = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::CollistionMap);
	m_CollistionMap->TransCenterSetting(L"Enchantress_CollistionMap.bmp", { 1280.f, 2880.f });
	m_CollistionMap->SetPivotPos({ 1280.f * 0.5f, 2880.f * 0.5f });

	// �ʱⰪ Off
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

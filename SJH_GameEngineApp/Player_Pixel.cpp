#include "ShovelKnight.h"
#include <SGameEngineResMgr.h>

void ShovelKnight::PlayerPixelCheck()
{
	m_PlayerCheckPos = GetPosition() + m_MovePos;
	m_PlayerCheckDir[(int)GlobalValue::PixelCheckDirect::Left] = { m_PlayerCheckPos.ix() - 10, m_PlayerCheckPos.iy() + 20 };
	m_PlayerCheckDir[(int)GlobalValue::PixelCheckDirect::Right] = { m_PlayerCheckPos.ix() + 10, m_PlayerCheckPos.iy() + 20 };
	m_PlayerCheckDir[(int)GlobalValue::PixelCheckDirect::Top] = { m_PlayerCheckPos.ix(), m_PlayerCheckPos.iy() - 20 };
	m_PlayerCheckDir[(int)GlobalValue::PixelCheckDirect::Bottom] = { m_PlayerCheckPos.ix(), m_PlayerCheckPos.iy() + 35 };
	m_PlayerCheckDir[(int)GlobalValue::PixelCheckDirect::Center] = { m_PlayerCheckPos.ix(), m_PlayerCheckPos.iy() };

	SGameEngineWinImage* FindImage = SGameEngineResMgr::Inst().FindImage(L"Plains.bmp");
	if (nullptr != FindImage)
	{
		for (int i = 0; i < 5; i++)
		{
			m_iPlayerCheckColor[i] = FindImage->GetPixelColor(m_PlayerCheckDir[i].ix(), m_PlayerCheckDir[i].iy());
		}
	}
}
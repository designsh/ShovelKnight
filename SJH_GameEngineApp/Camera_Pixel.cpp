#include "ShovelKnight.h"
#include <SGameEngineResMgr.h>

void ShovelKnight::CamPixelCheck()
{
	m_CamCheckPos = GetScene()->GetCamPos();
	m_CamCheckDir[(int)GlobalValue::PixelCheckDirect::Left] = { m_CamCheckPos.ix() + 10, m_CamCheckPos.iy() + 60 };
	m_CamCheckDir[(int)GlobalValue::PixelCheckDirect::Right] = { m_CamCheckPos.ix() + m_WindowSize.ix() - 10, m_CamCheckPos.iy() + 60 };
	m_CamCheckDir[(int)GlobalValue::PixelCheckDirect::Top] = { m_CamCheckPos.ix() + m_WindowSize.HarfX(), m_CamCheckPos.iy() + 5 };
	m_CamCheckDir[(int)GlobalValue::PixelCheckDirect::Bottom] = { m_CamCheckPos.ix() + m_WindowSize.HarfX(), m_CamCheckPos.iy() + m_WindowSize.iy() - 2 };

	SGameEngineWinImage* FindImage = SGameEngineResMgr::Inst().FindImage(L"Plains.bmp");
	if (nullptr != FindImage)
	{
		for (int i = 0; i < 4; i++)
		{
			m_iCamCheckColor[i] = FindImage->GetPixelColor(m_CamCheckDir[i].ix(), m_CamCheckDir[i].iy());
		}

		// 캠이동 체크
		FLOAT4 CamCheckMovePos = m_DirectPos;
		if (m_LadderPrevMoveDir == GlobalValue::BasicMoveType::Up)
		{
			if (CamCheckMovePos.y != 0.0f)
			{
				// 검은색(벽) 또는 회색(맵밖이면) 또는 -1(화면밖이면)
				if (m_iCamCheckColor[(int)GlobalValue::PixelCheckDirect::Top] == RGB(0, 0, 0) ||
					m_iCamCheckColor[(int)GlobalValue::PixelCheckDirect::Top] == -1)
				{
					CamCheckMovePos.y = 0.0f;
				}
			}
		}
		if (m_LadderPrevMoveDir == GlobalValue::BasicMoveType::Down)
		{
			if (CamCheckMovePos.y != 0.0f)
			{
				if (m_iCamCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] == RGB(0, 0, 0) ||
					m_iCamCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom] == -1)
				{
					CamCheckMovePos.y = 0.0f;
				}
			}
		}
		if (m_MoveDir == GlobalValue::BasicMoveType::Left)
		{
			if (CamCheckMovePos.x != 0.0f)
			{
				if (m_iCamCheckColor[(int)GlobalValue::PixelCheckDirect::Left] == RGB(0, 0, 0) ||
					m_iCamCheckColor[(int)GlobalValue::PixelCheckDirect::Left] == -1)
				{
					CamCheckMovePos.x = 0.0f;
				}
			}
		}
		if (m_MoveDir == GlobalValue::BasicMoveType::Right)
		{
			if (CamCheckMovePos.x != 0.0f)
			{
				if (m_iCamCheckColor[(int)GlobalValue::PixelCheckDirect::Right] == RGB(0, 0, 0) ||
					m_iCamCheckColor[(int)GlobalValue::PixelCheckDirect::Right] == -1)
				{
					CamCheckMovePos.x = 0.0f;
				}
			}
		}

		if (m_MoveDir == GlobalValue::BasicMoveType::Right)
		{
			if (GetPosition().x - GetScene()->GetCamPos().x >= m_WindowSize.fHarfX())
			{
				GetScene()->SetCamMove(CamCheckMovePos);
			}
		}
		else if (m_MoveDir == GlobalValue::BasicMoveType::Left)
		{
			if (GetPosition().x - GetScene()->GetCamPos().x <= m_WindowSize.fHarfX())
			{
				GetScene()->SetCamMove(CamCheckMovePos);
			}
		}
	}
}

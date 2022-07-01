#include "PlayerMaker.h"
#include "SGameCore.h"

void PlayerMaker::PlayerMaker_CreateFSM()
{
	m_PlayerFSM.CreateState(L"PlayerMaker_None", this, &PlayerMaker::IDLEStay, &PlayerMaker::IDLEStart, &PlayerMaker::IDLEEnd);
	m_PlayerFSM.CreateState(L"PlayerMaker_Move", this, &PlayerMaker::MoveStay, &PlayerMaker::MoveStart, &PlayerMaker::MoveEnd);
	m_PlayerFSM.ChangeState(L"PlayerMaker_None");
}

// 대기상태
void PlayerMaker::IDLEStart()
{
	m_AniPlayer->ChangeAnimation(L"PlayerMakerNone");
}

void PlayerMaker::IDLEStay()
{
	// 구름 러프가 완료해야만 이동이가능함
	if (false == m_bPlayerMove)
	{
		return;
	}

	// 여기서 키입력을 받는다.
	// 각 포인트로 러프를 하며 m_MoveTile을 통해 이동가능한 구간인지 판단한다.
	if (true == SGameEngineInput::IsPress(L"MakerUp"))
	{
		int MoveIndex = m_MoveTile->GetTileImageIndex(FLOAT4(m_PlayerPosIndex.ix(), m_PlayerPosIndex.iy() - 1));
		if (-1 != MoveIndex)
		{
			m_LerpStartPos = GetPosition();
			m_LerpEndPos = m_LerpPoint[1];
			m_iPlayerMakerPoint = 1;
			m_LerpStartMove = true;
			m_PlayerFSM.ChangeState(L"PlayerMaker_Move");
		}
		else // 이동 불가 사운드 실행
		{
			m_CantMoveSound = SGameEngineSound::Play(L"LevelMap_Can't_Pass.mp3", false, 0);
		}
	}

	if (true == SGameEngineInput::IsPress(L"MakerDown"))
	{
		int MoveIndex = m_MoveTile->GetTileImageIndex(FLOAT4(m_PlayerPosIndex.ix(), m_PlayerPosIndex.iy() + 1));
		if (-1 != MoveIndex)
		{
			m_LerpStartPos = GetPosition();
			m_LerpEndPos = m_LerpPoint[0];
			m_iPlayerMakerPoint = 0;
			m_LerpStartMove = true;
			m_PlayerFSM.ChangeState(L"PlayerMaker_Move");
		}
		else // 이동 불가 사운드 실행
		{
			m_CantMoveSound = SGameEngineSound::Play(L"LevelMap_Can't_Pass.mp3", false, 0);
		}
	}

	if (true == SGameEngineInput::IsPress(L"MakerLeft"))
	{
		int MoveIndex = m_MoveTile->GetTileImageIndex(FLOAT4(m_PlayerPosIndex.ix() - 1, m_PlayerPosIndex.iy()));
		if (-1 != MoveIndex)
		{
			m_LerpStartPos = GetPosition();
			m_LerpEndPos = m_LerpPoint[1];
			m_iPlayerMakerPoint = 1;
			m_LerpStartMove = true;
			m_PlayerFSM.ChangeState(L"PlayerMaker_Move");
		}
		else // 이동 불가 사운드 실행
		{
			m_CantMoveSound = SGameEngineSound::Play(L"LevelMap_Can't_Pass.mp3", false, 0);
		}
	}

	if (true == SGameEngineInput::IsPress(L"MakerRight"))
	{
		int MoveIndex = m_MoveTile->GetTileImageIndex(FLOAT4(m_PlayerPosIndex.ix() + 1, m_PlayerPosIndex.iy()));
		if (-1 != MoveIndex)
		{
			m_LerpStartPos = GetPosition();
			m_LerpEndPos = m_LerpPoint[2];
			m_iPlayerMakerPoint = 2;
			m_LerpStartMove = true;
			m_PlayerFSM.ChangeState(L"PlayerMaker_Move");
		}
		else // 이동 불가 사운드 실행
		{
			m_CantMoveSound = SGameEngineSound::Play(L"LevelMap_Can't_Pass.mp3", false, 0);
		}
	}

	if (false == m_LerpStartMove)
	{
		if (2 == m_iPlayerMakerPoint)
		{
			if (true == SGameEngineInput::IsPress(L"MakerMapSelect"))
			{
				m_StageSelectSound = SGameEngineSound::Play(L"LevelMap_StageSelect.mp3", false, 0);

				SGameCore::SceneManager.ChangeScene(L"Enchantress");
			}
		}
	}
}

void PlayerMaker::IDLEEnd()
{

}

// 이동상태
void PlayerMaker::MoveStart()
{
	m_AniPlayer->ChangeAnimation(L"PlayerMakerMove");

	// 이동 시작때마다 
	m_MoveStartSound = SGameEngineSound::Play(L"LevelMap_Move.mp3", false, 0);
}

void PlayerMaker::MoveStay()
{
	if (true == m_LerpStartMove)
	{
		m_LerpTime += SGameEngineTimer::MainTimer.FDeltaTime();
		m_LerpPos = FLOAT4::Lerp2D(m_LerpStartPos, m_LerpEndPos, m_LerpTime);

		SetPosition(m_LerpPos);

		if (1.0f < m_LerpTime)
		{
			// 러프완료시 모든 값 초기화
			m_LerpPos = FLOAT4::ZERO;
			m_LerpStartPos = FLOAT4::ZERO;
			m_LerpEndPos = FLOAT4::ZERO;
			m_LerpTime = 0.0f;
			m_LerpStartMove = false;

			// 러프 완료후 상태 변환
			m_PlayerFSM.ChangeState(L"PlayerMaker_None");
		}
	}
}

void PlayerMaker::MoveEnd()
{

}

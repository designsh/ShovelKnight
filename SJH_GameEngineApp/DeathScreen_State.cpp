#include "DeathScreen.h"

// 처음 등장
void DeathScreen::IDLEStart()
{
	m_AniPlayerMarker->ChangeAnimation(L"MakerIdle");

	// 각 오브젝트 이미지 Load
	m_AniSavePoint1->ChangeAnimation(L"SavePoint1Idle");
	m_AniSavePoint2->ChangeAnimation(L"SavePoint2Idle");
	m_AniSavePoint3->ChangeAnimation(L"SavePoint3Idle");
	m_AniSavePoint4->ChangeAnimation(L"SavePoint4Idle");
}

void DeathScreen::IDLEStay()
{
	// 모든 준비가 끝나면 Move상태로 변경한다.
	m_DeathScreenFSM.ChangeState(L"DeathScreen_MakerMove");
}

void DeathScreen::IDLEEnd()
{

}

// 플레이어 아이콘 이동
void DeathScreen::MakerMoveStart()
{
	// 처음등장시 효과음 발동
	m_DeathScreenSound = SGameEngineSound::Play(L"ShovelKnight_Death.mp3", false, 0);

	// 플레이어 사망시 이 상태가 되며
	// 여기서 현재 활성화된 세이브포인트(마지막활성화포인트)의 인덱스를 가져온다.
	m_iLastSavePointIndex = SavePoint::GetLastSaveData().m_iActiveSavePoint;
	if (4 < m_iLastSavePointIndex)
	{
		// 임의의 예외처리(절대 들어오면안됨)
		SGameEngineDebug::AssertMsg(L"if (4 < m_iLastSavePointIndex)");
		return;
	}

	// Maker 위치를 알아낸다.
	// 활성화 Index가 0이면 첫번째 세이브포인트를 가다가 죽었기때문에
	// 첫번째세이브포인트의 위치가 Maker의 초기위치가 된다.
	m_AniPlayerMarker->SetPivotPos(m_LinePos[m_iLastSavePointIndex + 1]);

	// 세이브포인트 활성화 인덱스에따라 각 애니메이션
	// 애니메이션 변경(일단 단순하게 if문으로)
	if (1 == m_iLastSavePointIndex)
	{
		m_AniSavePoint1->ChangeAnimation(L"SavePoint1Active");
	}
	else if (2 == m_iLastSavePointIndex)
	{
		m_AniSavePoint1->ChangeAnimation(L"SavePoint1Active");
		m_AniSavePoint2->ChangeAnimation(L"SavePoint2Active");
	}
	else if (3 == m_iLastSavePointIndex)
	{
		m_AniSavePoint1->ChangeAnimation(L"SavePoint1Active");
		m_AniSavePoint2->ChangeAnimation(L"SavePoint2Active");
		m_AniSavePoint3->ChangeAnimation(L"SavePoint3Active");
	}
	else if (4 == m_iLastSavePointIndex)
	{
		m_AniSavePoint1->ChangeAnimation(L"SavePoint1Active");
		m_AniSavePoint2->ChangeAnimation(L"SavePoint2Active");
		m_AniSavePoint3->ChangeAnimation(L"SavePoint3Active");
		m_AniSavePoint4->ChangeAnimation(L"SavePoint4Active");
	}

	// 플레이어 마커 러프시작으로 애니메이션 변경
	m_AniPlayerMarker->ChangeAnimation(L"MakerMove");
}

void DeathScreen::MakerMoveStay()
{
	// 플레이어 마커러프시작
	m_LerpMoveTime += SGameEngineTimer::MainTimer.FDeltaTime(m_LerpSpeed);
	m_MovePos = FLOAT4::Lerp2D(m_LinePos[m_iLastSavePointIndex + 1], m_LinePos[m_iLastSavePointIndex], m_LerpMoveTime);

	// 나의 위치는 갱신된다.
	m_AniPlayerMarker->SetPivotPos(m_MovePos);

	// 러프 종료시 모든 값을 초기화하며
	// GoldDisplay 상태로 변경
	if (1.0f < m_LerpMoveTime)
	{
		// 러프완료시 모든 값 초기화
		m_MovePos = FLOAT4::ZERO;
		m_LerpMoveTime = 0.0f;
		m_AniPlayerMarker->ChangeAnimation(L"MakerIdle");
		m_DeathScreenFSM.ChangeState(L"DeathScreen_GoldDisplay");
	}
}

void DeathScreen::MakerMoveEnd()
{
	
}

// 잃은 골드 표시
void DeathScreen::GoldDisplayStart()
{
	// 여기서 타임이벤터 생성
	if (0 == m_LostGoldEventer.IsEventSize())
	{
		// TimeEventerEnd로 하여 시간차 Display 생성
		//m_LostGoldEventer.CreateTimeEventEnd(0.2f, this, &DeathScreen::FirstLostGoldInfo);
		//m_LostGoldEventer.CreateTimeEventEnd(0.4f, this, &DeathScreen::SecondLostGoldInfo);
		//m_LostGoldEventer.CreateTimeEventEnd(0.6f, this, &DeathScreen::ThirdLostGoldInfo);
		m_LostGoldEventer.CreateTimeEventEnd(0.3f, this, &DeathScreen::DeathScreenEnd);
	}

	m_LostGoldEventer.Reset();
}

void DeathScreen::GoldDisplayStay()
{
	// 시간차로 잃은 골드량을 화면에 랜더러와 함께 표시한다.
	// 모두 표시하면 일정시간 후 메인플레이어의 정보를 수정한뒤 현재 액터는 Off된다.
	m_LostGoldEventer.Update();
}

void DeathScreen::GoldDisplayEnd()
{

}

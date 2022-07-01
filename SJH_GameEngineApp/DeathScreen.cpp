#include "DeathScreen.h"
#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>

// Static Var
SoundPlayer DeathScreen::m_DeathScreenSound;

// Static Func

// member Var
DeathScreen::DeathScreen()
    :m_WindowSize(FLOAT4::ZERO), m_DeathScreen(nullptr), m_DeathScreenFSM(),
    m_AniPlayerMarker(nullptr),
    m_AniSavePoint1(nullptr), m_AniSavePoint2(nullptr), m_AniSavePoint3(nullptr), m_AniSavePoint4(nullptr),
    m_GoldPouch1(nullptr), m_GoldPouch2(nullptr), m_GoldPouch3(nullptr),
    m_GoldBox1(nullptr), m_GoldBox2(nullptr), m_GoldBox3(nullptr),
    m_RecoveryText(nullptr),
    m_LostGoldEventer(), m_iLastSavePointIndex(0),
    m_LinePos(),
    m_iRecoveryGold1(0), m_iRecoveryGold2(0), m_iRecoveryGold3(0), m_iHoldingGold(0),
    m_MovePos(FLOAT4::ZERO), m_LerpMoveTime(0.0f), m_LerpSpeed(0.5f)
{
    // 현재 스테이지에서는 고정
    m_LinePos[0] = FLOAT4(403.f, 320.f);
    m_LinePos[1] = FLOAT4(500.f, 320.f);
    m_LinePos[2] = FLOAT4(596.f, 320.f);
    m_LinePos[3] = FLOAT4(692.f, 320.f);
    m_LinePos[4] = FLOAT4(788.f, 320.f);
    m_LinePos[5] = FLOAT4(884.f, 320.f);
}

DeathScreen::~DeathScreen()
{

}

// member Func
void DeathScreen::Start()
{
    // 현재 윈도우 크기 가져오기
    m_WindowSize = SGameEngineWindow::GetSize();

    //----------------------------------------------------------------------- 배경 설정 -------------------------------------------------------------------------//
    m_DeathScreen = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::DeathScreen);
    m_DeathScreen->TransCenterSetting(L"DeathScreen.bmp", { 1280.f, 720.f });
    m_DeathScreen->SetPivotPos({ m_WindowSize.x * 0.5f , m_WindowSize.y * 0.5f });
    m_DeathScreen->CamEffectOff();

    //-------------------------------------------------------------------- 애니메이션 설정 --------------------------------------------------------------------//
    // 플레이어 아이콘 애니메이션 
    m_AniPlayerMarker = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::DeathScreen_Maker);
    m_AniPlayerMarker->SetRenderScale({ 300.f, 300.f });
    m_AniPlayerMarker->SetPivotPos(m_LinePos[0]); // 처음만들어질땐 초기위치를 가진다.
    m_AniPlayerMarker->CreateAnimation(L"MakerIdle", L"skMapMarker.bmp", 0, 0);
    m_AniPlayerMarker->CreateAnimation(L"MakerMove", L"skMapMarker.bmp", 0, 1);
    m_AniPlayerMarker->CamEffectOff();

    // 세이브 포인트 애니메이션
    m_AniSavePoint1 = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::DeathScreen_Object);
    m_AniSavePoint1->SetRenderScale({ 300.f, 300.f });
    m_AniSavePoint1->SetPivotPos({495.f, 270.f});
    m_AniSavePoint1->CreateAnimation(L"SavePoint1Idle", L"DeathScreen_SavePoint.bmp", 0, 0);
    m_AniSavePoint1->CreateAnimation(L"SavePoint1Active", L"DeathScreen_SavePoint.bmp", 1, 3);
    m_AniSavePoint1->CamEffectOff();

    m_AniSavePoint2 = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::DeathScreen_Object);
    m_AniSavePoint2->SetRenderScale({ 300.f, 300.f });
    m_AniSavePoint2->SetPivotPos({591.f, 270.f});
    m_AniSavePoint2->CreateAnimation(L"SavePoint2Idle", L"DeathScreen_SavePoint.bmp", 0, 0);
    m_AniSavePoint2->CreateAnimation(L"SavePoint2Active", L"DeathScreen_SavePoint.bmp", 1, 3);
    m_AniSavePoint2->CamEffectOff();

    m_AniSavePoint3 = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::DeathScreen_Object);
    m_AniSavePoint3->SetRenderScale({ 300.f, 300.f });
    m_AniSavePoint3->SetPivotPos({687.f, 270.f});
    m_AniSavePoint3->CreateAnimation(L"SavePoint3Idle", L"DeathScreen_SavePoint.bmp", 0, 0);
    m_AniSavePoint3->CreateAnimation(L"SavePoint3Active", L"DeathScreen_SavePoint.bmp", 1, 3);
    m_AniSavePoint3->CamEffectOff();

    m_AniSavePoint4 = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::DeathScreen_Object);
    m_AniSavePoint4->SetRenderScale({ 300.f, 300.f });
    m_AniSavePoint4->SetPivotPos({783.f, 270.f});
    m_AniSavePoint4->CreateAnimation(L"SavePoint4Idle", L"DeathScreen_SavePoint.bmp", 0, 0);
    m_AniSavePoint4->CreateAnimation(L"SavePoint4Active", L"DeathScreen_SavePoint.bmp", 1, 3);
    m_AniSavePoint4->CamEffectOff();

    //-------------------------------------------------------------------- 기본이미지 설정 --------------------------------------------------------------------//
    // 골드주머니 이미지 랜더러
    m_GoldPouch1 = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::DeathScreen_Object);
    m_GoldPouch1->TransCenterSetting(L"GoldPouch_1.bmp", { 150.f, 150.f });
    m_GoldPouch1->SetPivotPos({ 500.f, 440.f });
    m_GoldPouch1->Off();
    m_GoldPouch1->CamEffectOff();

    m_GoldPouch2 = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::DeathScreen_Object);
    m_GoldPouch2->TransCenterSetting(L"GoldPouch_2.bmp", { 150.f, 150.f });
    m_GoldPouch2->SetPivotPos({ 500.f, 500.f });
    m_GoldPouch2->Off();
    m_GoldPouch2->CamEffectOff();

    m_GoldPouch3 = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::DeathScreen_Object);
    m_GoldPouch3->TransCenterSetting(L"GoldPouch_2.bmp", { 150.f, 150.f });
    m_GoldPouch3->SetPivotPos({ 500.f, 560.f });
    m_GoldPouch3->Off();
    m_GoldPouch3->CamEffectOff();

    // 회복 텍스트 랜더러
    m_RecoveryText = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::DeathScreen_Object);
    m_RecoveryText->TransCenterSetting(L"Recovery_Text.bmp", { 113.f, 58.f });
    m_RecoveryText->SetPivotPos({ 650.f, 400.f });
    m_RecoveryText->Off();
    m_RecoveryText->CamEffectOff();

    // 골드박스 이미지 랜더러
    m_GoldBox1 = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::DeathScreen_Object);
    m_GoldBox1->TransCenterSetting(L"GoldBox.bmp", { 32.f, 32.f });
    m_GoldBox1->SetPivotPos({ 580.f, 460.f });
    m_GoldBox1->Off();
    m_GoldBox1->CamEffectOff();

    m_GoldBox2 = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::DeathScreen_Object);
    m_GoldBox2->TransCenterSetting(L"GoldBox.bmp", { 32.f, 32.f });
    m_GoldBox2->SetPivotPos({ 580.f, 520.f });
    m_GoldBox2->Off();
    m_GoldBox2->CamEffectOff();

    m_GoldBox3 = CreateRenderer<SGameEngineRendererBasic>((int)GlobalValue::RenderGroup::DeathScreen_Object);
    m_GoldBox3->TransCenterSetting(L"GoldBox.bmp", { 32.f, 32.f });
    m_GoldBox3->SetPivotPos({ 580.f, 580.f });
    m_GoldBox3->Off();
    m_GoldBox3->CamEffectOff();

    //----------------------------------------------------------------------- FSM 설정 ----------------------------------------------------------------------//
    m_DeathScreenFSM.CreateState(L"DeathScreen_None", this, &DeathScreen::IDLEStay, &DeathScreen::IDLEStart, &DeathScreen::IDLEEnd);
    m_DeathScreenFSM.CreateState(L"DeathScreen_MakerMove", this, &DeathScreen::MakerMoveStay, &DeathScreen::MakerMoveStart, &DeathScreen::MakerMoveEnd);
    m_DeathScreenFSM.CreateState(L"DeathScreen_GoldDisplay", this, &DeathScreen::GoldDisplayStay, &DeathScreen::GoldDisplayStart, &DeathScreen::GoldDisplayEnd);
    m_DeathScreenFSM.ChangeState(L"DeathScreen_None");

}

void DeathScreen::Update()
{
    // 상태 업데이트
    m_DeathScreenFSM.Update();
}

void DeathScreen::FirstLostGoldInfo()
{
    m_GoldPouch1->On();
    m_GoldBox1->On();
    m_RecoveryText->On();
}

void DeathScreen::SecondLostGoldInfo()
{
    m_GoldPouch2->On();
    m_GoldBox2->On();
}

void DeathScreen::ThirdLostGoldInfo()
{
    m_GoldPouch3->On();
    m_GoldBox3->On();
}

void DeathScreen::DeathScreenEnd()
{
    // 플레이어 위치 조정
    GlobalValue::MainPlayer->SetPosition(SavePoint::GetLastSaveData().m_SavePointPos);

    // 카메라 위치조정
    GetScene()->SetCamPos(SavePoint::GetLastSaveData().m_CamPos);

    // 플레이어 정보 초기화
    GlobalValue::MainPlayer->GetPlayerInfo().ResetPlayerInfo();

    // 내상태를 Idle로 넘긴다.
    m_DeathScreenFSM.ChangeState(L"DeathScreen_None");

    // 나는 Off된다.
    Off();
}

void DeathScreen::DebugRender()
{
#ifdef DEBUG
    FLOAT4 MousePos = SGameEngineWindow::MousePos();
    SGameEngineString MousePosText = L"MousePos";
    MousePosText += L"X : ";
    MousePosText += SGameEngineString::ToString(MousePos.ix());
    MousePosText += L"Y : ";
    MousePosText += SGameEngineString::ToString(MousePos.iy());
    TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 40, MousePosText.c_str(), lstrlen(MousePosText.c_str()));
#endif
}

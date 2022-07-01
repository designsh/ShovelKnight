#include "Enchantress_FinalBoss.h"
#include <SGameEngineWindow.h>

// Static Var
SoundPlayer Enchantress_FinalBoss::m_FinalBossSound;

// Static Func

// member Var
Enchantress_FinalBoss::Enchantress_FinalBoss()
	: m_WindowSize(FLOAT4::ZERO), m_fStateChangeDelay(3.f), m_bAppearMove(false), m_fPatternStartTime(1.0f), m_MoveTargetPos(FLOAT4::ZERO), 
	m_iBossAttackSkillCnt(0), m_iBossDownAttackSkillCnt(0), m_iBossUpAttackSkillCnt(0), m_iTileObjectCnt(140), m_fCamShakeTime(3.f),
	m_bRegenSkilling(false), m_bDeathEffectMove(false), m_bBossFalling(false),
	m_DeathImageChange(), m_DeathImageChangeEnd(), m_DeathCamShake(),
	m_DeathLerpStart(false), m_DeathLerpTime(0.0f), m_DeathMoveStartPos(FLOAT4::ZERO), m_DeathMoveEndPos(FLOAT4::ZERO), m_DeathLerpPos(FLOAT4::ZERO),
	m_DeathCamMoveStartPos(FLOAT4::ZERO), m_DeathCamMoveEndPos(FLOAT4::ZERO), m_DeathCamLerpPos(FLOAT4::ZERO),
	m_bBlinkImage(false), m_fBlinkImageTotalTime(0.5f), m_fBlinkImageOnTime(0.2f), m_fBlinkImageOffTime(0.3f),
	m_DownShotMove(FLOAT4::ZERO), m_UpShotMove(FLOAT4::ZERO),
	m_LerpStartMove(false), m_LerpMovePos(FLOAT4::ZERO), m_LerpStartPos(FLOAT4::ZERO), m_LerpTime(0.0f),
	m_AniEnchantress(nullptr), m_EnchantressFSM(), m_EnchantressInfo(), m_EnchantressCol(nullptr), m_AniShildKnight(nullptr),
	m_LeftBeShotImage(nullptr), m_RightBeShotImage(nullptr),
	m_BrokenTile(nullptr), m_BrokenTileFilePath(), m_BrokenObject(), m_iDataStructXSize(0), m_iYSearchIndex(0),
	m_MoveDir(GlobalValue::BasicMoveType::Right), m_PrevMoveDir(GlobalValue::BasicMoveType::None),
	m_CamMoveDir(GlobalValue::BasicMoveType::Down), m_PrevCamMoveDir(GlobalValue::BasicMoveType::None),
	m_CamCheckPos(FLOAT4::ZERO), m_CamCheckDir(), m_iCamCheckColor(),
	m_CurAniMationName(), m_AniMationName(),
	m_MovePos(FLOAT4::ZERO), m_DirectPos(FLOAT4::ZERO)
{

}

Enchantress_FinalBoss::~Enchantress_FinalBoss()
{
	m_BrokenObject.clear();
}

// member Func
void Enchantress_FinalBoss::Start()
{
	// ������ ũ�⸦ �����´�.
	m_WindowSize = SGameEngineWindow::GetSize();

	// ���� �⺻��������
	m_EnchantressInfo.SetHP(10);
	m_EnchantressInfo.SetMaxHP(10);

	m_EnchantressInfo.SetMoveSpeed(200.f);

	// �浹ü ����
	Create_BossCollision();

	// �ִϸ��̼� ����
	Create_BossAnimation();

	// FSM ����
	Create_BossFSMState();

	// BeShot �̹��� ����
	Create_BossBeShotImage();

	// �ٴ�Ÿ�� ������Ʈ �����ȴ�.
	BrokenObjectSetting();
}

void Enchantress_FinalBoss::Update()
{
	// ��� ������ �� �ʱ�ȭ
	m_MovePos = FLOAT4::ZERO;

	// ���⿡ ���� �ִϸ��̼� ����
	DirCheck();

	// ���� ������Ʈ
	m_EnchantressFSM.Update();

	// �ǰݽ� �̹��� Blink
	BeShotImageBlink();

	// �̵�
	MovePosition(m_MovePos);
}

void Enchantress_FinalBoss::DebugRender()
{
	Col2DData ColData;
	ColData.m_Pos = GetCamPosition() - m_EnchantressCol->GetPivotPos();
	ColData.m_Size = m_EnchantressCol->GetScale();
	RECT ColRect = { ColData.iLeft(), ColData.iTop(), ColData.iRight(), ColData.iBottom() };
	if (true == m_EnchantressCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &ColRect, SGameEngineWindow::GetGreenBrush());
	}

	FLOAT4 Pos = GetPosition();
	SGameEngineString BossPos = L"BossPos";
	BossPos += L"X : ";
	BossPos += SGameEngineString::ToString(Pos.ix());
	BossPos += L"		";
	BossPos += L"Y : ";
	BossPos += SGameEngineString::ToString(Pos.iy());
	TextOut(SGameEngineWindow::GetBackBufferDC(), 0, 100, BossPos.c_str(), lstrlen(BossPos.c_str()));
}

void Enchantress_FinalBoss::ChangeAniMation(const SGameEngineString& _ChangeAniName)
{
	m_CurAniMationName = L"";
	if (m_MoveDir == (GlobalValue::BasicMoveType::Right))
	{
		m_CurAniMationName = L"Right_";
	}
	if (m_MoveDir == (GlobalValue::BasicMoveType::Left))
	{
		m_CurAniMationName = L"Left_";
	}

	m_AniMationName = _ChangeAniName;
	m_CurAniMationName += _ChangeAniName;

	m_AniEnchantress->ChangeAnimationContinue(m_CurAniMationName);
}

void Enchantress_FinalBoss::DirCheck()
{
	if (m_MoveDir != m_PrevMoveDir)
	{
		ChangeAniMation(m_AniMationName);
	}

	m_PrevMoveDir = m_MoveDir;
}

void Enchantress_FinalBoss::DelBrokenObject(int _IndexX, int _IndexY)
{
	m_BrokenObject[_IndexX][_IndexY] = nullptr;
}

void Enchantress_FinalBoss::BrokenTileObjectCheck()
{
	// �ٴ�Ÿ�� ������Ʈ�� �������� ������ �������� ������ FSM ���¸� �����Ѵ�.
	// ������ ������ų �����߿��� üũ�����ʱ� ���� Flag On
	if (m_iTileObjectCnt >= EnchantressBrokenTile::m_BrokenTileTotalCount)
	{
		m_iTileObjectCnt -= 20;
		if (0 > m_iTileObjectCnt)
		{
			m_iTileObjectCnt = 140;
		}

		m_bRegenSkilling = true;
		m_EnchantressFSM.ChangeState(L"Enchantress_BlockRegetSkillCharging");
	}
}

bool Enchantress_FinalBoss::RegenBrokenObject(FLOAT4 _BrokenTileIndex, FLOAT4 _MyIndex)
{
	// Ÿ���ε����� �̿��Ͽ� �����س��� �ڷ��� �����͸� �̿��Ͽ� ��ġ������ �����´�.
	FLOAT4 CurTilePos = m_BrokenTile->GetCurIndexToPos(_BrokenTileIndex);

	// �ش� ��ġ�� ���Ͱ� �����ϸ� ���̰� �����Ѵ�.
	// ���������ʴٸ� �����Ѵ�.
	if (nullptr != m_BrokenObject[_MyIndex.ix()][_MyIndex.iy()])
	{
		m_BrokenObject[_MyIndex.ix()][_MyIndex.iy()]->Death();
		m_BrokenObject[_MyIndex.ix()][_MyIndex.iy()] = nullptr;
	}

	// �ش� ���͸� �����ϰ� �ڷᱸ���� �����Ѵ�.
	EnchantressBrokenTile* NewBrokenObject = GetScene()->CreateActor<EnchantressBrokenTile>();
	NewBrokenObject->SetPosition(CurTilePos);
	NewBrokenObject->SetMyIndex(_MyIndex.ix(), _MyIndex.iy());

	// �ش� ���͵��� �����ϴ� �ڷᱸ���� �����Ѵ�.
	m_BrokenObject[_MyIndex.ix()][_MyIndex.iy()] = NewBrokenObject;
	if (nullptr == m_BrokenObject[_MyIndex.ix()][_MyIndex.iy()])
	{
		// �����ؼ� �־��µ� �߸��Ǿ��� �׷��� ���α׷��� �Ͷ߸���.
		// ����� ������ �ȵ�
		SGameEngineDebug::AssertMsg(L"if (nullptr == m_BrokenObject[_MyIndex.ix()][_MyIndex.iy()])");
		return false;
	}

	return true;
}

void Enchantress_FinalBoss::SetRegenSkillingFlagOff()
{
	m_bRegenSkilling = false;
}

void Enchantress_FinalBoss::BeShotImageBlink()
{
	if (true == m_bBlinkImage)
	{
		m_fBlinkImageOnTime -= SGameEngineTimer::FDeltaTime(5.f);
		if (0.0f >= m_fBlinkImageOnTime)
		{
			DirectCheckImage()->SetCutData(m_AniEnchantress->GetCurFrame());
			DirectCheckImage()->On();

			m_fBlinkImageOnTime = 0.2f;
		}

		m_fBlinkImageOffTime -= SGameEngineTimer::FDeltaTime(5.f);
		if (0.0f >= m_fBlinkImageOffTime)
		{
			DirectCheckImage()->Off();

			m_fBlinkImageOffTime = 0.3f;
		}

		m_fBlinkImageTotalTime -= SGameEngineTimer::FDeltaTime();
		if (0.0f >= m_fBlinkImageTotalTime)
		{
			// Flag ����
			m_bBlinkImage = false;
			m_fBlinkImageTotalTime = 0.5f;

			// �ش� �̹����� Off ��Ų��.
			m_LeftBeShotImage->Off();
			m_RightBeShotImage->Off();
		}
	}
}

SGameEngineRendererBasic* Enchantress_FinalBoss::DirectCheckImage()
{
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		return m_LeftBeShotImage;
	}
	else if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		return m_RightBeShotImage;
	}

	// �̰��� ���� ����
	return nullptr;
}

void Enchantress_FinalBoss::FinalBossImageStart()
{
	m_AniEnchantress->On();
}

void Enchantress_FinalBoss::FinalBossImageStay()
{

}

void Enchantress_FinalBoss::FinalBossImageEnd()
{
	m_AniEnchantress->Off();
}

void Enchantress_FinalBoss::ShildKnightImageStart()
{
	m_AniShildKnight->On();
}

void Enchantress_FinalBoss::ShildKnightImageStay()
{

}

void Enchantress_FinalBoss::ShildKnightImageEnd()
{
	m_AniShildKnight->Off();
}

void Enchantress_FinalBoss::ImageChangeEnd()
{
	// Ÿ���̺��� ���� ����
	m_DeathImageChange.LoopOff();

	// �ִϸ��̼� ����
	m_AniEnchantress->Off();
	m_AniShildKnight->On();
	m_AniShildKnight->ChangeAnimation(L"ShildKnight_MoveStart");

	// ���� ��ȯ
	m_EnchantressFSM.ChangeState(L"Enchantress_DeathEffectMove");
}

bool Enchantress_FinalBoss::GetBossFallingFlag()
{
	return m_bBossFalling;
}

// Camera Shake
void Enchantress_FinalBoss::CamShakeStart()
{

}

void Enchantress_FinalBoss::CamShakeStay()
{
	FLOAT4 PivotPos = FLOAT4::ZERO;
	PivotPos.x = SGameEngineWindow::GetSize().hfloat4().x - GetPosition().x;
	PivotPos.x += rand() % 20 - 10;
	GetScene()->SetCamPos(PivotPos);
}

void Enchantress_FinalBoss::CamShakeEnd()
{
	GetScene()->SetCamPos({SGameEngineWindow::GetSize().hfloat4().x - GetPosition().x, 0.f});
}

void Enchantress_FinalBoss::FinalBoss_InstantKill()
{
	// ü���� ��� 0���� �����
	m_EnchantressInfo.SetHP(0);

	// ���� ����������� ����ȴ�.
	m_EnchantressFSM.ChangeState(L"Enchantress_Death");
}

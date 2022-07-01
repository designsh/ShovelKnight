#include "Enchantress_FinalBoss_AttackSkill.h"
#include <SGameEngineWindow.h>
#include <SGameEngineResMgr.h>

#include "GlobalValue.h"

// Static Var

// Static Func

// member Var
Enchantress_FinalBoss_AttackSkill::Enchantress_FinalBoss_AttackSkill()
	: m_WindowSize(FLOAT4::ZERO),
	m_AniAttackSkill(nullptr), m_AttackSkillCol(nullptr), m_AttackSkillFSM(),
	m_CurAniMationName(), m_AniMationName(),
	m_AttackSkillCheckPos(FLOAT4::ZERO), m_AttackSkillCheckDir(), m_iAttackSkillCheckColor(),
	m_FiringDir(GlobalValue::BasicMoveType::None),
	m_MoveDir(GlobalValue::BasicMoveType::None), m_PrevMoveDir(GlobalValue::BasicMoveType::None),
	m_MovePos(FLOAT4::ZERO), 
	m_DirectPos(FLOAT4::ZERO), 
	m_FirePos(FLOAT4::ZERO)
{

}

Enchantress_FinalBoss_AttackSkill::~Enchantress_FinalBoss_AttackSkill()
{

}

// member Func
void Enchantress_FinalBoss_AttackSkill::Start()
{
	// ������ ũ�⸦ �����´�.
	m_WindowSize = SGameEngineWindow::GetSize();

	// �ִϸ��̼� ����
	m_AniAttackSkill = CreateRenderer<SGameEngineRendererAnimation>((int)GlobalValue::RenderGroup::Monster);
	m_AniAttackSkill->SetRenderScale({ 150, 150 });
	m_AniAttackSkill->CreateAnimation(L"IDLE", L"FinalStage_Boss_AttackSkill.bmp", 0, 0);
	m_AniAttackSkill->CreateAnimation(L"Down_Move", L"FinalStage_Boss_AttackSkill.bmp", 0, 3);                    // �Ʒ��� �߻�
	m_AniAttackSkill->CreateAnimation(L"Down_Right_Move", L"FinalStage_Boss_AttackSkill.bmp", 4, 7);         // �Ʒ����������� �߻�
	m_AniAttackSkill->CreateAnimation(L"Down_Left_Move", L"FinalStage_Boss_AttackSkill.bmp", 8, 11);         // �Ʒ��������� �߻�
	m_AniAttackSkill->CreateAnimation(L"Up_Move", L"FinalStage_Boss_AttackSkill.bmp", 12, 15);                    // ���� �߻�
	m_AniAttackSkill->CreateAnimation(L"Up_Right_Move", L"FinalStage_Boss_AttackSkill.bmp", 16, 19);         // ������������ �߻�
	m_AniAttackSkill->CreateAnimation(L"Up_Left_Move", L"FinalStage_Boss_AttackSkill.bmp", 20, 23);           // ���������� �߻�
	m_AniAttackSkill->CreateAnimation(L"Right_Move", L"FinalStage_Boss_AttackSkill.bmp", 24, 27);               // ���������� �߻�
	m_AniAttackSkill->CreateAnimation(L"Left_Move", L"FinalStage_Boss_AttackSkill.bmp", 28, 31);                 // �������� �߻�
	m_AniAttackSkill->Off();

	// �浹ü ����
	m_AttackSkillCol = CreateCollision<SGameEngineCollision>((int)GlobalValue::CollisionGroup::Monster);
	m_AttackSkillCol->SetScale({ 50, 50 });
	m_AttackSkillCol->AddStartEvent(this, &Enchantress_FinalBoss_AttackSkill::CollisionStart);
	m_AttackSkillCol->AddStayEvent(this, &Enchantress_FinalBoss_AttackSkill::CollisionStay);
	m_AttackSkillCol->AddEndEvent(this, &Enchantress_FinalBoss_AttackSkill::CollisionEnd);
	m_AttackSkillCol->SetCheckData(1);
	m_AttackSkillCol->Off();

	// FSM ����
	m_AttackSkillFSM.CreateState(L"Enchantress_AttackSkill_Find", this, &Enchantress_FinalBoss_AttackSkill::FindStay, &Enchantress_FinalBoss_AttackSkill::FindStart, &Enchantress_FinalBoss_AttackSkill::FindEnd);
	m_AttackSkillFSM.CreateState(L"Enchantress_AttackSkill_Move", this, &Enchantress_FinalBoss_AttackSkill::MoveStay, &Enchantress_FinalBoss_AttackSkill::MoveStart, &Enchantress_FinalBoss_AttackSkill::MoveEnd);
	m_AttackSkillFSM.CreateState(L"Enchantress_AttackSkill_Death", this, &Enchantress_FinalBoss_AttackSkill::DeathStay, &Enchantress_FinalBoss_AttackSkill::DeathStart, &Enchantress_FinalBoss_AttackSkill::DeathEnd);
	m_AttackSkillFSM.ChangeState(L"Enchantress_AttackSkill_Find");
}

void Enchantress_FinalBoss_AttackSkill::Update()
{
	m_MovePos = FLOAT4::ZERO;

	m_AttackSkillFSM.Update();

	MovePosition(m_MovePos);
}

void Enchantress_FinalBoss_AttackSkill::DebugRender()
{
	Col2DData ColData;
	ColData.m_Pos = GetCamPosition() - m_AttackSkillCol->GetPivotPos();
	ColData.m_Size = m_AttackSkillCol->GetScale();
	RECT ColRect = { ColData.iLeft(), ColData.iTop(), ColData.iRight(), ColData.iBottom() };
	if (true == m_AttackSkillCol->IsOn())
	{
		FrameRect(SGameEngineWindow::GetBackBufferDC(), &ColRect, SGameEngineWindow::GetGreenBrush());
	}
}

// �̵����� ����
void Enchantress_FinalBoss_AttackSkill::SetFirstMoveDirect(GlobalValue::BasicMoveType _Direct)
{
	m_MoveDir = _Direct;
}

// Ÿ����ġ�� ���� �߻���� ����
void Enchantress_FinalBoss_AttackSkill::SetFirstFireDirect(GlobalValue::BasicMoveType _Direct)
{
	m_FiringDir = _Direct;
}

void Enchantress_FinalBoss_AttackSkill::ChangeAniMation(const SGameEngineString& _ChangeAniName)
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
	if (m_MoveDir == (GlobalValue::BasicMoveType::Up))
	{
		m_CurAniMationName = L"Up_";
		if (m_FiringDir == GlobalValue::BasicMoveType::Left)
		{
			m_CurAniMationName += L"Left_";
		}
		if (m_FiringDir == GlobalValue::BasicMoveType::Right)
		{
			m_CurAniMationName += L"Right_";
		}
	}
	if (m_MoveDir == (GlobalValue::BasicMoveType::Down))
	{
		m_CurAniMationName = L"Down_";
		if (m_FiringDir == GlobalValue::BasicMoveType::Left)
		{
			m_CurAniMationName += L"Left_";
		}
		if (m_FiringDir == GlobalValue::BasicMoveType::Right)
		{
			m_CurAniMationName += L"Right_";
		}
	}

	m_AniMationName = _ChangeAniName;
	m_CurAniMationName += _ChangeAniName;

	m_AniAttackSkill->ChangeAnimationContinue(m_CurAniMationName);
}

void Enchantress_FinalBoss_AttackSkill::DirCheck()
{
	if (m_MoveDir != m_PrevMoveDir)
	{
		ChangeAniMation(m_AniMationName);
	}

	m_PrevMoveDir = m_MoveDir;
}

void Enchantress_FinalBoss_AttackSkill::MovePos_Check()
{
	m_DirectPos = FLOAT4::ZERO;
	m_FirePos = FLOAT4::ZERO;
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		m_DirectPos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(200.f);
	}
	if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		m_DirectPos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(200.f);
	}
	if (GlobalValue::BasicMoveType::Up == m_MoveDir)
	{
		m_DirectPos += FLOAT4::UP * SGameEngineTimer::FDeltaTime(200.f);
		if (GlobalValue::BasicMoveType::Left == m_FiringDir)
		{
			m_FirePos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(50.f);
		}
		else if (GlobalValue::BasicMoveType::Right == m_FiringDir)
		{
			m_FirePos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(50.f);
		}
	}
	if (GlobalValue::BasicMoveType::Down == m_MoveDir)
	{
		m_DirectPos += FLOAT4::DOWN * SGameEngineTimer::FDeltaTime(200.f);
		if (GlobalValue::BasicMoveType::Left == m_FiringDir)
		{
			m_FirePos += FLOAT4::LEFT * SGameEngineTimer::FDeltaTime(50.f);
		}
		else if (GlobalValue::BasicMoveType::Right == m_FiringDir)
		{
			m_FirePos += FLOAT4::RIGHT * SGameEngineTimer::FDeltaTime(50.f);
		}
	}

	m_MovePos = m_DirectPos + m_FirePos;
}

void Enchantress_FinalBoss_AttackSkill::MoveState_Check()
{
	// �ȼ�üũ�� �Ѵ�.
	AttackSkillPixelCheck();

	// �� �̵����⺰ �ȼ��� �������� �Ǹ� ���� �Ҹ��Ѵ�.
	if (GlobalValue::BasicMoveType::Left == m_MoveDir)
	{
		if (RGB(0, 0, 0) == m_iAttackSkillCheckColor[(int)GlobalValue::PixelCheckDirect::Left])
		{
			m_AttackSkillFSM.ChangeState(L"Enchantress_AttackSkill_Death");
		}
	}
	if (GlobalValue::BasicMoveType::Right == m_MoveDir)
	{
		if (RGB(0, 0, 0) == m_iAttackSkillCheckColor[(int)GlobalValue::PixelCheckDirect::Right])
		{
			m_AttackSkillFSM.ChangeState(L"Enchantress_AttackSkill_Death");
		}
	}
	if (GlobalValue::BasicMoveType::Up == m_MoveDir)
	{
		if (RGB(0, 0, 0) == m_iAttackSkillCheckColor[(int)GlobalValue::PixelCheckDirect::Top])
		{
			m_AttackSkillFSM.ChangeState(L"Enchantress_AttackSkill_Death");
		}
	}
	if (GlobalValue::BasicMoveType::Down == m_MoveDir)
	{
		if (RGB(0, 0, 0) == m_iAttackSkillCheckColor[(int)GlobalValue::PixelCheckDirect::Bottom])
		{
			m_AttackSkillFSM.ChangeState(L"Enchantress_AttackSkill_Death");
		}
	}
}

void Enchantress_FinalBoss_AttackSkill::AttackSkillPixelCheck()
{
	m_AttackSkillCheckPos = GetPosition() + m_MovePos;
	m_AttackSkillCheckDir[(int)GlobalValue::PixelCheckDirect::Left] = { m_AttackSkillCheckPos.ix() - 10, m_AttackSkillCheckPos.iy() + 20 };
	m_AttackSkillCheckDir[(int)GlobalValue::PixelCheckDirect::Right] = { m_AttackSkillCheckPos.ix() + 10, m_AttackSkillCheckPos.iy() + 20 };
	m_AttackSkillCheckDir[(int)GlobalValue::PixelCheckDirect::Top] = { m_AttackSkillCheckPos.ix(), m_AttackSkillCheckPos.iy() - 20 };
	m_AttackSkillCheckDir[(int)GlobalValue::PixelCheckDirect::Bottom] = { m_AttackSkillCheckPos.ix(), m_AttackSkillCheckPos.iy() + 35 };

	SGameEngineWinImage* FindImage = SGameEngineResMgr::Inst().FindImage(L"Enchantress_CollistionMap.bmp");
	if (nullptr != FindImage)
	{
		for (int i = 0; i < 4; i++)
		{
			m_iAttackSkillCheckColor[i] = FindImage->GetPixelColor(m_AttackSkillCheckDir[i].ix(), m_AttackSkillCheckDir[i].iy());
		}
	}
}

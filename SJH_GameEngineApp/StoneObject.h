#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineCollision.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"
#include "DropGold.h"

// �з� :
// �뵵 :
// ���� :
class StoneObject_Fragments;
class StoneObject : public SGameEngineActor
{
private:	// Static Var
	static FLOAT4 m_FragmentMoveDirect;

public:		// Static Func
	static FLOAT4 GetFragmentDirect();

private:	// member Var
	FLOAT4 m_WindowSize;                             // ������������ ũ��
	SGameEngineRendererBasic* m_Stone;               // ������� �̹���������
	SGameEngineCollision* m_StoneCol;                // ���� �浹ü

public:
	SGameEngineRendererAnimation* m_AniStone;        // ����ִϸ��̼�

private:
	StoneObject_Fragments* m_Fragment1;
	StoneObject_Fragments* m_Fragment2;
	StoneObject_Fragments* m_Fragment3;
	StoneObject_Fragments* m_Fragment4;

private:
	int m_iPlayerAttack;                             // �÷��̾�� ���� ��� ���ݹ޾Ҵ��� Count

public:		//constructer destructer
	StoneObject();
	virtual ~StoneObject();

public:		// delete constructer
	StoneObject(const StoneObject& _Other) = delete;
	StoneObject(const StoneObject&& _Other) = delete;

public:		//delete operator
	StoneObject& operator=(const StoneObject& _Other) = delete;
	StoneObject& operator=(const StoneObject&& _Other) = delete;

public:		//member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;

	// �浹ü
public:
	void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
	void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
	void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

public:
	// �÷��̾ ���� ġ�� Ƚ���� ���� �ִϸ��̼� ����
	void ChangeAnimation();

	// ������ �÷��̾ ���ʿ� �ִ��� �����ʿ��ִ��� �Ǵ�
	void ThisPivotPlayerPos();

};


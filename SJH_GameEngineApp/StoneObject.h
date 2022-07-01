#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>
#include <SGameEngineRendererAnimation.h>
#include <SGameEngineCollision.h>
#include <SGameEngineFSM.h>

#include "GlobalValue.h"
#include "DropGold.h"

// 분류 :
// 용도 :
// 설명 :
class StoneObject_Fragments;
class StoneObject : public SGameEngineActor
{
private:	// Static Var
	static FLOAT4 m_FragmentMoveDirect;

public:		// Static Func
	static FLOAT4 GetFragmentDirect();

private:	// member Var
	FLOAT4 m_WindowSize;                             // 현재윈도우의 크기
	SGameEngineRendererBasic* m_Stone;               // 광산더미 이미지랜더러
	SGameEngineCollision* m_StoneCol;                // 광산 충돌체

public:
	SGameEngineRendererAnimation* m_AniStone;        // 광산애니메이션

private:
	StoneObject_Fragments* m_Fragment1;
	StoneObject_Fragments* m_Fragment2;
	StoneObject_Fragments* m_Fragment3;
	StoneObject_Fragments* m_Fragment4;

private:
	int m_iPlayerAttack;                             // 플레이어에게 내가 몇번 공격받았는지 Count

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

	// 충돌체
public:
	void CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other);
	void CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other);
	void CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other);

public:
	// 플레이어가 나를 치는 횟수에 따라 애니메이션 변경
	void ChangeAnimation();

	// 내기준 플레이어가 왼쪽에 있는지 오른쪽에있는지 판단
	void ThisPivotPlayerPos();

};


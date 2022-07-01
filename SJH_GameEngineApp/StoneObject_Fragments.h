#pragma once
#include <SGameEngineActor.h>
#include <SGameEngineRendererBasic.h>

// 분류 :
// 용도 :
// 설명 :
class StoneObject_Fragments : public SGameEngineActor
{
private:	// Static Var
public:		// Static Func
private:	// member Var
	FLOAT4 m_WindowSize;                             // 현재윈도우의 크기
	SGameEngineRendererBasic* m_Fragment;            // 광산더미파편 이미지랜더러

private:
	FLOAT4 m_GravityPower;
	FLOAT4 m_GoupPower;
	FLOAT4 m_GoupPos;
	FLOAT4 m_MovePos;

private:
	FLOAT4 m_InitPos;

public:		//constructer destructer
	StoneObject_Fragments();
	virtual ~StoneObject_Fragments();

public:		// delete constructer
	StoneObject_Fragments(const StoneObject_Fragments& _Other) = delete;
	StoneObject_Fragments(const StoneObject_Fragments&& _Other) = delete;

public:		//delete operator
	StoneObject_Fragments& operator=(const StoneObject_Fragments& _Other) = delete;
	StoneObject_Fragments& operator=(const StoneObject_Fragments&& _Other) = delete;

public:		//member Func
	void Start() override;
	void Update() override;
	void DebugRender() override;

public:
	void FragmentMove();
	void FragmentMoveEnd();
	void FragmentSettingInitPos(FLOAT4 _InitPos);
};


#include "Platter.h"
#include "Chicken.h"
#include "Platter_FragmentsFloor.h"
#include "Platter_FragmentsLid.h"

void Platter::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder())
	{
		// ���� ġ�� �ΰ� �����̹����� �����ϸ�
		Platter_FragmentsFloor* CreateFragmentsFloor = GetScene()->CreateActor<Platter_FragmentsFloor>();
		CreateFragmentsFloor->SetPosition(GetPosition());

		Platter_FragmentsLid* CreateFragmentsLid = GetScene()->CreateActor<Platter_FragmentsLid>();
		CreateFragmentsLid->SetPosition(GetPosition());

		// ġŲ�� �����Ѵ�.
		Chicken* CreateChicken = GetScene()->CreateActor<Chicken>();
		CreateChicken->SetPosition(GetPosition());

		// ġŲ������ ������ ���� �״´�.
		Death();
	}
}

void Platter::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Platter::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

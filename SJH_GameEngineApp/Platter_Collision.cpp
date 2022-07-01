#include "Platter.h"
#include "Chicken.h"
#include "Platter_FragmentsFloor.h"
#include "Platter_FragmentsLid.h"

void Platter::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder())
	{
		// 나를 치면 두개 파편이미지를 생성하며
		Platter_FragmentsFloor* CreateFragmentsFloor = GetScene()->CreateActor<Platter_FragmentsFloor>();
		CreateFragmentsFloor->SetPosition(GetPosition());

		Platter_FragmentsLid* CreateFragmentsLid = GetScene()->CreateActor<Platter_FragmentsLid>();
		CreateFragmentsLid->SetPosition(GetPosition());

		// 치킨을 생성한다.
		Chicken* CreateChicken = GetScene()->CreateActor<Chicken>();
		CreateChicken->SetPosition(GetPosition());

		// 치킨생성이 끝나면 나는 죽는다.
		Death();
	}
}

void Platter::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void Platter::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

#include "StoneObject.h"

#include "ShovelKnight.h"
#include "StoneObject_Fragments.h"
#include "DropGold.h"

void StoneObject::CollisionStart(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{
	// 플레이어 어택모션과 충돌할때만 파편을 생성한다.
	if ((int)GlobalValue::CollisionGroup::PlayerAttack == _Other->GetOrder())
	{
		// 충돌했을때 파편액터를 생성한다.
		m_Fragment1 = GetScene()->CreateActor<StoneObject_Fragments>();
		m_Fragment1->SetPosition({ GetPosition().ix() - 20, GetPosition().iy() });
		m_Fragment1->FragmentSettingInitPos({ GetPosition().ix() - 20, GetPosition().iy() });

		m_Fragment2 = GetScene()->CreateActor<StoneObject_Fragments>();
		m_Fragment2->SetPosition({ GetPosition().ix() - 10, GetPosition().iy() });
		m_Fragment2->FragmentSettingInitPos({ GetPosition().ix() - 10, GetPosition().iy() });

		m_Fragment3 = GetScene()->CreateActor<StoneObject_Fragments>();
		m_Fragment3->SetPosition({ GetPosition().ix(), GetPosition().iy() });
		m_Fragment3->FragmentSettingInitPos({ GetPosition().ix(), GetPosition().iy() });

		m_Fragment4 = GetScene()->CreateActor<StoneObject_Fragments>();
		m_Fragment4->SetPosition({ GetPosition().ix() + 20, GetPosition().iy() });
		m_Fragment4->FragmentSettingInitPos({ GetPosition().ix() + 20, GetPosition().iy() });

		// 충돌했을때 골드도 생긴다
		float DropGoldSpeed1 = static_cast<float>(rand() % 100);
		DropGold* DropGold1 = GetScene()->CreateActor<DropGold>();
		DropGold1->SetDropGold(1);
		DropGold1->SetMoveSpeed(static_cast<float>((rand() % 10)) + DropGoldSpeed1 );
		DropGold1->SetPosition({ GetPosition().x, GetPosition().y - 30.f });

		float DropGoldSpeed2 = static_cast<float>(rand() % 100);
		DropGold* DropGold2 = GetScene()->CreateActor<DropGold>();
		DropGold2->SetDropGold(1);
		DropGold2->SetMoveSpeed(static_cast<float>((rand() % 10)) + DropGoldSpeed2);
		DropGold2->SetPosition({ GetPosition().x, GetPosition().y - 30.f });

		float DropGoldSpeed3 = static_cast<float>(rand() % 100);
		DropGold* DropGold3 = GetScene()->CreateActor<DropGold>();
		DropGold3->SetDropGold(5);
		DropGold3->SetMoveSpeed(static_cast<float>((rand() % 10)) + DropGoldSpeed3);
		DropGold3->SetPosition({ GetPosition().x, GetPosition().y - 30.f });

		float DropGoldSpeed4 = static_cast<float>(rand() % 100);
		DropGold* DropGold4 = GetScene()->CreateActor<DropGold>();
		DropGold4->SetDropGold(20);
		DropGold4->SetMoveSpeed(static_cast<float>((rand() % 10)) + DropGoldSpeed4);
		DropGold4->SetPosition({ GetPosition().x, GetPosition().y - 30.f });

		float DropGoldSpeed5 = static_cast<float>(rand() % 100);
		DropGold* DropGold5 = GetScene()->CreateActor<DropGold>();
		DropGold5->SetDropGold(50);
		DropGold5->SetMoveSpeed(static_cast<float>((rand() % 10)) + DropGoldSpeed5);
		DropGold5->SetPosition({ GetPosition().x, GetPosition().y - 30.f });
	}
}

void StoneObject::CollisionStay(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

void StoneObject::CollisionEnd(SGameEngineCollision* _This, SGameEngineCollision* _Other)
{

}

#include <Pch.hpp>
#include "PhysicsManager.hpp"
#include "../components/Transform.hpp"
#include "../components/Body.hpp"
#include "../components/Shape.hpp"

PhysicsManager::PhysicsManager()
{

}

PhysicsManager::~PhysicsManager()
{

}

void PhysicsManager::Update(float FrameTime)
{
	//integrate bodies
	for (auto gameObject : GameObjects)
	{
		Body* body = static_cast<Body*>(gameObject->GetComponent(TYPE_BODY));
		if (body != nullptr)
		{
			body->Integrate(0.0f, FrameTime);
		}
	}

	//reset prev contacts;
	Reset();

	//player bullet
	for (auto pObj1 = GameObjects.begin(); pObj1 != GameObjects.end(); ++pObj1)
	{
		Body* body1 = static_cast<Body*>((*pObj1)->GetComponent(TYPE_BODY));

		if (body1 == nullptr)
			continue;

		for (auto pObj2 = pObj1 + 1; pObj2 != GameObjects.end(); ++pObj2)
		{
			Body* body2 = static_cast<Body*>((*pObj2)->GetComponent(TYPE_BODY));

			if (body2 == nullptr)
				continue;

			CollisionDetection(
				body1->shape, body1->positionX, body1->positionY,
				body2->shape, body2->positionX, body2->positionY
			);
		}
	}

	//todo if advanced physics, resolve contacts

	for (auto pContact : contacts)
	{
		//CollideEvent collideEvent;
		//
		////pass the collide event to the two contact owners
		//pContact->mBodies[0]->mpOwner->HandleEvent(&collideEvent);
		//pContact->mBodies[1]->mpOwner->HandleEvent(&collideEvent);
	}
}

void PhysicsManager::Reset()
{
	for (auto c : contacts)
		delete c;

	contacts.clear();
}



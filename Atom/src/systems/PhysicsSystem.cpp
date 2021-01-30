/*
* @file		PhysicsBodyComponent.hpp
* @author	Gerald Lee
* @brief	PhysicsBodyComponent
* @date		2021-01-29
*/
#include <Pch.hpp>
#include "PhysicsSystem.hpp"
#include "utils/Log.hpp"
#include "core/AtomEngine.hpp"
#include "core/Types.hpp"
#include "components/AllComponents.hpp"

extern AtomEngine ae;

bool CheckCollisionAABBAABB(ShapeComponent::ShapeType shapeType1, const TransformComponent& transform1,
	ShapeComponent::ShapeType shapeType2, const TransformComponent& transform2, std::list<Contact*>& contacts)
{
	float left1, right1, top1, bottom1;
	float left2, right2, top2, bottom2;

	left1 = transform1.position.x - transform1.scale.x / 2;
	right1 = transform1.position.x + transform1.scale.x / 2;
	top1 = transform1.position.y + transform1.scale.y / 2;
	bottom1 = transform1.position.y - transform1.scale.y / 2;

	left2 = transform2.position.x - transform2.scale.x / 2;
	right2 = transform2.position.x + transform2.scale.x / 2;
	top2 = transform2.position.y + transform2.scale.y / 2;
	bottom2 = transform2.position.y - transform2.scale.y / 2;

	if (left1 > right2 || left2 > right1
		|| top1 < bottom2 || top2 < bottom1)
		return false;

	//Contact* pNewContact = new Contact();
	//pNewContact->bodies[0] = AABBShape1->body;
	//pNewContact->bodies[1] = AABBShape2->body;
	//contacts.push_back(pNewContact);

	return true;
}

void PhysicsSystem::init()
{
	CollisionFunctions[ShapeComponent::ShapeType::AABB][ShapeComponent::ShapeType::AABB] = CheckCollisionAABBAABB;
}

void PhysicsSystem::update()
{
	//reset prev contacts;
	Reset();

	double frameTime = ae.getUptime() / 1000;

	for (auto& itr = mEntities.begin(); itr != mEntities.end(); itr++) {
		EntityID entity1 = *itr;

		//component check
		if (!ae.hasComponent<ShapeComponent>(entity1))
			continue;
		auto& shape1 = ae.getComponent<ShapeComponent>(entity1);
		if (!ae.hasComponent<TransformComponent>(entity1))
			continue;
		auto& transform1 = ae.getComponent<TransformComponent>(entity1);
		if (!ae.hasComponent<PhysicsBodyComponent>(entity1))
			continue;
		auto& body1 = ae.getComponent<PhysicsBodyComponent>(entity1);

		//nested loop without repeat(starts from itr + 1)
		for (auto& itr2 = std::next(itr); itr2 != mEntities.end(); itr2++) {
			EntityID entity2 = *itr2;
			if (entity1 == entity2)
				continue;
			
			//component check
			if (!ae.hasComponent<ShapeComponent>(entity2))
				continue;
			auto& shape2 = ae.getComponent<ShapeComponent>(entity2);
			if (!ae.hasComponent<TransformComponent>(entity2))
				continue;
			auto& transform2 = ae.getComponent<TransformComponent>(entity2);
			if (!ae.hasComponent<PhysicsBodyComponent>(entity2))
				continue;
			auto& body2 = ae.getComponent<PhysicsBodyComponent>(entity2);

			//collision detection based on shapes
			bool collision = CollisionDetection(shape1, transform1, shape2, transform2);

			//update physics bodies
			updatePhysicsBody(body1, transform1, frameTime);
			updatePhysicsBody(body2, transform2, frameTime);
		}
	}
	
	////todo if advanced physics, resolve contacts
	//
	//for (auto pContact : contacts)
	//{
	//	//CollideEvent collideEvent;
	//	//
	//	////pass the collide event to the two contact owners
	//	//pContact->mBodies[0]->mpOwner->HandleEvent(&collideEvent);
	//	//pContact->mBodies[1]->mpOwner->HandleEvent(&collideEvent);
	//}
}

void PhysicsSystem::onEvent(Event& e)
{
}

void PhysicsSystem::Reset()
{
	for (auto c : contacts)
		delete c;

	contacts.clear();
}

bool PhysicsSystem::CollisionDetection(
	const ShapeComponent& shape1, const TransformComponent& transform1,
	const ShapeComponent& shape2, const TransformComponent& transform2)
{
	return CollisionFunctions[shape1.shapeType][shape2.shapeType](
		shape1.shapeType, transform1,
		shape2.shapeType, transform2,
		contacts);
}

void PhysicsSystem::updatePhysicsBody(
	PhysicsBodyComponent& body, 
	TransformComponent& transform, 
	double frameTime)
{
	if (body.staticBody)
		return;
	
	body.positionX = transform.position.x;
	body.positionY = transform.position.y;

	body.prevPositionX = body.positionX;
	body.prevPositionY = body.positionY;

	//compute acceleration
	body.accelerationX = body.totalForceX * body.mass;
	body.accelerationY = (body.totalForceY - GRAVITY) * body.mass;
	body.accelerationY = body.grounded && body.accelerationY < 0 ? 0 : body.accelerationY;

	//Integrate velocity
	body.velocityX = body.accelerationX * frameTime + body.velocityX;
	body.velocityY = body.accelerationY * frameTime + body.velocityY;
	body.velocityY = body.grounded && body.velocityY < 0 ? 0 : body.velocityY;

	body.positionX = body.positionX + body.velocityX * frameTime;
	body.positionY = body.positionY + body.velocityY * frameTime;

	//update transform
	transform.position.x = body.positionX;
	transform.position.y = body.positionY;
}

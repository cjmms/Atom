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

bool CheckCollisionAABBAABB(double frameTime,
	ShapeComponent::ShapeType shapeType1, TransformComponent& transform1, PhysicsBodyComponent& body1, 
	ShapeComponent::ShapeType shapeType2, TransformComponent& transform2, PhysicsBodyComponent& body2, 
	std::list<Contact*>& contacts)
{
	float left1, right1, top1, bottom1;
	float left2, right2, top2, bottom2;

	float halfWidth1 = transform1.scale.x / 2;
	float halfHeight1 = transform1.scale.y / 2;
	left1 = transform1.position.x - halfWidth1;
	right1 = transform1.position.x + halfWidth1;
	top1 = transform1.position.y + halfHeight1;
	bottom1 = transform1.position.y - halfHeight1;

	float halfWidth2 = transform2.scale.x / 2;
	float halfHeight2 = transform2.scale.y / 2;
	left2 = transform2.position.x - halfWidth2;
	right2 = transform2.position.x + halfWidth2;
	top2 = transform2.position.y + halfHeight2;
	bottom2 = transform2.position.y - halfHeight2;

	if (left1 + EPSILON > right2 || left2 + EPSILON > right1
		|| top1 < bottom2 + EPSILON || top2 < bottom1 + EPSILON)
		return false;

	//if collided -> case: dyn-static or dyn-dyn
	if (body2.staticBody)
	{
		//time to collide along asix
		float distX, distY;
		float timeX, timeY;
		
		if(body1.prevPositionX + halfWidth1 > transform2.position.x - halfWidth2
		&& body1.prevPositionX - halfWidth1 < transform2.position.x + halfWidth2)
		{
			//vertical collision only
			// ---
			// | |
			// ---
			//  ---
			//  | |
			//  ---

			//if (body1.velocityY > 0)
			//	transform1.position.y = transform2.position.y - halfHeight1 - halfHeight2;
			//else
			//	transform1.position.y = transform2.position.y + halfHeight1 + halfHeight2;

			distY = abs(transform1.position.y - transform2.position.y) - halfHeight1 - halfHeight2;
			timeY = distY / body1.velocityY;
			transform1.position.y = transform1.position.y + timeY * abs(body1.velocityY);
			transform1.position.x = transform1.position.x + timeY * abs(body2.velocityX);

			//assume sticky collision
			body1.totalForceY = 0;
			body1.accelerationY = 0;
			body1.velocityY = 0;
		}
		else if (body1.prevPositionY + halfHeight1 > transform2.position.y - halfHeight2
			&& body1.prevPositionY - halfHeight1 < transform2.position.y + halfHeight2)
		{
			//horizontal collision only
			// ---
			// | |  ---
			// ---	| |
			//      ---

			distX = abs(transform1.position.x - transform2.position.x) - halfWidth1 - halfWidth2;
			timeX = distX / body1.velocityX;
			transform1.position.x = transform1.position.x + timeX * abs(body1.velocityX);
			transform1.position.y = transform1.position.y + timeX * abs(body2.velocityY);

			//assume sticky collision
			body1.totalForceX = 0;
			body1.accelerationX = 0;
			body1.velocityX = 0;

		}
		else
		{
			//diagonal
			// ---
			// | |
			// ---	
			//     --- 
			//     | | 
			//	   ---

			distY = (transform1.position.y - transform2.position.y - halfHeight1 - halfHeight2) / 2;
			timeY = distY / body1.velocityY;
			distX = (transform1.position.x - transform2.position.x - halfWidth1 - halfWidth2) / 2;
			timeX = distX / body1.velocityX;

			if(timeX < timeY)
			{
				//horizontal reach faster
				//vertical collision
				// ---
				// | |
				// ---
				//   ---
				//   | |
				//   ---

				transform1.position.y = transform1.position.y - timeY * body1.velocityY;
				transform1.position.x = transform1.position.x - timeY * body2.velocityX;

				//assume sticky collision
				body1.totalForceY = 0;
				body1.accelerationY = 0;
				body1.velocityY = 0;
			}
			else
			{
				distX = (transform1.position.x - transform2.position.x - halfWidth1 - halfWidth2) / 2;
				timeX = distX / body1.velocityX;
				transform1.position.x = transform1.position.x - timeX * body1.velocityX;
				transform1.position.y = transform1.position.y - timeX * body2.velocityY;
				
			}
		}
		body1.prevPositionX = transform1.position.x;
		body1.prevPositionX = transform1.position.y;
	}
	else
	{
		//todo handle dyn-dyn collision, rebounce, etc
		//ResolveDynamicCollision();
	}

	//todo send event for phy collision for further gameplay logics (if necessary)
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

	frameTime = ae.getUptime() / 1000;

	for (auto& itr = mEntities.begin(); itr != mEntities.end(); itr++) {
		EntityID entity1 = *itr;

		//component check
		if (!hasRequiredComponents(entity1))
			continue;
		auto& shape1 = ae.getComponent<ShapeComponent>(entity1);
		auto& transform1 = ae.getComponent<TransformComponent>(entity1);
		auto& body1 = ae.getComponent<PhysicsBodyComponent>(entity1);

		//skip static body, !assume it is always static
		if (body1.staticBody)
			continue;

		//update physics bodies
		updatePhysicsBody(body1, transform1, frameTime);
		
		//nested loop
		for (auto& itr2 = mEntities.begin(); itr2 != mEntities.end(); itr2++) {
			EntityID entity2 = *itr2;
			if (entity1 == entity2)
				continue;
			
			//component check
			if (!hasRequiredComponents(entity1))
				continue;
			auto& shape2 = ae.getComponent<ShapeComponent>(entity2);
			auto& transform2 = ae.getComponent<TransformComponent>(entity2);
			auto& body2 = ae.getComponent<PhysicsBodyComponent>(entity2);

			//collision detection based on shapes
			bool collision = CollisionDetection(shape1, transform1, body1, shape2, transform2, body2);
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
	const ShapeComponent& shape1, TransformComponent& transform1, PhysicsBodyComponent& body1,
	const ShapeComponent& shape2, TransformComponent& transform2, PhysicsBodyComponent& body2)
{
	return CollisionFunctions[shape1.shapeType][shape2.shapeType](
		frameTime,
		shape1.shapeType, transform1, body1,
		shape2.shapeType, transform2, body2,
		contacts);
}

bool PhysicsSystem::hasRequiredComponents(EntityID entity)
{
	if (!ae.hasComponent<ShapeComponent>(entity))
		return false;
	if (!ae.hasComponent<TransformComponent>(entity))
		return false;
	if (!ae.hasComponent<PhysicsBodyComponent>(entity))
		return false;
	return true;
}

void PhysicsSystem::updatePhysicsBody(
	PhysicsBodyComponent& body, 
	TransformComponent& transform, 
	double frameTime)
{
	body.prevPositionX = transform.position.x;
	body.prevPositionY = transform.position.y;

	//update acceleration
	body.accelerationX = body.totalForceX / body.mass;
	body.accelerationY = body.totalForceY / body.mass - GRAVITY;
	//body.accelerationY = body.grounded && body.accelerationY < 0 ? 0 : body.accelerationY;

	//update velocity
	body.velocityX = body.accelerationX * frameTime + body.velocityX;
	//body.velocityX = -1;	//test
	//body.velocityY = 1;	//test
	body.velocityY = body.accelerationY * frameTime + body.velocityY;
	//body.velocityY = body.grounded && body.velocityY < 0 ? 0 : body.velocityY;

	//update position
	transform.position.x = transform.position.x + body.velocityX * frameTime;
	transform.position.y = transform.position.y + body.velocityY * frameTime;

}

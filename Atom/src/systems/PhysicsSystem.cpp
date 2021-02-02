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
	ShapeComponent::ShapeType shapeType1, const TransformComponent& transform1, PhysicsBodyComponent& body1, 
	ShapeComponent::ShapeType shapeType2, const TransformComponent& transform2, PhysicsBodyComponent& body2, 
	std::list<Contact*>& contacts)
{
	float left1, right1, top1, bottom1;
	float left2, right2, top2, bottom2;

	float halfWidth1 = transform1.scale.x / 2;
	float halfHeight1 = transform1.scale.y / 2;
	left1 = body1.positionX - halfWidth1;
	right1 = body1.positionX + halfWidth1;
	top1 = body1.positionY + halfHeight1;
	bottom1 = body1.positionY - halfHeight1;

	float halfWidth2 = transform2.scale.x / 2;
	float halfHeight2 = transform2.scale.y / 2;
	left2 = body2.positionX - halfWidth2;
	right2 = body2.positionX + halfWidth2;
	top2 = body2.positionY + halfHeight2;
	bottom2 = body2.positionY - halfHeight2;

	if (left1 > right2 || left2 > right1
		|| top1 < bottom2 || top2 < bottom1)
		return false;

	//if collided -> case: dyn-static or dyn-dyn
	if (body2.staticBody)
	{
		//time to collide along asix
		float distX, distY;
		float timeX, timeY;
		
		if(body1.prevPositionX + halfWidth1 > body2.positionX - halfWidth2
		&& body1.prevPositionX - halfWidth1 < body2.positionX + halfWidth2)
		{
			//vertical collision only
			// ---
			// | |
			// ---
			//  ---
			//  | |
			//  ---

			//if (body1.velocityY > 0)
			//	body1.positionY = body2.positionY - halfHeight1 - halfHeight2;
			//else
			//	body1.positionY = body2.positionY + halfHeight1 + halfHeight2;

			distY = abs(body1.positionY - body2.positionY) - halfHeight1 - halfHeight2;
			timeY = distY / body1.velocityY;
			body1.positionY = body1.positionY + timeY * abs(body1.velocityY);
			body1.positionX = body1.positionX + timeY * abs(body2.velocityX);

			//assume sticky collision
			body1.totalForceY = 0;
			body1.accelerationY = 0;
			body1.velocityY = 0;
		}
		else if (body1.prevPositionY + halfHeight1 > body2.positionY - halfHeight2
			&& body1.prevPositionY - halfHeight1 < body2.positionY + halfHeight2)
		{
			//horizontal collision only
			// ---
			// | |  ---
			// ---	| |
			//      ---

			distX = abs(body1.positionX - body2.positionX) - halfWidth1 - halfWidth2;
			timeX = distX / body1.velocityX;
			body1.positionX = body1.positionX + timeX * abs(body1.velocityX);
			body1.positionY = body1.positionY + timeX * abs(body2.velocityY);

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

			distY = (body1.positionY - body2.positionY - halfHeight1 - halfHeight2) / 2;
			timeY = distY / body1.velocityY;
			distX = (body1.positionX - body2.positionX - halfWidth1 - halfWidth2) / 2;
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

				body1.positionY = body1.positionY - timeY * body1.velocityY;
				body1.positionX = body1.positionX - timeY * body2.velocityX;

				//assume sticky collision
				body1.totalForceY = 0;
				body1.accelerationY = 0;
				body1.velocityY = 0;
			}
			else
			{
				distX = (body1.positionX - body2.positionX - halfWidth1 - halfWidth2) / 2;
				timeX = distX / body1.velocityX;
				body1.positionX = body1.positionX - timeX * body1.velocityX;
				body1.positionY = body1.positionY - timeX * body2.velocityY;
				
			}
		}
		body1.prevPositionX = body1.positionX;
		body1.prevPositionX = body1.positionY;
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
		if (!ae.hasComponent<ShapeComponent>(entity1))
			continue;
		auto& shape1 = ae.getComponent<ShapeComponent>(entity1);
		if (!ae.hasComponent<TransformComponent>(entity1))
			continue;
		auto& transform1 = ae.getComponent<TransformComponent>(entity1);
		if (!ae.hasComponent<PhysicsBodyComponent>(entity1))
			continue;
		auto& body1 = ae.getComponent<PhysicsBodyComponent>(entity1);

		//update physics bodies
		updatePhysicsBody(body1, transform1, frameTime);
		//skip static body
		if (body1.staticBody)
			continue;

		//nested loop
		for (auto& itr2 = mEntities.begin(); itr2 != mEntities.end(); itr2++) {
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
			bool collision = CollisionDetection(shape1, transform1, body1, shape2, transform2, body2);
		}

		//update transform
		transform1.position.x = body1.positionX;
		transform1.position.y = body1.positionY;
		//todo may need to update transform2
		//transform2.position.x = body2.positionX;
		//transform2.position.y = body2.positionY;
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
	const ShapeComponent& shape1, const TransformComponent& transform1, PhysicsBodyComponent& body1,
	const ShapeComponent& shape2, const TransformComponent& transform2, PhysicsBodyComponent& body2)
{
	return CollisionFunctions[shape1.shapeType][shape2.shapeType](
		frameTime,
		shape1.shapeType, transform1, body1,
		shape2.shapeType, transform2, body2,
		contacts);
}

void PhysicsSystem::updatePhysicsBody(
	PhysicsBodyComponent& body, 
	TransformComponent& transform, 
	double frameTime)
{
	body.positionX = transform.position.x;
	body.positionY = transform.position.y;

	body.prevPositionX = body.positionX;
	body.prevPositionY = body.positionY;

	if (body.staticBody)
		return;
	
	//update acceleration
	body.accelerationX = body.totalForceX / body.mass;
	body.accelerationY = body.totalForceY / body.mass - GRAVITY;
	//body.accelerationY = body.grounded && body.accelerationY < 0 ? 0 : body.accelerationY;

	//update velocity
	body.velocityX = body.accelerationX * frameTime + body.velocityX;
	//body.velocityX = 1;
	body.velocityY = body.accelerationY * frameTime + body.velocityY;
	//body.velocityY = body.grounded && body.velocityY < 0 ? 0 : body.velocityY;

	//update position
	body.positionX = body.positionX + body.velocityX * frameTime;
	body.positionY = body.positionY + body.velocityY * frameTime;

}

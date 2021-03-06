/*
* @file		PhysicsBodyComponent.hpp
* @author	Gerald Lee
* @brief	PhysicsBodyComponent
* @date		2021-01-29
*/
#include <Pch.hpp>
#include "PhysicsSystem.hpp"

#include "collisions/AABBCollision.hpp"
#include "utils/Log.hpp"
#include "core/AtomEngine.hpp"
#include "core/Types.hpp"
#include "components/AllComponents.hpp"

extern AtomEngine ae;

extern ChannelID sfxChannelID;

extern string sfxJump;
extern string sfxLand;

void playLandSound(Event& e) {
	ae.play(sfxLand, ChannelGroupTypes::C_SFX, 0.8f);
}



void PhysicsSystem::init()
{
	CollisionFunctions[ShapeComponent::ShapeType::AABB][ShapeComponent::ShapeType::AABB] = CheckCollisionAABBAABB;
}

void PhysicsSystem::update()
{

	//reset prev contacts;
	Reset();

	frameTime = ae.dt;
	if (frameTime == 0)
		return;

	for (auto& itr = mEntities.begin(); itr != mEntities.end(); itr++) {
		EntityID entity1 = *itr;

		//component check
		if (!hasRequiredComponents(entity1))
			continue;

		auto& shape1 = ae.getComponent<ShapeComponent>(entity1);
		auto& transform1 = ae.getComponent<TransformComponent>(entity1);
		auto& body1 = ae.getComponent<PhysicsBodyComponent>(entity1);
		

		bool previousGrounded = body1.grounded;

		//skip static body, !assume it is always static
		if (!body1.staticBody)
		{
			//update physics bodies (f, a, v, p)
			updatePhysicsBody(body1, transform1, frameTime);

			//collision checking loop
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

				if (collision)
				{
					Event e(EventID::E_COLLISION);
					e.setParam<EntityID>(EventID::P_COLLISION_ENTITYID1, entity1);
					e.setParam<EntityID>(EventID::P_COLLISION_ENTITYID2, entity2);
					//todo may need contact position and direction in future
					ae.sendEvent(e);
				}
				
			}
		}

		if (!previousGrounded && body1.grounded) {
			//land event

			//todo change event params(+ character obj) and sendEvent, in audio manager, get comp<character> to determine big/small
			//reference below

			// AUDIO EVENT
			//Event e(EventID::E_AUDIO_PLAY);
			//e.setParam<string>(EventID::P_AUDIO_PLAY_AUDIOLOC,sfxJump);
			//e.setParam<ChannelGroupTypes>(EventID::P_AUDIO_PLAY_CHANNELGROUP,ChannelGroupTypes::C_SFX);
			//e.setParam<float>(EventID::P_AUDIO_PLAY_VOLUMEDB, 0.8f);
			//ae.sendEvent(e);

			Event e(EventID::E_WINDOW_KEY_PRESSED);
			playLandSound(e);
		}
		else if (previousGrounded && !body1.grounded) {
			//jump event

			Event e(EventID::E_WINDOW_KEY_PRESSED);
			playLandSound(e);
		}

		postUpdate(transform1, body1);
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

void PhysicsSystem::postUpdate(TransformComponent& transform, PhysicsBodyComponent& body)
{
	body.prevPositionX = transform.position.x;
	body.prevPositionY = transform.position.y;
	body.prevScaleX = transform.scale.x;
	body.prevScaleY = transform.scale.y;
}

void PhysicsSystem::onEvent(Event& e)
{
}

void PhysicsSystem::Reset()
{
	//todo contact logics
	//for (auto c : contacts)
	//	delete c;
	//
	//contacts.clear();
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

	//assume not grounded, set to true when vertical collision happens
	if (!body.staticBody)
	{
		body.grounded = false;
	}

	//update acceleration
	body.accelerationX = body.totalForceX / frameTime / body.mass ;
	body.accelerationY = body.totalForceY / frameTime / body.mass;
	//body.accelerationY = body.totalForceY / frameTime / body.mass  - GRAVITY;
	//body.accelerationY = body.grounded && body.accelerationY < 0 ? 0 : body.accelerationY;

	//update velocity
	body.velocityX = body.accelerationX * frameTime + body.velocityX;
	//apply friction if grounded, assume grounded if prev. Vy == 0
	//if (body.velocityY == 0)
	if(!body.frictionless)
	{
		//advance phy: friction
		float frictionCoefficient = 0.3;
		float frictionSpeed = frictionCoefficient * frameTime * GRAVITY;
		//reduce speed by friction until speed becomes zero
		int sign = signbit(body.velocityX) ? -1 : 1;
		body.velocityX = abs(body.velocityX) > frictionSpeed ? body.velocityX - frictionSpeed * sign : 0;
		sign = signbit(body.velocityY) ? -1 : 1;
		body.velocityY = abs(body.velocityY) > frictionSpeed ? body.velocityY - frictionSpeed * sign : 0;
	}
	
	//body.velocityX = -1;	//test
	//body.velocityY = 1;	//test
	body.velocityY = body.accelerationY * frameTime + body.velocityY;
	//body.velocityY = body.grounded && body.velocityY < 0 ? 0 : body.velocityY;

	//update position
	transform.position.x = transform.position.x + body.velocityX * frameTime;
	transform.position.y = transform.position.y + body.velocityY * frameTime;

	body.totalForceY = 0;
	body.totalForceX = 0;
}

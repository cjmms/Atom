/*
* @file		PhysicsSystem.hpp
* @author	Gerald Lee
* @brief	Physics Manager + collision 
* @date		2021-01-26
*/

#pragma once
#include <list>
#include <string>
#include <lib\glm\glm\ext\matrix_float4x4.hpp>
#include "../components/ShapeComponent.hpp"
#include "components/TransformComponent.hpp"
#include "core/System.hpp"

//class GameObject;
class Contact;
class PhysicsBodyComponent;
class Transform;

class Contact
{
public:
	Contact()
	{
		bodies[0] = bodies[1] = nullptr;
	}
	~Contact() = default;
public:
	PhysicsBodyComponent* bodies[2];
	//todo maybe Normal, Time
private:
private:
};


bool CheckCollisionAABBAABB(double frameTime,
	ShapeComponent::ShapeType shapeType1, const TransformComponent& transform1, PhysicsBodyComponent& body1,
	ShapeComponent::ShapeType shapeType2, const TransformComponent& transform2, PhysicsBodyComponent& body2,
	std::list<Contact*>& contacts);

class PhysicsSystem : public System
{
public:
	//PhysicsSystem();
	//~PhysicsSystem();
	void init() override;
	void update() override;
	void onEvent(Event& e) override;

	void Reset();

	bool CollisionDetection(
		const ShapeComponent& shape1, TransformComponent& transform1, PhysicsBodyComponent& body1,
		const ShapeComponent& shape2, TransformComponent& transform2, PhysicsBodyComponent& body2
	);

public:
	std::list<Contact*> contacts;

	//2D array of function pointers, used to store the collision functions
	bool (*CollisionFunctions[ShapeComponent::ShapeType::Num][ShapeComponent::ShapeType::Num])(
		double frameTime,
		ShapeComponent::ShapeType shapeType1, TransformComponent& transform1, PhysicsBodyComponent& body1,
		ShapeComponent::ShapeType shapeType2, TransformComponent& transform2, PhysicsBodyComponent& body2,
		std::list<Contact*>& contacts
		);


private:
	bool hasRequiredComponents(EntityID entity);
	void updatePhysicsBody(PhysicsBodyComponent& body, TransformComponent& transform, double frameTime);
	void updatePreviousPosition(TransformComponent& transform, PhysicsBodyComponent& body);
private:
	double frameTime;
	
};
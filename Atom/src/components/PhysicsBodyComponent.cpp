#include <Pch.hpp>
//#include "PhysicsBodyComponent.hpp"
//#include "TransformComponent.hpp"
////#include "../GameObject.h"
//
//PhysicsBodyComponent::PhysicsBodyComponent() //: Component(TYPE_BODY)
//{
//	positionX = 0.0f, positionY = 0.0f;
//	prevPositionX = 0.0f, prevPositionY = 0.0f;
//	velocityX = 0.0f, velocityY = 0.0f;
//	accelerationX = 0.0f, accelerationY = 0.0f;
//	totalForceX = 0.0f, totalForceY = 0.0f;
//	mass = 1.0f, invMass = 1.0f;
//
//	//Transform* transform = static_cast<Transform*>(mpOwner->GetComponent(TYPE_TRANSFORM));
//}
//
//PhysicsBodyComponent::~PhysicsBodyComponent()
//{
//}
//
//void PhysicsBodyComponent::Integrate(bool grounded, float DeltaTime)
//{
//
//	if (transform != nullptr)
//	{
//		positionX = transform->position.x;
//		positionY = transform->position.y;
//	}
//
//	prevPositionX = positionX;
//	prevPositionY = positionY;
//
//	//Compute acceleration
//	//mTotalForceY += Gravity;
//	accelerationX = totalForceX * mass;
//	accelerationY = (totalForceY - 9.81) * mass;
//	accelerationY = grounded && accelerationY < 0 ? 0 : accelerationY;
//	
//	//Integrate velocity
//	velocityX = accelerationX * DeltaTime + velocityX;
//	velocityY = accelerationY * DeltaTime + velocityY;
//	velocityY = grounded && velocityY < 0 ? 0 : velocityY;
//	
//	if (transform != nullptr)
//	{
//		positionX = positionX + velocityX * DeltaTime;
//		positionY = positionY + velocityY * DeltaTime;
//		transform->position.x = positionX;
//		transform->position.y = positionY;
//	}
//
//
//}

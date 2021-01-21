#include <Pch.hpp>
#include "Body.hpp"
#include "Transform.hpp"
//#include "../GameObject.h"
#include "Shape.hpp"

Body::Body(Transform* transform) //: Component(TYPE_BODY)
{
	float mPositionX, mPositionY = 0.0f;
	float mPrevPositionX, mPrevPositionY = 0.0f;
	float mVelocityX, mVelocityY = 0.0f;
	float mAccX, mAccY = 0.0f;
	float mTotalForceX, mTotalForceY = 0.0f;
	float mMass, mInvMass = 1.0f;

	shape = nullptr;

	this->transform = transform;
	//Transform* transform = static_cast<Transform*>(mpOwner->GetComponent(TYPE_TRANSFORM));
}

Body::~Body()
{
	delete shape;
}

void Body::Update()
{

}

void Body::Integrate(float Gravity, float DeltaTime) 
{

	if (transform != nullptr)
	{
		positionX = transform->positionX;
		positionY = transform->positionY;
	}

	prevPositionX = positionX;
	prevPositionY = positionY;

	//Compute acceleration
	//mTotalForceY += Gravity;
	accelerationX = totalForceX * mass;
	accelerationY = totalForceY * mass;

	//Integrate velocity
	velocityX = accelerationX * DeltaTime + velocityX;
	velocityY = accelerationY * DeltaTime + velocityY;

	if (transform != nullptr)
	{
		transform->positionX = positionX;
		transform->positionY = positionY;
	}


}

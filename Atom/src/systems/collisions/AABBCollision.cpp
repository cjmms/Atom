/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
*
* @file		AABBCollision.cpp
* @author	Gerald Lee
* @brief	Collision Detection for Rectangular Components
* @date		2021-02-08
*/

#include <Pch.hpp>
#include "components/ShapeComponent.hpp"
#include "components/TransformComponent.hpp"
#include "components/PhysicsBodyComponent.hpp"
#include "systems/PhysicsSystem.hpp"

void verticalCollision(TransformComponent& transform1, PhysicsBodyComponent& body1, TransformComponent& transform2, PhysicsBodyComponent& body2, float halfHeight1, float halfHeight2)
{
	//transform1.position.y = transform1.position.y + timeX * abs(body1.velocityX);
	if (transform1.position.y > transform2.position.y)
		transform1.position.y = transform2.position.y + halfHeight1 + halfHeight2;
	else
		transform1.position.y = transform2.position.y - halfHeight1 - halfHeight2;

	//below
	if (transform1.position.y < transform2.position.y)
	{
		if (!body2.staticBody)
		{
			//left-right-> abs
			if (abs(body2.velocityX) < abs(body1.velocityX))
			{
				//advance phy: stacking an non-static object
				body2.velocityX = body1.velocityX;
			}

			//upward only-> no need abs
			if (abs(body2.velocityY) < abs(body1.velocityY))
			{
				//by conversation of momentum
				//m1v1 + m2v2 = v3(m1+m2)
				//v3 = (m1v1 + m2v2)/(m1+m2)
				body1.velocityY = (body1.mass * body1.velocityY + body2.mass * body2.velocityY) / (body1.mass + body2.mass);
				body2.velocityY = body1.velocityY;
			}
		}
		else
		{
			if (body1.velocityY > 0)
				body1.velocityY = 0;
		}
	}
	else
	{
		if (!body2.staticBody)
		{
			body1.velocityX = body2.velocityX;
		}

		//assume sticky collision
		body1.totalForceY = 0;
		body1.accelerationY = 0;
		body1.velocityY = 0;
		body1.grounded = true;
	}
}

void horizontalCollision(TransformComponent& transform1, PhysicsBodyComponent& body1, TransformComponent& transform2, PhysicsBodyComponent& body2, float halfWidth1, float halfWidth2)
{
	//transform1.position.x = transform1.position.x + timeX * abs(body1.velocityX);
	if (transform1.position.x > transform2.position.x)
		transform1.position.x = transform2.position.x + halfWidth1 + halfWidth2;
	else
		transform1.position.x = transform2.position.x - halfWidth1 - halfWidth2;

	//pushing logic
	if (!body2.staticBody)
	{
		if (abs(body2.velocityX) < abs(body1.velocityX))
		{
			body1.velocityX = (body1.mass * body1.velocityX + body2.mass * body2.velocityX) / (body1.mass + body2.mass);
			body2.velocityX = body1.velocityX;
		}
	}
	else
	{
		body1.totalForceX = 0;
		body1.accelerationX = 0;
		body1.velocityX = 0;
	}
}

bool CheckCollisionAABBAABB(double frameTime,
	const ShapeType shapeType1, TransformComponent& transform1, PhysicsBodyComponent& body1,
	const ShapeType shapeType2, TransformComponent& transform2, PhysicsBodyComponent& body2,
	std::list<Contact*>& contacts)
{
	float left1, right1, top1, bottom1;
	float left2, right2, top2, bottom2;

	float halfWidth1 = fabs(transform1.scale.x) / 2;
	float halfHeight1 = fabs(transform1.scale.y) / 2;
	left1 = transform1.position.x - halfWidth1;
	right1 = transform1.position.x + halfWidth1;
	top1 = transform1.position.y + halfHeight1;
	bottom1 = transform1.position.y - halfHeight1;

	float halfWidth2 = fabs(transform2.scale.x) / 2;
	float halfHeight2 = fabs(transform2.scale.y) / 2;
	left2 = transform2.position.x - halfWidth2;
	right2 = transform2.position.x + halfWidth2;
	top2 = transform2.position.y + halfHeight2;
	bottom2 = transform2.position.y - halfHeight2;

	if (left1 > right2 + EPSILON || left2 > right1 + EPSILON
		|| top1 + EPSILON < bottom2 || top2 + EPSILON < bottom1)
		return false;

	if (body1.isTrigger || body2.isTrigger)
		return true;

	//time to collide along asix
	float distX, distY;
	float timeX, timeY;

	if (abs(body1.prevPositionX - body2.prevPositionX) + EPSILON < (fabs(body1.prevScaleX) + fabs(body2.prevScaleX)) / 2.0)
	{
		//vertical collision only
		// ---
		// | |
		// ---
		//  ---
		//  | |
		//  ---

		distY = abs(transform1.position.y - transform2.position.y) - halfHeight1 - halfHeight2;
		timeY = body1.velocityY == 0 ? 0 : distY / body1.velocityY;
		verticalCollision(transform1, body1, transform2, body2, halfHeight1, halfHeight2);
	}
	else if (abs(body1.prevPositionY - body2.prevPositionY) + EPSILON < (fabs(body1.prevScaleY) + fabs(body2.prevScaleY)) / 2.0)
	{
		//horizontal collision only
		// ---
		// | |  ---
		// ---	| |
		//      ---

		distX = abs(transform1.position.x - transform2.position.x) - halfWidth1 - halfWidth2;
		timeX = body1.velocityX == 0 ? 0 : distX / body1.velocityX;
		horizontalCollision(transform1, body1, transform2, body2, halfWidth1, halfWidth2);
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

		distY = abs(transform1.position.y - transform2.position.y) - halfHeight1 - halfHeight2;
		timeY = body1.velocityY == 0 ? 0 : distY / body1.velocityY;
		distX = abs(transform1.position.x - transform2.position.x) - halfWidth1 - halfWidth2;
		timeX = body1.velocityX == 0 ? 0 : distX / body1.velocityX;

		if (timeY == 0)
		{
			verticalCollision(transform1, body1, transform2, body2, halfHeight1, halfHeight2);
		}
		else if (timeX == 0)
		{
			horizontalCollision(transform1, body1, transform2, body2, halfWidth1, halfWidth2);
		}
		else if (abs(timeX) < abs(timeY))
		{
			//horizontal reach faster
			//vertical collision
			// ---
			// | |
			// ---
			//   ---
			//   | |
			//   ---

			verticalCollision(transform1, body1, transform2, body2, halfHeight1, halfHeight2);
		}
		else
		{
			horizontalCollision(transform1, body1, transform2, body2, halfWidth1, halfWidth2);
		}
	}

	//todo send event for phy collision for further gameplay logics (if necessary)
	//Contact* pNewContact = new Contact();
	//pNewContact->bodies[0] = AABBShape1->body;
	//pNewContact->bodies[1] = AABBShape2->body;
	//contacts.push_back(pNewContact);

	return true;
}

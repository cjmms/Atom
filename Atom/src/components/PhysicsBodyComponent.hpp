/*
* @file		PhysicsBodyComponent.hpp
* @author	Gerald Lee
* @brief	PhysicsBodyComponent
* @date		2021-01-28
*/

#pragma once
#include <string>
#include <Pch.hpp>
#include <core/Types.hpp>
#include "ShapeComponent.hpp"

class PhysicsBodyComponent
{
public:
	//float positionX = 0.0f, positionY = 0.0f;
	float prevPositionX = 0.0f, prevPositionY = 0.0f;
	float velocityX = 0.0f, velocityY = 0.0f;
	float accelerationX = 0.0f, accelerationY = 0.0f;	//a = F / m
	float totalForceX = 0.0f, totalForceY = 0.0f;
	float mass = 1.0f, invMass = 1.0f;

	bool grounded = false;
	bool staticBody = true;

public:
	PhysicsBodyComponent() {};
	PhysicsBodyComponent(float mass, bool staticBody) : mass(mass), staticBody(staticBody) {};
};

inline void to_json(ordered_json& j, const PhysicsBodyComponent& x) {
	to_json(j["mass"], x.mass);
	to_json(j["staticBody"], x.staticBody);
}

inline void from_json(const ordered_json& j, PhysicsBodyComponent& x) {
	from_json(j["mass"], x.mass);
	from_json(j["staticBody"], x.staticBody);
}

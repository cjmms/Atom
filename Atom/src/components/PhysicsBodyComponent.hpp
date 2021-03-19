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
#include "utils/Serde.hpp"

class PhysicsBodyComponent
{
public:
	//float positionX = 0.0f, positionY = 0.0f;
	float prevPositionX = 0.0f, prevPositionY = 0.0f;
	float prevScaleX = 0.0f, prevScaleY = 0.0f;
	float velocityX = 0.0f, velocityY = 0.0f;
	float accelerationX = 0.0f, accelerationY = 0.0f;	//a = F / m
	float totalForceX = 0.0f, totalForceY = 0.0f;
	float mass = 1.0f, invMass = 1.0f;
	//float direction;	//for aiming, right = 0, ACW

	bool grounded = false;
	bool staticBody = true;
	bool isTrigger = false;
	bool frictionless = false;
	bool gravity = true;

public:
	PhysicsBodyComponent() {};
	PhysicsBodyComponent(float mass, bool staticBody, bool frictionless = false, bool gravity = true) : mass(mass), staticBody(staticBody), frictionless(frictionless), gravity(gravity) {};
};

inline void to_json(ordered_json& j, const PhysicsBodyComponent& x) {
	to_json(j["mass"], x.mass);
	to_json(j["staticBody"], x.staticBody);
	to_json(j["isTrigger"], x.isTrigger);
	to_json(j["frictionless"], x.frictionless);
	to_json(j["gravity"], x.gravity);
}

inline void from_json(const ordered_json& j, PhysicsBodyComponent& x) {
	from_json(j["mass"], x.mass);
	from_json(j["staticBody"], x.staticBody);
	from_json(j["isTrigger"], x.isTrigger);
	from_json(j["frictionless"], x.frictionless);
	from_json(j["gravity"], x.gravity);
}

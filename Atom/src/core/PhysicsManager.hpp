#pragma once
#include <list>
#include <string>
#include <lib\glm\glm\ext\matrix_float4x4.hpp>
#include "../components/Shape.hpp"

//class GameObject;
class Contact;
class Body;
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
	Body* bodies[2];
	//todo maybe Normal, Time
private:
private:
};

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();
	void Update(float FrameTime);

	void Reset();
	bool CollisionDetection(
		Shape* shape1, float pos1X, float pos1Y,
		Shape* shape2, float pos2X, float pos2Y
	);

public:
	std::list<Contact*> contacts;

	//2D array of function pointers, used to store the collision functions
	bool (*CollisionFunctions[Shape::ShapeType::Num][Shape::ShapeType::Num])(
		Shape* shape1, float pos1X, float pos1Y,
		Shape* shape2, float pos2X, float pos2Y,
		std::list<Contact*>& contacts
		);
private:

private:
	
};
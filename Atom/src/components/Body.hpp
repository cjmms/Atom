#pragma once
#include <string>

//#include "Component.h"
//#include "glew.h"
#include "Shape.hpp"

class Transform;

class Body// : public Component
{
public:
	Body(Transform* transform);
	~Body();

	void Update();
	void Integrate(bool grounded, float DeltaTime);

public:
	float positionX, positionY;
	float prevPositionX, prevPositionY;
	float velocityX, velocityY;
	float accelerationX, accelerationY;	//a = F / m
	float totalForceX, totalForceY;
	float mass, invMass;

	Shape* shape;
	Shape::ShapeType shapeType;
private:
private:
	Transform* transform;

};
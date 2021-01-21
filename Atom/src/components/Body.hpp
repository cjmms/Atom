#pragma once
#include <string>

//#include "Component.h"
//#include "glew.h"

class Shape;
class Transform;

class Body// : public Component
{
public:
	Body(Transform* transform);
	~Body();

	void Update();
	virtual void Serialize(std::ifstream& InputStream);
	void Integrate(float Gravity, float DeltaTime);

public:
	float positionX, positionY;
	float prevPositionX, prevPositionY;
	float velocityX, velocityY;
	float accelerationX, accelerationY;	//a = F / m
	float totalForceX, totalForceY;
	float mass, invMass;

	Shape* shape;
private:
private:
	Transform* transform;

};
#pragma once
#include <list>
#include <string>
#include <lib\glm\glm\ext\matrix_float4x4.hpp>

//class GameObject;
class Shape;
class Contact;
class Body;
class Transform;

class Transform// : public Component
{
public:
	Transform();
	~Transform();

	void Update();
	float* GetTransform();
	//virtual void Serialize(std::ifstream& InputStream);

public:
	float positionX, positionY, positionZ;
	float scaleX, scaleY;
	float angle;

private:
	glm::mat4 Rotate(const int i, const float theta);
	glm::mat4 Scale(const float x, const float y, const float z);
	glm::mat4 Translate(const float x, const float y, const float z);
private:
	glm::mat4 transformationMatrix;

};

//todo dependencies(Shape, Contact) are temporary placed here. Re-organize classes later 
class Shape
{
public:
	enum ShapeType
	{
		AABB,
		NUM,
	};

	Shape(ShapeType Type, Body* body, Transform* transform);
	virtual ~Shape();

public:
	Body* body;
	Transform* transform;
	ShapeType type;
};

class Body
{
public:
	Body();
	~Body();

	void Update();
	//virtual void Serialize();
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

};

class ShapeAABB : public Shape
{
public:
	ShapeAABB(Body* body, Transform* transform);
	//~ShapeAABB() = default;
	bool PointCollisionDetection(float PointX, float PointY);
public:
	float left, right, top, bottom;
private:
private:
};

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
	void Update();

	void Reset();
	bool CollisionDetection(
		Shape* pShape1, float Pos1X, float Pos1Y,
		Shape* pShape2, float Pos2X, float Pos2Y
	);

public:
	std::list<Contact*> mContacts;

	//2D array of function pointers, used to store the collision functions
	bool (*CollisionFunctions[Shape::ShapeType::NUM][Shape::ShapeType::NUM])(
		Shape* pShape1, float Pos1X, float Pos1Y,
		Shape* pShape2, float Pos2X, float Pos2Y,
		std::list<Contact*>& mContacts
		);
private:

private:
	
};
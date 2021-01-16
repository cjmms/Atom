#pragma once
#include <list>

class GameObject;
class Shape;
class Contact;
class Body;
class Transform;

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
	int vertexNum;
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
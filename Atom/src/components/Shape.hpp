#pragma once

class Body;
class Transform;

class Shape
{
public:
	enum ShapeType
	{
		//Circle,
		AABB,
		//Pentagon,
		Num
	};

	Shape(ShapeType Type, Body* body, Transform* transform);
	virtual ~Shape();

	virtual bool PointCollisionDetection(float PointX, float PointY) = 0;

public:
	Body* body;
	Transform* transform;
	ShapeType type;
protected:

};

class ShapeAABB : public Shape
{
public:
	ShapeAABB(Body* body, Transform* transform);
	~ShapeAABB() {};
	bool PointCollisionDetection(float PointX, float PointY);
public:
	float left, right, top, bottom;
private:
private:
};

#include <Pch.hpp>
#include "Shape.hpp" 
#include "Body.hpp"
#include "Transform.hpp"
//#include "Component.hpp"

Shape::Shape(ShapeType Type, Body* body, Transform* transform)
{
	this->body = body;
	this->transform = transform;
}

Shape::~Shape()
{
}

ShapeAABB::ShapeAABB(Body* body, Transform* transform) : Shape(Shape::ShapeType::AABB, body, transform)
{
	type = AABB;
	//pivot top-left
	left = 0;
	right = transform->scaleX;
	top = 0;
	bottom = transform->scaleY;
	
	//pivot center
	//left = -0.5f * transform->scaleX;
	//right = 0.5f * transform->scaleX;
	//top = 0.5f * transform->scaleY;
	//bottom = -0.5f * transform->scaleY;
}

bool ShapeAABB::PointCollisionDetection(float PointX, float PointY)
{
	float left, right, top, bottom;
	left = body->positionX - left;
	right = body->positionX - right;
	top = body->positionY - top;
	bottom = body->positionY - bottom;

	if (PointX < left || PointX > right || PointY < top || PointY > bottom)
		return false;

	return true;
}

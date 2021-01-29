#include <Pch.hpp>
//#include "ShapeComponent.hpp" 
//#include "PhysicsBodyComponent.hpp"
//#include "TransformComponent.hpp"
//
//ShapeComponent::ShapeComponent(ShapeComponent::ShapeType type)
//{
//	this->type = type;
//	//todo local assignments
//	//this->body = body;
//	//this->transform = transform;
//}
//
//ShapeComponent::~ShapeComponent()
//{
//}
//
//AABBShapeComponent::AABBShapeComponent() : ShapeComponent(ShapeComponent::ShapeType::AABB)
//{
//	////pivot top-left
//	//left = 0;
//	//right = transform->scale.x;
//	//top = 0;
//	//bottom = transform->scale.y;
//	
//	//pivot center
//	transform = 
//	left = -0.5f * transform->scale.x;
//	right = 0.5f * transform->scale.x;
//	top = 0.5f * transform->scale.y;
//	bottom = -0.5f * transform->scale.y;
//}
//
////bool PointCollisionDetection(float pointX, float pointY);
//bool AABBShapeComponent::PointCollisionDetection(float pointX, float pointY)
//{
//	left = body->positionX - left;
//	right = body->positionX - right;
//	top = body->positionY - top;
//	bottom = body->positionY - bottom;
//
//	if (pointX < left || pointX > right || pointY < top || pointY > bottom)
//		return false;
//
//	return true;
//}

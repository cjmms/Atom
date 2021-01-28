#include <Pch.hpp>
//#include "PhysicsManager.hpp"
//#include "../components/Transform.hpp"
//#include "../components/Body.hpp"
//#include "../components/Shape.hpp"
//
//bool CheckCollisionAABBAABB(
//	Shape* AABBShape1, float pos1X, float pos1Y,
//	Shape* AABBShape2, float pos2X, float pos2Y,
//	std::list<Contact*>& contacts)
//{
//	float left1, right1, top1, bottom1;
//	float left2, right2, top2, bottom2;
//
//	ShapeAABB* pAABB1 = (ShapeAABB*)AABBShape1;
//	ShapeAABB* pAABB2 = (ShapeAABB*)AABBShape2;
//
//	left1 = pos1X + pAABB1->left;
//	right1 = pos1X + pAABB1->right;
//	top1 = pos1Y + pAABB1->top;
//	bottom1 = pos1Y - pAABB1->bottom;
//
//	left2 = pos2X + pAABB2->left;
//	right2 = pos2X + pAABB2->right;
//	top2 = pos2Y + pAABB2->top;
//	bottom2 = pos2Y - pAABB2->bottom;
//	
//	/*left1 = pos1X + pAABB1->left;
//	right1 = pos1X + pAABB1->right;
//	top1 = pos1Y + pAABB1->top;
//	bottom1 = pos1Y + pAABB1->bottom;
//
//	left2 = pos2X + pAABB2->left;
//	right2 = pos2X + pAABB2->right;
//	top2 = pos2Y + pAABB2->top;
//	bottom2 = pos2Y + pAABB2->bottom;*/
//
//	if (left1 > right2 || left2 > right1
//		|| top1 < bottom2 || top2 < bottom1)
//		return false;
//
//	Contact* pNewContact = new Contact();
//	pNewContact->bodies[0] = AABBShape1->body;
//	pNewContact->bodies[1] = AABBShape2->body;
//	contacts.push_back(pNewContact);
//
//	return true;
//}
//
//PhysicsManager::PhysicsManager()
//{
//	CollisionFunctions[Shape::ShapeType::AABB][Shape::ShapeType::AABB] = CheckCollisionAABBAABB;
//}
//
//PhysicsManager::~PhysicsManager()
//{
//
//}
//
//void PhysicsManager::Update(float FrameTime, Body* b1, Body* b2)
//{
//	//reset prev contacts;
//	Reset();
//
//	bool collision = CollisionDetection(
//		b1->shape, b1->positionX, b1->positionY,
//		b2->shape, b2->positionX, b2->positionY
//	);
//
//	b1->Integrate(true, FrameTime);
//	b2->Integrate(collision, FrameTime);
//
//	//for (auto gameObject : GameObjects)
//	//{
//	//	Body* body = static_cast<Body*>(gameObject->GetComponent(TYPE_BODY));
//	//	if (body != nullptr)
//	//	{
//	//		body->Integrate(0.0f, FrameTime);
//	//	}
//	//}
//	//
//	//for (auto pObj1 = GameObjects.begin(); pObj1 != GameObjects.end(); ++pObj1)
//	//{
//	//	Body* body1 = static_cast<Body*>((*pObj1)->GetComponent(TYPE_BODY));
//	//
//	//	if (body1 == nullptr)
//	//		continue;
//	//
//	//	for (auto pObj2 = pObj1 + 1; pObj2 != GameObjects.end(); ++pObj2)
//	//	{
//	//		Body* body2 = static_cast<Body*>((*pObj2)->GetComponent(TYPE_BODY));
//	//
//	//		if (body2 == nullptr)
//	//			continue;
//	//
//	//		CollisionDetection(
//	//			body1->shape, body1->positionX, body1->positionY,
//	//			body2->shape, body2->positionX, body2->positionY
//	//		);
//	//	}
//	//}
//	//
//	////todo if advanced physics, resolve contacts
//	//
//	//for (auto pContact : contacts)
//	//{
//	//	//CollideEvent collideEvent;
//	//	//
//	//	////pass the collide event to the two contact owners
//	//	//pContact->mBodies[0]->mpOwner->HandleEvent(&collideEvent);
//	//	//pContact->mBodies[1]->mpOwner->HandleEvent(&collideEvent);
//	//}
//}
//
//void PhysicsManager::Reset()
//{
//	for (auto c : contacts)
//		delete c;
//
//	contacts.clear();
//}
//
//
//bool PhysicsManager::CollisionDetection(Shape* shape1, float pos1X, float pos1Y, Shape* shape2, float pos2X, float pos2Y)
//{
//	return CollisionFunctions[shape1->type][shape2->type](
//		shape1, pos1X, pos1Y,
//		shape2, pos2X, pos2Y,
//		contacts);
//}
//
//

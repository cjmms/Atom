/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		AABBCollision.hpp
* @author	Gerald Lee
* @brief	Collision Detection for Rectangular Components
* @date		2021-02-08
*/

#pragma once

#include <list>
#include <string>
#include "components/ShapeComponent.hpp"
#include "components/TransformComponent.hpp"
#include "core/System.hpp"
#include "systems/PhysicsSystem.hpp"

bool CheckCollisionAABBAABB(double frameTime,
    const ShapeType shapeType1, TransformComponent& transform1, PhysicsBodyComponent& body1,
    const ShapeType shapeType2, TransformComponent& transform2, PhysicsBodyComponent& body2,
    std::list<Contact*>& contacts);

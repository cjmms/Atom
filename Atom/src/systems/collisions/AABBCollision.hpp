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

#pragma once

#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"

class ShapeComponent
{
public:
	ShapeType shapeType;
	
};

inline void to_json(ordered_json& j, const ShapeComponent& x) {
	to_json(j["shapeType"], x.shapeType);
}

inline void from_json(const ordered_json& j, ShapeComponent& x) {
	from_json(j["shapeType"], x.shapeType);
}
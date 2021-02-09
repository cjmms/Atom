#pragma once

#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"

class ShapeComponent
{
public:
	enum ShapeType
	{
		//Circle,
		AABB,
		//Polygon,
		Num
	};

	ShapeType shapeType;
	
};

inline void to_json(ordered_json& j, const ShapeComponent& x) {
	to_json(j["shapeType"], x.shapeType);
}

//todo gerald any better way to do enum deserialization?
inline void from_json(const ordered_json& j, ShapeComponent& x) {
	int type = 0;
	from_json(j["shapeType"], type);
	x.shapeType = (ShapeComponent::ShapeType)type;
}

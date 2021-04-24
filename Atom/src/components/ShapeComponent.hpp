/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		ShapeComponent.hpp
* @author	Gerald Lee
* @brief	Shape Component
* @date		2021-01-29
*/

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
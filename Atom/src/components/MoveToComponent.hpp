/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		MoveToComponent.hpp
* @author	Kishore Kandasamy Balakrishnan
* @brief	Used to define the movement of an entity on trigger
* @date		2021-04-13
*/

#pragma once

#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"

class MoveToComponent {
public:
	float velocityX = -0.3f;
	float velocityY = -0.3f;
	float GridX = 0.0f;	//Number of grids to move
	float GridY = 0.0f;	//Number of grids to move

	string tag;

};

inline void to_json(ordered_json& j, const MoveToComponent& x) {
	to_json(j["velocityX"], x.velocityX);
	to_json(j["velocityY"], x.velocityY);
	to_json(j["GridX"], x.GridX);
	to_json(j["GridY"], x.GridY);
	to_json(j["tag"], x.tag);
}

inline void from_json(const ordered_json& j, MoveToComponent& x) {
	from_json(j["velocityX"], x.velocityX);
	from_json(j["velocityY"], x.velocityY);
	from_json(j["GridX"], x.GridX);
	from_json(j["GridY"], x.GridY);
	from_json(j["tag"], x.tag);
}

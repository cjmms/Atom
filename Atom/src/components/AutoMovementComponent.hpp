/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		AutoMovementComponent.hpp
* @author	Gerald Lee
* @brief	for horizontal movement of bots
* @date		2021-03-16
*/

#pragma once

#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"

class AutoMovementComponent {
public:
	float velocityX = -0.3f;
	float velocityY = -0.3f;
	float tripTime = 2.0f;	//time to turn its side

	float currentTime = 0.0f;
	bool oppositeDirection = false;
};

inline void to_json(ordered_json& j, const AutoMovementComponent& x) {
	to_json(j["velocityX"], x.velocityX);
	to_json(j["velocityY"], x.velocityY);
	to_json(j["tripTime"], x.tripTime);
}

inline void from_json(const ordered_json& j, AutoMovementComponent& x) {
	from_json(j["velocityX"], x.velocityX);
	from_json(j["velocityY"], x.velocityY);
	from_json(j["tripTime"], x.tripTime);
}

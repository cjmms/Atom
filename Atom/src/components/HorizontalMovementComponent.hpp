/*
* @file		HorizontalMovementComponent.hpp
* @author	Gerald Lee
* @brief	for horizontal movement of bots
* @date		2021-03-16
*/

#pragma once

#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"

class HorizontalMovementComponent {
public:
	float velocity = -0.3f;
	float tripTime = 2.0f;	//time to turn its side

	float currentTime = 0.0f;
	bool oppositeDirection = false;
};

inline void to_json(ordered_json& j, const HorizontalMovementComponent& x) {
}

inline void from_json(const ordered_json& j, HorizontalMovementComponent& x) {
}


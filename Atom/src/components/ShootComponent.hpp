/*
* @file		ShootComponent.hpp
* @author	Gerald Lee
* @brief	ShootComponent
* @date		2021-03-05
*/

#pragma once
#include <Pch.hpp>
#include <core/Types.hpp>
#include "utils/Serde.hpp"

class ShootComponent
{
public:
	bool isShooting;
	float direction;
	float shootInterval = 0.5f;
	float timer;

public:
	ShootComponent() {
		isShooting = false;
		direction = 0;
		timer = shootInterval;
	};
};

inline void to_json(ordered_json& j, const ShootComponent& x) {
	to_json(j["shootInterval"], x.shootInterval);
}

inline void from_json(const ordered_json& j, ShootComponent& x) {
	from_json(j["shootInterval"], x.shootInterval);
}

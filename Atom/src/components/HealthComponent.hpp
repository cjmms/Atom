/*
* @file		HealthComponent.hpp
* @author	Gerald Lee
* @brief	HealthComponent
* @date		2021-03-05
*/

#pragma once
#include <Pch.hpp>
#include <core/Types.hpp>
#include "utils/Serde.hpp"

class HealthComponent
{
public:
	int health;

public:
	HealthComponent() {};
};

inline void to_json(ordered_json& j, const HealthComponent& x) {
	to_json(j["health"], x.health);
}

inline void from_json(const ordered_json& j, HealthComponent& x) {
	from_json(j["health"], x.health);
}

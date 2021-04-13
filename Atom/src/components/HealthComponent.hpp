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
	int totalHealth;

	bool died = false;

	//for rendering
	float offsetX = 0.0f, offsetY = 0.02f;
	float width = 0.1f, height = 0.01f;
	
	//for disappearance logic
	float timeToDisappear = 3.0f;	//disappear after being unchanged for 1.0s
	float fadeOutTime = 3.0f;
	float currentTime = 999.0;

public:
	HealthComponent() {
		
	};
};

inline void to_json(ordered_json& j, const HealthComponent& x) {
	to_json(j["health"], x.health);
	to_json(j["totalHealth"], x.totalHealth);
}

inline void from_json(const ordered_json& j, HealthComponent& x) {
	from_json(j["health"], x.health);
	from_json(j["totalHealth"], x.totalHealth);
}

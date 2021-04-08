#pragma once

#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"

class PushUpComponent {
public:
	float ForceX = 0.0f;		//Sideward Force
	float ForceY = 3.0f;		//Upward Force
	float PositionX = 0.0f;		//X-Position of platform
	float PositionY = 0.0f;		//Y-Position of platform
	float Scale = 1.0f;			//Scale of Platform

	float currentTime = 0.0f;
	bool oppositeDirection = false;
};

inline void to_json(ordered_json& j, const PushUpComponent& x) {
	to_json(j["ForceX"], x.ForceX);
	to_json(j["ForceY"], x.ForceY);
	to_json(j["PositionX"], x.PositionX);
	to_json(j["PositionY"], x.PositionY);
	to_json(j["Scale"], x.Scale);
}

inline void from_json(const ordered_json& j, PushUpComponent& x) {
	from_json(j["ForceX"], x.ForceX);
	from_json(j["ForceY"], x.ForceY);
	from_json(j["PositionX"], x.PositionX);
	from_json(j["PositionY"], x.PositionY);
	from_json(j["Scale"], x.Scale);
}
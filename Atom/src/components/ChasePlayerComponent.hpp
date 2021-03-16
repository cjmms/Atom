/*
* @file		ChasePlayer.hpp
* @author	Gerald Lee
* @brief	enemy chase player
* @date		2021-03-10
*/

#pragma once

#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"
class ChasePlayerComponent {
public:
    //todo hard coded value, should be retrieved by gameobject manager, serialization(etc)
    EntityID target = 36;
    float distance = 3; //start chasing at certain distance
    float speed = 0.3;
};

inline void to_json(ordered_json& j, const ChasePlayerComponent& x) {
}

inline void from_json(const ordered_json& j, ChasePlayerComponent& x) {
}


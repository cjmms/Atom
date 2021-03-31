/*
* @file		LevelTriggerComponent.hpp
* @author	Gerald Lee
* @brief	enter next level when both character touch the trigger
* @date		2021-03-10
*/

#pragma once

#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"
class LevelTriggerComponent {
public:
    EntityID characterEntered = -1;
};

inline void to_json(ordered_json& j, const LevelTriggerComponent& x) {
}

inline void from_json(const ordered_json& j, LevelTriggerComponent& x) {
}

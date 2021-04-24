/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		AutoShootComponent.hpp
* @author	Gerald Lee
* @brief	Enemy Auto Shoot Mechanism
* @date		2021-03-10
*/

#pragma once

#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"

class AutoShootComponent {
public:
    //todo hard coded value, should be retrieved by gameobject manager(etc)
    EntityID target = 36;
};

inline void to_json(ordered_json& j, const AutoShootComponent& x) {
}

inline void from_json(const ordered_json& j, AutoShootComponent& x) {
}


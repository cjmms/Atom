/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		BulletComponent.hpp
* @author	Gerald Lee
* @brief	bullet tag component
* @date		2021-03-16
*/

#pragma once

#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"

class BulletComponent {
public:
};

inline void to_json(ordered_json& j, const BulletComponent& x) {
}

inline void from_json(const ordered_json& j, BulletComponent& x) {
}


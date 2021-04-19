/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		IndicatorComponent.hpp
* @author	Gerald Lee
* @brief	tag component for character indicator
* @date		2021-03-16
*/

#pragma once

#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"

class IndicatorComponent {
public:
};

inline void to_json(ordered_json& j, const IndicatorComponent& x) {
}

inline void from_json(const ordered_json& j, IndicatorComponent& x) {
}


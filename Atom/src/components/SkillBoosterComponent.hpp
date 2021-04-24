/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		SkillBoosterComponent.hpp
* @author	Gerald Lee
* @brief	SkillBooster Component
* @date		date 2021-03-14
*/

#pragma once
#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"

class SkillBoosterComponent
{
public:

	SkillType skillType;
	bool destroy = false;
};

inline void to_json(ordered_json& j, const SkillBoosterComponent& x) {
	to_json(j["skillType"], x.skillType);
}

inline void from_json(const ordered_json& j, SkillBoosterComponent& x) {
	from_json(j["skillType"], x.skillType);

}
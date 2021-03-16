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
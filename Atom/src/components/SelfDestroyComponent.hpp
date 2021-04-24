/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		SelfDestroyComponent.hpp
* @author	Gerald Lee
* @brief	SelfDestroyComponent
* @date		2021-03-31
*/

#pragma once
#include <Pch.hpp>
#include <core/Types.hpp>
#include "utils/Serde.hpp"

class SelfDestroyComponent
{
public:
	float timeLimit = 2.0f;

	float timer = 2.0f;

public:
	SelfDestroyComponent() {}
	SelfDestroyComponent(float time) : timeLimit(time), timer(time) {}
};

inline void to_json(ordered_json& j, const SelfDestroyComponent& x) {
	to_json(j["timeLimit"], x.timeLimit);
}

inline void from_json(const ordered_json& j, SelfDestroyComponent& x) {
	from_json(j["timeLimit"], x.timeLimit);
}

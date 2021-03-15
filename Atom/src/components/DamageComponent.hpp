/*
* @file		DamageComponent.hpp
* @author	Gerald Lee
* @brief	DamageComponent
* @date		2021-03-05
*/

#pragma once
#include <Pch.hpp>
#include <core/Types.hpp>
#include "utils/Serde.hpp"

class DamageComponent
{
public:
	int damage;
	bool destroy = false;	//destroy this component after hit (assume bullet)

public:
	DamageComponent() {};
	DamageComponent(int damage) : damage(damage) {};
};

inline void to_json(ordered_json& j, const DamageComponent& x) {
	to_json(j["damage"], x.damage);
}

inline void from_json(const ordered_json& j, DamageComponent& x) {
	from_json(j["damage"], x.damage);
}

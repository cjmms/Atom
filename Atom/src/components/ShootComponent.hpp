/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		ShootComponent.hpp
* @author	Gerald Lee
* @brief	ShootComponent
* @date		2021-03-05
*/

#pragma once
#include <Pch.hpp>
#include <core/Types.hpp>
#include "utils/Serde.hpp"

class ShootComponent
{
public:
	float shootInterval = 0.5f;
	int bulletPerShoot = 1;

	string bulletTexturePath = "Atom/res/art/CharacterBullet.png";
	float bulletSpeed = 1.0;
	float bulletScale = 0.05;

	bool isShooting;
	float direction;
	float timer;

public:
	ShootComponent() {
		isShooting = false;
		direction = 0;
		timer = shootInterval;
	};
};

inline void to_json(ordered_json& j, const ShootComponent& x) {
	to_json(j["shootInterval"], x.shootInterval);
	to_json(j["bulletPerShoot"], x.bulletPerShoot);
	to_json(j["bulletTexturePath"], x.bulletTexturePath);
	to_json(j["bulletSpeed"], x.bulletSpeed);
	to_json(j["bulletScale"], x.bulletScale);
}

inline void from_json(const ordered_json& j, ShootComponent& x) {
	from_json(j["shootInterval"], x.shootInterval);
	from_json(j["bulletPerShoot"], x.bulletPerShoot);
	from_json(j["bulletTexturePath"], x.bulletTexturePath);
	from_json(j["bulletSpeed"], x.bulletSpeed);
	from_json(j["bulletScale"], x.bulletScale);
}

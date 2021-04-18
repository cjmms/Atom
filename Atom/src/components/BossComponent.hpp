/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		BossComponent.hpp
* @author	Gerald Lee
* @brief	boss tag component
* @date		2021-03-16
*/

#pragma once

#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"

class BossComponent {
public:
	float shootInterval = 0.5f;
	int bulletPerShoot = 10;

	string bulletTexturePath = "Atom/res/art/EnemyBullet.png";
	float bulletSpeed = 1.0;
	float bulletScale = 0.05;

	bool isShooting;
	float direction;
	float timer;
};

inline void to_json(ordered_json& j, const BossComponent& x) {
}

inline void from_json(const ordered_json& j, BossComponent& x) {
}


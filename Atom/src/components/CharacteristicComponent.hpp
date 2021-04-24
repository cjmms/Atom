/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		CharactersticComponent.hpp
* @author	Kishore Kandasamy Balakrishnan
* @brief	Component to determine additional characterstic to an entity
* @date		2021-03-14
*/

#pragma once
#include "Pch.hpp"
#include "utils/Serde.hpp"

struct PowerUp
{
	bool isActive = false;
	bool isEnabled = false;
};

class CharacteristicComponent
{
public:
	bool isBig;

	bool inGodMode = false;
	bool inSuperGodMode = false;

	PowerUp canWallJump;
	PowerUp canDoubleJump;

};

inline void to_json(ordered_json& j, const CharacteristicComponent& x) {
	to_json(j["isBig"], x.isBig);
}

inline void from_json(const ordered_json& j, CharacteristicComponent& x) {
	from_json(j["isBig"], x.isBig);

}
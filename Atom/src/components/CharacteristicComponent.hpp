#pragma once
#include "Pch.hpp"
#include "utils/Serde.hpp"

struct PowerUp
{
	bool isActive = true;	//todo for testing only
	bool isEnabled = true;
};

class CharacteristicComponent
{
public:
	bool isBig;

	PowerUp canWallJump;
	PowerUp canDoubleJump;

};

inline void to_json(ordered_json& j, const CharacteristicComponent& x) {
	to_json(j["isBig"], x.isBig);
}

inline void from_json(const ordered_json& j, CharacteristicComponent& x) {
	from_json(j["isBig"], x.isBig);

}
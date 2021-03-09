#pragma once
#include "Pch.hpp"

struct PowerUp
{
	bool isActive;
	bool isEnabled;
};

class Characterstic
{
public:
	bool isBigGuy;
	bool isSmallGuy;
	bool isGrounded;

	PowerUp canWallJump;
	PowerUp canDoubleJump;
};
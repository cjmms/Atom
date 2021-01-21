/*
Copyright (C) 2020 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written consent of DigiPen Institute of Technology is prohibited.
File Name: FrameRateController.cpp
Purpose: control the frame rate of the game
Language: VC++
Platform: Microsoft Visual Studio Community 2019 Version 16.6.1, Microsoft .NET Framework Version 4.8.03752, Windows 10
Project: CS529_FinalProject
Author: Gerald Lee, gerald.lee, 60000220
Creation date: 20202-10-11
*/

#include "FrameRateController.hpp"
#include <climits>

#include "GLFW/glfw3.h"

FrameRateController::FrameRateController(unsigned int maxFrameRate)
{
	if (maxFrameRate == 0)
		maxFrameRate = UINT_MAX;

	tickStart = 0;
	tickEnd = 0;
	frameTime = 0;
	maxFrameRate = maxFrameRate;
	ticksPerFrame = 1 / maxFrameRate;
}

FrameRateController::~FrameRateController()
{

}

void FrameRateController::FrameStart()
{
	tickStart = glfwGetTime();
}

void FrameRateController::FrameEnd()
{
	tickEnd = glfwGetTime();
	while (tickEnd - tickStart < ticksPerFrame)
	{
		//wait until next frame
		tickEnd = glfwGetTime();
	}

	frameTime = tickEnd - tickStart;
}

double FrameRateController::GetFrameTime()
{
	return frameTime;
}
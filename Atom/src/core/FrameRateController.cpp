#include <Pch.hpp>
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
	ticksPerFrame = 1.0 / maxFrameRate;
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
#pragma once

class FrameRateController
{
public:
	FrameRateController(unsigned int maxFrameRate);
	~FrameRateController();

	void FrameStart();
	void FrameEnd();
	double GetFrameTime();
public:
private:
private:
	double tickStart;
	double tickEnd;
	double maxFrameRate;
	double ticksPerFrame;
	double frameTime;
};


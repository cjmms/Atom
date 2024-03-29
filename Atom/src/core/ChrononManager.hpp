/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		ChrononManager.hpp
* @author	Abhikalp Unakal
* @brief	ChrononManager.hpp - frame rate controller with nanosecond precision using std::chrono 
* @date		2021-01-22
*/

#ifndef CHRONONMANAGER_HPP
#define CHRONONMANAGER_HPP

#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Log.hpp"

using timeres = std::chrono::steady_clock::duration;
const int LIMITMAXFPS = 10000;
const long long LIMITMAXFRAMES = std::numeric_limits<long long>::max() - LIMITMAXFPS;

class ChrononManager {
public:
	ChrononManager() : mMaxFPS(0), mTotalFrames(0) {
		mClockInit = std::chrono::steady_clock::now();
	}
	void startframe() {
		mStart = std::chrono::steady_clock::now();
	}
	void endFrame() {

		auto resolution = std::chrono::steady_clock::duration::period::den;

		while (1) {
			mEnd = std::chrono::steady_clock::now();
			auto elapsed = mEnd - mStart;
			// NO OVERFLOW
			auto maxFPS = mMaxFPS == 0 ? LIMITMAXFPS : mMaxFPS;
			if (elapsed.count() < resolution / maxFPS) {
				// do nothing waste time in the while(1)
			}
			else {
				//if(elapsed)
				mEnd = std::chrono::steady_clock::now();
				mTotalFrames = std::min(LIMITMAXFRAMES, mTotalFrames + 1);
				return;
			}
		}
	}
	void setMaxFPS(unsigned int maxfps) {
		mMaxFPS = maxfps;
	}

	long long getTotalFrames() {
		return mTotalFrames;
	}
	// total time in seconds
	double getUptime() {
		auto resolution = timeres::period::den;
		auto elapsed = std::chrono::steady_clock::now() - mClockInit;
		return ((double)elapsed.count() / resolution);
	}

	double getFPS() {
		auto resolution = timeres::period::den;
		auto elapsed = mEnd - mStart;
		auto ticks = elapsed.count();
		if (ticks < 1LL) {
			return 0.0;
		}
		return ((double)resolution / elapsed.count());
	}
	double updatedt() {
		auto resolution = timeres::period::den;
		auto elapsed = mEnd - mStart;
		auto ticks = std::min(100000000LL, elapsed.count());
		return ((double)ticks / resolution);
	}

private:
	std::chrono::time_point<std::chrono::steady_clock, timeres> mClockInit;
	std::chrono::time_point<std::chrono::steady_clock, timeres> mStart;
	std::chrono::time_point<std::chrono::steady_clock, timeres> mEnd;
	unsigned int mMaxFPS;
	long long mTotalFrames;
};
#endif CHRONONMANAGER_HPP
/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		FadeComponent.hpp
* @author	Abhikalp Unakal
* @brief	FadeComponent
* @date		2021-04-07
*/

#ifndef FADECOMPONENT_HPP
#define FADECOMPONENT_HPP
#include <Pch.hpp>
#include "core/Types.hpp"
#include "utils/Serde.hpp"

class FadeComponent {
public:
	float startAlpha = 1.0f;
	float endAlpha = 1.0f;
	float timerSeconds = 1.0f;
	// a = low_out, b = hi_out, t(0) = b, t(1) = a, 
	float lerp10(float a, float b, float t, float lo, float hi) {
		if (lo == hi) {
			return b;
		}
		t = (t - lo) / (hi - lo);
		float res = b * (1 - t) + a * (t);
		return res;
	}
	// a = low_out, b = hi_out, t(0) = a, t(1) = b, 
	float lerp01(float a, float b, float t, float lo, float hi) {
		if (lo == hi) {
			return a;
		}
		t = (t - lo) / (hi - lo);
		float res = a * (1 - t) + b * (t);
		return res;
	}
};

// RENDERBOX COMPONENT SERDE
inline void to_json(ordered_json& j, const FadeComponent& x) {
	to_json(j["startAlpha"], x.startAlpha);
	to_json(j["endAlpha"], x.endAlpha);
	to_json(j["timerSeconds"], x.timerSeconds);
}

inline void from_json(const ordered_json& j, FadeComponent& x) {
	from_json(j["startAlpha"], x.startAlpha);
	from_json(j["endAlpha"], x.endAlpha);
	from_json(j["timerSeconds"], x.timerSeconds);
}

#endif // !RENDERCOMPONENT_HPP
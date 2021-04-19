/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		AnimationComponent.hpp
* @author	Abhikalp Unakal
* @brief	Animation Component
* @date		2021-04-11
*/

#ifndef ANIMATIONCOMPONENT_HPP
#define ANIMATIONCOMPONENT_HPP

#include "Pch.hpp"
#include "core/Types.hpp"
#include "utils/Serde.hpp"

class AnimationStates {
public:
	int id;
	string label;
	int totalframes;
	float duration;
	std::vector<int> frames;
};

inline void to_json(ordered_json& j, const AnimationStates& x) {
	to_json(j["id"], x.id);
	to_json(j["label"], x.label);
	to_json(j["totalframes"], x.totalframes);
	to_json(j["duration"], x.duration);
	j["frames"] = ordered_json::array();
	for (auto& frame : x.frames) {
		ordered_json jframe;
		to_json(jframe, frame);
		j["frames"].push_back(jframe);
	}
}

inline void from_json(const ordered_json& j, AnimationStates& x) {
	from_json(j["id"], x.id);
	from_json(j["label"], x.label);
	from_json(j["totalframes"], x.totalframes);
	from_json(j["duration"], x.duration);
	int tempframe;
	for (auto& jframe : j["frames"]) {
		from_json(jframe, tempframe);
		x.frames.push_back(tempframe);
	}
}

class AnimationComponent {
public:
	string spriteloc;
	int width;
	int height;
	int rows;
	int cols;
	int currstate;
	std::vector<AnimationStates> allstates;
};
inline void to_json(ordered_json& j, const AnimationComponent& x) {
	to_json(j["spriteloc"], x.height);
	to_json(j["width"], x.width);
	to_json(j["height"], x.height);
	to_json(j["rows"], x.rows);
	to_json(j["cols"], x.cols);
	to_json(j["currstate"], x.currstate);
	j["states"] = ordered_json::array();
	for (auto& state : x.allstates) {
		ordered_json jstate;
		to_json(jstate, state);
		j["states"].push_back(j);
	}
}

inline void from_json(const ordered_json& j, AnimationComponent& x) {
	from_json(j["spriteloc"], x.height);
	from_json(j["width"], x.width);
	from_json(j["height"], x.height);
	from_json(j["rows"], x.rows);
	from_json(j["cols"], x.cols);
	from_json(j["currstate"], x.currstate);
	AnimationStates tempState;
	for (auto& statejson : j["states"]) {
		from_json(statejson, tempState);
		x.allstates.push_back(tempState);
	}
}

#endif
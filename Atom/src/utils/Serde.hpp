/*
* @file		Serde.hpp
* @author	Abhikalp Unakal
* @brief	Class with helpers for all (Se)rialization and (De)serialization
* @date		2021-01-16
*/

#ifndef SERDE_HPP
#define SERDE_HPP

#include <Pch.hpp>
#include "core/Types.hpp"
#include "utils/AtomScancode.hpp"

#define REGISTER_STRING(x) {x,#x},

// read file and write into json
inline void load(string filepath, ordered_json& j) {
	std::ifstream in(filepath);
	in >> j;
}

// read json and write to file
inline void save(string filepath, const ordered_json& j) {
	std::ofstream out(filepath);
	out << std::setw(4) << j;
}

//// SERDE FOR ENUMS
NLOHMANN_JSON_SERIALIZE_ENUM(ShapeType, {
	REGISTER_STRING(AABB)
	REGISTER_STRING(NUM)
	});

NLOHMANN_JSON_SERIALIZE_ENUM(SkillType, {
	REGISTER_STRING(DoubleJump)
	REGISTER_STRING(WallJump)
	});

// EVENTID
NLOHMANN_JSON_SERIALIZE_ENUM(EventID, {
	// WINDOW
	REGISTER_STRING(E_WINDOW_QUIT)
	REGISTER_STRING(E_WINDOW_RESIZED)
		REGISTER_STRING(P_WINDOW_RESIZED_WIDTH)
		REGISTER_STRING(P_WINDOW_RESIZED_HEIGHT)
	// KEYBOARD
	REGISTER_STRING(E_WINDOW_KEY_PRESSED)
		REGISTER_STRING(P_WINDOW_KEY_PRESSED_KEYCODE)
	REGISTER_STRING(E_WINDOW_KEY_RELEASED)
		REGISTER_STRING(P_WINDOW_KEY_RELEASED_KEYCODE)
	REGISTER_STRING(E_WINDOW_KEY_TRIGGERED)
		REGISTER_STRING(P_WINDOW_KEY_TRIGGERED_KEYCODE)
	// MOUSE
	REGISTER_STRING(E_WINDOW_MOUSE_MOVE)
		REGISTER_STRING(P_WINDOW_MOUSE_MOVE_X)
		REGISTER_STRING(P_WINDOW_MOUSE_MOVE_Y)
	REGISTER_STRING(E_WINDOW_MOUSE_DOWN)
		REGISTER_STRING(P_WINDOW_MOUSE_DOWN_BUTTON)
		REGISTER_STRING(P_WINDOW_MOUSE_DOWN_X)
		REGISTER_STRING(P_WINDOW_MOUSE_DOWN_Y)
	REGISTER_STRING(E_WINDOW_MOUSE_UP)
		REGISTER_STRING(P_WINDOW_MOUSE_UP_BUTTON)
		REGISTER_STRING(P_WINDOW_MOUSE_UP_X)
		REGISTER_STRING(P_WINDOW_MOUSE_UP_Y)
	// GRAPHICS
	REGISTER_STRING(E_GRAPHICS_DEBUG_TOGGLE)
	// CAMERA
	REGISTER_STRING(E_GRAPHICS_CAMERA_UPDATED)
		REGISTER_STRING(P_GRAPHICS_CAMERA_UPDATED_ENTITYID)
	// BROADCAST EVENT
	REGISTER_STRING(E_BROADCAST_EVENT)
		REGISTER_STRING(P_BROADCAST_EVENT_DATA)
	// TIMED EVENTS
	REGISTER_STRING(E_TIMED_EVENT)
		REGISTER_STRING(P_TIMED_EVENT_TIME_START)
		REGISTER_STRING(P_TIMED_EVENT_TIME_EXEC)
		REGISTER_STRING(P_TIMED_EVENT_DATA)
	// DIRECTMESSAGE EVENTS
	REGISTER_STRING(E_DM_EVENT)
		REGISTER_STRING(P_DM_EVENT_ENTITYID)
		REGISTER_STRING(P_DM_EVENT_DATA)
	// GAMESTATE EVENTS
	REGISTER_STRING(E_GS_LEVEL)
		REGISTER_STRING(P_GS_LEVEL_NAME)
	// FIRE BULLET
	REGISTER_STRING(E_BULLET_FIRED)
		REGISTER_STRING(P_BULLET_FIRED_ORIGIN_ID)
	// AUDIO EVENTS
	REGISTER_STRING(E_AUDIO_PLAY),
		REGISTER_STRING(P_AUDIO_PLAY_AUDIOLOC),
		REGISTER_STRING(P_AUDIO_PLAY_CHANNELGROUP),
		REGISTER_STRING(P_AUDIO_PLAY_VOLUMEDB),
	// COLLISION EVENTS
	REGISTER_STRING(E_COLLISION),
		REGISTER_STRING(P_COLLISION_ENTITYID1),
		REGISTER_STRING(P_COLLISION_ENTITYID2),
		REGISTER_STRING(EP_TOTAL)
	});


//// SERDE (SERIALIZER DESERIALIZER) FOR BASIC TYPES

////////////////////////////////// INT
inline void to_json(ordered_json& j, const int& x) {
	j = x;
}

inline void from_json(const ordered_json& j, int& x) {
	x = j.get<int>();
}
/////////////////////////////////

///////////////////////////////// UNSIGNED INT
inline void to_json(ordered_json& j, const unsigned int& x) {
	j = x;
}

inline void from_json(const ordered_json& j, unsigned int& x) {
	x = j.get<unsigned int>();
}
/////////////////////////////////

///////////////////////////////// FLOAT
inline void to_json(ordered_json& j, const float& x) {
	j = x;
}

inline void from_json(const ordered_json& j, float& x) {
	x = j.get<float>();
}
/////////////////////////////////

///////////////////////////////// STRING
inline void to_json(ordered_json& j, const string& x) {
	j = x.c_str();
}

inline void from_json(const ordered_json& j, string& x) {
	x = j.get<string>();
}
/////////////////////////////////

///////////////////////////////// BOOL
inline void to_json(ordered_json& j, const bool& x) {
	j = x;
}

inline void from_json(const ordered_json& j, bool& x) {
	x = j.get<bool>();
}
/////////////////////////////////

///////////////////////////////// VEC2
inline void to_json(ordered_json& j, const glm::vec2& x) {
	j = {
		{"x",x.x},
		{"y",x.y},
	};
}

inline void from_json(const ordered_json& j, glm::vec2& x) {
	j.at("x").get_to(x.x);
	j.at("y").get_to(x.y);
}

///////////////////////////////// VEC3
inline void to_json(ordered_json& j, const glm::vec3& x) {
	j = {
		{"x",x.x},
		{"y",x.y},
		{"z",x.z},
	};
}

inline void from_json(const ordered_json& j, glm::vec3& x) {
	j.at("x").get_to(x.x);
	j.at("y").get_to(x.y);
	j.at("z").get_to(x.z);
}

///////////////////////////////// VEC4
inline void to_json(ordered_json& j, const glm::vec4& x) {
	j = {
		{"x",x.x},
		{"y",x.y},
		{"z",x.z},
		{"w",x.w},
	};
}

inline void from_json(const ordered_json& j, glm::vec4& x) {
	j.at("x").get_to(x.x);
	j.at("y").get_to(x.y);
	j.at("z").get_to(x.z);
	j.at("w").get_to(x.w);
}

///////////////////////////////// MAT4
inline void to_json(ordered_json& j, const glm::mat4& x) {
	j = {
		{x[0][0],x[1][0],x[2][0],x[3][0]},
		{x[0][1],x[1][1],x[2][1],x[3][1]},
		{x[0][2],x[1][2],x[2][2],x[3][2]},
		{x[0][3],x[1][3],x[2][3],x[3][3]}
	};
}

inline void from_json(const ordered_json& j, glm::mat4& x) {
	for (int k = 0; k < 4; ++k) {
		for (int l = 0; l < 4; ++l) {
			j.at(k).at(l).get_to(x[k][l]);
		}
	}
}

// ATOMKEYCODES
NLOHMANN_JSON_SERIALIZE_ENUM(AtomScancode, {
	REGISTER_STRING(ATOM_SCANCODE_D)
	REGISTER_STRING(ATOM_SCANCODE_T)
	REGISTER_STRING(ATOM_SCANCODE_X)
	REGISTER_STRING(ATOM_SCANCODE_Z)
	REGISTER_STRING(ATOM_SCANCODE_RIGHT)
	REGISTER_STRING(ATOM_SCANCODE_LEFT)
	REGISTER_STRING(ATOM_SCANCODE_DOWN)
	REGISTER_STRING(ATOM_SCANCODE_UP)
	REGISTER_STRING(ATOM_NUM_SCANCODES)
	});

#endif
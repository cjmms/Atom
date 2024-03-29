/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		Types.hpp
* @author	Abhikalp Unakal
* @brief	All Custom Data Types and defines
* @date		2021-01-16
*/

#ifndef TYPES_HPP
#define TYPES_HPP

#include <Pch.hpp>

// CONSTANTS 
#define PI 3.14159f
#define GRAVITY 9.81f
#define EPSILON 0.00001

// DEFINES
#define APPNAME "Space Jump"
#define MAX_TITLE_LEN 80
#define FPS 120
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 800
#define FMODMAXCHANNELS 512
#define FADE_OUT_TIME 1.0f
#define FADE_IN_TIME 1.0f
#define COUNT_INTROS 7
#define TOTAL_LEVELS 26
#define ED_LEVELS 20

// USING
using string = std::string;
using ordered_json = nlohmann::ordered_json;
using json = nlohmann::json;

// ECS
using ResourceID = std::uint32_t;
using EntityID = std::uint32_t;
const EntityID MAX_ENTITIES = 10000;
using ComponentID = std::uint8_t;
const ComponentID MAX_COMPONENTS = 32;
using Archetype = std::bitset<MAX_COMPONENTS>;

// SKILLS
enum SkillType
{
	DoubleJump,
	WallJump,
	BulletCount,
	BulletSpeed,
	Trigger,
	FullHealth,
	DoubleHealth,
};


// PARTICLES
enum ParticleEffectType {
	PE_CIRCLE,
	PE_LINEAR
};

struct CircleParticleEffect {
public:
	int numParticles;
	float scale;
	glm::vec2 time;
};


struct LinearParticleEffect {
public:

};


// PHYSICS
enum ShapeType {
	AABB,
	NUM
};

// TILEMAP
class Gridnode {
public:
	int data;
};

class Grid {
public:
	string filename;
	int rows;
	int cols;
	int tilesize;
	std::vector<std::vector<Gridnode>> cells;
};

// ANIMATION AND STATES
enum PlayerStates {
	PS_IDLE,
	PS_RUN,
	PS_JUMP,
	PS_ATTACK,
	PS_DEFEND,
	PS_DEAD,
	PS_TOTAL
};


// AUDIO
using ChannelMap = std::map<unsigned int, FMOD::Channel*>;
using SoundMap = std::map<string, FMOD::Sound*>;
using ChannelID = unsigned int;
using SoundID = unsigned int;

enum ChannelGroupTypes {
	C_SFX,
	C_MUSIC,
	C_DIALOGUE,
	C_TOTAL
};

class AudioDSPData {
public:
	float* buffer;
	float volumeLinear;
	int nSamples;
	int channels;
};

// EVENTS
enum EventID {
	// WINDOW
	E_WINDOW_QUIT,
	E_WINDOW_RESIZED,
		P_WINDOW_RESIZED_WIDTH,
		P_WINDOW_RESIZED_HEIGHT,
	// KEYBOARD
	E_WINDOW_KEY_PRESSED,
		P_WINDOW_KEY_PRESSED_KEYCODE,
	E_WINDOW_KEY_RELEASED,
		P_WINDOW_KEY_RELEASED_KEYCODE,
	E_WINDOW_KEY_TRIGGERED,
		P_WINDOW_KEY_TRIGGERED_KEYCODE,
	// MOUSE
	E_WINDOW_MOUSE_MOVE,
		P_WINDOW_MOUSE_MOVE_X,
		P_WINDOW_MOUSE_MOVE_Y,
	E_WINDOW_MOUSE_DOWN,
		P_WINDOW_MOUSE_DOWN_BUTTON,
		P_WINDOW_MOUSE_DOWN_X,
		P_WINDOW_MOUSE_DOWN_Y,
	E_WINDOW_MOUSE_UP,
		P_WINDOW_MOUSE_UP_BUTTON,
		P_WINDOW_MOUSE_UP_X,
		P_WINDOW_MOUSE_UP_Y,
	// GRAPHICS
	E_GRAPHICS_DEBUG_TOGGLE,
	// CAMERA
	E_GRAPHICS_CAMERA_UPDATED,
		P_GRAPHICS_CAMERA_UPDATED_ENTITYID,
	// BROADCAST
	E_BROADCAST_EVENT,
		P_BROADCAST_EVENT_DATA,
	// TIMED EVENTS
	E_TIMED_EVENT,
		P_TIMED_EVENT_TIME_START,
		P_TIMED_EVENT_TIME_EXEC,
		P_TIMED_EVENT_DATA,
	// DIRECTMESSAGE EVENTS
	E_DM_EVENT,
		P_DM_EVENT_ENTITYID,
		P_DM_EVENT_DATA,
	// GAME STATE EVENTS
	E_GS_LEVEL,
		P_GS_LEVEL_NAME,
	// FIRE BULLET
	E_BULLET_FIRED,
		P_BULLET_FIRED_ORIGIN_ID,
	// AUDIO EVENTS
	E_AUDIO_PLAY,
		P_AUDIO_PLAY_AUDIOLOC,
		P_AUDIO_PLAY_CHANNELGROUP,
		P_AUDIO_PLAY_VOLUMEDB,
	E_COLLISION,
		P_COLLISION_ENTITYID1,
		P_COLLISION_ENTITYID2,
	E_TRIGGER,
		P_TRIGGER_ENTITYID1,
		P_TRIGGER_ENTITYID2,
	//E_SELF_DESTROY,
	//	P_SELF_DESTROY_ENTITYID,
	// ANIMATION EVENTS
	E_ANIMATION,
		P_ANIMATION_STATE,
	E_ENTITY_DIE,
		P_ENTITY_DIE,
	EP_TOTAL

};


#endif
#include <Pch.hpp>
#include "LevelManager.hpp"
#include "AtomEngine.hpp"
#include "core/Types.hpp"

extern AtomEngine ae;
extern bool menu_start;
extern bool menu_ingame;
extern bool menu_inprogress;

extern string musicTrackGame;
extern string musicTrackIntro;
extern ChannelID musicChannelID;
extern float musicVolumedB;


LevelManager::LevelManager()
{

}

void LevelManager::init()
{
	ae.addEventListener(EventID::E_COLLISION, [this](Event& e) {this->onEvent(e); });
	ae.addEventListener(EventID::E_TRIGGER, [this](Event& e) {this->onEvent(e); });
}


float LevelManager::lerp10(float a, float b, float t, float lo, float hi) {
	if (lo == hi) {
		return b;
	}
	t = (t - lo) / (hi - lo);
	float res = b * (1 - t) + a * (t);
	return res;
}

float LevelManager::lerp01(float a, float b, float t, float lo, float hi) {
	if (lo == hi) {
		return a;
	}
	t = (t - lo) / (hi - lo);
	float res = a * (1 - t) + b * (t);
	return res;
}

// every frame 
void LevelManager::update()
{
	//logic to move to next level automatically
	if ((levelTime != -1 && ae.getUptime() - levelStartTime > levelTime) || (level < COUNT_INTROS - 1 && screenByPass()))
	{
		loadNextLevel();
	}

	if (do_fade_in) {
		if (fadeIn() || screenByPass()) {
			level = next_level;
			level_alpha = 1.0f;
			do_fade_in = false;
			menu_inprogress = false;
			if (level >= COUNT_INTROS && level < ED_LEVELS) {
				ae.mAudioManager->stop(musicChannelID);
				musicChannelID = ae.play(musicTrackGame, ChannelGroupTypes::C_MUSIC, musicVolumedB, -1);
			}
			if (level == COUNT_INTROS-1 || level == 0) {
				ae.mAudioManager->stop(musicChannelID);
				musicChannelID = ae.play(musicTrackIntro, ChannelGroupTypes::C_MUSIC, musicVolumedB, -1);
			}
		}
	}
	else if (do_fade_out) {
		if (fadeOut() || screenByPass()) {
			ae.mSystemManager->getSystem<MoveToSystem>()->tags.clear();
			unload();
			
			load(next_level);
			ae.mCameraManager->setPosition(glm::vec2(0, 0));
			level_alpha = 0.0f;
			do_fade_out = false;
			do_fade_in = true;
		}
	}
	
}

bool LevelManager::screenByPass()
{
	return (ae.mInputManager->isKeyTriggered(ATOM_KEYCODE_LBUTTON)
		|| ae.mInputManager->isKeyTriggered(ATOM_KEYCODE_RBUTTON)
		|| ae.mInputManager->isKeyTriggered(ATOM_KEYCODE_SPACE)
		|| ae.mInputManager->isKeyTriggered(ATOM_KEYCODE_ESCAPE)
		|| ae.mInputManager->isKeyTriggered(ATOM_KEYCODE_RETURN)
		);
	
}

void LevelManager::onEvent(Event& e)
{
	//restart level
	if (e.getType() == EventID::E_COLLISION) {
		EntityID e1 = e.getParam<EntityID>(EventID::P_COLLISION_ENTITYID1);
		EntityID e2 = e.getParam<EntityID>(EventID::P_COLLISION_ENTITYID2);

		EntityID player = -1;
		EntityID deadzone = -1;

		if (ae.hasComponent<ControllerComponent>(e1))
		{
			player = e1;
			deadzone = e2;
		}
		else if (ae.hasComponent<ControllerComponent>(e2))
		{
			player = e2;
			deadzone = e1;
		}
		else
			return;

		if (ae.hasComponent<TagComponent>(deadzone) 
			&& ae.getComponent<TagComponent>(deadzone).tag == "DeadZone")
		{
			auto& health = ae.getComponent<HealthComponent>(player);
			if (!health.died)
			{
				//send die event
				Event e(EventID::E_ENTITY_DIE);
				e.setParam<EntityID>(EventID::P_ENTITY_DIE, player);
				ae.sendEvent(e);
			}
			health.died = true;
			health.health = 0;
		}

	}
	//enter next level
	else if (e.getType() == EventID::E_TRIGGER) {

		EntityID e1 = e.getParam<EntityID>(EventID::P_TRIGGER_ENTITYID1);
		EntityID e2 = e.getParam<EntityID>(EventID::P_TRIGGER_ENTITYID2);

		EntityID player = -1;
		EntityID trigger = -1;

		bool triggeredNextLevel = false;

		if (ae.hasComponent<ControllerComponent>(e1))
		{
			player = e1;
			trigger = e2;
		}
		else if (ae.hasComponent<ControllerComponent>(e2))
		{
			player = e2;
			trigger = e1;
		}
		else
		{
			return;
		}

		if (ae.hasComponent<LevelTriggerComponent>(trigger))
		{
			loadNextLevel();
		}
	}
}

void LevelManager::load(int level) {

	//level_alpha = 1.0f;
	fade_out_timer = FADE_OUT_TIME;
	fade_in_timer = FADE_IN_TIME;

	//levelstring = string("Atom/res/levels/Level") + std::to_string(level) + string("_Settings.levelJson");
	levelstring = string("Atom/res/levels/") + levelPaths[level];
	std::ifstream in(levelstring);
	ordered_json json;
	in >> json;
	in.close();
	this->level = level;
	//std::string mapName = levelJson["Map"];
	this->load(levelstring);

	levelStartTime = ae.getUptime();

	// if last level go back to main menu
	if (level == TOTAL_LEVELS-1)
	{
		loadLevel(COUNT_INTROS-1);
	}
}

void LevelManager::startGame()
{
	loadDefaultFile();
	ae.mLevelManager->loadLevel(0);
}



void LevelManager::loadNextLevel()
{
	loadLevel(level + 1);
}

void LevelManager::loadPreviosLevel()
{
	loadLevel(level - 1);
}

void LevelManager::loadLevel(int l)
{
	next_level = l;
	do_fade_out = true;
	do_fade_in = false;
}

bool LevelManager::fadeOut()
{
	if (fade_out_timer > 0) {
		level_alpha = lerp10(level_alpha_end, level_alpha, ae.dt, 0.0f, fade_out_timer);
		fade_out_timer -= ae.dt;
		return false;
	}
	else {
		return true;
	}
}

// load level
void LevelManager::load(string filepath) {
	string defaultFile = string("Atom/res/levels/") + "Level_Default.json";
	std::ifstream in2(defaultFile);
	ordered_json defaultJson;
	in2 >> defaultJson;

	std::ifstream in(filepath);
	ordered_json levelJson;
	in >> levelJson;
	// tilemap
	if (!filepath.empty()) {
		std::string maploc = levelJson["Map"];
		int rows = -1, cols = -1, wallid = -1;
		float tilesize_x = 0.0f;
		float tilesize_y = 0.0f;
		std::ifstream inmap(maploc);
		ordered_json mapJson;
		inmap >> mapJson;

		if (mapJson["time"].is_null())
			levelTime = -1;
		else
			levelTime = mapJson["time"];

		rows = mapJson["grid"].size();
		cols = mapJson["grid"][0].size();
		//wallid = mapJson["wall_id"];

		//todo cache map details into <unordered map> for optimzation here

		// size normalized to [0,800]
		tilesize_x = (float)mapJson["tilesize_x"] * 2 / ae.mGraphicsManager->GetLevelWidth();
		tilesize_y = (float)mapJson["tilesize_y"] * 2 / ae.mGraphicsManager->GetLevelWidth();

		//merge along row
		int mergeStartIndex = -1;
		float wallHeight = 1, wallWidth = 1;

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				string gridID = mapJson["grid"][i][j];
				EntityID entityID;

				bool emptyObject = true;

				if (levelJson[gridID].is_null() && defaultJson[gridID].is_null())
					emptyObject = true;
				else
					emptyObject = false;

				if (!emptyObject)
				{
					ordered_json objectJson;
					if (!levelJson[gridID].is_null())
						objectJson = levelJson[gridID];
					else
						objectJson = defaultJson[gridID];

					ae.deserializeEntity(objectJson, entityID);

					auto& t = ae.getComponent<TransformComponent>(entityID);
					t.position = glm::vec3{
						-1.0f + j * tilesize_x + tilesize_x / 2.0f,
						1.0f - i * tilesize_y - tilesize_y / 2.0f,
						0.0f
					};
					t.scale = glm::vec3{
						tilesize_x * t.scale.x,
						tilesize_y * t.scale.y,
						0.0f
					};

					if (ae.hasComponent<PhysicsBodyComponent>(entityID))
					{
						auto& p = ae.getComponent<PhysicsBodyComponent>(entityID);
						p.prevPositionX = t.position.x;
						p.prevPositionY = t.position.y;
						p.prevScaleX = t.scale.x;
						p.prevScaleY = t.scale.y;
					}
				}

				//for merging of phys body
				//if not null and is wall
				if (!emptyObject && ae.hasComponent<TagComponent>(entityID) && ae.getComponent<TagComponent>(entityID).tag == "wall")
				{
					if (mergeStartIndex == -1)
					{
						mergeStartIndex = j;
					}
					auto& t = ae.getComponent<TransformComponent>(entityID);
					wallHeight = t.scale.y;
					wallWidth = t.scale.x;
				}
				//if has gap or end of row->merge
				if (mergeStartIndex != -1 && (j == cols - 1 || emptyObject))
				{
					if (j == cols - 1)
					{
						j++;
					}

					//merge from index to prev item
					EntityID mergedPhysicsBody = ae.createEntity();
					TransformComponent mergedTransform;
					float gridWidth = j - mergeStartIndex;
					/*if (gridWidth == 1)
						gridWidth = wallWidth;*/
					float positionX = gridWidth / 2.0 + mergeStartIndex - 0.5;
					mergedTransform.position = glm::vec3{
						-1.0f + positionX * tilesize_x + tilesize_x / 2.0f,
						1.0f - i * tilesize_y - tilesize_y / 2.0f,
						0.0f
					};
					mergedTransform.scale = glm::vec3{
						gridWidth == 1 ? wallWidth : tilesize_x * gridWidth,
						wallHeight,
						0.0f
					};
					ae.addComponent(mergedPhysicsBody, mergedTransform);

					//RectangleComponent mergedRect;
					//mergedRect.color = glm::vec3(0, 1, 0);
					//addComponent(mergedPhysicsBody, mergedRect);

					ShapeComponent mergedShape;
					mergedShape.shapeType = ShapeType::AABB;
					ae.addComponent(mergedPhysicsBody, mergedShape);

					PhysicsBodyComponent mergedBody;
					mergedBody.mass = 1.0;
					mergedBody.staticBody = true;
					mergedBody.isTrigger = false;
					mergedBody.frictionless = false;
					mergedBody.gravity = false;
					mergedBody.prevPositionX = mergedTransform.position.x;
					mergedBody.prevPositionY = mergedTransform.position.y;
					mergedBody.prevScaleX = mergedTransform.scale.x;
					mergedBody.prevScaleY = mergedTransform.scale.y;
					ae.addComponent(mergedPhysicsBody, mergedBody);

					//reset index
					mergeStartIndex = -1;

				}
			}
		}

	}

	if(!levelJson["characters"].is_null())
		loadCharacters(levelJson["characters"]);

	in.close();
	in2.close();
}

void LevelManager::loadCharacters(string charloc)
{
	//string charloc = "Atom/res/levels/characters.json";
	std::ifstream inmap(charloc);
	ordered_json characterJson;
	inmap >> characterJson;

	// entities
	if (!characterJson["Entities"].is_null()) {
		for (auto& entityjson : characterJson["Entities"]) {
			EntityID entid;
			ae.deserializeEntity(entityjson, entid);
		}
	}
}

bool LevelManager::fadeIn()
{
	if (fade_in_timer > 0.0f) {
		level_alpha = lerp01(level_alpha, 1.0f, ae.dt, 0.0f, fade_in_timer);
		fade_in_timer -= ae.dt;
		return false;
	}
	else {
		return true;
	}
}

// unload level
void LevelManager::unload() {
	std::vector<EntityID> toEject;
	for (auto& entity : ae.mEntityManager->mAllocdEntities) {
		toEject.push_back(entity);
	}
	for (auto& entity : toEject) {
		ae.destroyEntity(entity);
	}
	ae.mEntityManager->mLivingEntityCount = 0;
}

// save
void LevelManager::save() {
	string filepath = "last_checkpoint.json";

	std::ofstream out(filepath);
	ordered_json j;
	j["Entities"] = ordered_json::array();
	for (auto entity : ae.mEntityManager->mAllocdEntities) {
		ordered_json json_ent;
		ae.serializeEntity(json_ent, entity);
		j["Entities"].push_back(json_ent);
	}
	out << std::setw(4) << j;
}

void LevelManager::loadDefaultFile(){
	levelPaths = std::vector<string>();
	
	string filepath = "Atom/res/levels/Level_Default.json";

	std::ifstream in(filepath);
	ordered_json j;
	in >> j;
	levelPaths = j["levels"].get<std::vector<string>>();

	in.close();
}

void LevelManager::restartWholeGame()
{
	loadLevel(COUNT_INTROS);
}

void LevelManager::restartCurrentLevel()
{
	loadLevel(level);
}

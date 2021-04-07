#include <Pch.hpp>
#include "LevelManager.hpp"
#include "AtomEngine.hpp"

extern AtomEngine ae;


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
		return a;
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



/*

	fade time = 4.0f
	T1(30) T2(40)

	playint T1 ----------|[1.0]->[0.0]@T1 (2sec) [0.0]->[1.0]@T2
						 --,--playing T2 ----------...


	fade10

	fade_out_timer 2.0f

	lo,hi : 30,40 [10 -> 1]
				[2 -> 0.2]

	t : 32
	t = (t - lo) / (hi - lo); [0,1]

	t = 0.2

	res = b(1-t) + a(t);

	res (0.8)


	lerp10(a,b,,lo,hi){
		
	}

	lerp01(){

	}

	L1------------|[1.0]->[0.0]@T1 : alpha
				  --
	L2				[0.0]->[1.0]@T2 : alpha-----------
*/


// every frame 
void LevelManager::update()
{
	//logic to move to next level automatically
	if (levelTime != -1 && ae.getUptime() - levelStartTime > levelTime)
	{
		enterNextLevel = true;
	}

	if (restartGame)
	{
		unload();
		level = 2;
		if (level < 2)
			level = 2;
		load(level);
		level_alpha = 0.0f;
		fade_in_level = true;
		restartGame = false;
	}
	else if (enterPreviousLevel)
	{
		if (fade_out_timer > 0 && !screenByPass()) {
			level_alpha = lerp10(level_alpha_end, level_alpha, ae.dt, 0.0f, fade_out_timer);
			fade_out_timer -= ae.dt;
			//std::cout << "level alpha : " << level_alpha << std::endl;
		}
		else {
			unload();
			level--;
			if (level < 2)
				level = 2;
			load(level);
			level_alpha = 0.0f;
			fade_in_level = true;
			enterPreviousLevel = false;
		}
	}
	else if (enterNextLevel )
	{

		if (fade_out_timer > 0 && !screenByPass()) {
			level_alpha = lerp10(level_alpha_end, level_alpha, ae.dt, 0.0f, fade_out_timer);
			fade_out_timer -= ae.dt;
		}
		else {
			unload();
			level++;
			load(level);
			level_alpha = 0.0f;
			fade_in_level = true;
			enterNextLevel = false;
			//std::cout << "level alpha : " << level_alpha << std::endl;
		}
	}
	else if (restartLevel)
	{
		//if (fade_out_timer > 0) {
		//	level_alpha = lerp10(level_alpha_end, level_alpha, ae.dt, 0.0f, fade_out_timer);
		//	fade_out_timer -= ae.dt;
		//	//std::cout << "level alpha : " << level_alpha << std::endl;
		//}
		//else 
		{
			unload();
			load(level);
			level_alpha = 0.0f;
			fade_in_level = true;
			restartLevel = false;

		}
	}
	else if (fade_in_level) {
		if (fade_in_timer > 0.0f) {
			level_alpha = lerp01(level_alpha, 1.0f,ae.dt, 0.0f, fade_in_timer);
			fade_in_timer -= ae.dt;
			std::cout << "level alpha fade in : " << level_alpha << std::endl;
		}
		else {
			fade_in_level = false;
		}
	}

	//reset level status




}

bool LevelManager::screenByPass()
{
	return (ae.mInputManager->isKeyPressed(VK_LBUTTON)
		|| ae.mInputManager->isKeyPressed(VK_RBUTTON)
		|| ae.mInputManager->isKeyPressed(VK_SPACE)
		|| ae.mInputManager->isKeyPressed(VK_ESCAPE)
		|| ae.mInputManager->isKeyPressed(VK_RETURN)
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
			restartLevel = true;
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
			EntityID& characterEntered = ae.getComponent<LevelTriggerComponent>(trigger).characterEntered;
			//if both distinct char entered 
			if (characterEntered != -1 && characterEntered != player)
				enterNextLevel = true;
			else
				characterEntered = player;
		}
	}
}

void LevelManager::load(int level) {

	level_alpha = 1.0f;
	fade_out_timer = 3.0f;
	fade_in_timer = 0.5f;

	levelstring = string("Atom/res/levels/Level") + std::to_string(level) + string("_Settings.json");
	std::ifstream in(levelstring);
	ordered_json json;
	in >> json;
	in.close();
	this->level = level;
	//std::string mapName = json["Map"];
	this->load(levelstring);

	levelStartTime = ae.getUptime();

	if (level == 15)
	{
		//UI: restart game
		ae.mIsPaused = true;
		ae.mUIManager->checkRestartGame = true;
	}
}

void LevelManager::startGame()
{
	load(13);
	level_alpha = 0.0f;
}

void LevelManager::loadNextLevel()
{
	enterNextLevel = true;
}

void LevelManager::loadPreviosLevel()
{
	enterPreviousLevel = true;
}

// load level
void LevelManager::load(string filepath) {
	std::ifstream in(filepath);
	ordered_json json;
	in >> json;
	// tilemap
	if (!filepath.empty()) {
		std::string maploc = json["Map"];
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
		tilesize_x = (float)mapJson["tilesize_x"] * 2 / SCREEN_WIDTH;
		tilesize_y = (float)mapJson["tilesize_y"] * 2 / SCREEN_HEIGHT;

		//merge along row
		int mergeStartIndex = -1;
		float wallHeight = 1, wallWidth = 1;

		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				string gridID = mapJson["grid"][i][j];
				EntityID entityID;
				if (!json[gridID].is_null())
				{
					ordered_json objectJson = json[gridID];
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
				if (!json[gridID].is_null() && ae.hasComponent<TagComponent>(entityID) && ae.getComponent<TagComponent>(entityID).tag == "wall")
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
				if (mergeStartIndex != -1 && (j == cols - 1 || json[gridID].is_null()))
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

	loadCharacters();

	in.close();
}

void LevelManager::loadCharacters()
{
	if (level > 1 && level < 10) {
		string charloc = "Atom/res/levels/characters.json";
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

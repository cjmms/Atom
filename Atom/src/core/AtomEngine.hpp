/*
* @file		AtomEngine.hpp
* @author	Abhikalp Unakal
* @brief	Core Engine API
* @date		2021-01-26
*/

#ifndef ATOMENGINE_HPP
#define ATOMENGINE_HPP

// ------------------------------------INCLUDES---------------------------------------------
#include "utils/Log.hpp"
#include "core/ChrononManager.hpp"
#include "core/Event.hpp"
#include "core/EventManager.hpp"
#include "core/EntityManager.hpp"
#include "core/ComponentManager.hpp"
#include "core/System.hpp"
#include "core/SystemManager.hpp"
#include "core/GraphicsManager.hpp"
#include "core/InputManager.hpp"
#include "core/AudioManager.hpp"
#include "core/ResourceManager.hpp"
#include "core/UIManager.hpp"
#include "core/Types.hpp"
#include "components/AllComponents.hpp"

#include "systems/ControllerSystem.hpp"
#include "systems/DamageSystem.hpp"
#include "systems/PhysicsSystem.hpp"
#include "systems/RectangleRenderSystem.hpp"
#include "systems/ShootSystem.hpp"
#include "systems/HealthRenderSystem.hpp"
#include "systems/HealthSystem.hpp"

// ------------------------------------ATOM ENGINE---------------------------------------------

extern FMOD_VECTOR listener_position;
extern FMOD_VECTOR listener_fwd;
extern FMOD_VECTOR listener_up;
extern float listener_step;

class AtomEngine {
public:
	inline void init() {



		mChrononManager = std::make_unique<ChrononManager>();
		mEntityManager = std::make_unique<EntityManager>();
		mComponentManager = std::make_unique<ComponentManager>();
		mGraphicsManager = std::make_unique<GraphicsManager>();
		mSystemManager = std::make_unique<SystemManager>();
		mEventManager = std::make_unique<EventManager>();
		mResourceManager = std::make_unique<ResourceManager>();
		mInputManager = std::make_unique<InputManager>();
		mAudioManager = std::make_unique<AudioManager>();
		mUIManager = std::make_unique<UIManager>();

		dt = 0.0;

		mChrononManager->setMaxFPS(FPS);
		mGraphicsManager->init();
		mUIManager->init(mGraphicsManager->getWindow());
		mResourceManager->init();
		mSystemManager->init();
		mInputManager->init();
		mAudioManager->init();

		mIsRunning = true;

		// TODO : move all this registration and init code into level manager 

		// register all components 
		registerComponent<TagComponent>();
		registerComponent<RectangleComponent>();
		registerComponent<TransformComponent>();
		registerComponent<PhysicsBodyComponent>();
		registerComponent<ShapeComponent>();
		registerComponent<ControllerComponent>();
		registerComponent<HealthComponent>();
		registerComponent<ShootComponent>();
		registerComponent<DamageComponent>();

		// register all systems
		registerSystem<RectangleRenderSystem>();
		registerSystem<PhysicsSystem>();
		registerSystem<ControllerSystem>();
		registerSystem<ShootSystem>();
		registerSystem<DamageSystem>();
		registerSystem<HealthSystem>();
		registerSystem<HealthRenderSystem>();


		// set archetypes
		{
			// this is a bitset denoting the system archetye
			Archetype typeRectangleRender;
			typeRectangleRender.set(getComponentType<RectangleComponent>());
			typeRectangleRender.set(getComponentType<TransformComponent>());
			setSystemArchetype<RectangleRenderSystem>(typeRectangleRender);

			Archetype typePhysics;
			typePhysics.set(getComponentType<TransformComponent>());
			typePhysics.set(getComponentType<PhysicsBodyComponent>());
			typePhysics.set(getComponentType<ShapeComponent>());
			setSystemArchetype<PhysicsSystem>(typePhysics);

			Archetype typeController;
			typeController.set(getComponentType<ControllerComponent>());
			typeController.set(getComponentType<PhysicsBodyComponent>());
			typeController.set(getComponentType<TransformComponent>());
			typeController.set(getComponentType<ShootComponent>());
			setSystemArchetype<ControllerSystem>(typeController);

			Archetype typeShoot;
			typeShoot.set(getComponentType<ShootComponent>());
			typeShoot.set(getComponentType<TransformComponent>());
			setSystemArchetype<ShootSystem>(typeShoot);

			Archetype typeDamage;
			typeDamage.set(getComponentType<DamageComponent>());
			setSystemArchetype<DamageSystem>(typeDamage);

			Archetype typeHealth;
			typeHealth.set(getComponentType<HealthComponent>());
			setSystemArchetype<HealthSystem>(typeHealth);

			Archetype typeHealthRender;
			typeHealthRender.set(getComponentType<TransformComponent>());
			typeHealthRender.set(getComponentType<HealthComponent>());
			setSystemArchetype<HealthRenderSystem>(typeHealthRender);


		}
		// reinit systems because archetypes changed 
		initSystem();


	}
	inline void update() {
		startFrame();

		mInputManager->update();
		mEventManager->update();
		mSystemManager->update();
		mUIManager->update();
		mGraphicsManager->update();
		mResourceManager->update();
		mAudioManager->update();
		
		endFrame();
	}

	inline void onEvent(Event& e) {
		mUIManager->onEvent(e);
		mGraphicsManager->onEvent(e);
		mResourceManager->onEvent(e);
		mSystemManager->onEvent(e);
		mAudioManager->onEvent(e);
	}


	// Essential helpers to expose engine api 
	// ChrononManager
	inline void startFrame() {
		mChrononManager->startframe();
	}
	inline void endFrame() {
		mChrononManager->endFrame();
		dt = mChrononManager->updatedt();
	}
	inline double getFPS() {
		return mChrononManager->getFPS();
	}
	inline void setMaxFPS(unsigned int maxfps) {
		mChrononManager->setMaxFPS(maxfps);
	}
	inline double getUptime() {
		return mChrononManager->getUptime();
	}
	inline long long getTotalFrames() {
		return mChrononManager->getTotalFrames();
	}

	// AudioManager
	inline FMOD::Sound* loadSound(string audioloc,
		FMOD_MODE _mode = FMOD_DEFAULT | FMOD_3D | FMOD_LOOP_OFF | FMOD_CREATECOMPRESSEDSAMPLE | FMOD_3D_INVERSEROLLOFF,
		FMOD_CREATESOUNDEXINFO* _exinfo = NULL
	) {
		return mAudioManager->loadSound(audioloc, _mode, _exinfo);
	}

	inline void unloadSound(string audioloc) {
		return mAudioManager->unloadSound(audioloc);
	}

	inline ChannelID play(string audioloc, ChannelGroupTypes cgtype, float volumedB = 0.0f) {
		return mAudioManager->play(audioloc, cgtype, volumedB);
	}
	
	inline float getVolumedB(ChannelID channelid) {
		return mAudioManager->getChannelVolumedB(channelid);
	}

	inline void setVolume(ChannelID channelid, float volumedB) {
		mAudioManager->setChannelVolumedB(channelid, std::clamp(volumedB, 0.0f, 1.0f));
	}

	inline void listener3DSetXOffset(float offset) {
		listener_position.x = 0.0f + offset;
		mAudioManager->mCoreSystem->set3DListenerAttributes(0, &listener_position, 0, &listener_fwd, &listener_up);
	}

	inline void listener3DSetYOffset(float offset) {
		listener_position.y = 0.0f + offset;
		mAudioManager->mCoreSystem->set3DListenerAttributes(0, &listener_position, 0, &listener_fwd, &listener_up);
	}
	
	// GraphicsManager
	inline void printGraphicsInfo() {
		mGraphicsManager->printInfo();
	}
	inline string getGraphicsWindowTitle() {
		return mGraphicsManager->getWindowTitle();
	}
	inline void setGraphicsWindowTitle(string s) {
		mGraphicsManager->setWindowTitle(s);
	}
	inline void resizeGraphicsWindow(unsigned int w, unsigned int h) {
		mGraphicsManager->resize(w, h);
	}

	// ResourceManager
	template <typename T>
	inline T& getOrLoadResource(string resloc) {
		return mResourceManager->load<T>(resloc);
	}

	template <typename T>
	inline void unloadReource(string resloc) {
		return mResourceManager->unload(string res);
	}

	bool resourceExsists(string resloc) {
		return mResourceManager->exists(resloc);
	}

	// Entity
	inline EntityID createEntity() {
		return mEntityManager->createEntity();
	}
	inline void destroyEntity(EntityID entity) {
		mEntityManager->destroyEntity(entity);
		mComponentManager->entityDestroyed(entity);
		mSystemManager->entityDestroyed(entity);
	}
	template <typename T>
	inline bool hasComponent(EntityID entity) {
		const char* typeName = typeid(T).name();
		ComponentID comid = mComponentManager->getComponentType<T>();
		return mEntityManager->hasComponent(entity, comid);
	}

	inline bool hasComponent(EntityID entity, ComponentID comid) {
		return mEntityManager->hasComponent(entity, comid);
	}

	// Component
	template<typename T>
	inline void registerComponent() {
		mComponentManager->registerComponent<T>();
	}
	template<typename T>
	inline void addComponent(EntityID entity, T component) {
		mComponentManager->addComponent<T>(entity, component);
		auto atype = mEntityManager->getArchetype(entity);
		atype.set(mComponentManager->getComponentType<T>(), true);
		mEntityManager->setArchetype(entity, atype);
		mSystemManager->entityArchetypeChanged(entity, atype);
	}
	template<typename T>
	inline void removeComponent(EntityID entity) {
		mComponentManager->removeComponent<T>(entity);
		auto atype = mEntityManager->getArchetype(entity);
		atype.set(mComponentManager->getComponentType<T>(), false);
		mEntityManager->setArchetype(entity, atype);
		mSystemManager->entityArchetypeChanged(entity, atype);
	}
	template<typename T>
	inline T& getComponent(EntityID entity) {
		return mComponentManager->getComponent<T>(entity);
	}
	template<typename T>
	inline ComponentID getComponentType() {
		return mComponentManager->getComponentType<T>();
	}

	// System
	void initSystem() {
		mSystemManager->init();
	}
	template<typename T>
	inline std::shared_ptr<T> registerSystem() {
		return mSystemManager->registerSystem<T>();
	}
	template<typename T>
	inline void setSystemArchetype(Archetype atype) {
		mSystemManager->setArchetype<T>(atype);
	}

	// Event 
	inline void addEventListener(EventID eventId, std::function<void(Event&)> const& listener) {
		mEventManager->addListener(eventId, listener);
	}
	inline void removeEventListener(EventID eventId, std::function<void(Event&)> const& listener) {
		mEventManager->removeListener(eventId, listener);
	}
	inline void sendEvent(Event& event) {
		mEventManager->sendEvent(event);
	}
	inline void sendEvent(EventID eventId) {
		mEventManager->sendEvent(eventId);
	}
	inline void onTimedEvent(Event& e) {

	}

	// Serde
	// Write
	template <typename T>
	inline void serializeComponent(ordered_json& j, const EntityID& entity) {
		if (hasComponent<T>(entity)) {
			const auto& component = getComponent<T>(entity);
			to_json(j, component);
		}
	}
	inline void serializeEntity(ordered_json& j, const EntityID& entity) {
		j["EntityID"] = entity;
		serializeComponent<TagComponent>(j["TagComponent"], entity);
		serializeComponent<TransformComponent>(j["TransformComponent"], entity);
		serializeComponent<RectangleComponent>(j["RectangleComponent"], entity);
		serializeComponent<ShapeComponent>(j["ShapeComponent"], entity);
		serializeComponent<PhysicsBodyComponent>(j["PhysicsBodyComponent"], entity);
		serializeComponent<ControllerComponent>(j["ControllerComponent"], entity);
		serializeComponent<ShootComponent>(j["ShootComponent"], entity);
		serializeComponent<HealthComponent>(j["HealthComponent"], entity);
	}
	// Read
	template <typename T>
	inline void deserializeComponent(ordered_json& j, EntityID& entity) {
		T component;
		if (!j.is_null()) {
			from_json(j, component);
			addComponent(entity, component);
		}
	}
	inline void deserializeEntity(ordered_json& j, EntityID& entity) {
		entity = createEntity();
		if (j["EntityID"].is_null() || j["EntityID"] != entity) {
			j["EntityID"] = entity;
		}
		deserializeComponent<TagComponent>(j["TagComponent"], entity);
		deserializeComponent<TransformComponent>(j["TransformComponent"], entity);
		deserializeComponent<RectangleComponent>(j["RectangleComponent"], entity);
		deserializeComponent<ShapeComponent>(j["ShapeComponent"], entity);
		deserializeComponent<PhysicsBodyComponent>(j["PhysicsBodyComponent"], entity);
		deserializeComponent<ControllerComponent>(j["ControllerComponent"], entity);
		deserializeComponent<ShootComponent>(j["ShootComponent"], entity);
		deserializeComponent<HealthComponent>(j["HealthComponent"], entity);
	}

	inline float random() {
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0, 1);//uniform distribution between 0 and 1
		return (float)dis(gen);
	}

	inline void createTile(glm::vec3 pos, glm::vec3 color, glm::vec3 scale) {
		EntityID tile = createEntity();
		RectangleComponent rc;

		addComponent<TagComponent>(tile, TagComponent{
			"tile"
			});
		addComponent<RectangleComponent>(tile, RectangleComponent{
			color,
			false,
			""
			});
		addComponent<TransformComponent>(tile, TransformComponent{
			pos,
			glm::vec3{0.0f,0.0f,0.0f},
			scale,
			glm::mat4(1)
			});
		addComponent<ShapeComponent>(tile, ShapeComponent{
			ShapeType::AABB
			});
		addComponent<PhysicsBodyComponent>(tile, PhysicsBodyComponent{
			1.0f,
			true
		});
	}

	// load level
	inline void load(string filepath) {
		std::ifstream in(filepath);
		ordered_json j;
		in >> j;
		// tilemap
		if (!j["Map"].is_null()) {
			string maploc = j["Map"];
			int rows=-1, cols=-1, wallid=-1;
			float tilesize_x = 0.0f;
			float tilesize_y = 0.0f;
			std::ifstream inmap(maploc);
			ordered_json jm;
			inmap >> jm;
			rows = jm["grid"].size();
			cols = jm["grid"][0].size();
			wallid = jm["wall_id"];
			
			// size normalized to [0,800]
			tilesize_x = (float)jm["tilesize_x"]*2/SCREEN_WIDTH;
			tilesize_y = (float)jm["tilesize_y"]*2/SCREEN_HEIGHT; 
			for (int i = 0; i < rows; ++i) {
				for (int j = 0; j < cols; ++j) {
					if (jm["grid"][i][j] == wallid) {
						createTile(
							glm::vec3{-1.0f + j * tilesize_x + tilesize_x / 2.0f,
								1.0f - i * tilesize_y - tilesize_y/2.0f,
								0.0f },
							glm::vec3{ random(),random(),random() },
							glm::vec3{tilesize_x,tilesize_y,0.0f}
						);
					}
				}
			}
		}

		// entities
		if (!j["Entities"].is_null()) {
			for (auto& entityjson : j["Entities"]) {
				EntityID entid;
				deserializeEntity(entityjson, entid);
			}
		}
		in.close();
	}
	// unload level
	inline void unload() {
		std::vector<EntityID> toEject;
		for (auto& entity : mEntityManager->mAllocdEntities) {
			toEject.push_back(entity);
		}
		for (auto& entity : toEject) {
			destroyEntity(entity);
		}
		mEntityManager->mLivingEntityCount = 0;
	}
	// save
	void save(string filepath) {
		std::ofstream out(filepath);
		ordered_json j;
		j["Entities"] = ordered_json::array();
		for (auto entity : mEntityManager->mAllocdEntities) {
			ordered_json json_ent;
			serializeEntity(json_ent, entity);
			j["Entities"].push_back(json_ent);
		}
		out << std::setw(4) << j;
	}

	// shutdown
	void shutdown() {
		mAudioManager.reset();
		mInputManager.reset();
		mResourceManager.reset();
		mEventManager.reset();
		mSystemManager.reset();
		mUIManager.reset();
		mGraphicsManager.reset();
		mComponentManager.reset();
		mEntityManager.reset();
		mChrononManager.reset();
	}

public:
	double dt;
	bool mIsRunning;

	std::unique_ptr<ChrononManager> mChrononManager;
	std::unique_ptr<EntityManager> mEntityManager;
	std::unique_ptr<ComponentManager> mComponentManager;
	std::unique_ptr<SystemManager> mSystemManager;
	std::unique_ptr<EventManager> mEventManager;
	std::unique_ptr<GraphicsManager> mGraphicsManager;
	std::unique_ptr<ResourceManager> mResourceManager;
	std::unique_ptr<InputManager> mInputManager;
	std::unique_ptr<AudioManager> mAudioManager;
	std::unique_ptr<UIManager> mUIManager;
};

#endif // !ATOMENGINE_HPP

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
#include "core/LevelManager.hpp"
#include "core/Types.hpp"
#include "core/CameraManager.hpp"
#include "components/AllComponents.hpp"

// ------------------------------------ATOM ENGINE---------------------------------------------
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
		mCameraManager = std::make_unique<CameraManager>();
		mLevelManager = std::make_unique<LevelManager>();

		dt = 0.0;

		mChrononManager->setMaxFPS(FPS);
		mGraphicsManager->init();
		mResourceManager->init();
		mSystemManager->init();
		mInputManager->init();
		mAudioManager->init();
		mCameraManager->init();
		mLevelManager->init();

		mIsRunning = true;
	}
	inline void update() {
		startFrame();

		mInputManager->update();
		mEventManager->update();
		mSystemManager->update();
		mGraphicsManager->update();
		mResourceManager->update();
		mAudioManager->update();
		mCameraManager->update();
		mLevelManager->update();

		endFrame();
	}

	inline void onEvent(Event& e) {
		mGraphicsManager->onEvent(e);
		mResourceManager->onEvent(e);
		mSystemManager->onEvent(e);
		mAudioManager->onEvent(e);
		mCameraManager->onEvent(e);
		mLevelManager->onEvent(e);
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
	}

	// load level
	inline void load(string filepath) {
		std::ifstream in(filepath);
		ordered_json j;
		in >> j;
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
		mCameraManager.reset();
		mAudioManager.reset();
		mInputManager.reset();
		mResourceManager.reset();
		mEventManager.reset();
		mSystemManager.reset();
		mGraphicsManager.reset();
		mComponentManager.reset();
		mEntityManager.reset();
		mChrononManager.reset();
		mLevelManager.reset();
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
	std::unique_ptr<CameraManager> mCameraManager;
	std::unique_ptr<LevelManager> mLevelManager;
};

#endif // !ATOMENGINE_HPP

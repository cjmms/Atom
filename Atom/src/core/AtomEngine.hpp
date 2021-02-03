/*
* @file		AtomEngine.hpp
* @author	Abhikalp Unakal
* @brief	Core Engine API
* @date		2021-01-26
*/

#ifndef ATOMENGINE_HPP
#define ATOMENGINE_HPP

// core
#include "core/ChrononManager.hpp"
#include "core/Event.hpp"
#include "core/EventManager.hpp"
#include "core/EntityManager.hpp"
#include "core/ComponentManager.hpp"
#include "core/System.hpp"
#include "core/SystemManager.hpp"
#include "core/GraphicsManager.hpp"
#include "core/InputManager.hpp"
#include "core/ResourceManager.hpp"
#include "core/Types.hpp"

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

		dt = 0.0;

		mChrononManager->setMaxFPS(FPS);
		mGraphicsManager->init();
		mResourceManager->init();
		mSystemManager->init();
		mInputManager->init();

		mIsRunning = true;
	}
	inline void update() {
		startFrame();

		mEventManager->update();
		mSystemManager->update();
		mGraphicsManager->update();
		mResourceManager->update();
		mInputManager->update();

		endFrame();
	}

	inline void onEvent(Event& e) {
		mGraphicsManager->onEvent(e);
		mResourceManager->onEvent(e);
		mSystemManager->onEvent(e);
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
		return mResourceManager->get<T>(resloc);
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
};



#endif // !ATOMENGINE_HPP

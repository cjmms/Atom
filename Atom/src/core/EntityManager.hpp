/*
* @file		EntityManager.hpp
* @author	Abhikalp Unakal
* @brief	EntityManager - class to deal with creation,destruction, setting Archetype, and hasComponent queries on a particular entity 
* @date		2021-01-22
*/

#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "core/Types.hpp"

class Event;

class EntityManager {
public:
	EntityManager();

	EntityID createEntity();

	void destroyEntity(EntityID entity);

	void setArchetype(EntityID entity, Archetype atype);

	Archetype getArchetype(EntityID entity);

	bool hasComponent(EntityID entity, ComponentID compid);

	void EnqueueDestroyEntity(EntityID entity);

	void update();

	void onEvent(Event& e);

public:
	std::deque<EntityID> mAvailableEntities{};
	std::set<EntityID> mAllocdEntities{};
	std::array<Archetype, MAX_ENTITIES> mArchetypes{};
	uint32_t mLivingEntityCount{};

private:
	std::vector<EntityID> destroyList;
};

#endif
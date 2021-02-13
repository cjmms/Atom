/*
* @file		EntityManager.hpp
* @author	Abhikalp Unakal
* @brief	EntityManager - class to deal with creation,destruction, setting Archetype, and hasComponent queries on a particular entity 
* @date		2021-01-22
*/

#ifndef ENTITYMANAGER_HPP
#define ENTITYMANAGER_HPP

#include "Pch.hpp"
#include "limits.h"
#include "core/Types.hpp"
#include "utils/Log.hpp"

class EntityManager {
public:
	EntityManager() {
		for (EntityID entity = 0; entity < MAX_ENTITIES; ++entity) {
			mAvailableEntities.push_back(entity);
		}
	}
	EntityID createEntity() {
		assert(mLivingEntityCount < MAX_ENTITIES && "Entity Limit Exceeded");
		EntityID id = mAvailableEntities.front();
		mAllocdEntities.insert(id);
		mAvailableEntities.pop_front();
		++mLivingEntityCount;
		if (mLivingEntityCount == UINT32_MAX && mAvailableEntities.size() > 0) {
			mLivingEntityCount = 0;
		}
		ATOM_TRACE("[Entity ID: {}] Entity created", id);
		return id;
	}

	void destroyEntity(EntityID entity) {
		assert(entity < MAX_ENTITIES && "EntityID out of range.");
		mArchetypes[entity].reset();
		mAvailableEntities.push_back(entity);
		mAllocdEntities.erase(entity);
		--mLivingEntityCount;
		ATOM_TRACE("[Entity ID: {}] Entity destroyed", entity);
	}

	void setArchetype(EntityID entity, Archetype atype) {
		assert(entity < MAX_ENTITIES && "EntityID out of range.");
		mArchetypes[entity] = atype;
		ATOM_TRACE("[Entity ID: {}] Archetype changed", entity);
	}

	Archetype getArchetype(EntityID entity) {
		assert(entity < MAX_ENTITIES && "EntityID out of range.");
		return mArchetypes[entity];
	}

	bool hasComponent(EntityID entity, ComponentID compid) {
		return mArchetypes[entity].test(compid);
	}

public:
	std::deque<EntityID> mAvailableEntities{};
	std::set<EntityID> mAllocdEntities{};
	std::array<Archetype, MAX_ENTITIES> mArchetypes{};
	uint32_t mLivingEntityCount{};
};

#endif
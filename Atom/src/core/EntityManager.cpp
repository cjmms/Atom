/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
*
* @file		EntityManager.cpp
* @author	Abhikalp Unakal
* @brief	EntityManager - class to deal with creation,destruction, setting Archetype, and hasComponent queries on a particular entity
* @date		2021-01-22
*/

#include <Pch.hpp>
#include "limits.h"
#include "core/Types.hpp"
#include "utils/Log.hpp"
#include "EntityManager.hpp"
#include "core/AtomEngine.hpp"
#include "core/Event.hpp"

extern AtomEngine ae;

EntityManager::EntityManager()
{
	//ae.addEventListener(EventID::E_SELF_DESTROY, [this](Event& e) {this->onEvent(e); });
	
	for (EntityID entity = 0; entity < MAX_ENTITIES; ++entity) {
		mAvailableEntities.push_back(entity);
	}
}

EntityID EntityManager::createEntity()
{
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

void EntityManager::destroyEntity(EntityID entity)
{
	assert(entity < MAX_ENTITIES && "EntityID out of range.");
	assert(mLivingEntityCount > 0);
	mArchetypes[entity].reset();
	mAvailableEntities.push_back(entity);
	mAllocdEntities.erase(entity);
	--mLivingEntityCount;
	ATOM_TRACE("[Entity ID: {}] Entity destroyed", entity);
}

void EntityManager::setArchetype(EntityID entity, Archetype atype) {
	assert(entity < MAX_ENTITIES && "EntityID out of range.");
	mArchetypes[entity] = atype;
	ATOM_TRACE("[Entity ID: {}] Archetype changed", entity);
}

Archetype EntityManager::getArchetype(EntityID entity) {
	assert(entity < MAX_ENTITIES && "EntityID out of range.");
	return mArchetypes[entity];
}

bool EntityManager::hasComponent(EntityID entity, ComponentID compid) {
	return mArchetypes[entity].test(compid);
}

void EntityManager::EnqueueDestroyEntity(EntityID entity)
{
	//O(n) operation, but the list should be small
	if (std::find(destroyList.begin(), destroyList.end(), entity) == destroyList.end())
		destroyList.push_back(entity);
}

void EntityManager::update()
{
	for (int i = destroyList.size() - 1; i >= 0; i--)
	{
		ae.destroyEntity(destroyList[i]);
	}
	destroyList.clear();
}

void EntityManager::onEvent(Event& e)
{
	//if (e.getType() == EventID::E_SELF_DESTROY) {
	//	EntityID entity = e.getParam<EntityID>(EventID::P_SELF_DESTROY_ENTITYID);
	//	EnqueueDestroyEntity(entity);
	//}
}

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
		mAvailableEntities.insert(entity);
	}
}

EntityID EntityManager::createEntity()
{
	assert(mLivingEntityCount < MAX_ENTITIES && "Entity Limit Exceeded");
	EntityID id = *mAvailableEntities.begin();
	mAllocdEntities.insert(id);
	mAvailableEntities.erase(mAvailableEntities.begin());
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
	mAvailableEntities.insert(entity);
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

/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		ComponentManager.hpp
* @author	Abhikalp Unakal
* @brief	ComponentContainer - class to pack and store components in a component allocd pool with packing for efficiency
* @date		2021-01-22
*/

#ifndef COMPONENTCONTAINER_HPP
#define COMPONENTCONTAINER_HPP

#include "Pch.hpp"
#include "Types.hpp"
#include "utils/Log.hpp"

class IComponentContainer {
public:
	virtual ~IComponentContainer() = default;
	virtual void entityDestroyed(EntityID entity) = 0;
};


template<typename T>
class ComponentContainer : public IComponentContainer {
public:
	void insert(EntityID entity, T component) {
		if (mCount == mComponentContainer.size()) {
			mComponentContainer.resize(mComponentContainer.size() * 2 + 1); // adding 1 to account for 0
		}
		assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() && "Component added to same entity more than once.");
		size_t newIndex = mCount;
		mEntityToIndexMap[entity] = newIndex;
		mIndexToEntityMap[newIndex] = entity;
		mComponentContainer[newIndex] = component;
		++mCount;
	}

	void remove(EntityID entity) {
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Removing non-existent component.");



		// Copy element at end into end where element got deleted to keep density
		size_t indexOfRemovedEntityID = mEntityToIndexMap[entity];
		size_t indexOfLastElement = mCount - 1;
		mComponentContainer[indexOfRemovedEntityID] = mComponentContainer[indexOfLastElement];

		// Update map
		EntityID entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
		mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntityID;
		mIndexToEntityMap[indexOfRemovedEntityID] = entityOfLastElement;

		mEntityToIndexMap.erase(entity);
		mIndexToEntityMap.erase(indexOfLastElement);
		mComponentContainer.pop_back();
		--mCount;

	}

	T& getData(EntityID entity) {
		assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() && "Retrieving non-existent component.");
		return mComponentContainer[mEntityToIndexMap[entity]];
	}

	void entityDestroyed(EntityID entity) override {
		if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()) {
			remove(entity);
		}
	}

private:
	std::vector<T> mComponentContainer = std::vector<T>();
	std::unordered_map<EntityID, size_t> mEntityToIndexMap{};
	std::unordered_map<size_t, EntityID> mIndexToEntityMap{};
	size_t mCount{0};
};

#endif
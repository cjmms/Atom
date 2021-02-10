/*
* @file		ResourceManager.hpp
* @author	Abhikalp Unakal
* @brief	ResourceManager - class to load resources from system - platform dependent code
* @date		2021-01-22
*/

#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include "Pch.hpp"
#include "core/Types.hpp"
#include "core/Event.hpp"
#include "utils/ResourceLoader.hpp"

class ResourceManager {
public:
	void init() {
		mNextRes = 0;
	}
	void onEvent(Event& e) {

	}
	void update() {

	}

	bool exists(string resloc) {
		return (mResID.count(resloc) > 0);
	}

	template <typename T>
	T& load(string resloc) {
		ResourceID id;
		if (mResID.count(resloc) > 0) {
			id = mResID[resloc];
			return std::any_cast<T&>(mResPool[id]);
		}

		mResID[resloc] = mNextRes;
		T res;
		loadResource(res, resloc);
		mResPool[mNextRes] = res;
		++mNextRes;
		return std::any_cast<T&>(mResPool[mNextRes - 1]);
	}

	template <typename T>
	void unload(string resloc) {
		if (mResID.count(resloc) > 0) {
			ResourceID id = mResID[resloc];
			T& res = mResPool[id];
			unloadResource(res);
			mResPool.erase(mResID[resloc]);
			mResID.erase(resloc);
		}
		ATOM_WARN("ResourceManager : unload : No such resource");
	}
private:
	std::unordered_map<std::string, ResourceID> mResID;
	std::unordered_map<ResourceID, std::any> mResPool;
	ResourceID mNextRes;
};
#endif // !RESOURCEMANAGER_HPP
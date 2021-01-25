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

// if windows
#ifdef _WIN64
#include "platform/windows/ResourceLoader.hpp"
#endif

// if macos
#ifdef __APPLE__
#include "platform/macos/ResourceLoader.hpp"
#endif


class ResourceManager {
public:
	void init() {
		mNextRes = 0;
	}
	void onEvent(Event& e) {

	}
	void update() {

	}
	template <typename T>
	T& get(std::string resloc) {
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
private:
	std::unordered_map<std::string, ResourceID> mResID;
	std::unordered_map<ResourceID, std::any> mResPool;
	ResourceID mNextRes;

};
#endif // !RESOURCEMANAGER_HPP
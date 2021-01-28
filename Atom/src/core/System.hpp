/*
* @file		System.hpp
* @author	Abhikalp Unakal
* @brief	System base class 
* @date		2021-01-27
*/


#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include "Pch.hpp"
#include "core/Types.hpp"
#include "core/Event.hpp"

class System {
public:
	virtual void init() {

	}
	virtual void update() {

	}
	virtual void onEvent(Event& e) {

	}
public:
	std::set<EntityID> mEntities;
	bool mInit = false;
};

#endif

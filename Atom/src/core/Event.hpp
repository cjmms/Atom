/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
* 
* @file		Event.hpp
* @author	Abhikalp Unakal
* @brief	Base class an Event
* @date		2021-01-12
*/

#ifndef EVENT_HPP
#define EVENT_HPP
#include <Pch.hpp>
#include "Types.hpp"

class Event {
public:
	Event() = delete;

	explicit Event(EventID type) : mType(type) {

	}

	template<typename T>
	void setParam(EventID id, T value) {
		mData[id] = value;
	}

	template<typename T>
	T getParam(EventID id) {
		return std::any_cast<T>(mData[id]);
	}

	EventID getType() const {
		return mType;
	}

	string getTypeName() const {
		return typeid(mType).name();
	}

private:
	EventID mType{};
	std::unordered_map<EventID, std::any> mData{};
};

#endif
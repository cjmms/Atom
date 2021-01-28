#ifndef TRANSFORMSYSTEM_HPP
#define TRANSFORMSYSTEM_HPP

#include "Pch.hpp"
#include "core/System.hpp"
#include "core/Event.hpp"
#include "core/Types.hpp"

class TransformSystem : public System {
public:
	void init() override;
	void update() override;
	void onEvent(Event& e) override;
};


#endif
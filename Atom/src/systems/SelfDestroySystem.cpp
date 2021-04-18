/*
* Copyright (C) 2021 DigiPen Institute of Technology.
* Reproduction or disclosure of this file or its contents without the
* prior written consent of DigiPen Institute of Technology is prohibited.
*
* @file		SelfDestroySystem.hpp
* @author	Gerald Lee
* @brief	Logic to destroy Bullets after a certain amount of time
* @date		2021-03-31
*/

#include "Pch.hpp"
#include "SelfDestroySystem.hpp"
#include "core/Types.hpp"
#include "core/AtomEngine.hpp"
#include "utils/Log.hpp"
#include "SelfDestroySystem.hpp"

extern AtomEngine ae;

void SelfDestroySystem::init()
{
}

void SelfDestroySystem::update()
{
	float frameTime = ae.dt;
	if (frameTime == 0)
		return;

	for (auto& entity : mEntities)
	{
		auto& selfDestroy = ae.getComponent<SelfDestroyComponent>(entity);
		selfDestroy.timer -= frameTime;
		if (selfDestroy.timer <= 0)
		{
			ae.EnqueueDestroyEntity(entity);
		}
	}
	
}

void SelfDestroySystem::onEvent(Event& e)
{
}

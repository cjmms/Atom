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
			ae.destroyEntity(entity);
		}
	}
	
}

void SelfDestroySystem::onEvent(Event& e)
{
}

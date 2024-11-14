#include "CustomDebugDrawService.h"

#include "CustomDebugDrawComponent.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;
using namespace KTEngine::Math;

void CustomDebugDrawService::Render()
{
	for (CustomDebugDrawComponent* debugDrawComponent : mCustomDebugDrawComponents)
	{
		debugDrawComponent->AddDebugDraw();
	}
}

void CustomDebugDrawService::Register(CustomDebugDrawComponent* debugDrawComponent)
{
	auto iter = std::find(mCustomDebugDrawComponents.begin(), mCustomDebugDrawComponents.end(), debugDrawComponent);
	if (iter == mCustomDebugDrawComponents.end())
	{
		mCustomDebugDrawComponents.push_back(debugDrawComponent);
	}
}

void CustomDebugDrawService::Unregister(CustomDebugDrawComponent* debugDrawComponent)
{
	auto iter = std::find(mCustomDebugDrawComponents.begin(), mCustomDebugDrawComponents.end(), debugDrawComponent);
	if (iter != mCustomDebugDrawComponents.end())
	{
		mCustomDebugDrawComponents.erase(iter);
	}
}
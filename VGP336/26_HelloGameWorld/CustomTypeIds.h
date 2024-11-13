#pragma once

#include <KTEngine/Inc/KTEngine.h>

enum class CustomCompoenntId
{
	CustomDebugDraw = static_cast<uint32_t>(KTEngine::ComponentId::Count)
};

enum class CustomServiceId
{
	CustomDebugDrawDisplay = static_cast<uint32_t>(KTEngine::ServiceId::Count)
};
#pragma once

#include "Component.h"

namespace KTEngine
{
	class UIComponent : public Component
	{
	public:
		virtual void Render() = 0;
	};
}
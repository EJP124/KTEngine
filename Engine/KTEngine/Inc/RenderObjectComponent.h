#pragma once


#include "Component.h"

namespace KTEngine
{
	class RenderObjectComponent : public Component
	{
	public:
		void Initialize() override;
		void Terminate() override;

		void Deserialize(const rapidjson::Value& value) override;

		virtual Graphics::ModelId GetModelId() const { return 0; }
		virtual const Graphics::Model& GetModel() const = 0;

		bool CanCastShadow() const { return mCastShadow; }
	private:
		bool mCastShadow = true;
	};
}
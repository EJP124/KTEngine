#pragma once

#include "MeshBuffer.h"
#include "Material.h"
#include "TextureManager.h"
#include "Transform.h"
#include "ModelManager.h"


namespace KTEngine::Graphics
{
	struct Model;

	struct RenderObject
	{
		void Terminate();

		Transform transform;
		MeshBuffer meshBuffer;

		Material material;

		TextureId diffuseMapId;
		TextureId normalMapId;
		TextureId specMapId;
		TextureId bumpMapId;

		ModelId modelId = 0;
		const Skeleton* skeleton = nullptr;
	};

	using RenderGroup = std::vector<RenderObject>;
	[[nodiscard]]RenderGroup CreateRenderGroup(ModelId& id);
	[[nodiscard]]RenderGroup CreateRenderGroup(const Model& model, ModelId id = 0);
	void CleanupRenderGroup(RenderGroup& renderGroup);

	void SetRenderGroupPosition(RenderGroup& renderGroup, const Math::Vector3& pos);

	template<class Effect>
	void DrawRenderGroup(Effect& effect, const RenderGroup& renderGroup)
	{
		for (const RenderObject& renderObject : renderGroup)
		{
			effect.Render(renderObject);
		}
	}
}
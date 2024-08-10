#include "Precompiled.h"
#include "ModelManager.h"

#include "ModelIO.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;

namespace
{
	std::unique_ptr<ModelManager> sModelManager;
}
void ModelManager::StaticInitialize()
{
	ASSERT(sModelManager == nullptr, "ModelManager: is already initialized");
	sModelManager = std::make_unique<ModelManager>();
}
void ModelManager::StaticTerminate()
{
	sModelManager.reset();
}
ModelManager* ModelManager::Get()
{
	ASSERT(sModelManager != nullptr, "ModelManager: is not initialized");
	return sModelManager.get();
}
ModelId ModelManager::GetModelId(const std::filesystem::path& filepath)
{

	return std::filesystem::hash_value(filepath);
}

ModelId ModelManager::LoadModelId(const std::filesystem::path& filepath)
{
	const ModelId modelId = GetModelId(filepath);
	auto [iter, success] = mInventory.insert({ modelId,nullptr });
	if (success)
	{
		auto& modelPtr = iter->second;
		modelPtr = std::make_unique<Model>();
		ModelIO::LoadModel(filepath, *modelPtr);
		ModelIO::LoadMaterial(filepath, *modelPtr);
		ModelIO::LoadSkeleton(filepath, *modelPtr);
		ModelIO::LoadAnimation(filepath, *modelPtr);
	}
	return modelId;
}

void ModelManager::AddAnimation(ModelId id, const std::filesystem::path& filepath)
{
	auto model = mInventory.find(id);
	if (model != mInventory.end())
	{
		ModelIO::LoadAnimation(filepath, *model->second);
	}
}

const Model* ModelManager::GetModel(ModelId id) const
{
	auto model = mInventory.find(id);
	if (model != mInventory.end())
	{
		return model->second.get();
	}
	return nullptr;
}
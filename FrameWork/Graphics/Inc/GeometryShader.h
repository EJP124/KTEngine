#pragma once

namespace KTEngine::Graphics
{
	class GeometryShader final
	{
	public:
		void Initialize(const std::filesystem::path& filePath, uint32_t format);
		void Terminate();
		void Bind();

	private:
		ID3D11GeometryShader* mGeometryShader = nullptr;
	};
}
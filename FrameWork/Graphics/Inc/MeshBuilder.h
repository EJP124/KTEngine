#pragma once
#include "MeshTypes.h"

namespace KTEngine::Graphics
{
	class MeshBuilder
	{
	public:
		// Pyramid
		static MeshPC CreatePyramidPC(float size);

		// Cube
		static MeshPC CreateCubePC(float size, const Color& color);
		static MeshPC CreateCubePC(float size);

		// Rect
		static MeshPC CreateRectPC(float width, float height, float depth);
		static Mesh CreateRect(float width, float height, float depth);
		// Plane
		static MeshPC CreatePlanePC(uint32_t numRows, uint32_t numCols, float spacing);
		static Mesh CreateGroundPlane(uint32_t numRows, uint32_t numCols, float spacing);
		static MeshPC CreateVerticalPlanePC(uint32_t numRows, uint32_t numCols, float spacing);
		static MeshPC CreateHorizontalPlanePC(uint32_t numRows, uint32_t numCols, float spacing);
		static MeshPX CreateVerticalPlanePX(uint32_t numRows, uint32_t numCols, float spacing);
		static MeshPX CreateHorizontalPlanePX(uint32_t numRows, uint32_t numCols, float spacing);
		static Mesh CreateHorizontalPlane(uint32_t numRows, uint32_t numCols, float spacing);

		// Cylinder
		static MeshPC CreateCylinderPC(uint32_t slices, uint32_t rings);

		// Sphere
		static MeshPC CreateSpherePC(uint32_t slices, uint32_t rings, float radius);
		static MeshPX CreateSpherePX(uint32_t slices, uint32_t rings, float radius);
		static Mesh CreateSphere(uint32_t slices, uint32_t rings, float radius);

		// SkySphere
		static MeshPX CreateSkySpherePX(uint32_t slices, uint32_t rings, float radius);

		// SkyBox
		static MeshPX CreateSkyBoxPX(float size);

		// Screen Quad
		static MeshPX CrearsScreenQuad();

		static Mesh CreateSpriteQuad(float width, float height);
			
		
	};
}
#include "Precompiled.h"
#include "MeshBuilder.h"

using namespace KTEngine;
using namespace KTEngine::Graphics;

namespace
{
	Color GetNextColor(int& index)
	{
		constexpr Color colorTable[] = {
			Colors::SeaGreen,
			Colors::Red,
			Colors::Aquamarine,
			Colors::PaleVioletRed,
			Colors::HotPink,
			Colors::Yellow,
			Colors::Orange
		};

		index = (index + 1) % std::size(colorTable);
		return colorTable[index];
	}

	void CreateCubeIndices(std::vector<uint32_t>& indices)
	{
		indices = {
			// front
			0, 1, 2,
			0, 2, 3,

			// right
			3, 2, 6,
			3, 6, 7,

			// back
			7, 6, 5,
			7, 5, 4,

			//left
			0, 5, 1,
			0, 4, 5,

			// top
			1, 5, 6,
			1, 6, 2,

			// bottom
			0, 3, 7,
			0, 7, 4
		};
	}

	void CreatePlaneIndices(std::vector<uint32_t>& indices, uint32_t numRows, uint32_t numCols)
	{
		for (uint32_t r = 0; r < numRows; ++r)
		{
			for (uint32_t c = 0; c < numCols; ++c)
			{
				uint32_t i = (r * (numCols + 1)) + c;

				// triangle 1
				indices.push_back(i);
				indices.push_back(i + numCols + 2);
				indices.push_back(i + 1);

				// triangle 2
				indices.push_back(i);
				indices.push_back(i + numCols + 1);
				indices.push_back(i + numCols + 2);
			}
		}
	}

	void CreateCapIndices(std::vector<uint32_t>& indices, uint32_t slices, uint32_t topIndex, uint32_t bottomIndex)
	{
		for (uint32_t s = 0; s < slices; ++s)
		{
			// bottom triangle
			indices.push_back(bottomIndex);
			indices.push_back(s);
			indices.push_back(s + 1);

			// top triangle
			uint32_t topRowIndex = topIndex - slices - 1 + s;
			indices.push_back(topIndex);
			indices.push_back(topRowIndex + 1);
			indices.push_back(topRowIndex);
		}
	}
}




MeshPC MeshBuilder::CreatePyramidPC(float size)
{
	MeshPC mesh;
	const float hs = size * 0.5f;

	int index = rand() % 100;
	// front
	mesh.vertices.push_back({ { -hs, -hs, -hs }, GetNextColor(index) });
	mesh.vertices.push_back({ { 0.0f,  hs, 0.0f }, GetNextColor(index) });
	mesh.vertices.push_back({ {  hs, -hs, -hs }, GetNextColor(index) });
	// back
	mesh.vertices.push_back({ { -hs, -hs, hs }, GetNextColor(index) });
	mesh.vertices.push_back({ {  hs, -hs, hs }, GetNextColor(index) });

	mesh.indices = {
		// front
		0, 1, 2,
		// right
		2, 1, 4,
		// back
		4, 1, 3,
		//left
		0, 3, 1,
		// bottom
		0, 2, 4,
		0, 4, 3
	};

	return mesh;
}

MeshPC MeshBuilder::CreateCubePC(float size, const Color& color)
{
	MeshPC mesh;
	const float hs = size * 0.5f;

	// front
	mesh.vertices.push_back({ { -hs, -hs, -hs }, color });
	mesh.vertices.push_back({ { -hs,  hs, -hs }, color });
	mesh.vertices.push_back({ {  hs,  hs, -hs }, color });
	mesh.vertices.push_back({ {  hs, -hs, -hs }, color });
	// back
	mesh.vertices.push_back({ { -hs, -hs, hs }, color });
	mesh.vertices.push_back({ { -hs,  hs, hs }, color });
	mesh.vertices.push_back({ {  hs,  hs, hs }, color });
	mesh.vertices.push_back({ {  hs, -hs, hs }, color });

	CreateCubeIndices(mesh.indices);

	return mesh;
}

MeshPC MeshBuilder::CreateCubePC(float size)
{
	MeshPC mesh;
	const float hs = size * 0.5f;

	int index = rand() % 100;
	// front
	mesh.vertices.push_back({ { -hs, -hs, -hs }, GetNextColor(index) });
	mesh.vertices.push_back({ { -hs,  hs, -hs }, GetNextColor(index) });
	mesh.vertices.push_back({ {  hs,  hs, -hs }, GetNextColor(index) });
	mesh.vertices.push_back({ {  hs, -hs, -hs }, GetNextColor(index) });
	// back
	mesh.vertices.push_back({ { -hs, -hs, hs }, GetNextColor(index) });
	mesh.vertices.push_back({ { -hs,  hs, hs }, GetNextColor(index) });
	mesh.vertices.push_back({ {  hs,  hs, hs }, GetNextColor(index) });
	mesh.vertices.push_back({ {  hs, -hs, hs }, GetNextColor(index) });

	CreateCubeIndices(mesh.indices);

	return mesh;
}

MeshPC MeshBuilder::CreateRectPC(float width, float height, float depth)
{
	MeshPC mesh;
	const float hw = width * 0.5f;
	const float hh = height * 0.5f;
	const float hd = depth * 0.5f;

	int index = rand() % 100;
	// front
	mesh.vertices.push_back({ { -hw, -hh, -hd }, GetNextColor(index) });
	mesh.vertices.push_back({ { -hw,  hh, -hd }, GetNextColor(index) });
	mesh.vertices.push_back({ {  hw,  hh, -hd }, GetNextColor(index) });
	mesh.vertices.push_back({ {  hw, -hh, -hd }, GetNextColor(index) });
	// back
	mesh.vertices.push_back({ { -hw, -hh, hd }, GetNextColor(index) });
	mesh.vertices.push_back({ { -hw,  hh, hd }, GetNextColor(index) });
	mesh.vertices.push_back({ {  hw,  hh, hd }, GetNextColor(index) });
	mesh.vertices.push_back({ {  hw, -hh, hd }, GetNextColor(index) });

	CreateCubeIndices(mesh.indices);

	return mesh;
}

Mesh MeshBuilder::CreateRect(float width, float height, float depth)
{
	Mesh mesh;
	float halfWidth = width * 0.5f;
	float halfHeight = height * 0.5f;
	float halfDepth = depth * 0.5f;

	// Define 8 vertices (position, normal, tangent, UV, bone data)
	mesh.vertices = {
		// Front face
		{{-halfWidth, -halfHeight, -halfDepth}, {0, 0, -1}, {1, 0, 0}, {0, 1}, {0, 0, 0, 0}, {1, 0, 0, 0}},
		{{ halfWidth, -halfHeight, -halfDepth}, {0, 0, -1}, {1, 0, 0}, {1, 1}, {0, 0, 0, 0}, {1, 0, 0, 0}},
		{{ halfWidth,  halfHeight, -halfDepth}, {0, 0, -1}, {1, 0, 0}, {1, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}},
		{{-halfWidth,  halfHeight, -halfDepth}, {0, 0, -1}, {1, 0, 0}, {0, 0}, {0, 0, 0, 0}, {1, 0, 0, 0}},

		// ... (Repeat similar for other 5 faces)
	};

	// Define indices for the 6 faces (12 triangles)
	mesh.indices = {
		// Front face
		0, 1, 2, 2, 3, 0,
		// Back face
		4, 5, 6, 6, 7, 4,
		// Left face
		8, 9, 10, 10, 11, 8,
		// Right face
		12, 13, 14, 14, 15, 12,
		// Top face
		16, 17, 18, 18, 19, 16,
		// Bottom face
		20, 21, 22, 22, 23, 20
	};

	return mesh;
}

MeshPC MeshBuilder::CreatePlanePC(uint32_t numRows, uint32_t numCols, float spacing)
{
	MeshPC mesh;

	int index = rand() % 100;

	const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;

	float x = -hpw;
	float y = -hph;

	for (uint32_t r = 0; r <= numRows; ++r)
	{
		for (uint32_t c = 0; c <= numCols; ++c)
		{
			mesh.vertices.push_back({ {x, y, 0.0f}, GetNextColor(index) });
			x += spacing;
		}

		x = -hpw;
		y += spacing;
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

Mesh MeshBuilder::CreateGroundPlane(uint32_t numRows, uint32_t numCols, float spacing)
{
	Mesh mesh;

	const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;
	const float uInc = 1.0f / static_cast<float>(numCols);
	const float vInc = 1.0f / static_cast<float>(numRows);

	float x = -hpw;
	float z = -hph;
	float u = 0.0f;
	float v = 1.0f;

	for (uint32_t r = 0; r <= numRows; ++r)
	{
		for (uint32_t c = 0; c <= numCols; ++c)
		{
			mesh.vertices.push_back({
				{x, 0.0f, z},
				{0.0f,1.0f,0.0f},
				{0.0f,0.0f,1.0f},
				{u,v} });
			x += spacing;
			u += uInc;
		}
		x = -hpw;
		z += spacing;
		u = 0.0f;
		v -= vInc;
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

MeshPC MeshBuilder::CreateVerticalPlanePC(uint32_t numRows, uint32_t numCols, float spacing)
{
	srand(time(nullptr));
	int index = rand() % 100;

	MeshPC mesh;

	const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;

	float x = -hpw;
	float y = -hph;

	for (uint32_t r = 0; r <= numRows; ++r)
	{
		for (uint32_t c = 0; c <= numCols; ++c)
		{
			mesh.vertices.push_back({ {x, y, 0.0f}, GetNextColor(index) });
			x += spacing;
		}

		x = -hpw;
		y += spacing;
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

MeshPC MeshBuilder::CreateHorizontalPlanePC(uint32_t numRows, uint32_t numCols, float spacing)
{
	srand(time(nullptr));
	int index = rand() % 100;

	MeshPC mesh;

	const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;

	float x = -hpw;
	float z = -hph;

	for (uint32_t r = 0; r <= numRows; ++r)
	{
		for (uint32_t c = 0; c <= numCols; ++c)
		{
			mesh.vertices.push_back({ {x, 0.0f, z}, GetNextColor(index) });
			x += spacing;
		}

		x = -hpw;
		z += spacing;
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

MeshPX MeshBuilder::CreateVerticalPlanePX(uint32_t numRows, uint32_t numCols, float spacing)
{
	MeshPX mesh;

	const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;
	const float uInc = 1.0f / static_cast<float>(numCols);
	const float vInc = 1.0f / static_cast<float>(numRows);

	float x = -hpw;
	float y = -hph;
	float u = 0.0f;
	float v = 1.0f;

	for (uint32_t r = 0; r <= numRows; ++r)
	{
		for (uint32_t c = 0; c <= numCols; ++c)
		{
			mesh.vertices.push_back({ {x, y, 0.0f}, {u, v} });
			x += spacing;
			u += uInc;
		}

		x = -hpw;
		y += spacing;
		u = 0.0f;
		v += (-vInc);
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

MeshPX MeshBuilder::CreateHorizontalPlanePX(uint32_t numRows, uint32_t numCols, float spacing)
{
	MeshPX mesh;

	const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;
	const float uInc = 1.0f / static_cast<float>(numCols);
	const float vInc = 1.0f / static_cast<float>(numRows);

	float x = -hpw;
	float z = -hph;
	float u = 0.0f;
	float v = 1.0f;

	for (uint32_t r = 0; r <= numRows; ++r)
	{
		for (uint32_t c = 0; c <= numCols; ++c)
		{
			mesh.vertices.push_back({ {x, 0.0f, z}, {u, v} });
			x += spacing;
			u += uInc;
		}

		x = -hpw;
		z += spacing;
		u = 0.0f;
		v += (-vInc);
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}
Mesh MeshBuilder::CreateHorizontalPlane(uint32_t numRows, uint32_t numCols, float spacing)
{
	Mesh mesh;

	const Math::Vector3 up = Math::Vector3::YAxis;
	const Math::Vector3 right = Math::Vector3::XAxis;
	const float hpw = static_cast<float>(numCols) * spacing * 0.5f;
	const float hph = static_cast<float>(numRows) * spacing * 0.5f;
	const float uInc = 1.0f / static_cast<float>(numCols);
	const float vInc = 1.0f / static_cast<float>(numRows);

	float x = -hpw;
	float z = -hph;
	float u = 0.0f;
	float v = 1.0f;

	for (uint32_t r = 0; r <= numRows; ++r)
	{
		for (uint32_t c = 0; c <= numCols; ++c)
		{
			mesh.vertices.push_back({ {x, 0.0f, z}, up, right, {u, v} });
			x += spacing;
			u += uInc;
		}

		x = -hpw;
		z += spacing;
		u = 0.0f;
		v += (-vInc);
	}

	CreatePlaneIndices(mesh.indices, numRows, numCols);

	return mesh;
}

MeshPC MeshBuilder::CreateCylinderPC(uint32_t slices, uint32_t rings)
{
	MeshPC mesh;

	int index = rand() % 100;
	const float hh = static_cast<float>(rings) * 0.5f;

	for (uint32_t r = 0; r <= rings; ++r)
	{
		float rPos = static_cast<float>(r);
		for (uint32_t s = 0; s <= slices; ++s)
		{
			float sPos = static_cast<float>(s);
			float rotation = (sPos / static_cast<float>(slices)) * Math::Constants::TwoPi;

			mesh.vertices.push_back({ {
					cos(rotation),
					rPos - hh,
					sin(rotation)},
					GetNextColor(index) });
		}
	}

	mesh.vertices.push_back({ { 0.0f, hh, 0.0f}, GetNextColor(index) });
	mesh.vertices.push_back({ { 0.0f, -hh, 0.0f}, GetNextColor(index) });

	CreatePlaneIndices(mesh.indices, rings, slices);
	CreateCapIndices(mesh.indices, slices, mesh.vertices.size() - 2, mesh.vertices.size() - 1);

	return mesh;
}

MeshPC MeshBuilder::CreateSpherePC(uint32_t slices, uint32_t rings, float radius)
{
	MeshPC mesh;

	int index = rand() % 100;

	float vertRotation = (Math::Constants::Pi / static_cast<float>(rings - 1));
	float horzRotation = (Math::Constants::TwoPi / static_cast<float>(slices));

	for (uint32_t r = 0; r <= rings; ++r)
	{
		float rPos = static_cast<float>(r);
		float phi = rPos * vertRotation;
		for (uint32_t s = 0; s <= slices; ++s)
		{
			float sPos = static_cast<float>(s);
			float rotation = sPos * horzRotation;

			mesh.vertices.push_back({ {
					radius * sin(rotation) * sin(phi),
					radius * cos(phi),
					radius * cos(rotation) * sin(phi)},
					GetNextColor(index) });
		}
	}

	CreatePlaneIndices(mesh.indices, rings, slices);

	return mesh;
}


MeshPX MeshBuilder::CreateSpherePX(uint32_t slices, uint32_t rings, float radius)
{
	MeshPX mesh;

	float vertRotation = (Math::Constants::Pi / static_cast<float>(rings));
	float horzRotation = (Math::Constants::TwoPi / static_cast<float>(slices));
	float uStep = 1.0f / static_cast<float>(slices);
	float vStep = 1.0f / static_cast<float>(rings);

	for (uint32_t r = 0; r <= rings; ++r)
	{
		float rPos = static_cast<float>(r);
		float phi = rPos * vertRotation;
		for (uint32_t s = 0; s <= slices; ++s)
		{
			float sPos = static_cast<float>(s);
			float rotation = sPos * horzRotation;

			float u = 1.0f - (uStep * sPos);
			float v = vStep * rPos;
			mesh.vertices.push_back({ {
					radius * sin(rotation) * sin(phi),
					radius * cos(phi),
					radius * cos(rotation) * sin(phi)},
					{u, v } });
		}
	}

	CreatePlaneIndices(mesh.indices, rings, slices);

	return mesh;
}

MeshPX MeshBuilder::CreateSkySpherePX(uint32_t slices, uint32_t rings, float radius)
{
	MeshPX mesh;

	float vertRotation = (Math::Constants::Pi / static_cast<float>(rings - 1));
	float horzRotation = (Math::Constants::TwoPi / static_cast<float>(slices));
	float uInc = 1.0f / static_cast<float>(slices);
	float vInc = 1.0f / static_cast<float>(rings);

	for (uint32_t r = 0; r <= rings; ++r)
	{
		float rPos = static_cast<float>(r);
		float phi = rPos * vertRotation;
		for (uint32_t s = 0; s <= slices; ++s)
		{
			float slicePos = static_cast<float>(s);
			float rotation = slicePos * horzRotation;

			float u = 1.0f - (uInc * slicePos);
			float v = vInc * rPos;
			mesh.vertices.push_back({ {
					radius * cos(rotation) * sin(phi),
					radius * cos(phi),
					radius * sin(rotation) * sin(phi)},
					{u, v } });
		}
	}

	CreatePlaneIndices(mesh.indices, rings, slices);

	return mesh;
}
Mesh MeshBuilder::CreateSphere(uint32_t slices, uint32_t rings, float radius)
{
	Mesh mesh;

	float vertRotation = (Math::Constants::Pi / static_cast<float>(rings));
	float horzRotation = (Math::Constants::TwoPi / static_cast<float>(slices));
	float uInc = 1.0f / static_cast<float>(slices);
	float vInc = 1.0f / static_cast<float>(rings);

	for (uint32_t r = 0; r <= rings; ++r)
	{
		float rPos = static_cast<float>(r);
		float phi = rPos * vertRotation;
		for (uint32_t s = 0; s <= slices; ++s)
		{
			float sPos = static_cast<float>(s);
			float rotation = sPos * horzRotation;

			float u = 1.0f - (uInc * sPos);
			float v = vInc * rPos;

			float x = radius * sin(rotation) * sin(phi);
			float y = radius * cos(phi);
			float z = radius * cos(rotation) * sin(phi);
			Math::Vector3 position = { x,y,z };
			Math::Vector3 normal = Math::Normalize(position);
			Math::Vector3 tangent = Math::Normalize({ -z, 0.0f, x });
			Math::Vector2 uvCoord = { u, v };

			mesh.vertices.push_back({
				position,
				normal,
				tangent,
				uvCoord
				});
		}
	}

	CreatePlaneIndices(mesh.indices, rings, slices);

	return mesh;
}

MeshPX MeshBuilder::CreateSkyBoxPX(float size)
{
	MeshPX mesh;
	const float hs = size * 0.5f;
	const float q = 0.25f;
	const float q2 = 2.0f * q;
	const float q3 = 3.0f * q;
	const float t = 0.333333334f;
	const float t2 = 2.0f * t;

	//Left
	mesh.vertices.push_back({ { hs,-hs, -hs}, {0.0f, t2} });
	mesh.vertices.push_back({ { hs, hs, -hs}, {0.0f, t} });
	mesh.vertices.push_back({ { hs, hs, hs}, {q, t} });
	mesh.vertices.push_back({ { hs,-hs, hs}, {q, t2} });

	//Top
	mesh.vertices.push_back({ { hs, hs, hs},{ q , t} });
	mesh.vertices.push_back({ { hs, hs,-hs},{ q , 0.0f } });
	mesh.vertices.push_back({ {-hs, hs,-hs},{ q2 , 0.0f } });
	mesh.vertices.push_back({ {-hs, hs, hs},{ q2 , t } });

	//Front					    
	mesh.vertices.push_back({ {-hs,-hs, hs},{q2,t2} });
	mesh.vertices.push_back({ {-hs, hs, hs},{q2,  t} });
	mesh.vertices.push_back({ { hs, hs, hs},{q,  t} });
	mesh.vertices.push_back({ { hs,-hs, hs},{q,t2} });

	//Bottom				    
	mesh.vertices.push_back({ { hs, -hs, hs}, {q, t2} });
	mesh.vertices.push_back({ { hs, -hs, -hs}, {q, 1.0f} });
	mesh.vertices.push_back({ { -hs, -hs, -hs}, {q2, 1.0f} });
	mesh.vertices.push_back({ { -hs, -hs, hs}, {q2, t2} });

	//Right					    
	mesh.vertices.push_back({ { -hs, -hs, -hs }, { q3, t2} });
	mesh.vertices.push_back({ { -hs, hs, -hs }, { q3, t} });
	mesh.vertices.push_back({ { -hs, hs, hs }, { q2, t} });
	mesh.vertices.push_back({ { -hs, -hs, hs }, { q2, t2} });

	//Back
	mesh.vertices.push_back({ {-hs, -hs, -hs}, {q3, t2} });
	mesh.vertices.push_back({ {-hs, hs, -hs}, {q3, t} });
	mesh.vertices.push_back({ {hs, hs, -hs}, {1.0f, t} });
	mesh.vertices.push_back({ {hs, -hs, -hs}, {1.0f, t2} });

	mesh.indices = {
		//Left
		2,1,0,
		2,0,3,
		//Top
		6,5,4,
		6,4,7,
		//Front
		8,9,10,
		11,8,10,
		//Bottom
		12,13,14,
		15,12,14,
		//Right
		16,17,18,
		19,16,18,
		//Back
		22, 21,20,
		22,20,23
	};
	return mesh;
}


MeshPX MeshBuilder::CrearsScreenQuad()
{
	MeshPX mesh;
	mesh.vertices.push_back({ { -1.0f, 1.0f, 0.0f },{ 0.0f, 0.0f } });
	mesh.vertices.push_back({ { 1.0f, 1.0f, 0.0f },{ 1.0f, 0.0f } });
	mesh.vertices.push_back({ { 1.0f, -1.0f, 0.0f},{ 1.0f, 1.0f } });
	mesh.vertices.push_back({ { -1.0f, -1.0f, 0.0f },{ 0.0f, 1.0f } });
	mesh.indices = { 0,1,3,1,2,3 };

	return mesh;
}

Mesh MeshBuilder::CreateSpriteQuad(float width, float height)
{
	Mesh mesh;

	const float hw = width * 0.5f;
	const float hh = height * 0.5f;

	mesh.vertices.push_back({ {-hw, -hh, 0.0f}, -Math::Vector3::ZAxis, Math::Vector3::XAxis, {0.0f, 1.0f} });
	mesh.vertices.push_back({ {-hw,  hh, 0.0f}, -Math::Vector3::ZAxis, Math::Vector3::XAxis, {0.0f, 0.0f} });
	mesh.vertices.push_back({ { hw,  hh, 0.0f}, -Math::Vector3::ZAxis, Math::Vector3::XAxis, {1.0f, 0.0f} });
	mesh.vertices.push_back({ { hw, -hh, 0.0f}, -Math::Vector3::ZAxis, Math::Vector3::XAxis, {1.0f, 1.0f} });

	mesh.indices = {
		0, 1, 2,
		0, 2, 3
	};

	return mesh;
}


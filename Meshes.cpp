#include "Meshes.h"
#include "Mesh.h"
#include "Types.h"
#include "VertexAttributeSets.h"

using namespace Graphics;

Mesh* Meshes::TRIANGLE = nullptr;
Mesh* Meshes::QUAD = nullptr;

void Meshes::initialize()
{
	// TRIANGLE
	{
		f32 vertices[] = {
			-0.5, -0.5, 0.0, 1.0, 0.0, 0.0,
			0.5, -0.5, 0.0, 0.0, 1.0, 0.0,
			0.0, 0.5, 0.0, 0.0, 0.0, 1.0
		};
		TRIANGLE = new Mesh(vertices, sizeof(vertices), *VertexAttributeSets::POSITION_COLOR);
	}

	// QUAD
	{
		f32 vertices[] = {
			0.5f, 0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f, 0.5f, 0.0f
		};
		u32 indices[] = {
			0, 1, 3,
			1, 2, 3
		};
		QUAD = new Mesh(vertices, sizeof(vertices), indices, 6, *VertexAttributeSets::POSITION);
	}
}

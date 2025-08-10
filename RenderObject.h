#pragma once
#include "Types.h"
#include "Mesh.h"

namespace Graphics
{
	struct RenderObject
	{
		RenderObject(Mesh* mesh)
			: mesh(mesh)
		{}

		RenderObject(mat4 transform, Mesh* mesh)
			: transform(transform), mesh(mesh)
		{}

		RenderObject()
		{}

		mat4 transform = mat4(1.0f);
		Mesh* mesh = nullptr;
	};
}
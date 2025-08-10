#pragma once
#include "Types.h"

namespace Graphics
{
	class VertexAttributeSet;

	class VertexArrayObject
	{
		friend class Mesh;
		friend class InstancedMesh;

	public:
		VertexArrayObject();
		~VertexArrayObject();
		u32 id() const { return id_; }
	
	private:
		u32 id_;

		void bind();
	};
}
